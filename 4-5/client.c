#include <stdio.h>   
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int main(int argc, char *argv[])
{
    int client_socket;
    struct sockaddr_in server_addr;
    unsigned short server_port;
    int recv_msg_size;
    char *server_ip;

    if (argc != 5)
    {
       fprintf(stderr, "Usage: %s <Server IP> <Server Port> <Child part> <Total sum>\n", argv[0]);
       exit(1);
    }

    server_ip = argv[1];
    server_port = atoi(argv[2]);
    double childPart= atof(argv[3]);
    int totalSum = atoi(argv[4]);

    if ((client_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) DieWithError("socket() failed");

    memset(&server_addr, 0, sizeof(server_addr));  
    server_addr.sin_family      = AF_INET;        
    server_addr.sin_addr.s_addr = inet_addr(server_ip); 
    server_addr.sin_port        = htons(server_port);

    if (connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) DieWithError("connect() failed");

    double realMoney = totalSum * childPart;
    double sumFromServer;

    printf("part: %f\n", realMoney);

    double sendData[1];
    double recvData[1];
    sendData[0] = realMoney;
    send(client_socket, sendData, sizeof(sendData), 0);
    close(client_socket);
    return 0;
}
