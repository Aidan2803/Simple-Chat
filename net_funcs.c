#include "net_funcs.h"
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

int Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

ssize_t Read(int fd, void *buf, size_t count) {
    ssize_t read_count = read(fd, buf, count);
    if (read_count == -1) {
        perror("Read failed");
        exit(EXIT_FAILURE);
    }
    return read_count;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("Connect failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

int InetPton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res <= 0) {
        if (res == 0) {
            fprintf(stderr, "Invalid address format\n");
        } else {
            perror("InetPton failed");
        }
        exit(EXIT_FAILURE);
    }
    return res;
}
