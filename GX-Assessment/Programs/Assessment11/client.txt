#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define SERVER_IP "172.20.10.3"
#define PORT 8080

int main() {
    int socket_fd;
    struct sockaddr_in address;
    char buff[100] = {0};

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket Failed");
        return 1;
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &address.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

    if (connect(socket_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Connection failed");
        return 1;
    }

    int read_size = read(socket_fd, buff, sizeof(buff) - 1);
    if (read_size <= 0) {
        perror("Read failed or server closed connection");
        close(socket_fd);
        return 1;
    }
    buff[read_size] = '\0';
    printf("Server: %s\n", buff);

    while (1) {
        memset(buff, 0, sizeof(buff));
        printf("Client: ");
        fgets(buff, sizeof(buff), stdin);
        buff[strcspn(buff, "\n")] = 0;

        if (send(socket_fd, buff, strlen(buff), 0) < 0) {
            perror("Send failed");
            break;
        }

        read_size = read(socket_fd, buff, sizeof(buff) - 1);
        if (read_size <= 0) {
            printf("Server disconnected or read error\n");
            break;
        }
        buff[read_size] = '\0';
        printf("Server: %s\n", buff);

        if (strcmp(buff, "exit") == 0) {
            printf("Client: Closing connection.\n");
            break;
        }
    }

    close(socket_fd);
    return 0;
}

