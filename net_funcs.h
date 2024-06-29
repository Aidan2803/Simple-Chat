#ifndef NET_FUNCS_H
#define NET_FUNCS_H

#include <sys/types.h>
#include <sys/socket.h>

int Socket(int domain, int type, int protocol);
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
ssize_t Read(int fd, void *buf, size_t count);
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
int InetPton(int af, const char *src, void *dst);

#endif
