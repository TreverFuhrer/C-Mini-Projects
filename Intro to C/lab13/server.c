/*
* A server program that servs a client by converting a message to uppercase. 
* The server is configured to handle multiple clients
*/ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

#define PORT 8088
#define BUFFER_SIZE 1024

void toUpperCase(char *str) {
    for (int i = 0; str[i]; ++i) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creates a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return 1;
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

     // Bind the socket to the specified address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    // Listen for connections. 
    if (listen(server_fd, 10) < 0) {
        perror("listen");
        return 1;
    }

    // Keep accepting incoming connections and process requests
    while(1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            return 1;
        }

        if (fork() == 0) {
            // Step 1: Read client's initial request
            char init[BUFFER_SIZE]={0};
            int readBytes = read(new_socket, init, BUFFER_SIZE);
            init[readBytes] = '\0';
            printf("Client says: %s\n", init);

            // Step 2: Reply with confirmation
            char confirmation[] = "Sure, send me the message.";
            write(new_socket, confirmation, strlen(confirmation));

            // Step 3: read message from client
            char strToConvert[BUFFER_SIZE] = {0};
            readBytes = read(new_socket, strToConvert, BUFFER_SIZE);
            strToConvert[readBytes] = '\0';
            printf("Client wants to convert this to uppercase: %s\n", strToConvert);

            // Step 4: Convert the recieved message to uppercase and send back to client (write)
            /********************** TODO **********************/
            toUpperCase(strToConvert);
            write(new_socket, strToConvert, strlen(strToConvert));

            close(new_socket);  // this closes the socket for each process handling a client
            exit(0);
        }
        close(new_socket);  // this closes the socket of the parent process. Basically parent doesnt have anything to do here.
    }

    return 0;
}


