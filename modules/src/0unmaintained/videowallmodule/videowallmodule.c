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

#include "dllmodule.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <string.h>

#include <windows.h>

#include "videowallicon.xpm"

#include "stringtype.h"
#include "rgbtype.h"

static const char* SPEC = 
"mod_spec { name=mod_videoWallOutput; number_of_inputs=4; number_of_outputs=0; "
"deterministic=true; }";

static const char* INPUT_SPECS[] = 
{
  "input_spec { type=typ_string; default=Signal; const=true; strong_dependency=true; }",
  "input_spec { type=typ_rgb; const=true; strong_dependency=true; }",
  "input_spec { type=typ_string; default=1Block; const=true; strong_dependency=true; }",
  "input_spec { type=typ_rgb; const=true; strong_dependency=true; }"
};

// Einstellungen fuer den seriellen Port:
static const char* SERIAL_PORT = "COM1";
static const int BAUD_RATE = 19200;
static const int STOP_BITS = ONESTOPBIT;
static const int BYTE_SIZE = 8;

static int instanceCount = 0;
static HANDLE hCommStatic;

typedef struct _Instance
{
	StringType* borderMode;
	RGBType* borderColor;
	StringType* centerMode;
	RGBType* centerColor;
	HANDLE hComm;
} Instance, *InstancePtr;

int init(logT log_function)
{
  return 1;
}

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
		fprintf(stderr,"SerialOutput: Couldnt open %s\n",serialPort);
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
		fprintf(stderr,"SerialOutput: Couldnt set CommTimeouts\n");
		CloseHandle(hComm);		
		return INVALID_HANDLE_VALUE;
	}

	memset(&dcb, sizeof(dcb), 0);
	dcb.DCBlength = sizeof(dcb);

	if (!GetCommState(hComm,&dcb))
	{
		fprintf(stderr,"SerialOutput: Couldnt get CommState\n");
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

		fprintf(stderr,"SerialOutput: Couldnt Set CommState\n");


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
		
		fprintf( stderr, "SerialOutput: %s\n",lpMsgBuf );
		
		LocalFree( lpMsgBuf );

		CloseHandle(hComm);		
		return INVALID_HANDLE_VALUE;
	}

	return hComm;
}

void* newInstance()
{
	InstancePtr inst = (InstancePtr) malloc(sizeof(Instance));

	++instanceCount;

	if (instanceCount == 1)
	{
		hCommStatic = initPort(SERIAL_PORT, BAUD_RATE, STOP_BITS, BYTE_SIZE);

		if (hCommStatic == INVALID_HANDLE_VALUE)
		{
			free(inst);
			return 0;
		}
	}
   
	inst->hComm = hCommStatic;
	return inst;
}


void deleteInstance(void* instance)
{
	InstancePtr inst = (InstancePtr) instance;
	--instanceCount;
	if (instanceCount == 0)
	{
		CloseHandle(hCommStatic);
		hCommStatic = INVALID_HANDLE_VALUE;
	}
	free(instance);
}

const char* getSpec(void)
{
  return SPEC;
}

int setInput(void* instance,int index,void* typePointer)
{
	InstancePtr inst = (InstancePtr) instance;

	switch(index)
	{
	case 0:
		inst->borderMode = (StringType*) typePointer;
		break;
	case 1:
		inst->borderColor = (RGBType*) typePointer;
		break;
	case 2:
		inst->centerMode = (StringType*) typePointer;
		break;
	case 3:
		inst->centerColor = (RGBType*) typePointer;
		break;
	}

	return 1;
}

void * getOutput (void* instance,int index)
{
	return 0;
}

void slowWriteFile(HANDLE ser, const char* msg)
{
	int i;
	int len = strlen(msg);
	int numberOfBytesWritten;
	for (i = 0; i < len; ++i)
	{
		WriteFile(ser,msg + i,1,&numberOfBytesWritten,0);
		Sleep(1);
	}
}

void createBorderCommand(char commandLine[2048],
						 const char* borderMode,
						 RGBType* color)
{
	if (strcmp(borderMode,"Signal") == 0)
	{
		strcpy(commandLine,"blk 1 4 3\n");
	}
	else if (strcmp(borderMode,"Farbe") == 0)
	{
		sprintf(commandLine,"co %i %i %i mon 4 3\n",color->r * 63,
			color->g * 63, color->b * 63);
	}
	else if (strcmp(borderMode,"Zufall") == 0)
	{
		double r = (double) rand() / RAND_MAX;
		double g = (double) rand() / RAND_MAX;
		double b = (double) rand() / RAND_MAX;

		sprintf(commandLine,"co %i %i %i mon 4 3\n",r * 63,
			g * 63, b * 63);
	}
	else
	{
		fprintf(stderr,"Falscher BorderMode: <%s>\n", borderMode);
		strcpy(commandLine,"");
	}
}

