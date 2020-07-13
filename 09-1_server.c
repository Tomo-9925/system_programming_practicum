#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

enum {IPPORT_NO=50001};
enum {RETRY_MAX=20};

void err(char *);

int main(int argc, char *argv[])
{
    int		so, so2, len, i;
    struct sockaddr_in	sin;
    char	buf[1024];

    if ((so=socket(AF_INET, SOCK_STREAM, 0))==EOF)
	err("opening stream socket.");
    memset((char *)&sin, 0, sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_port=htons(IPPORT_NO);
    sin.sin_addr.s_addr=INADDR_ANY;
    i=RETRY_MAX;
    while(--i)
    {
	if (bind(so, (struct sockaddr *)&sin, sizeof(sin))==0)
	    break;
	if (errno!=EADDRINUSE)
	    err("binding stream socket.");
    }
    if (i==0)
	err("retry count over!");
    if (listen(so, 5)==EOF)
	err("listen");
    if ((so2=accept(so, NULL, NULL))==EOF)
	err("accept");
    close(so);
    printf("ACCEPT OK!\n");
    while(1)
    {
	memset(buf, 0, sizeof(buf));
	if ((len=recv(so2, buf, sizeof(buf), 0))==0)
	    break;
	buf[len-1]='\0';
	printf("RECEIVE SIZE=[%d], DATA=[%s]\n",  len, buf);
	buf[len-1]='\n';
	len=send(so2, buf, len, 0);
    }
    shutdown(so2, 2);
    close(so2);
}

void err(char *message)
{
    fprintf(stderr, "error: %s\n", message);
    exit(1);
}
