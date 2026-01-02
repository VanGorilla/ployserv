#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>


#define PORT 80
#define BUFFER_SIZE 1024

int setup_server();
int send_start_page(int client_fd);