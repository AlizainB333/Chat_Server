#include "server.h"



int main() {
    // Set Up Server
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