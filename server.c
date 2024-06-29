#include "net_funcs.h"
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <signal.h>

static int serverfd = 0;
static int accepted_socketfd = 0;

int signal_handler(int signal_number){
    if(serverfd != 0){
        close(serverfd);
    }
    if(accepted_socketfd != 0){
        close(accepted_socketfd);
    }

    exit(signal_number);
}


int main() {
    signal(SIGINT, signal_handler);
    int serverfd = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(50000);

    Bind(serverfd, (struct sockaddr*)&addr, sizeof(addr));
    Listen(serverfd, 5);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    accepted_socketfd = Accept(serverfd, 0, 0);

    struct pollfd fds[2] = {
        {0, POLLIN, 0},
        {accepted_socketfd, POLLIN, 0}
    };

    while(1){
        poll(fds, 2, 50000);
        char buffer[255] = {0};
        if (fds[0].revents & POLLIN){
            read(0, buffer, 255);
            send(accepted_socketfd, buffer, 255, 0);
        } else if(fds[1].revents & POLLIN){
            recv(accepted_socketfd, buffer, 255, 0);
            printf("%s\n", buffer);
        }
    }

    return 0;
}
