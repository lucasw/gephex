#ifndef INCLUDED_TYPE_VIEW_FACTORY_H
#define INCLUDED_TYPE_VIEW_FACTORY_H

#include <string>
#include <list>
#include <map>

namespace gui
{
  class TypeView;
  class TypeViewConstructor;

  class TypeViewInfo
  {
  public:
    explicit TypeViewInfo(const std::string& name,
			  const std::string& id)
      : m_name(name) , m_id(id) {}

    std::string getName() const { return m_name; }
    std::string getID() const { return m_id; }

  private:
    std::string m_name;
    std::string m_id;
  };

  /**
   * Diese Klasse erzeugt die TypeViews
   */
  class TypeViewFactory
  {
  public:
    typedef std::map<std::string, std::string> ParamMap;
    typedef std::list<TypeViewInfo> TypeViewInfoList;

    TypeViewFactory(const std::string& media_path);
    ~TypeViewFactory();

    /**
     * Ein neues Propertywidget mit einem bestimmten Typ erzeugen.
     */
    TypeViewConstructor* getConstructor(const std::string& viewID) const;

    /**
     * Liste der möglichen Properties für einen Typ zurückgeben.
     */
    std::list<TypeViewInfo>
      getCompatibleViews(const std::string& typeID) const;

    /**
     * Register a Constructor for a special TypeView
     */
    void registerTypeViewConstructor(const std::string& typeID,
				     TypeViewConstructor*);


  private:
    typedef std::map<std::string, TypeViewInfoList> TypeToInfoMap;
    typedef std::map<std::string, TypeViewConstructor*> ViewToConstructorMap;
    TypeToInfoMap m_infoMap;
    ViewToConstructorMap m_constructorMap;
  };

} // end of namespace gui
#endif
