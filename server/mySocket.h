#ifndef MYSOCKET_H
#define MYSOCKET_H

int myRead(int fd, void *sp, size_t size_len);
int myWrite(int fd, void *sp, size_t size_len);

int writeto(int ,char *);//将缓冲区中的字符数组，写到soket函数
int readfrom(int ,char *);//将客户端传来的字符数组，存放在缓冲区中

int Socket(int domain, int type);
int Bind(int sockfd, const struct sockaddr *net_addr, socklen_t addrlen);
int Listen(int sockfd, int listenNum);

/*设置句柄为非阻塞方式*/
void setSockNonBlock(int sock);

#endif

