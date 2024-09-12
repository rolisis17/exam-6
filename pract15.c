#include <libc.h>

typedef struct client{
    int id;
    char msg[424242];
} t_client;

t_client clients[1024];
char  buffwrite[424242], buffread[424242];
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
    int	sockfd = max = socket(AF_INET, SOCK_STREAM, 0); 
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
        for (int fd = 0; fd <= max; fd++) {
            if (FD_ISSET(fd, &read_fds) && fd == sockfd) {
                int ClientFd = accept(sockfd, NULL, NULL);
                max = ClientFd > max ? ClientFd : max;
                clients[ClientFd].id = next_id++;
                bzero(clients[ClientFd].msg, strlen(clients[ClientFd].msg));
                FD_SET(ClientFd, &active_fds);
                fprintf(buffwrite, "Server : client %d just arrived\n", clients[ClientFd].id);
                sendMsg(ClientFd);
                break;
            }
            else {
                int ret = recv()
            }
        }
    }
}