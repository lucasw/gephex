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

#include <qlayout.h>
#include <qtable.h>
//#include <qscrollview.h>

#include "ipropertydescription.h"
#include "iwidgetconstructor.h"

namespace gui
{

  static const int NUM_ROWS = 32;

  PropertyView::PropertyView(QWidget* parent)
    : QWidget(parent,"Property View",0), table(0)
  {
	  m_layout = new QHBoxLayout(this);
  }

  PropertyView::~PropertyView()
  {
	  deleteTable();
  }

  namespace
  {
    QTable* buildNewTable(QWidget* parent)
    {
      int numberOfRows = NUM_ROWS;

	  //QHBoxLayout* l = new QHBoxLayout(parent);
      //QScrollView* scroller = new QScrollView(parent);
	  //	  l->addWidget(scroller);
      
      QTable* table = new QTable(numberOfRows, 3,
                                 parent,
                                 "Property Table");
	  
      QHeader* header = table->horizontalHeader();
	
      header->setLabel(0,"Property", 85);
      header->setLabel(1,"Value", 115);
      header->setLabel(2,"hide", 30);
	
      table->setLeftMargin( 0 );
      table->verticalHeader()->hide();
      table->setShowGrid(false);

      // resize colum if content is larger then columsize
      /*      for (int i = 0; i < 3; ++i)
	      table->setColumnStretchable(i,true);*/

      for (int i = 0; i < numberOfRows; ++i)
	{
	  table->setRowHeight(i,10);
          //	  table->setRowStretchable(i, true);
	}
      table->show();
      
      return table;
      }
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

		/* for (int i = 0; i < table->numRows(); ++i)
	  {
	    for (int j = 0; j < table->numCols(); ++j)
	      {
		if (table->cellWidget(i,j) != 0)
		  table->clearCellWidget(i,j);
	      }
	  }*/

	delete table;
	widgetCtors.clear();
	table = 0;
      }
  }

  void PropertyView::displayProperties(const IPropertyDescription& desc)
  {	 

    this->deleteTable();

    table = buildNewTable(this);
	m_layout->addWidget(table);
	m_layout->activate();
		
    std::list<PropertyEntry> entries = desc.getEntries();

    int rowIndex = 0;
    for (std::list<PropertyEntry>::const_iterator it = entries.begin(); 
	 it != entries.end(); ++it)
      {
	const PropertyEntry& current = *it;
		
	table->setItem(rowIndex,0,new QTableItem( table, QTableItem::Never,
						   current.getName().c_str()));

	const std::list<const IWidgetConstructor*>& wCtors = current.getWidgetCtors();
	int colIndex = 1;
	for (std::list<const IWidgetConstructor*>::const_iterator it2 = wCtors.begin();
	     it2 != wCtors.end(); ++it2)
	  {
	    const IWidgetConstructor* ctor = *it2;
	    QWidget* widget = ctor->constructWidget(table);

            if (table->rowHeight(rowIndex) < widget->height())
              table->setRowHeight(rowIndex, widget->height());

	    table->setCellWidget(rowIndex,colIndex,widget);
	    
	    widgetCtors.push_back(std::pair<const IWidgetConstructor*,
				  QWidget*>(ctor,widget));

	    ++colIndex;
	  }

	++rowIndex;
      }

  }

  void PropertyView::undisplayProperties()
  {	    
    this->deleteTable();
  }

} // end of namespace
