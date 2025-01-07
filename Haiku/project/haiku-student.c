#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define PORT 40000
#define LIBRARIAN_PORT 40001
#define LIBRARIAN_IP "46.10.253.12"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <IP> <port (40000)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    int sock = 0;
    struct sockaddr_in serv_addr;
    char haiku[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("\nConnection Failed \n");
        return -1;
    }

    // Receive haiku
    recv(sock, haiku, 1024, 0);

    // Print the received haiku
    printf("Received Haiku:\n%s\n", haiku);

    // Close the socket
    close(sock);

    // Connect to librarian and send haiku for logging
    int librarian_sock;
    struct sockaddr_in librarian_addr;

    if ((librarian_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    librarian_addr.sin_family = AF_INET;
    librarian_addr.sin_port = htons(LIBRARIAN_PORT);
    if (inet_pton(AF_INET, LIBRARIAN_IP, &librarian_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(librarian_sock, (struct sockaddr *)&librarian_addr, sizeof(librarian_addr)) < 0) {
        perror("Connection to librarian failed");
        exit(EXIT_FAILURE);
    }

    // Send haiku to librarian for logging
    send(librarian_sock, haiku, strlen(haiku), 0);

    close(librarian_sock);

    return 0;
}
