# Estructura de un makefile. El archivo debe llamarse Makefile
#   objetivo:   dependencias
#       comandos


mserver_http.ej:		mserver.c
	gcc -g -ansi -pedantic $^ -o $@
    
# -g			Incluye la información de depuración
# -ansi			Compila sólo con la norma ANSI
# -pedantic		Es escrupuloso en la verificación de la norma ANSI
# $^   			Se sustituye por una lista separada por espacios que incluye todas las dependencias
# $@    		Se sustituye por el objetivo de la presente regla  



#EJEMPLO DE UTILIZACIÓN
#Ejecutable:	Objeto1.o	Objeto2.o 
#	gcc		Objeto1.o Objeto2.o -o Ejecutable
#												Enlaza los dos objetos para obtener el programa
#												Ejecutable tiene dos dependencias: Objeto1.o y Objeto2.o
#
#Objeto1.o:		Fuente1.c	Cabecera1.h
#	gcc -c 	Fuente1.c
#												Compila el primer archivo fuente y sólo obtiene el objeto
#												Objeto1.o tiene dos dependencias: Fuente1.c y Cabecera1.h
#												Cabecera1.h deberá estar en una línea #include de Fuente1.c
#
#Objeto2.o:		Fuente2.c	Cabecera2.h	
#	gcc -c	Fuente2.c
#												Compila el segundo archivo fuente y sólo obtiene el objeto
#												Objeto2.o tiene dos dependencias: Fuente2.c y Cabecera2.h
#												Cabecera2.h deberá estar en una línea #include de Fuente2.c

