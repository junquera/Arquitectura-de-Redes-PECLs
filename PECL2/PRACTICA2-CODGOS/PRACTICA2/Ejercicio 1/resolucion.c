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
 u_long addr;
 struct hostent *hp;
 char **p;
 
 if (argc != 2)
    {
     printf("Uso: %s direccion IP\n",argv[0]);
     exit(1);
    }

 /*Cambia del formato notación de punto a formato binario*/
 if ((addr=inet_addr(argv[1])) == -1 )
    {
     printf("La direccion IP tiene que estar en notacion x.x.x.x \n");
     exit(2);
    }
    
 /*Obtiene una estructura hostent con la información del host dado en binario.*/  
 hp=gethostbyaddr( (char *)&addr, sizeof(addr),AF_INET); 
 
 if (hp==NULL)
    {
     printf("No se pude encontar la informacion sobre el equipo %s\n", argv[1]);
     exit(3);
    }
 
for (p=hp->h_addr_list; *p != 0; p++)
     {
      struct in_addr in;
      memcpy(&in.s_addr, *p, sizeof(in.s_addr));
      /*Pasa el binario de la tabla a in.s_addr porque esa estructura la necesita 
      inet_ntoa, para pasarla a formato notación de punto */
      printf("La dirección IP (%s) corresponde a %s \n", inet_ntoa(in),hp->h_name);
     }
  exit(0);
}
