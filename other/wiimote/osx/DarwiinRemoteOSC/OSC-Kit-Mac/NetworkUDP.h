#ifdef __sgi
#include <netinet/in.h>
#endif

#if defined (__APPLE__) && (__GNUC__)
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

struct NetworkReturnAddressStruct {
    struct sockaddr_in  cl_addr;
    int clilen;
    int sockfd;
};
