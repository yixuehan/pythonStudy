#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        perror("socket");
        return 1;
    }
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = INADDR_ANY;
    socklen_t len = sizeof(addr);

    if (-1 == bind(sockfd, reinterpret_cast<sockaddr*>(&addr), len)) {
        perror("bind");
        return 1;
    }

    if (-1 == listen(sockfd, 1024)) {
        perror("listen");
        return 1;
    }

}
