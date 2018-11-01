
#ifndef RITO_SERVER_H
#define RITO_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <sys/stat.h>

void sig_chld(int signo);


#endif /* RITO_SERVER_H */