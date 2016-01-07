/* cliente.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#define SERV_ADDR (IPPORT_RESERVED+1)
#define DATA "##--##--##----***----##--##--##"

int main (int argc, char *argv[])
{
 int sock;
 struct sockaddr_in server;
 struct hostent *hp;
 if (argc<2)
    {
      printf("Uso: %s como nombre de host\n",argv[0]);
      exit(1);
    }
sock=socket(AF_INET,SOCK_STREAM,0);

if (sock<0)
   {
     perror("No se ha podido crear el socket");
     exit(1);
   }
server.sin_family =AF_INET;
hp=gethostbyname(argv[1]);

if (hp==0)
   {
     fprintf(stderr, "%s: No conozco ese computador\n",argv[1]);
     exit(2);
   } 
memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
server.sin_port = htons (SERV_ADDR);

if (connect(sock, (struct sockaddr *)&server, sizeof(server))<0)
   {
     perror("La conexion no sido aceptada");
     exit(1);
   }

 if (write(sock,DATA, strlen(DATA)+1)<0)
    perror("No he podido escribir el mensaje");

 close(sock);
 exit(0);
}