void createCenterCommand(char commandLine[2048],
						 const char* centerMode,
						 RGBType* color)
{
	if (strcmp(centerMode,"1Block") == 0)
	{
		strcpy(commandLine,"blk 4 0 0\n");
	}
	else if (strcmp(centerMode,"4Block") == 0)
	{
		strcpy(commandLine,"blk 2 0 0 blk 2 2 0 blk 2 2 2 blk 2 0 2\n");
	}
	else if (strcmp(centerMode,"16Block") == 0)
	{
		strcpy(commandLine,"real m 0\n");
	}
	else if (strcmp(centerMode,"Farbe") == 0)
	{
		sprintf(commandLine,"co %i %i %i m 0\n",color->r * 63,
			color->g * 63, color->b * 63);
	}
	else if (strcmp(centerMode,"Zufall") == 0)
	{
		int x;
		int y;
		static char temp[1024];
		commandLine[0] = 0;
		for (y = 0; y <= 3; ++y)
		{
			for (x = 0; x <= 3; ++x)
			{
				double r = (double) rand() / RAND_MAX;
				double g = (double) rand() / RAND_MAX;
				double b = (double) rand() / RAND_MAX;

				sprintf(temp,"co %i %i %i mon %i %i ",r * 63,
				g * 63, b * 63, x, y);
				strcat(commandLine,temp);
			}
		}
		strcat(commandLine,"\n");
	}
	else
	{
		fprintf(stderr,"Falscher CenterMode: <%s>\n", centerMode);
		strcpy(commandLine,"");
	}
}

void sendIfChanged(const char* text, char* oldText, HANDLE hComm)
{
	if (strcmp(text, oldText) != 0)
	{
		printf("serialModule sez: i write %s\n", text);

		//WriteFile(inst->hComm,outText,len,&numberOfBytesWritten,0);
		slowWriteFile(hComm,text);

		strcpy(oldText,text);
	}
}

void update(void* instance)
{
	static char borderCommand[2048] = {0};
	static char centerCommand[2048] = {0};
	static char oldBorderCommand[2048] = {0};
	static char oldCenterCommand[2048] = {0};
	static char recBuffer[2048];	

	InstancePtr inst = (InstancePtr) instance;
	int numberOfBytesWritten = 0;
	int numberOfBytesRead;


	ReadFile(inst->hComm,recBuffer,1024,&numberOfBytesRead,0);
	recBuffer[numberOfBytesRead] = 0;
	if (numberOfBytesRead != 0)
		printf("serialModule: read <%s>\n", recBuffer);

	createBorderCommand(borderCommand,inst->borderMode->text,
						inst->borderColor);

	createCenterCommand(centerCommand,inst->centerMode->text,
						inst->centerColor);


	sendIfChanged(borderCommand, oldBorderCommand, inst->hComm);
	sendIfChanged(centerCommand, oldCenterCommand, inst->hComm);
	
}

const char* getInputSpec (int index)
{
  return INPUT_SPECS[index];
}
	
const char* getOutputSpec (int index)
{
  return 0;
}

int getInfo(char* buf,int bufLen)
{
  static const char* INFO = "info { name=[Video Wall] group=Outputs "
	  "inputs=[4 Rand{hidden=true; widget_type=combo_box; values=[Signal,Farbe,Zufall]} "
		"RandFarbe{widget_type=color_selector; hidden=true;} Mitte{hidden=true; widget_type=combo_box; values=[1Block,4Block,16Block,Farbe,Zufall]} "
		"InnereFarbe{widget_type=color_selector; hidden=true;}] outputs=0 type=xpm }";
	char* tmpBuf;
  int reqLen = strlen(INFO) + 1 + getSizeOfXPM(serialicon_xpm);
  if (buf != 0 && reqLen <= bufLen)
    {
			char* offset;
			int i;
			int lines = getNumberOfStringsXPM(serialicon_xpm);
		  tmpBuf = malloc(reqLen);
			memcpy(tmpBuf,INFO,strlen(INFO)+1);
			offset = tmpBuf + strlen(INFO)+1;
			for (i = 0; i < lines; ++i)
			{
				char* source = serialicon_xpm[i];
				memcpy(offset,source,strlen(source)+1);
				offset += strlen(source) + 1;
			}			
      memcpy(buf,tmpBuf,reqLen);
			free(tmpBuf);
    }
  return reqLen;
}

