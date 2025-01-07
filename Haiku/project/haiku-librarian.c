#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

#define PORT 40001

void get_timestamp(char *timestamp) {
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timestamp, 80, "[%Y-%m-%d %H:%M:%S]", info);
}

void save_haiku_to_log(char *haiku) {
    FILE *log_file = fopen("haiku_log.txt", "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }

    char timestamp[80];
    get_timestamp(timestamp);

    fprintf(log_file, "Timestamp:\n%s\n%s\n", timestamp, haiku);
    fflush(log_file);
    fclose(log_file);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    printf("Librarian started. Waiting for haikus...\n");

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to localhost port 40001
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Socket binding successful.\n");

    // Start listening
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connections
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    printf("Haiku saved to log file.\n");

    // Receive haiku from client and save to log file
    while (1) {
        int bytes_received = read(new_socket, buffer, 1024);
        if (bytes_received == 0) {
            break;
        }

        buffer[bytes_received] = '\0'; // Null-terminate the received data
        save_haiku_to_log(buffer);

        printf("Haiku saved to log file.\n");
        fflush(stdout); // Flush stdout

        memset(buffer, 0, sizeof(buffer));
    }

    close(new_socket);
    close(server_fd);

    return 0;
}

