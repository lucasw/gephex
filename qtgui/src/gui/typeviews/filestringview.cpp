/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#include "filestringview.h"

#include <sstream>
#include <iostream> //debug only
#include <algorithm>
#include <list>
#include <cassert>
#include <cctype> //tolower

#include <QtGui/qlayout.h>
#include <QtGui/QPushButton>
#include <QtGui/qfiledialog.h>
#include <QtGui/qmessagebox.h>

#include "utils/structreader.h"
#include "utils/stringtokenizer.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#define PATH_IS_CASE_INSENSITIVE 1
#endif

#if !defined(COMP_VC)
using std::tolower;
#endif

namespace gui
{

  template <class InputIterator1, class InputIterator2,
	    class T, class BinaryFunction1, class BinaryFunction2>
  T combine_reduce(InputIterator1 first1, InputIterator1 last1,
		   InputIterator2 first2, InputIterator2 last2,
		   T init,
		   BinaryFunction1 binary_op_r,
		   BinaryFunction2 binary_op_c)
  {
    InputIterator1 it1 = first1;
    InputIterator2 it2 = first2;

    T s = init;
    while (it1 != last1 && it2 != last2)
      {
	s = binary_op_r(s, binary_op_c(*it1, *it2));
	++it1;
	++it2;
      }
    return s;
  }

  static bool binary_and(bool b1, bool b2)
  {
    return b1 && b2;
  }
  
  // case sensitive compare function
  static bool char_equals(char t1, char t2)
  {
    return t1 == t2;
  }

  // TODO: workaround for mingw 3.4.2
  static char my_tolower(char c)
  {
    return tolower(c);
  }

  /**
   * Returns true iff s begins with prefix.
   */
  bool is_prefix(std::string prefix, std::string s)
  {
#if defined(PATH_IS_CASE_INSENSITIVE)
	  std::transform(prefix.begin(), prefix.end(),
			 prefix.begin(), my_tolower);

	  std::transform(s.begin(), s.end(),
			 s.begin(), my_tolower);
#endif

    return prefix.length() <= s.length() &&
      combine_reduce(s.begin(), s.end(),
                     prefix.begin(), prefix.end(),
                     true,
                     binary_and,
                     char_equals);
    /*
    if (prefix.length() > s.length())
      return false;

    std::string::const_iterator it_s = s.begin();
    for (std::string::const_iterator it_p = prefix.begin();
	 it_p != prefix.end(); ++it_p, ++it_s)
      {
	if (*it_s != *it_p)
	  return false;
      }

      return true;*/
  }

  /**
   * Checks wether path begins with one of the dirs.
   *
   * If so, it removes this common prefix from path and returns
   * a relative path. If not, path is returned unchanged.
   *
   * The first matching dir in dirs is uses.
   */
  static std::string path_to_rel(const std::string& path,
				 const std::list<std::string>& dirs)
  {
    
    std::list<std::string>::const_iterator 
      it = std::find_if(dirs.begin(), dirs.end(), 
			std::bind2nd(std::ptr_fun(is_prefix), path));

    if (it == dirs.end())
      {
	return path;
      }
    else
      {
	std::string prefix = *it;
	assert(path.length() >= prefix.length());

	std::string rel_path = path.substr(prefix.length());
        // TODO: moc from qt2.3 chokes on this code
        // find another way to remove (back)slash
        /*	if (is_prefix("/", rel_path) || is_prefix("\\", rel_path))
	  {
	    rel_path = rel_path.substr(1);
            }*/
	return rel_path;
      }
  }

  class FileStringView: public gui::TypeView
  {
    Q_OBJECT
			
  public:
    FileStringView(QWidget* parent,
		   const ParamMap& params,
		   const std::string& media_path)
      : TypeView(parent, params), first_select(true)
    {
      utils::StructReader sr(params);
    
      std::string fullMask = "";
      
      for (int i = 1; ; ++i)
	{
	  std::ostringstream os;
	  os << "file_mask" << i;
	    
	  std::string fileMask = sr.getStringValue(os.str(), "_");
	  std::string fileMaskName = sr.getStringValue(os.str() + "_name",
						       "_");

	  if (fileMask == "_")
	    break;

	  m_fullMask += fileMaskName + " ( " + fileMask + " );;";
	}

      // media_path is a semikolon separated list of directory-names
      utils::StringTokenizer st(media_path);
      std::string token;
      while ((token = st.next(";")) != "")
	{
	  //TODO: some checks on token?
	  m_media_dirs.push_back(token);
	}
      if (m_media_dirs.empty())
	{
	  throw std::runtime_error("media_path is empty");
	}

      this->setMinimumSize(100, 24);
      m_select = new QPushButton(this);

      m_layout->addWidget(m_select);

      m_select->show();

      connect(m_select, SIGNAL(clicked()), this, SLOT(selectFile()));
    }

    virtual ~FileStringView() {}
		
    virtual void valueChange(const utils::Buffer& newValue)
    {
      int len = newValue.getLen();
      const char* dumm;

      if (len <= 0)
        {
          dumm = "";
          len = 1;
        }
      else
        {
          dumm = reinterpret_cast<const char*>(newValue.getPtr());
        }

      if (dumm[len-1] != 0)
        {
          std::cout << "ignoring string with missing termination\n";
          return;
        }

      m_select->setText(QString(dumm));
      setToolTip(QString(dumm));
    }

private slots:
    void userSelectedFile(const QString& name_)
    {
    }

    void selectFile()
    {
      std::string path = "";
      if (first_select)
        {
          path = m_media_dirs.back();
          first_select = false;
        }
      QStringList files = QFileDialog::getOpenFileNames (this,
							 "choose files",
							 path.c_str(),
							 m_fullMask.c_str());

      std::string name("");
      for (QStringList::Iterator it = files.begin(); it != files.end(); ++it)
	{
          std::string fname = (*it).toUtf8().constData();
          if (it != files.begin())
            name += ",";

          name += path_to_rel(fname, m_media_dirs);
	}
      
      if (name.length() != 0)
	{
	  utils::Buffer
	    b(reinterpret_cast<const unsigned char*>(name.c_str()),
	      name.length()+1);
	  
	  emit valueChanged(b);
	}
    }

  private:
    QPushButton* m_select;
    std::string m_fullMask;

    typedef std::list<std::string> DirList;
    DirList m_media_dirs;

    bool first_select;
  };
	
  // constructor

  FileStringViewConstructor::FileStringViewConstructor(const std::string& media_path)
    : TypeViewConstructor("file dialog", "file_selector"),
      m_media_path(media_path)
  {
  }

  TypeView* FileStringViewConstructor::construct(QWidget* parent,
						 const ParamMap& params) const
  {
    return new FileStringView(parent, params, m_media_path);
  }

}

#include "filestringview_moc_cpp.cpp"
