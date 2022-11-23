#include <stdio.h>
#include <stdlib.h>

// bzero
#include <string.h>
// structs needed to create sockets
#include <winsock2.h>
// math!
#include <math.h>

#pragma comment(lib, "ws2_32.lib") // Winsock Library

void client_handler(SOCKET sock);

int main(int argc, char *argv[])
{
    // fun fact! sockets and C do not like windows
    // so we have to use the winsock2 operating system
    // and compile with the `-lwsock32` flag

    // we have to initialize the library. it's weird
    WSADATA wsa;

    printf("Starting...");

    // we are giving the WSAStartup function the memory address of the struct and the version(?) of the library to load
    // it returns 0 if successful, so we stop if not 0
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    printf("Lib✅");

    // make a struct to store our (server) information
    struct sockaddr_in server;

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // now we actually want a socket
    // a socket is just an integer that points to a file descriptor on the operating system
    // a reference number
    SOCKET server_sock;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == INVALID_SOCKET)
    {
        printf("Could not create socket : %d\n", WSAGetLastError());
        return -1;
    }

    printf("Sock");

    // bind the socket (reserves the port for this process)
    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Bind✅\n");

    // Listen to incoming connections
    listen(server_sock, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");

    struct sockaddr_in client;
    char *serv_msg;
    SOCKET new_socket;
    int addr_len = sizeof(struct sockaddr_in);

    int received_int, client_input;
    double to_receive;

    while ((new_socket = accept(server_sock, (struct sockaddr *)&client, &addr_len)) != INVALID_SOCKET)
    {
        client_handler(new_socket);
    }

    if (new_socket == INVALID_SOCKET)
    {
        // cause of this is usually messing with internet settings
        printf("Accept failed with error code : %d", WSAGetLastError());
        return 1;
    }

    puts("Server stopping...");

    // clean up the library
    closesocket(server_sock);
    WSACleanup();
}
void client_handler(SOCKET sock)
{
    double client_radian = 0;
    int trig_type = 0;
    double result = 0;

    puts("Connection accepted");

    while (1)
    {
        puts("Running Calculation...");
        // step one recv trig function of choice

        // receive number from client
        // recv (socket, buff, size, flags)
        // socket -> connection
        // buff -> where to write data. default is (char *) but can be anything if you are *Sure* of types
        // size -> how big
        // flags -> special connection flags
        // positive number good
        // <=0 Bad
        if (recv(sock, (char *)&client_radian, sizeof(client_radian), 0) == SOCKET_ERROR)
        {
            break;
        }
        // step two recv double representing radian value
        if (recv(sock, (char *)&trig_type, sizeof(trig_type), 0) == SOCKET_ERROR)
        {
            break;
        }

        // match input with appropriate trig functions
        // all trig functions take and return double radians
        switch (trig_type)
        {
        case 1:
            result = sin(client_radian);
            break;

        case 2:
            result = cos(client_radian);
            break;

        case 3:
            result = tan(client_radian);
            break;

        case 4:
            result = asin(client_radian);
            break;

        case 5:
            result = acos(client_radian);
            break;

        case 6:
            result = atan(client_radian);
            break;
        }

        // Reply to the client
        puts("Replying...");

        // send (socket, buff, size, flags)
        // similar to recv
        if (send(sock, (char *)&result, sizeof(result), 0) < 0)
        {
            break;
        }
        puts("🔁");
    }

    puts("Connection closed");
    closesocket(sock);
    puts("Waiting for next client...\n");
}