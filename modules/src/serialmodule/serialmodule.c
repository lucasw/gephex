#include "dllmodule.h"

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include <string.h>

#include <windows.h>

#include "serialicon.xpm"

#include "stringtype.h"

static const char* SPEC = 
"mod_spec { name=mod_serialOutput; number_of_inputs=1; number_of_outputs=0; "
"deterministic=true; }";

static const char* INPUT_SPECS[] = 
{
  "input_spec { type=typ_string; const=true; strong_dependency=true; }",
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
	StringType *in;
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
	assert(index == 0);
	inst->in = (StringType*) typePointer;
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

void update(void* instance)
{
	static char oldText[2048] = {0};
	static char recBuffer[2048];	

	InstancePtr inst = (InstancePtr) instance;
	int numberOfBytesWritten = 0;
	int numberOfBytesRead;

	ReadFile(inst->hComm,recBuffer,1024,&numberOfBytesRead,0);
	recBuffer[numberOfBytesRead] = 0;
	if (numberOfBytesRead != 0)
		printf("serialModule: read <%s>\n", recBuffer);

	if (strcmp(inst->in->text, oldText) != 0)
	{
		printf("serialModule sez: i write %s\n", inst->in->text);

		//WriteFile(inst->hComm,outText,len,&numberOfBytesWritten,0);
		slowWriteFile(inst->hComm,inst->in->text);

		strcpy(oldText,inst->in->text);
	}
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
  static const char* INFO = "info { name=[Serial Output] group=Outputs inputs=[1 Steuerung{widget_type=videowall_edit;}] outputs=0 type=xpm }";
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

