#include <stdio.h>     
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>   
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAXPENDING 8

double sumFromClients = 0;

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

void hadleTCPConnection(int socket, double totalSum) {
    double childPart;
    double recvData[1];

    recv(socket, recvData, sizeof(recvData), 0);
    childPart = recvData[0];
    sumFromClients += childPart;

    close(socket);
}

int main(int argc, char *argv[])
{
    unsigned short port;
    int server_socket;
    int client_socket;
    int client_length;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    
    if (argc != 3)
    {
        fprintf(stderr, "Usage:  %s <Port for clients> <Total sum>\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);
    double totalSum = atof(argv[2]);

    if ((server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) DieWithError("socket() failed");
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;              
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) DieWithError("bind() failed");
    printf("Open socket on %s:%d\n", inet_ntoa(server_addr.sin_addr), port);
    
    listen(server_socket, MAXPENDING);
    for (int i = 0; i < 8; i++) {
        client_length = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_length);
        printf("connect: %s\n", inet_ntoa(client_addr.sin_addr));
        hadleTCPConnection(client_socket, totalSum);
    }
    printf("Sum: %f\n", sumFromClients);
    printf("Total sum: %f\n", totalSum);
    if (totalSum != sumFromClients) {
        printf("Lawer sKaMer\n");
    } else {
        printf("CORRECT\n");
    }
    return 0;
}
