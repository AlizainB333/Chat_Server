#include "server.h"


int init_server(int port) {
    int server_fd;
    // Create a socket for the server 
    server_fd  = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("Socket Connection Error\n");
        exit(EXIT_FAILURE);
    }
    printf("Server Socket Created\n");

    // Bind to a port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    if(bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("Bind Unsuccesful\n");
        exit(EXIT_FAILURE);
    }
    printf("Bind Succesful\n");

    // Make this socket a listening port to receive requests
    int MAX_CONNECTIONS = 3;
    if(listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("listen failed\n");
    }
    printf("Listening on port 8080...\n");

    return server_fd;
}

