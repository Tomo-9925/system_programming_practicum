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
    int num;
    char *pt;
    memset(buf, 0, sizeof(buf));
    if ((len=recv(so2, buf, sizeof(buf), 0))==0)
      break;
    pt = strtok(buf, " ");
    pt = strtok(NULL, " ");  // 2つ目の文字列にポインタを移動
    // 1つ目の文字で処理を分岐
    if(buf[0]=='l') {
      long tmp;
      tmp = strtol(pt, NULL, 10);  // 文字列を数値に変換
      pritnf("%ld\n", tmp);
      num = sprintf(buf, "%ld", tmp*10);  // 10倍した数値を文字列に変換してbufに格納，格納した文字のバイト数をnumに格納
    } else if(buf[0]=='d') {
      double tmp;
      tmp = strtod(pt, 0);
      printf("%f\n", tmp);
      num = sprintf(buf, "%f", tmp*10);
    } else {
      continue;  // 書式に沿ってないデータは無視
    }
    buf[num] = '\n';  // 文字列の終わりの'\0'を'\n'に変更
    buf[++num] = '\0';  // '\n'の後ろに'\0'を配置
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
