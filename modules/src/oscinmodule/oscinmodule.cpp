#include "oscinmodule.h"

#include <map>
#include <vector>
#include <stdexcept>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>

static logT s_log;

const int SOCKET_ERROR = -1;
const int INVALID_SOCKET = -1;

typedef short udp_port_t; // TODO

class udp_listen_socket
{
public:
  udp_listen_socket(udp_port_t port)
    : buffer(4096) // maximal length of osc messages increase if needed
  {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == INVALID_SOCKET)
      throw std::runtime_error("could open socket");
    
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    if (bind(sockfd, (sockaddr*) &servaddr, sizeof(servaddr) ) == SOCKET_ERROR)
      {
	close(sockfd);
	throw std::runtime_error("could not bind socket");
      }

    // set socket to non blocking mode
    int val= fcntl(sockfd, F_GETFL, 0);
    fcntl( sockfd, F_SETFL, val | O_NONBLOCK );
  }
  
  ~udp_listen_socket()
  {
    close(sockfd);
  }
  
  bool add_package(std::vector<uint8_t>& p)
  {
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    
    int n = recvfrom(sockfd,
		     &buffer[0], buffer.size(),
		     0,
		     (sockaddr*) &cliaddr, &len );
    if ( n < 0 )
      {
	if ( errno != EWOULDBLOCK )
	  {
	    throw std::runtime_error("read error on socket");
	  }
	else
	  {
	    // no packages to read
	    return false;
	  }
      }
    else
      {
	if ( n%4 != 0 ) // no osc package. ignore it
	  {
	    s_log(0, "wrong package size");      
	    return true;
	  }

	std::copy(reinterpret_cast<uint8_t*>(&n),
		  reinterpret_cast<uint8_t*>(&n)+4,
		  back_inserter(p) );
	
	std::copy(buffer.begin(),buffer.begin()+ n, back_inserter(p) );
	
	return true;
      }
  }
  
private:
  int sockfd;
  std::vector<uint8_t> buffer;
};



static std::map<udp_port_t, udp_listen_socket*> udpsockets;




typedef struct _MyInstance {

  udp_port_t old_port;

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
    // get socket or create socket
  std::map<udp_port_t, udp_listen_socket*>::iterator it = udpsockets.find(my->old_port);
  if (it != udpsockets.end())
    {
      delete udpsockets[my->old_port];
      udpsockets.erase(it);
    }
  
  free(my);
}

void update(void* instance)
{
  InstancePtr inst = (InstancePtr) instance;
  MyInstancePtr my = inst->my;

  try
    {
      udp_port_t port = trim_int(inst->in_port->number, 0, 65535);

      // get socket or create socket
      std::map<udp_port_t, udp_listen_socket*>::iterator it;
      it = udpsockets.find(port);
      if (it == udpsockets.end())
	{
	  udpsockets[port] = new udp_listen_socket(port);
	}
      
      udp_listen_socket& s = *udpsockets[port];

      // get pending packages
      std::vector<uint8_t> packages;
      while( s.add_package(packages) ) {}
      
      osc_set_buffer(inst->out_r, &packages[0], packages.size());
  
      my->old_port=port;
  
    }
  catch (std::runtime_error& e)
    {
      s_log(0, e.what());
      osc_set_buffer(inst->out_r, 0, 0);
    }

  assert( osc_invariant(inst->out_r) );
}

