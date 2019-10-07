#ifndef LIB_SOCKET_H
#define LIB_SOCKET_H

#if defined (_MSC_VER)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h> //hostent
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#endif
#include <iostream>
#include <cerrno>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <ctime>


/////////////////////////////////////////////////////////////////////////////////////////////////////
//utils
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::string str_extract(const std::string& str_in);
std::string prt_time();
int set_daemon(const char* str_dir);
void wait(int nbr_secs);


/////////////////////////////////////////////////////////////////////////////////////////////////////
//socket_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class socket_t
{
public:
  socket_t();
  socket_t(int socket_fd, sockaddr_in sock_addr);
  ~socket_t();
  void close();
  int write_all(const void* buf, int size_buf);
  int read_all(void* buf, int size_buf);
  int hostname_to_ip(const char* host_name, char* ip);

public:
  // socket descriptor 
#if defined (_MSC_VER)
  SOCKET m_socket_fd;
#else
  int m_socket_fd;
#endif
  sockaddr_in m_sockaddr_in; // client address (used to store return value of server accept())
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//tcp_server_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class tcp_server_t : public socket_t
{
public:
  tcp_server_t(const unsigned short server_port);
  socket_t accept();
  ~tcp_server_t();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
//tcp_client_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

class tcp_client_t : public socket_t
{
public:
  tcp_client_t(const char* host_name, const unsigned short server_port);
  ~tcp_client_t();
  int connect();

protected:
  std::string m_server_ip;
  unsigned short m_server_port;
};

#endif