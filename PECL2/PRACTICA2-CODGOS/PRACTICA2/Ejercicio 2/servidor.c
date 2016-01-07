/* servidor.c */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#define STDOUT 1
#define SERV_ADDR (IPPORT_RESERVED+1)

int main()
{
int connect;
int sock,length,msgsock;
struct sockaddr_in server, client;
char buf[1024];

int client_size = sizeof(client);

sock=socket(AF_INET, SOCK_STREAM,0);

if (sock<0)
  {
    perror("No hay socket de escucha");
    exit(1);
  }

server.sin_family=AF_INET;
server.sin_addr.s_addr=htonl(INADDR_ANY);
server.sin_port = htons(SERV_ADDR);

if (bind(sock,(struct sockaddr *)&server, sizeof(server))<0)
  {
    perror("Direccion no asignada");
    exit(1);
  }

listen(sock,1);
while (1)
 {
  /*Estar� bloqueado esperando petici�n de conexi�n*/

  connect = accept(sock, (struct sockaddr *)&client, &client_size);
  if (connect ==-1)
     perror("Conexion no aceptada");
  else{
      long port = ntohs(client.sin_port);

      int ipAddr = client.sin_addr.s_addr;
      char ip[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, &ipAddr, ip, INET_ADDRSTRLEN);

      struct hostent *hp;
      hp=gethostbyaddr( (char *)&ipAddr, sizeof(ipAddr),AF_INET);
      char* nombre = hp->h_name;

      printf("%d:%s:%s\n", port, ip, nombre);
 }
   close(connect);
  }
exit(0);
}
