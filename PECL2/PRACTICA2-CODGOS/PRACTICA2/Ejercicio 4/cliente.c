/*  cliente.c   */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) 
{
  int i,c,sd;
  struct sockaddr_in server_addr;
  struct hostent *hp;
  long int num[2], res;

  if (argc!=3)
    {
     fprintf(stderr, "Uso: %s primer_sumando segundo_sumando\n", argv[0]);
     return 1;
    }
  sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	
	
  bzero((char *)&server_addr, sizeof(server_addr));
  hp = gethostbyname ("localhost");
        
  memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(56789);	
	
  /* se establece la conexión */
  connect(sd, (struct sockaddr *) &server_addr, sizeof(server_addr));

  num[0]=htonl(atoi(argv[1]));
  num[1]=htonl(atoi(argv[2]));

  write(sd, (char *) num, 2 *sizeof(long int));	/*envía la petición*/

  for(i=0;
      i<sizeof(long int)&&(c=read(sd,((char *)&res)+i,sizeof(long int)-i))>0;i+=c);
   /* recibe la respuesta */       
	
  printf("El resultado es:  %d \n", ntohl(res));
  close (sd);

  return 0;
}
