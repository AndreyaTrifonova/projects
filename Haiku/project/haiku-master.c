#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <libgen.h>
#include <time.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20
#define PORT 40000

void shuffle_words(char dictionary[MAX_WORDS][MAX_WORD_LENGTH], int word_count) {
    srand(time(NULL));
    for (int i = 0; i < word_count; i++) {
        int j = rand() % word_count;
        char temp[MAX_WORD_LENGTH];
        strcpy(temp, dictionary[i]);
        strcpy(dictionary[i], dictionary[j]);
        strcpy(dictionary[j], temp);
    }
}

void generate_haiku(char* haiku, int wait_time) {
    FILE *dict_file;
    char dictionary[MAX_WORDS][MAX_WORD_LENGTH];
    int syllable_count = 0;
    int words_per_row[3] = {5, 7, 5};

    dict_file = fopen("dictionary.txt", "r");
    if (dict_file == NULL) {
        perror("Error opening dictionary file");
        exit(EXIT_FAILURE);
    }

    int word_count = 0;
    while (word_count < MAX_WORDS && fscanf(dict_file, "%s", dictionary[word_count]) == 1) {
        printf(" %s\n", dictionary[word_count]); // Print word to screen
        word_count++;
        sleep(wait_time); // Add delay based on wait time
    }

    fclose(dict_file);

    shuffle_words(dictionary, word_count);

    haiku[0] = '\0';
    for (int i = 0; i < 3; i++) {
        while (syllable_count < words_per_row[i]) {
            int index = rand() % word_count; // Get a random index within the word count
            strcat(haiku, dictionary[index]);
            strcat(haiku, " ");
            syllable_count++; // Assuming each word has one syllable
        }
        strcat(haiku, "\n");
        syllable_count = 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <dictionary_file> <wait_time> <port (40000)>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *dictionary_file = argv[1];
    int wait_time = atoi(argv[2]);
    int port = atoi(argv[3]);

    char *dir = dirname(dictionary_file);
    chdir(dir);

    int server_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char haiku[MAX_WORDS * MAX_WORD_LENGTH] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connection...\n");

    while(1) {
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        generate_haiku(haiku, wait_time);
        send(new_socket, haiku, strlen(haiku), 0);

        close(new_socket);
    }

    close(server_fd);

    return 0;
}

