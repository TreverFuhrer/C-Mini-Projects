/*
* A client program that requests the server to convert a message to uppercase
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8088
#define BUFFER_SIZE 1024

int main() {
    int sock;
    
    // Creates a socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;  
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server with specified address and port number
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Step 1: Send initial request
    char request[] = "Can you convert a message to uppercase?";
    write(sock, request, strlen(request));

    // Step 2: Read confirmation
    char confirm[BUFFER_SIZE];
    int readBytes = read(sock, confirm, BUFFER_SIZE);
    confirm[readBytes] ='\0';
    printf("Server Confirmed saying: %s\n", confirm);

   
    // Step 3: Enter a message from terminal and then Send it to the server
    char msg[BUFFER_SIZE]={0};
    printf("Enter a message:");
    fgets(msg, BUFFER_SIZE, stdin);   
    msg[strcspn(msg, "\n")] = '\0';  // otherwise it will read the newline you entered after the input
    write(sock, msg, strlen(msg));

    // Step 4: Recieve (read) the converted message from the server
    /********************** TODO **********************/
    char uppercaseMsg[BUFFER_SIZE];
    readBytes = read(sock, uppercaseMsg, BUFFER_SIZE);
    uppercaseMsg[readBytes] ='\0';
    printf("Uppercase: %s\n", uppercaseMsg);

    close(sock);
    
    return 0;
}
