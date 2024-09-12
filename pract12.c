#include <libc.h>

typedef struct client{
    char msg[424242];
    int id;
} t_client;

t_client clients[1024];
char buffwrite[424242], buffread[424242];
int max = 0, next_id = 0;
fd_set active_fds, read_fds, write_fds;

void exitError(char *str) {
    write(2, str, strlen(str));
    exit(1);
}

void sendMsg(int sender_fd) {
    for (int fd = 0; fd <= max; fd++)
        if (FD_ISSET(fd, &write_fds) && fd != sender_fd) write(fd, buffwrite, strlen(buffwrite));
}

int main(int ac, char **av) {
    if (ac != 2) exitError("Wrong number of arguments\n");
    int sockfd = max = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) exitError("Fatal error\n");
    FD_ZERO(&active_fds);
    FD_SET(sockfd, &active_fds);
	struct sockaddr_in servaddr; 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) exitError("Fatal error\n");
	if (listen(sockfd, 10) != 0) exitError("Fatal error\n");
    while (1) {
        read_fds = write_fds = active_fds;
        if (select(max + 1, &read_fds, &write_fds, NULL, NULL) < 0) continue;
        for (int fd = 0; fd <= max; fd++){
            if (FD_ISSET(fd, &read_fds) && fd == sockfd) {
                int ClientSocket = accept(sockfd, NULL, NULL);
                max = ClientSocket > max ? ClientSocket : max;
                clients[ClientSocket].id = next_id++;
                bzero(clients[ClientSocket].msg, strlen(clients[fd].msg));
                FD_SET(ClientSocket, &active_fds);
                sprintf(buffwrite, "Server : client %d just arrived\n", clients[ClientSocket].id);
                sendMsg(ClientSocket);
                break;
            }
            else {

            }
        }
    }
}