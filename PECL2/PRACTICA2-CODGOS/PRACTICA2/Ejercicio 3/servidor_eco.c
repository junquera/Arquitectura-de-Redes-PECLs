/*  servidor_eco.c   */

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TAM 64

void traza_estado(const char *mensaje)
 {
	printf("\n------------------- %s --------------------\n", mensaje);
	system("netstat -at | head -2 | tail -1");
	system("netstat -at | grep 56789");
	printf("---------------------------------------------------------\n\n");
  }

int main(int argc, char *argv[])
{
	int s, s_conec, leido;
	unsigned int tam_dir;
	struct sockaddr_in dir, dir_cliente;
	char buf[TAM];
	int opcion=1;

	if ((s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
       {
	   perror("Error creando socket");
	   return 1;
	 }

	/* Para reutilizar puerto inmediatamente */
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opcion, sizeof(opcion))<0)
 	 {
          perror("Error en setsockopt");
          return 1;
        }

	dir.sin_addr.s_addr=INADDR_ANY;
	dir.sin_port=htons(56789);
	dir.sin_family=PF_INET;

	if (bind(s, (struct sockaddr *)&dir, sizeof(dir)) < 0)
      {
	   perror("Error en bind");
	   close(s);
	   return 1;
	 }

	if (listen(s, 5) < 0)
        {
	   perror("Error en listen");
	   close(s);
	   return 1;
	}

	traza_estado("Despues de listen");

	while(1)
 	 {
	  tam_dir=sizeof(dir_cliente);
	  
        if ((s_conec=accept(s, (struct sockaddr *)&dir_cliente, &tam_dir))<0)
           {
		  perror("Eerror en accept");
		  close(s);
		  return 1;
		}

		traza_estado("Despues de accept");
	
		while((leido=read(s_conec, buf, TAM))>0)
            {
		   if (write(s_conec, buf, leido)<0)
                {
		     perror("Error en write");
		     close(s);
		     close(s_conec);
		     return 1;
		     }
		 }
	
		if (leido<0)
             {
		  perror("Error en read");
		  close(s);
		  close(s_conec);
		  return 1;
		 }
		close(s_conec);
		traza_estado("Despues de cierre de conexión");
	   }

	close(s);
	return 0;
}
