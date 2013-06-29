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

#include "serialmodule.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <string.h>

#include <windows.h>

#include "keycommands.h"

// parameters for the serial port:
static const char* SERIAL_PORT = "COM1";
static const int BAUD_RATE = 19200;
static const int STOP_BITS = ONESTOPBIT;
static const int BYTE_SIZE = 8;

/**
 * Tries to open a serial port with the specified parameters.
 * If unsuccessfull, INVALID_HANDLE_VALUE is returned.
 */
static HANDLE initPort(const char* serialPort, int baudRate,
		       int stopBits, int byteSize);

/**
 * Writes to a file handle. Delays after each byte and
 * appends a newline if msg does not end with one.
 */
static void slowWriteFile(HANDLE ser, const char* msg);

/**
 * Determines from the keystatus, the current key_change and from
 * the keygroup, wether a command is to be sent.
 */
static const char* get_command(int key_status[20], int key_change,
			       const char commands[80][256],
			       int* key_group);

/**
 * Checks wether command is a valid command.
 * For now, valid commands must have the form:
 *
 *   CMD   ::= <BLK> | <CO>
 *   BLK   ::= blk <SIZE> <COORD> <COORD>
 *   CO    ::= co <COL> <COL> <COL> <MONITOR>
 *
 *   COORD ::= 0|1|2|3
 *   SIZE  ::= 1|2|3|4
 *   COL   ::= [0..63]
 *   MONITOR ::= m 0 | mon <COORD> <COORD> | mon 4 3 
 *   
 */
int check_command(const char* command);

static logT s_log;

typedef struct _MyInstance {

  HANDLE hComm;
  StringType old_control;

  int key_status[20];
  int current_group;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{
  s_log = log_function;
  return 1;
}

void shutDown(void)
{
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));
  int i;

  my->hComm = initPort(SERIAL_PORT, BAUD_RATE, STOP_BITS, BYTE_SIZE);
  if (my->hComm == INVALID_HANDLE_VALUE)
    {
      free(my);
      return 0;
    }

  string_initInstance(&my->old_control);
  for (i = 0; i < sizeof(my->key_status) / sizeof(my->key_status[0]); ++i)
    my->key_status[i] = -1;

  my->current_group = 0;
   
  return my;
}

void destruct(MyInstance* my)
{
  CloseHandle(my->hComm);
  my->hComm = INVALID_HANDLE_VALUE;
  free(my);
}


void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstance* my = inst->my;
  char recBuffer[2048];	
 
  
  int numberOfBytesRead;
  int key_change = trim_int(inst->in_key_change->number, -1, 117);
  const char* key_command = 0;

  // Did the user press a key?
  key_command = get_command(my->key_status, key_change, commands,
			    &my->current_group);

  if (key_command) //yes, he did, send the command

    {
      char buffer[2048];
      _snprintf(buffer, sizeof(buffer), "I write '%s'", key_command);
      s_log(2, buffer);
      
      slowWriteFile(my->hComm, key_command);
    }

  // read what the remote computer has to tell us
  ReadFile(my->hComm, recBuffer, 1024, &numberOfBytesRead,0);

  recBuffer[numberOfBytesRead] = 0;
  if (numberOfBytesRead != 0)
    {
      char buffer[2048];
      _snprintf(buffer, sizeof(buffer), "I read '%s'", recBuffer);
      s_log(2, buffer);
    }
 
  // send input string if it has changed
  if (strcmp(inst->in_control->text, my->old_control.text) != 0)
    {
      char buffer[2048];

	  if (!check_command(inst->in_control->text))
	  {
		  _snprintf(buffer, sizeof(buffer),
			  "Not sending bad command: '%s'",
			  inst->in_control->text);
		  s_log(1, buffer);
	  }
	  else
	  {
		  _snprintf(buffer, sizeof(buffer), "I write '%s'",
			  inst->in_control->text);
		  s_log(2, buffer);
		  
		  slowWriteFile(my->hComm, inst->in_control->text);
      }
      string_assign(&my->old_control, inst->in_control);
    }
}

/***************************************************************************/

static const char* get_command(int key_status[20], int key_change,
			       const char commands[80][256],
			       int* key_group)
{
  int key;

  assert(*key_group >= 0 && *key_group <8);

  if (key_change < 0 || key_change > 117)
    return 0;
  if (key_change > 17 && key_change < 100)
    return 0;
  assert(0 <= key_change && key_change <= 117);
  assert(key_change <= 17 || key_change >= 100);

  key = (key_change >= 100) ? key_change - 100 : key_change;
  assert(0 <= key && key <= 17);

  if (key_status[key] != key_change)
  {
      key_status[key] = key_change;
	  
      if (key >= 10)
	  {
		  *key_group = key - 10;
		  return 0;
	  }
      else
	  {
		  const char* command;
		  assert(0 <= key && key < 10);
		  
		  command = commands[key + *key_group * 10];
		  if (strlen(command) > 0)
			  return command;
		  else
			  return 0;
	  }
  }
  
  return 0;
}

/***************************************************************************/

static void slowWriteFile(HANDLE ser, const char* msg)
{
    int i;
    int len = strlen(msg);
	int numberOfBytesWritten;
	for (i = 0; i < len; ++i)
	{
		WriteFile(ser,msg + i,1,&numberOfBytesWritten,0);
		Sleep(1);
	}

   if (msg[len-1] != '\n')
     WriteFile(ser,"\n",1,&numberOfBytesWritten,0);
}

/***************************************************************************/

static HANDLE initPort(const char* serialPort, int baudRate,
		       int stopBits, int byteSize)
{
	COMMTIMEOUTS timeouts;
	DCB dcb; //settings for the serial port
	int ret;
	HANDLE hComm;

	hComm = CreateFile( serialPort,
		GENERIC_READ | GENERIC_WRITE, 
		0, 
		0, 
		OPEN_EXISTING,
		0/*FILE_FLAG_OVERLAPPED*/,
		0);
	
	if (hComm == INVALID_HANDLE_VALUE)
	{
	  char buffer[128];
	  _snprintf(buffer, sizeof(buffer), "Couldnt open '%s'", serialPort);
	  s_log(0, buffer);
	  return INVALID_HANDLE_VALUE;
	}

	// Make readFile return immediately, wether data arrived or not
	timeouts.ReadIntervalTimeout = MAXDWORD;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;

	ret = SetCommTimeouts(hComm, &timeouts);

	if (ret == 0)
	{
	  s_log(0,"Couldnt set CommTimeouts");
	  CloseHandle(hComm);
	  return INVALID_HANDLE_VALUE;
	}

	memset(&dcb, sizeof(dcb), 0);
	dcb.DCBlength = sizeof(dcb);

	if (!GetCommState(hComm,&dcb))
	{
	  s_log(0,"Couldnt get CommState");
	  CloseHandle(hComm);		
	  return INVALID_HANDLE_VALUE;
	}

	dcb.BaudRate = baudRate;
	dcb.fParity = FALSE;
	dcb.Parity = NOPARITY;
	dcb.StopBits = stopBits;
	dcb.ByteSize = byteSize;

	if (!SetCommState(hComm, &dcb))
	{
		LPVOID lpMsgBuf;
		char buffer[1024];

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);
		
		_snprintf( buffer, sizeof(buffer),
			   "Could not set CommState: '%s'",lpMsgBuf );

		s_log(0, buffer);

		LocalFree( lpMsgBuf );

		CloseHandle(hComm);		
		return INVALID_HANDLE_VALUE;
	}

	return hComm;
}
/***************************************************************************/
