#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 8080

int main() {
    int socket_fd, new_socket;
    struct sockaddr_in address;
    int addr_len = sizeof(address);
    char buff[100] = {0};

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return 1;
    }

    if (listen(socket_fd, 3) < 0) {
        perror("Listen failed");
        return 1;
    }

    printf("Waiting for connection...\n");

    if ((new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t *)&addr_len)) < 0) {
        perror("Accept failed");
        return 1;
    }

    strcpy(buff, "Connected... Let's Talk");
    printf("---------------------------------\n");
    printf("Ready to send message from server\n");
    printf("Wait for client to send message\n");
    printf("Type \"exit\" to close connection\n");
    printf("---------------------------------\n");
    send(new_socket, buff, strlen(buff), 0);

    while (1) {
        memset(buff, 0, sizeof(buff));

        int read_size = read(new_socket, buff, sizeof(buff) - 1);
        if (read_size <= 0) {
            printf("Client disconnected or error occurred\n");
            break;
        }

        printf("Client: %s\n", buff);

        printf("Server: ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = 0;

        if (send(new_socket, buff, strlen(buff), 0) < 0) {
            perror("Send failed");
            break;
        }

        if (strcmp(buff, "exit") == 0) {
            printf("Server: Closing connection.\n");
            break;
        }
    }

    close(new_socket);
    close(socket_fd);

    return 0;
}

