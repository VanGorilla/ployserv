#include <stdio.h>

#include "server.h"

// Function to initialize and listen on a socket
int setup_server() {
    int server_fd;
    struct sockaddr_in address;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Define the address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

int send_start_page(int client_fd) {

    printf("Sending start page\n");
    FILE* fptr = fopen("resource/startpage.html", "r");

    // Error handling
    if(fptr == 0) {
        perror("Error opening startpage.html");
        return 0;
    }

    // Read response from file
    fseek(fptr, 0L, SEEK_END);
    int len = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);
    char* buf = malloc(len);
    fread(buf, 1, len, fptr);
    fclose(fptr);

    // Send response
    send(client_fd, buf, len, 0);
    free(buf);



    return len;
}