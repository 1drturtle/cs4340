#include <stdio.h>
#include <stdlib.h>

// bzero
#include <string.h>
// structs needed to create sockets
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock Library

int main(int argc, char *argv[])
{
    // fun fact! sockets and C do not like windows
    // so we have to use the winsock2 operating system
    // and compile with the `-lwsock32` flag

    // we have to initialize the library. it's weird
    WSADATA wsa;

    puts("\nInitialising Winsock...");

    // we are giving the WSAStartup function the memory address of the struct and the version(?) of the library to load
    // it returns 0 if successful, so we stop if not 0
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    puts("Initialised.");

    // make a struct to store our (server) information
    struct sockaddr_in server;

    // now we actually want a socket
    SOCKET sock_p;
    sock_p = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_p == INVALID_SOCKET)
    {
        printf("Could not create socket : %d\n", WSAGetLastError());
        return -1;
    }

    puts("Socket created.\n");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // bind the socket (reserves the port for this process)
    if (bind(sock_p, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Socked bound");

    // Listen to incoming connections
    listen(sock_p, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");

    struct sockaddr_in client;
    char *serv_msg;
    SOCKET new_socket;
    int addr_len = sizeof(struct sockaddr_in);

    int received_int, client_input;

    while ((new_socket = accept(sock_p, (struct sockaddr *)&client, &addr_len)) != INVALID_SOCKET)
    {
        received_int = 0;
        puts("Connection accepted");

        // receive number from client
        recv(new_socket, &received_int, sizeof(received_int), 0);
        client_input = ntohl(received_int);

        // print out what we got
        printf("%d\n", client_input);

        // Reply to the client
        puts("Replying...");

        serv_msg = "server message out\n";
        send(new_socket, serv_msg, strlen(serv_msg), 0);

        puts("Waiting for next client...");
    }

    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
        return 1;
    }

    puts("Server stopping...");

    // clean up the library
    closesocket(sock_p);
    closesocket(new_socket);
    WSACleanup();
}