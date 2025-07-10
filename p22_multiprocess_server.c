#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>

void handle_client(int client_fd) {
    char buffer[100];

    read(client_fd, buffer, sizeof(buffer));
    printf("Client says: %s\n", buffer);
    write(client_fd, "Hello from server (child process)\n", 35);
    close(client_fd);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);

    signal(SIGCHLD, SIG_IGN);  // Prevent zombie processes

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    printf("Server is running...\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&addr, &addr_len);

        if (fork() == 0) {
            // Child process
            close(server_fd);  // Child doesn't need listening socket
            handle_client(client_fd);
            exit(0);  // End child
        } else {
            // Parent process
            close(client_fd);  // Parent doesn't need client socket
        }
    }

    return 0;
}
