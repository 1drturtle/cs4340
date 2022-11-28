# Sockets with C

Chris Agrella

Client/Server

## Algorithms/Data Structures

- This code does not use many typical algorithms
- TCP would be the closest since it's a protocol
- Many structures were used to hold server/ip information
- Example: `struct sockaddr_in`
  - This is used to establish IP of server in client, and the binding address of server.

```c
struct sockaddr_in {
    short            sin_family;   // what type of internet, IPV4 or IPV6
    unsigned short   sin_port;     // Port of the internet, but has to be converted to network byte order. e.g. htons(3490)
    struct in_addr   sin_addr;     // internet address, see below
    char             sin_zero[8];  // nobody knows what this does.
};

struct in_addr {
    unsigned long s_addr;  // IP Address of server, loaded with inet_addr(IP address)
};
```


## Challenges

- All network information needed to be converted to a "network byte order". Fortunately C had functions to do that
- UNIX networking with C does not work with Windows!
  - Had to find and use the windows socket library which had much less documentation
  - Windows library requires much more setup which was also hard to find the correct way to do it.
- Figuring out how to send doubles and integers over socket by pretending an integer was a character buffer.

## Future Work

- Using multi-threading to accept multiple connections simultaneously.
- Allow user to choose degree or radian (I couldn't get this to work for some reason)