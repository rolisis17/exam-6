#include <libc.h>

typedef struct Client
{
    int id;
    char msg[424242];
} t_Client;

t_Client clients[1024];
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
	if (sockfd == -1) exitError("Fatal error \n");
    FD_ZERO(&active_fds);
    FD_SET(sockfd, &active_fds);
	struct sockaddr_in servaddr; 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(av[1]));
	if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) exitError("Fatal error \n");
	if (listen(sockfd, 10) != 0) exitError("Fatal error \n");
    while(1) {
        write_fds = read_fds = active_fds;
        if (select(max + 1, &read_fds, &write_fds, NULL, NULL) < 0) continue;
        for (int fd = 0; fd <= max; fd++) {
            if (FD_ISSET(fd, &read_fds) && fd == sockfd) {
                int cltfd = accept(sockfd, NULL, NULL);
                max = cltfd > max ? cltfd : max;
                FD_SET(cltfd, &active_fds);
                clients[cltfd].id = next_id++;
                bzero(clients[cltfd].msg, strlen(clients[cltfd].msg));
                sprintf(buffwrite, "Server : client %d just arrived\n", clients[cltfd].id);
                sendMsg(cltfd);
                break;
            }
            else {

            }
        }
    }
}
