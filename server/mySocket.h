#ifndef MYSOCKET_H
#define MYSOCKET_H

int myRead(int fd, void *sp, size_t size_len);
int myWrite(int fd, void *sp, size_t size_len);

int writeto(int ,char *);//���������е��ַ����飬д��soket����
int readfrom(int ,char *);//���ͻ��˴������ַ����飬����ڻ�������

int Socket(int domain, int type);
int Bind(int sockfd, const struct sockaddr *net_addr, socklen_t addrlen);
int Listen(int sockfd, int listenNum);

/*���þ��Ϊ��������ʽ*/
void setSockNonBlock(int sock);

#endif

