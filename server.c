#include "server.h"

#define BUFFER_SIZE 1024



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


int main() {
    int server_fd = init_server(8080);
    char buffer[BUFFER_SIZE];
    
    // Server Run
    while(1) {

        int client_fd = accept(server_fd, NULL, NULL);
        printf("Client Connectted\n");

        while(1) {
            int bytes_recv = recv(client_fd, buffer, BUFFER_SIZE-1, 0);
    
            if(bytes_recv > 0) {
                buffer[bytes_recv] = '\0';
                printf("Client Message is: %s", buffer);
            }
            else if(bytes_recv == 0) {
                perror("Client Disconnected");
                break;
            }
            else {
                perror("Error did nto receive message correctly");
                break;
            }
        }
        close(client_fd);

    }

    return 0;
}

