#ifndef INCLUDED_SOCKET_UTILS_H
#define INCLUDED_SOCKET_UTILS_H

#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

namespace net {

#if defined(OS_POSIX)
  static const int SOCKET_ERROR = -1;
  static const int INVALID_SOCKET = -1;
#endif

class SocketUtils
  {
  public:
    static void closeSocket(int& socket);

    /**
     * Returns wether a read on fd will block.
     * @param fd the file descriptor
     * @param timeout the timeout in ms
     * @return wether a read to fd will block
     */
    static bool doesReadBlock(int fd, int timeout);

	/**
	 * For the stupid win32 WSAStartup shit
	 */
	static void initNetwork();

	/**
	 * For the stupid win32 WSACleanup shit
	 */
	static void shutDownNetwork();
  };

}
#endif
