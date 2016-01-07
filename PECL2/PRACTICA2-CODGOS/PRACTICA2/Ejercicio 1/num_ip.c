/* resolucion.c */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, const char *argv[])
{
 char *addr;
 struct hostent *hp;
 char **p, **p1;

 if (argc != 2)
    {
     printf("Uso: %s nombre equipo\n",argv[0]);
     exit(1);
    }

 addr = argv[1];
 /*Obtiene una estructura hostent con la informaci�n del host dado en binario.*/
 hp=gethostbyname2(addr, AF_INET);

 if (hp==NULL)
    {
     printf("No se pude encontar la informacion sobre el equipo %s\n", argv[1]);
     exit(3);
    }

    for (p=hp->h_addr_list; *p != 0; p++)
         {
          struct in_addr in;
          memcpy(&in.s_addr, *p, sizeof(in.s_addr));

          printf("La direcci�n IP (%s) corresponde a %s \n", inet_ntoa(in), addr);
         }
   for (p1=hp->h_aliases; *p1 != 0; p++)
        {
         printf("El alias (%s) corresponde a %s \n", *p1, addr);
        }
  exit(0);
}
