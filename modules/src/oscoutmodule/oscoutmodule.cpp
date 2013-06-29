#include "oscoutmodule.h"

#include<iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>

static logT s_log;

typedef struct _MyInstance {

 int dummy; // replace this with your favourite vars

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

  if (my == 0)
  {
          s_log(0, "Could not allocate memory for MyInstance struct\n");
          return 0;
  }

  // Add your initialization here

  return my;
}

void destruct(MyInstance* my)
{
  // Add your cleanup here
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  assert ( osc_invariant(inst->in_r) );
  
  unsigned char* pos = inst->in_r->data;
  size_t len = inst->in_r->len;

  struct sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons( trim_int(inst->in_port->number, 0, 65535));
  sin.sin_addr.s_addr = inet_addr(inst->in_dest->text);
  int s = socket(AF_INET, SOCK_DGRAM, 0);
  bind(s, (struct sockaddr *)&sin, sizeof(sin));
  
  while (len > 0)
    {
      assert( len >=4 );
      unsigned int p_len = *reinterpret_cast<unsigned int*>(pos);
      pos += 4;
      len -= 4;
      
      assert (len >= p_len );
      assert (p_len % 4 == 0);
      // send(pos,pos+p_len)

      ssize_t nums = sendto(s, pos, p_len, 0 , (struct sockaddr *)&sin, sizeof(sin) );
      
      pos += p_len;
      len -= p_len;
    }

  // close socket
  close(s);
  
  assert( len == 0 );
}

