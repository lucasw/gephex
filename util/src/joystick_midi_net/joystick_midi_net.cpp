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

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#if defined(OS_WIN32)
#include <windows.h>
#include <io.h>
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
#include <fcntl.h> 
#endif

#include <errno.h>

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "libjoystick.h"

#define MIDI_CTRLCHANGE 0xb0


struct OldValues
{
  unsigned char axis[32];
  unsigned char button[32];
};

static void sleep_in_millis(unsigned long millis);
//static void keys_init();
static int keys_read();
static void close_socket(int* socket);
static int open_socket(int port, int* socket);
static int send_data(int socket,
		     struct sockaddr* addr,
		     const unsigned char* buffer, int len);


static int joystick_read_midi(Joystick* self,
                              struct OldValues* old,
                              unsigned char* buf, int len,
                              int control_offset);


void usage()
{
  printf("\nUsage: joystick_midi_net [<hostname> [<port> [<joy_id> "
	 "[<control_offset>]]]]\n\n");
}

void parse_commandline(int argc, const char* argv[],
		       const char** host_name, int* port,
		       int* id, int* control_offset)
{
  // default values:
  *host_name = "localhost";
  *port = 1337;
  *id = 0;
  *control_offset = 0;

  if (argc >= 2)
    {
      if (strcmp(argv[1], "--help") == 0)
	usage();
      else
	*host_name = argv[1];

      if (argc >= 3)
	{
	  *port = atoi(argv[2]);

	  if (argc >= 4)
	    {
	      *id = atoi(argv[3]);

	      if (argc >= 5)
		{
		  *control_offset = atoi(argv[4]);
		}
	    }
	}
    }
}

int main(int argc, const char* argv[])
{
  struct sockaddr_in addr;
  struct hostent* phost;
  int socket;
  int err;
  int port;
  const char* host_name;
  int id;
  int control_offset;
  int num_joysticks = 0;

  JoystickDriver *jst_drv = 0;
  Joystick* jst = 0;
  struct OldValues old;

  int quit;

  parse_commandline(argc, argv, &host_name, &port, &id, &control_offset);

#ifdef OS_WIN32
  {
    /* Start up the windows networking */
    WORD version_wanted = MAKEWORD(1,1);
    WSADATA wsaData;
    
    if ( WSAStartup(version_wanted, &wsaData) != 0 ) 
      {
        fprintf(stderr,"Couldn't initialize Winsock 1.1");
      }
  }
#endif

  try {
    jst_drv = new JoystickDriver("default");
  } catch (std::exception& e) {
    fprintf(stderr, "Could not create joystick driver: %s\n", e.what());
    return 1;
  }

  num_joysticks = jst_drv->num_devices();

  printf("Number of joysticks: %i\n", num_joysticks);

  printf("Opening joystick %i:\n", id);

  try {
    jst = jst_drv->open(id);
  } catch (std::exception& e) {
    fprintf(stderr, "No Joystick found: %s\n", e.what());
    return 1;
  }

  err = open_socket(0, &socket);
  if (err == 0)
    {
      fprintf(stderr, "Could not open socket\n");
      return 1;
    }
  
  
  phost = gethostbyname(host_name);    
  if (phost == 0)
    {
      fprintf(stderr, "Could not resolve hostname: %s\n", host_name);
      return 1;
    }

  addr.sin_family = AF_INET;
  addr.sin_port = htons ((short)port);
  addr.sin_addr = *((struct in_addr *)phost->h_addr);

  fprintf(stdout, "Network socket is open\n");
  fprintf(stdout, "Sending to '%s' on port '%i'\n", host_name, port);
  fprintf(stdout, "Joystick id = %i; Control-Offset = %i;\n",
	  id, control_offset);
  
  quit = 0;
  while (quit == 0)
    {
      int sleep_millis = 10;
      unsigned char buf[64];
      int len = 0;


#if defined(OS_POSIX)
      int key = keys_read();	  

      switch(key)
        {
        case -1:
          break;
        case 'c':
          printf("Recalibrating...\n");
          jst->recalibrate();
          break;
        case 'q':
          quit = 1;
          break;
        default:
          break;
        }
#endif

      len = joystick_read_midi(jst, &old, buf, len, control_offset);
      if (len > 0)
	send_data(socket,
		  (struct sockaddr*) &addr,
		  (unsigned char*) buf, len);

      // sleep a little
      sleep_in_millis(sleep_millis);
    }

  close_socket(&socket);
  delete jst;
  delete jst_drv;
  
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

  return 0;
}


