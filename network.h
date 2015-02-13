#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>

int get_socket();
int connect_to_socket(int socketfd, char *host, char *port);
ssize_t readLine(int fd, void *buffer, size_t n);
#endif
