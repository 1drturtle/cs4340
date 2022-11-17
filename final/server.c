#include <stdio.h>
#include <stdlib.h>

// data structs used for system calls
#include <sys/types.h>
// structs needed to create sockets
#include <sys/socket.h>
// structs needed to work with domains & IP addresses
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    // socket file descriptor
    int sockfd;
    // `accept` socket file description
    int newsockfd;
    // port number of server to listen on
    int portno;
    // size of client address
    int clilen;
    // number of characters read/written
    int n;

    // 256 byte buffer storing data read or to be written
    char buffer[256];
    // serv_addr - address of server
    // cli_addr  - address of client (once connected)
    // sockaddr_in: contains ip address information & port
    struct sockaddr_in serv_addr, cli_addr;
}