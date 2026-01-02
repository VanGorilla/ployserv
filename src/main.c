#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#include "server.h"

// Main function
int main() {
    int server_fd = setup_server();
    printf("Chess game server listening on port %d\n", PORT);

    int client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    while (1) {
        // Accept a client connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }

        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        read(client_fd, buffer, BUFFER_SIZE);
        printf("Received from client %d: %s\n", client_fd, buffer);

        send_start_page(client_fd);

        close(client_fd);
    }

    close(server_fd);
    return 0;
}
