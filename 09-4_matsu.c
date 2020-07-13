#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

enum {IPPORT_NO=1142};
enum {RETRY_MAX=20};

void err(char *);

int main(int argc, char *argv[])
{
  int    so, so2, len, i;
  struct sockaddr_in sin;
  char   buf[1024];

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
    int num, cnt=0;
    long N;
    char *pt;
    memset(buf, 0, sizeof(buf));
    if ((len=recv(so2, buf, sizeof(buf), 0))==0)
      break;
    pt = strtok(buf, " ");
    pt = strtok(NULL, " ");
    N = strtol(pt, NULL, 10);
    if(buf[0]=='l') {
      long tmp[1024];
      // 送られてきたデータを区切り文字（コンマ，半角スペース）ごとに読み込み
      while((pt=strtok(NULL, ", "))!=NULL) {
        if(cnt!=0)
          printf(" ");
        tmp[cnt] = strtol(pt, NULL, 10);
        printf("%ld", tmp[cnt]);
        cnt++;
        if(cnt==N)  // 指定した文字数まで来たとき読み込み終了
          break;
      }
    } else if(buf[0]=='d') {
      double tmp[1024];
      while((pt=strtok(NULL, ", "))!=NULL) {
        if(cnt!=0)
          printf(" ");
        tmp[cnt] = strtod(pt, 0);
        printf("%f", tmp[cnt]);
        cnt++;
        if(cnt==N)
          break;
      }
    } else if(buf[0]=='c') {
      char tmp[1024];
      while((pt=strtok(NULL, ", "))!=NULL) {
        if(cnt!=0)
          printf(" ");
        tmp[cnt] = *pt;
        printf("%c", tmp[cnt]);
        cnt++;
        if(cnt==N)
          break;
      }
    } else {
      continue;
    }
    puts("");  // 標準出力にて改行
    num = sprintf(buf, "%d", cnt);
    buf[num] = '\n';
    buf[++num] = '\0';
    printf("=> %s", buf);
    len=send(so2, buf, num, 0);
  }
  shutdown(so2, 2);
  close(so2);
}

void err(char *message)
{
  fprintf(stderr, "error: %s\n", message);
  exit(1);
}
