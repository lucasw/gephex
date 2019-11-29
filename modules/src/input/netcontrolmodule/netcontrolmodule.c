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

#include "netcontrolmodule.h"

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
#endif
#include <errno.h>

static void close_socket(int* socket);
static int open_socket(int port, int* socket);
static void receiver_data(int socket, MidiType* buffer);

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
      fprintf(stderr, "Couldn't initialize Winsock 1.1");
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
  close_socket(&my->socket);
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;
  int port = trim_int(inst->in_port->number, 0, 64000);

  if (port != my->oldPortNumber)
    {
      int err;
      close_socket(&my->socket);
      err = open_socket(port, &my->socket);
      if (err == 0)
	{
	  fprintf(stderr, "Could not open socket on port %i\n", port);

	}
      my->oldPortNumber = port;

      fprintf(stdout,
	      "[netcontrolmodule::update] opened socket on port %i\n", port);
    }


  receiver_data(my->socket, inst->out_signal);
}


// helper functions

static void close_socket(int* socket)
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
static int open_socket(int port, int* socket_ptr)
{
  struct sockaddr_in local_sin;
  
  *socket_ptr = socket(AF_INET, SOCK_DGRAM, 0); 
  if (*socket_ptr == INVALID_SOCKET)
    {
      return 0;
    }

  local_sin.sin_family = AF_INET;
  local_sin.sin_port = htons ((short)port);
  local_sin.sin_addr.s_addr = htonl (INADDR_ANY);
	
  if (bind (*socket_ptr, (struct sockaddr *) &local_sin, 
	    sizeof (local_sin)) == SOCKET_ERROR)
    {
      close_socket(socket_ptr);
      return 0;
    }  
  
  fprintf(stdout, "[netcontrolmodule::open_socket] listening on port %i\n",
	  port);

  return 1;
}

static void receiver_data(int socket, MidiType* buffer)
{
#define MAX_MSG_LEN 4096
  static unsigned char data_buf[MAX_MSG_LEN];
  int capacitiy;
  unsigned char* buf;
  int buf_size;
  fd_set readfds;
  int i;

  if (socket == INVALID_SOCKET)
    {
      /*fprintf(stderr, "[netcontrolmodule::receiver_data] %s\n",
	      "Invalid socket handle\n");*/

      buffer->len = 0;
      return;
    }

  capacitiy = MAX_MSG_LEN;
  buf = data_buf;
  buf_size = 0;
  //read up to 10 packets
  for (i = 0; i < 10; ++i)
  {
    int len;
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&readfds);
    FD_SET(socket,&readfds);
    select(socket+1,&readfds,0,0,&tv);
    //TODO: handle EINTR!

    if (FD_ISSET(socket, &readfds))
      {
	errno = 0;
	do {
	  len = recv(socket, (char*) buf, capacitiy, 0);
	  if (len == -1 && errno != EINTR)
	    {
	      fprintf(stderr,"[netcontrolmodule::receiver_data] errno = %i\n",
		      errno);
		  break;	
	    }
	} while ( errno == EINTR );      
      }
    else
      break; // quit reading loop if no packets are pending

    capacitiy -= len;
    buf += len;
    buf_size += len;
  }  
  
  if (buf_size != 0)
    {
      /*fprintf(stdout, "[netcontrolmodule::receiver_data] "
	      "read %i bytes\n", buf_size);*/
      midi_set_buffer(buffer, data_buf, buf_size);
    }
  else
    buffer->len = 0;
  return;
}
