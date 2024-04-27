#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "network.h"

#define PORT 8080

void c_function(const char*) {
    printf("C Function: %s\n",Transmit.exe);
}

int setup_server_socket() {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(af_inet, sock_stream, 0)) == 0) {
        perror("socket failed");
        exit(exit_fail);
    }

    if (setsockopt(server_fd, sol_socket, so_reusaddr | so_reuseport, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(exit_fail);
    }

    address.sin_family = af_inet;
    address.sin_addr.s_addr = inaddr_any;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(exit_fail);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(exit_fail);
    }

    return server_fd;
}
