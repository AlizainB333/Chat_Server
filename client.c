#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024


int make_client() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(client_fd < 0) {
        perror("Client socket couldnt be created");
        exit(EXIT_FAILURE);
    }

    return client_fd;
}


int main() {
    // Create Client
    int client_fd = make_client();
    printf("Client Made With File ID %d\n", client_fd);

    // Create structure of server IP and Port
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);


    // Connect to server
    if (connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
        perror("Error Could Not Connect\n");
        exit(EXIT_FAILURE);
    }

    printf("Succesfully Connected to Server\n");

    char buffer[BUFFER_SIZE];

    while(1) {
        printf("Enter Message to Send to Server: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        
        int bytes = send(client_fd, buffer, BUFFER_SIZE, 0);
        if(bytes == -1) {
            perror("Send Error\n");
        }
        printf("Message Sent Succesfully\n");

        
    }

    close(client_fd);

    return 0;   
}




