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

#ifndef INCLUDED_MODULE_H
#define INCLUDED_MODULE_H

#include <string>
#include <vector>
#include <list>
#include <stdexcept>

#include "utils/autoptr.h"

class IModule;
class IOutputPlug;
class IType;

class TypeAttributes;
namespace utils {
class Buffer;
}

/**
 * Kapselt die Funktionalität eines Inputpins. 
 */
class IInput{
public:
	
	virtual ~IInput(){}; //TODO

	virtual const IType* getData() const = 0;

	/**
	* Liefert das Modul zurück, das an diesem Input "haengt".
	* @return Das über diesen Input verbundene Modul.
	*/
	virtual IModule* getConnectedModule() const = 0;

	/**
	* Verbindet den Input mit einem OutputPlug.	
	*
	* @param p Der Plug mit dem der Input verbunden wird.
	* @exception std::runtime_error falls der Input schon
	*                               mit einem Output verbunden ist.
	*/
	virtual void plugIn(utils::AutoPtr<IOutputPlug>& p)
	  throw (std::runtime_error) = 0;

	/**
	* Löst die Verbindung des Inputs.
	* Setzt auch connectedData auf 0.
	*/
	virtual void unPlug() = 0;

	/**
	* Gibt den Typ des Inputs zurück.
	* @return Typ des Inputs
	*/
	virtual int getType() const = 0;

	/**
	* Gibt an ob die Daten des Inputs vom Modul bei
	* der Berechnung geändert werden oder nicht.
	* @return true wenn die Daten vom Modul nicht geändert werden;
	*         false sonst.
	*/
	virtual bool isConst() const = 0;

	/**
	* TODO
	*/
	virtual bool isStrongDependency() const = 0;

	virtual void setValue(const utils::Buffer& serializedData) = 0;

  virtual int getIndex() const = 0;

  virtual IModule* getModule() const = 0;

	virtual const TypeAttributes* getTypeAttributes() const = 0;

	/**
	 * Must be called before update() for the module of this input
	 * (if this input is needed and the connected module has changed).
	 * Can be used to implicitly convert types etc. pp.
	 *
	 * This piece of documentation seems very weird to me.
	 * I think it should be marked as deprecated or obsolete.
	 */
	virtual void update() = 0;
};

/**
 * Kapselt die Funktionalität eines Outputpins. 
 */
class IOutput
{
public:
  virtual ~IOutput(){}; //TODO
  
  //virtual void setData(const IType* data) = 0;

	/**
	 * Das Modul das diesen Output besitzt.
	 * @return Das Modul das diesen Output besitzt. Wird für 
	 *         IInput.getConnectedModule() benötigt.
	 */
	virtual IModule* getModule() const = 0;

	/**
	 * Verbindet den Output mit einem neuen Input. Der Output kann mit
	 * beliebig vielen Inputs verbunden werden. Für jeden wird ein
	 * OutputPlug erzeugt. 
	 * @param i Der Input der mit dem Output verbunden wird.
	 */
	virtual utils::AutoPtr<IOutputPlug> plugIn(IInput& i) = 0;

	/**
	 * Entfernt einen OutputPlug und damit die Verbindung zum 
	 * entsprechenden Input.
	 * @param plug Der OutputPlug der entfernt werden soll.
	 */
	virtual void unPlug(IInput& plug) = 0;

	/**
	 * Liefert die TypID des Outputs zurück.
	 * @return Die TypID des Outputs.
	 */
	virtual int getType() const = 0;

  virtual std::list<IInput*> getConnectedInputs() const = 0;

  /**
   * Returns the patched Input of this Output.
   *
   * When a input is patched to a output, it means that this input
   * is not processed by the module but "tunneled" directly
   * to that output.
   * 
   * @return A pointer to the this output is patched to, or 0 if
   *         the output is not patched.
   */
  virtual IInput* getPatchedInput() const = 0;

