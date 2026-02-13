#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int server_fd;

    // Create a socket for the server 
    server_fd  = socket(AF_INET, SOCK_STREAM, 0);
    // Check if error
    if(server_fd == -1) {
        perror("Socket Connection Error\n");
    }
    printf("File Descripter is %d\n", server_fd);


    // Bind to a port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8080);

    if(bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("Bind Unsuccesful\n");
    }
    printf("Bind Succesful\n");

    // Make this socket a listening port to receive requests
    int MAX_CONNECTIONS = 3;
    if(listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("listen failed\n");
    }
    printf("Listening on port 8080...\n");

    // Try to accept client
    int client_socket;
    client_socket = accept(server_fd, NULL, NULL);
    
    if(client_socket < 0) {
        perror("Client Couldnt Connect\n");
    } 
    printf("Client Connected\n");







    
    
    return 0;
}