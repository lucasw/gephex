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

#include "propertyview.h"

#include <QtGui/QLayout>
#include <QtGui/QTableWidget>

#include "ipropertydescription.h"
#include "iwidgetconstructor.h"

namespace gui
{

  static const int NUM_ROWS = 32;

  PropertyView::PropertyView(QWidget* parent)
    : QWidget(parent), table(0)
  {
    m_layout = new QHBoxLayout(this);
  }

  PropertyView::~PropertyView()
  {
    deleteTable();
  }

  void PropertyView::deleteTable()
  {
    if (table != 0)
      {
	for (std::list<std::pair<const IWidgetConstructor*,
	       QWidget*> >::const_iterator it = widgetCtors.begin(); 
	     it != widgetCtors.end(); ++it)
	  {
	    const IWidgetConstructor* ctor = it->first;
	    QWidget* w = it->second;
	    ctor->destroyWidget(w);
	  }

	widgetCtors.clear();
	delete table;
	table = 0;
      }
  }

  void PropertyView::displayProperties(const IPropertyDescription& desc)
  {	 
    deleteTable();

    std::list<PropertyEntry> entries = desc.getEntries();

    table = new QTableWidget(entries.size(), 2, this);
	      
    QStringList headerLabels;
    headerLabels.append("Value");
    headerLabels.append("Hide");

    table->setHorizontalHeaderLabels(headerLabels);

    table->setShowGrid(false);

    int rowIndex = 0;
    for (std::list<PropertyEntry>::const_iterator it = entries.begin(); 
	 it != entries.end(); ++it, ++rowIndex)
      {
	const PropertyEntry& current = *it;
		
	table->setVerticalHeaderItem(rowIndex,
				     new QTableWidgetItem(current.getName().c_str()));

	const std::list<const IWidgetConstructor*>& wCtors = current.getWidgetCtors();
	int colIndex = 0;
	for (std::list<const IWidgetConstructor*>::const_iterator it2 = wCtors.begin();
	     it2 != wCtors.end(); ++it2, ++colIndex)
	  {
	    const IWidgetConstructor* ctor = *it2;
	    QWidget* widget = ctor->constructWidget(table);

            if (table->rowHeight(rowIndex) < widget->height())
	      table->setRowHeight(rowIndex, widget->height());

	    table->setCellWidget(rowIndex,colIndex,widget);
	    
	    widgetCtors.push_back(std::make_pair(ctor,widget));
	  }
      }

    m_layout->addWidget(table);
    
    table->show();
  }

  void PropertyView::undisplayProperties()
  {	    
    this->deleteTable();
  }

} // end of namespace
