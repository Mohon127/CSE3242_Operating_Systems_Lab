#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>

void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    char buffer[100];

    read(client_fd, buffer, sizeof(buffer));
    printf("Client says: %s\n", buffer);
    write(client_fd, "Hi from multi-threaded server\n", 31);
    close(client_fd);

    free(arg); // Free dynamically allocated memory
    return NULL;
}

int main() {
    int server_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    printf("Multi-threaded server running...\n");

    while (1) {
        int* client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, (struct sockaddr*)&addr, &addr_len);

        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_fd);
        pthread_detach(tid); // Automatically clean up finished threads
    }

    return 0;
}
