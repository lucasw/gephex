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

#ifndef __INCLUDED_CONTROL_VALUE_DISPATCHER_H__
#define __INCLUDED_CONTROL_VALUE_DISPATCHER_H__

#include <string>
#include <map>
#include <list>

#include "interfaces/icontrolvaluereceiver.h"

#include "point.h"
#include "utils/buffer.h"

class IModelControlReceiver;

namespace gui
{

  // Diese Klasse erhält die aktuellen Werte aller Inputs
  // von der engine und verteilt sie an registrierte
  // Kunden. Dieser Service ist natürlich nicht kostenlos,
  // in der Preisgestaltung ist die Klasse aber sehr flexibel.
  // So sind z.B. monatliche, quartiäre oder jährliche Zahlungen
  // möglich. Ist ein Kunde erst einmal registriert, erhält
  // er die Daten genau eines Inputs zugesandt. Es können sich
  // auch mehrere Kunden für einen Input registrieren. Der
  // Preis verdoppelt sich dann jedoch.

class ControlValueDispatcher : public IControlValueReceiver
{

  ControlValueDispatcher(const ControlValueDispatcher&); // nicht impl.
  ControlValueDispatcher& operator=(const ControlValueDispatcher&); // nicht impl.
  
public:
	ControlValueDispatcher(IModelControlReceiver&);
	virtual ~ControlValueDispatcher();

	void registerValueReceiver(int nodeID, int inputIndex,
				  IControlValueReceiver& r);

	void unregisterValueReceiver(int nodeID, int inputIndex,
				     IControlValueReceiver& r);

	virtual void controlValueChanged(int nodeID,int intputIndex,
					 const utils::Buffer& newValue);

	virtual void syncInputValuesStarted();
	virtual void syncInputValuesFinished();

        void clear();

private:
  std::map<std::pair<int,int>, std::list<IControlValueReceiver*> > receivers;
  
  // wenn zu (nodeID,inputIndex) noch kein Eintrag ex., wird er angelegt
  std::list<IControlValueReceiver*>& find(int nodeID, int inputIndex);

  IModelControlReceiver* m_model;

};

}

#endif
