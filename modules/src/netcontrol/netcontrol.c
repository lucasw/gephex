#include "netcontrol.h"

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#elif defined(OS_POSIX)
const int SOCKET_ERROR = -1;
const int INVALID_SOCKET = -1;

#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <sys/poll.h>
#include <netinet/in.h>
//#include <arpa/inet.h>
#include <netdb.h>
//#include <fcntl.h> 
#include <errno.h>
#endif

static void closeSocket(int* socket);
static int openSocket(int port, int* socket);
static void receiveData(int socket, MidiType* buffer);

typedef struct _MyInstance {

  int socket;
  int oldPortNumber;

} MyInstance, *MyInstancePtr;

int init(logT log_function)
{

#ifdef OS_WIN32
  /* Start up the windows networking */
  WORD version_wanted = MAKEWORD(1,1);
  WSADATA wsaData;
    
  if ( WSAStartup(version_wanted, &wsaData) != 0 ) 
    {
      throw SocketException("Couldn't initialize Winsock 1.1");
    }
#endif

  return 1;
}

void shutDown(void)
{
#ifdef OS_WIN32
  if ( WSACleanup() == SOCKET_ERROR ) 
    {
      if ( WSAGetLastError() == WSAEINPROGRESS ) 
	{
	  WSACancelBlockingCall();
	  WSACleanup();
	}
    }
#endif
}

MyInstance* construct()
{
  MyInstance* my = (MyInstancePtr) malloc(sizeof(MyInstance));

  my->socket = INVALID_SOCKET;
  my->oldPortNumber = -1;

  return my;
}

void destruct(MyInstance* my)
{
  closeSocket(&my->socket);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int port = inst->in_port->number;

  if (port != my->oldPortNumber)
    {
      int err;
      closeSocket(&my->socket);
      err = openSocket(port, &my->socket);
      if (err == 0)
	{
	  fprintf(stderr, "Could not open socket on port %i\n", port);

	}
      my->oldPortNumber = port;
    }

  receiveData(my->socket, inst->out_signal);
}


// helper functions

static void closeSocket(int* socket)
{
  if (*socket != INVALID_SOCKET)
    {
#if defined(OS_POSIX)
      close(*socket);
#elif defined(OS_WIN32)
      closesocket(*socket);
#endif
    }

  *socket = INVALID_SOCKET;
}

// returns 1 on success
static int openSocket(int port, int* socket_ptr)
{
  struct sockaddr_in local_sin;
  
  *socket_ptr = socket(AF_INET, SOCK_DGRAM, 0); 
  if (*socket_ptr == INVALID_SOCKET)
    {
      return 0;
    }

  local_sin.sin_family = AF_INET;
  local_sin.sin_port = htons (port);
  local_sin.sin_addr.s_addr = htonl (INADDR_ANY);
	
  if (bind (*socket_ptr, (struct sockaddr *) &local_sin, 
	    sizeof (local_sin)) == SOCKET_ERROR)
    {
      closeSocket(socket_ptr);
      return 0;
    }  

  return 1;
}

static void receiveData(int socket, MidiType* buffer)
{
#define MAX_MSG_LEN 1024
  static unsigned char buf[MAX_MSG_LEN];
  int len;
  fd_set readfds;

  if (socket == INVALID_SOCKET)
    {
      buffer->len = 0;
      return;
    }
  
  {
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_SET(socket,&readfds);
    select(socket+1,&readfds,0,0,&tv);
    //TODO: interrupted!
  }

  if (FD_ISSET(socket, &readfds))
    {
      errno = 0;
      do {
	len = recv(socket, (char*) buf, MAX_MSG_LEN, 0);
	if (len == -1 && errno != EINTR)
	  {
	    fprintf(stderr,"Fehler bei netcontrol::recv!\n errno=%i\n", errno);
	  }
	else
	  {
	    midi_set_buffer(buffer, buf, len);
	    return;
	  }
      } while ( errno == EINTR );      
    }
  
  buffer->len = 0;
  return;
}
