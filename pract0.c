#include <libc.h>

typedef struct client {
    char    msg[424242];
    int     id;
} t_client;

t_client clients[1024];
char buffread[424242], buffwrite[424242];
int max = 0, next_id = 0;
fd_set active_fds, Read_fds, Write_fds;

void exitError(char *str) {
    write(2, str, strlen(str));
    exit(1);
}

void sendMsg(int sender_fd) {
    for (int fd = 0; fd <= max; fd++)
        if (FD_ISSET(fd, &Write_fds) && fd != sender_fd) write(fd, &buffwrite, strlen(buffwrite));
}

int main(int ac, char **av) {
    if (ac != 2) exitError("Wrong number of arguments\n");
    int sockfd = max = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) exitError("Fatal error\n");
    FD_ZERO(&active_fds);
    FD_SET(sockfd, &active_fds);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(2130706433); // 127.0.0.1
    servaddr.sin_port = htons(atoi(av[1]));
    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) exitError("Fatal error\n");
    if (listen(sockfd, 10) != 0) exitError("Fatal error\n");
    while(1) {
        Read_fds = Write_fds = active_fds;
        if (select(max + 1, &Read_fds, &Write_fds, NULL, NULL) < 0) continue;
        for (int fd = 0; fd <= max; fd++) {
            if (FD_ISSET(fd, &Read_fds) && fd == sockfd) {
                int clientSocket = accept(sockfd, NULL, NULL);
                max = clientSocket > max ? clientSocket : max;
                clients[clientSocket].id = next_id++;
                bzero(clients[clientSocket].msg, strlen(clients[clientSocket].msg));
                FD_SET(clientSocket, &active_fds);
                sprintf(buffwrite, "Server: client %d just arrived\n", clients[clientSocket].id);
                sendMsg(clientSocket);
                break;
            }
            else {
                int read = recv(fd, buffread, sizeof(buffread), 0);
                if (read <= 0) { 
                    sprintf(buffwrite, "Server: client %d just left\n", clients[fd].id);
                    sendMsg(fd);
                    FD_CLR(fd, &active_fds);
                    close(fd);
                    break;
                }
                else {
                    for (int i = 0, j = strlen(clients[fd].msg); i < read; i++, j++) {
                        clients[fd].msg[j] = buffread[i];
                        if (clients[fd].msg[j] == '\n') {
                            clients[fd].msg[j] = '\0';
                            sprintf(buffwrite, "Client %d: %s\n", clients[fd].id, clients[fd].msg);
                            sendMsg(fd);
                            bzero(clients[fd].msg, strlen(clients[fd].msg));
                            j = -1;
                        }
                    }
                    break;
                }
            }
        }
    }

}