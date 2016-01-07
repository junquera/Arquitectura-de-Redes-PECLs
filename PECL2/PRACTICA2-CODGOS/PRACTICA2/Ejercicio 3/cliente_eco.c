/*  cliente_eco.c   */

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define TAM 64

int main(int argc, char *argv[])
 {
	int s, leido;
	struct sockaddr_in dir;
	struct hostent *host_info;
	char buf[TAM];


	while ((leido=read(0, buf, TAM))>0)
 	 {
             if ((s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
             {
                   perror("Error creando socket");
                   return 1;
             }

             host_info=gethostbyname("localhost");
             memcpy(&dir.sin_addr.s_addr, host_info->h_addr, host_info->h_length);
             dir.sin_port=htons(56789);
             dir.sin_family=PF_INET;

             if (connect(s, (struct sockaddr *)&dir, sizeof(dir)) < 0)
             {
                   perror("Error en la conexion");
                   close(s);
                   return 1;
             }
          if (write(s, buf, leido)<0)
            {
               perror("Error en write");
               close(s);
               return 1;
             }
          if ((leido=read(s, buf, TAM))<0)
             {
               perror("Error en read");
               close(s);
               return 1;
              }
	   write(1, buf, leido);
         close(s);
         }
	return 0;
}