  /**
   * Tells this output, what its patched input is.
   * See IModule::getPatchedInput().
   *
   * @param in The input that is patched directly to this output.
   *           Must not be 0.
   */
  virtual void setPatchedInput(IInput* in) = 0;

  /**
   * Tells this output, that it is no longer patched.
   * See IModule::getPatchedInput().
   *
   * @param in The input that is patched directly to this output.
   *           Can be 0 if there is no patched input.
   */
  virtual void unPatch() = 0;
};

/**
 * Die Klasse IOutputPlug dient dazu, mit einem Output beliebig viele
 * Inputs zu verbinden. Dazu wird für jede Verbindung genau ein OutputPlug 
 * erzeugt.
 */
class IOutputPlug
{
public:
	virtual ~IOutputPlug() {}; //TODO

	virtual void setData(const IType* data) = 0;

	virtual const IType* getData() const = 0;	

	/**
	 * Gibt den Output zurück an dem dieser Stecker hängt.
	 * @return den zugeordneten Output.
	 */
	virtual IOutput* getOutput() const = 0;

	/**
	 * Gibt das zugeordnete Modul zurück.
	 * @return das Modul dem der zugeordnete Output gehört.
	 */
	virtual IModule* getModule() const = 0;

	/**
	 * Gibt den Input zurück an dem dieser Stecker hängt.
	 * @return den zugeordneten Input.
	 */
	virtual IInput* getInput() const = 0;

	 /**
	 * Gibt an ob die Daten des zugeordneten Inputs vom Modul bei
	 * der Berechnung geändert werden oder nicht.
	 * @return true wenn die Daten vom Modul nicht geändert werden;
	 *         false sonst.
	 */
	virtual bool isConst() const = 0;
};


/**
 * Ueber dieses Interface kann auf Berechnungsmodule zugegriffen werden.
 */
class IModule
{
public:
  typedef utils::AutoPtr<IInput> IInputPtr;
  typedef utils::AutoPtr<IOutput> IOutputPtr;

	IModule(int id) : m_id(id) {}

	virtual ~IModule() {};

	int getID() const { return m_id; }
	void setID(int id) { m_id = id; }

	virtual std::string module_class_name() const = 0;

	/**
	 * Gibt alle Inputs des Moduls zurück.
	 * @return std::vector mit den Inputs. 
	 */
	virtual const std::vector<IInputPtr>& getInputs() const = 0;
		
	/**
	 * Gibt alle Outputs des Moduls zurück.
	 * @return std::vector mit den Outputs.
	 */
	virtual const std::vector<IOutputPtr>& getOutputs() const = 0;
		
	/**
	 * Das ist nicht die Berechnungsfunktion. Sie wird von der Engine so
	 * oft aufgerufen, bis zu der übergebenen Liste keine Elemente
	 * mehr hinzugefügt werden. 
	 * Nach jedem Aufruf aktualisiert die Engine alle Inputs die
	 * zur Liste hinzugefügt werden (falls diese nicht eh schon aktuell 
	 * sind). Das Modul teilt auf diesem Weg mit, dass es diese 
	 * Inputs im nächsten Rechenschritt braucht.
	 * Wenn die keine Elemente mehr zur Liste hinzugefügt werden
	 * wird update aufgerufen.
	 * @param l Liste der Inputs, die vom Modul im nächsten Rechenschritt
	 *        benötigt werden.
	 */
	virtual IInput* dependencies() = 0;

	/**
	 * Das ist die Berechnungsfunktion.
	 */
	virtual void update() = 0;

     

	/**
	 * Gibt an ob das Modul bei gleichen Inputwerten dieselben Outputwerte
	 * produziert.
	 * @return true falls das Modul bei denselbe Inputwerten immer 
	 *              dieselben Outputwerte erzeugt. D.h. wenn sich das
	 *              Modul wie eine Funktion verhält;
	 *         false sonst.
	 */
    virtual bool isDeterministic() const = 0;

private:
	int m_id;

};

#endif
