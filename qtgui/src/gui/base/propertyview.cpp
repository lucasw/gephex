#include "propertyview.h"

#include <qtable.h>

#include "ipropertydescription.h"
#include "iwidgetconstructor.h"

namespace gui
{

  PropertyView::PropertyView(QWidget* parent)
    : QWidget(parent,"Property View",0), table(0)
  {
  }

  namespace
  {
    QTable* buildNewTable(QWidget* parent)
    {
      int numberOfRows = 24;
      QTable* table = new QTable(numberOfRows,3,parent,"Property Table");

      QHeader* header = table->horizontalHeader();
	
      header->setLabel(0,"Eigenschaft", 80);
      header->setLabel(1,"Wert", 80);
      header->setLabel(2,"verstecken", 25);
	
      table->setLeftMargin( 0 );
      table->verticalHeader()->hide();
      table->setShowGrid(false);

      // resize colum if content is larger then columsize
      /*      for (int i = 0; i < 3; ++i)
	      table->setColumnStretchable(i,true);*/

      for (int i = 0; i < numberOfRows; ++i)
	{
	  table->setRowHeight(i,40);
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
      }
  }

  void PropertyView::displayProperties(const IPropertyDescription& desc)
  {	 

    this->deleteTable();

    table = buildNewTable(this);
		
    std::list<PropertyEntry> entries = desc.getEntries();

    int cellIndex = 0;
    for (std::list<PropertyEntry>::const_iterator it = entries.begin(); 
	 it != entries.end(); ++it)
      {
	const PropertyEntry& current = *it;
		
	table->setItem(cellIndex,0,new QTableItem( table, QTableItem::Never,
						   current.getName().c_str()));

	const std::list<const IWidgetConstructor*>& wCtors = current.getWidgetCtors();
	int rowIndex = 1;
	for (std::list<const IWidgetConstructor*>::const_iterator it2 = wCtors.begin();
	     it2 != wCtors.end(); ++it2)
	  {
	    const IWidgetConstructor* ctor = *it2;
	    QWidget* widget = ctor->constructWidget(table);
	    table->setCellWidget(cellIndex,rowIndex,widget);
	    
	    widgetCtors.push_back(std::pair<const IWidgetConstructor*,
				  QWidget*>(ctor,widget));

	    ++rowIndex;
	  }

	++cellIndex;
      }

  }

} // end of namespace