// helper functions

void sleep_in_millis(unsigned long millis)
{
#if defined(OS_POSIX)
  struct timespec tspec;
  tspec.tv_sec = 0;
  tspec.tv_nsec = millis*1000*1000;
  nanosleep(&tspec,0);
#elif defined(OS_WIN32)
  Sleep(millis);
#endif
}

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

  return 1;
}

static int send_data(int socket,
		     struct sockaddr* addr,
		     const unsigned char* buf, int length)
{
  int left;
  int len;
  int sent;


  sent = 0;
  errno = 0;  
  len = length;
  left = len;
  do {
#if defined OS_WIN32
const char* bbb = reinterpret_cast<const char*>(buf);
#elif defined OS_POSIX
const void* bbb = reinterpret_cast<const void*>(buf);
#endif
    len = sendto(socket, bbb, left, 0, addr, sizeof(struct sockaddr_in));
    if ( len > 0 ) 
      {
	sent += len;
	left -= len;
	buf += len;
      }
    else if (len == -1 && errno != EINTR)
      {	  
	fprintf(stderr, "Couldnt send: %s\n", strerror(errno));
      }
  }
#if defined(OS_WIN32)
  while ( (left > 0) && ((len > 0) || errno == EINTR 
			 || errno == 0) );
#elif defined(OS_POSIX)
  while ( (left > 0) && ((len > 0) || errno == EINTR) );
#endif

  //    fprintf(stdout, "Sent %i bytes\n", sent);
  
  return sent;
}


static int joystick_read_midi(Joystick* jst, struct OldValues* old,
			      unsigned char* midi_buffer,
			      int size, int control_offset)
{  
  int num_axes = jst->num_axes();
  int num_buttons = jst->num_buttons();
  int i, len = 0;
	
  jst->poll();

  for (i = 0; i < num_axes; ++i)
    {
      unsigned char axc = (unsigned char) (jst->get_axis(i) * 127);
      //assert ( 0 <= axc && axc <= 127 );
		
      if (abs(axc - old->axis[i]) > 0)
        {
          old->axis[i] = axc;
          midi_buffer[len++] = MIDI_CTRLCHANGE + 0; //channel 0
          midi_buffer[len++] = i + control_offset;
          midi_buffer[len++] = axc;
        }
    }
  for (i = 0; i < num_buttons; ++i)
    {
      unsigned char b = jst->get_button(i) * 127;
		
      //assert ( 0 <= b && b <= 127 );
		
      if (b != old->button[i])
        {
          old->button[i] = b;
          midi_buffer[len++] = MIDI_CTRLCHANGE + 1; // channel 1
          midi_buffer[len++] = i + control_offset;
          midi_buffer[len++] = b;
          //printf("Sent button %i (value = %i)\n", i, b);
        }
    }


  return len;
}

/*
static void keys_init()
{
  //const int STDIN = 0;
#if defined(OS_POSIX)
	//    int val = fcntl(STDIN, F_GETFL, 0);

	//	fcntl(fileno(stdin), F_SETFL, val | O_NONBLOCK);
#elif defined(OS_WIN32)	
#endif
}*/

static int keys_read()
{
  char c;
  fd_set readfds;
  struct timeval tv;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&readfds);
  FD_SET(fileno(stdin),&readfds);
  select(fileno(stdin)+1,&readfds,0,0,&tv);
  //TODO: handle EINTR

  errno = 0;
  if (FD_ISSET(fileno(stdin), &readfds))
    {
      do {
	int len = read(fileno(stdin), &c, 1);
	if (len == -1)
	  {
	    if (errno == EINTR)
	      continue;
	    
            //	    if (errno == EWOULDBLOCK)
            //	      return -1;

	    fprintf(stderr, "Error while reading from stdin!\n");
	    return -1;
	  }
	else
	  {
	    break;
	  }
      } while (errno == EINTR);

      return c;
    }

  return -1;
}

