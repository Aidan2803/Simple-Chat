#include "net_funcs.h"
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <signal.h>

static int client_sockfd = 0;

int signal_handler(int signal_number){
    if(client_sockfd != 0){
        close(client_sockfd);
    }
    exit(signal_number);
}

int main() {
    signal(SIGINT, signal_handler);
    client_sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(50000);

    InetPton(AF_INET, "127.0.0.1", &addr.sin_addr);
    Connect(client_sockfd, (struct sockaddr*)&addr, sizeof(addr));

    struct pollfd fds[2] = {
        {0, POLLIN, 0},
        {client_sockfd, POLLIN, 0}
    };

    while(1){
        poll(fds, 2, 50000);
        char buffer[255] = {0};
        if (fds[0].revents & POLLIN){
            read(0, buffer, 255);
            send(client_sockfd, buffer, 255, 0);
        } else if(fds[1].revents & POLLIN){
            recv(client_sockfd, buffer, 255, 0);
            printf("%s\n", buffer);
        }
    }

    return 0;
}
