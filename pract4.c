#include <libc.h>

typedef struct client {
    char msg[424242];
    int id;
} t_client;

t_client    clients[424242];
char buffRead[424242], buffWrite[424242];
int max = 0, next_id = 0;
fd_set active_fds, read_fds, write_fds;

void exitError(char *str){
    write(2, str, strlen(str));
    exit(1);
}

void sendMsg(int sender_fd){
    for (int fd = 0; fd <= max; fd++)
        if (FD_ISSET(fd, &write_fds) && fd != sender_fd) write(fd, &buffWrite, strlen(buffWrite));
}