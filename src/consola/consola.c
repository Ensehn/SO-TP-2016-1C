/*
 * consola.c
 *
 *  Created on: 16/4/2016
 *      Author: utnso
 */

#include <stdio.h>
#include <stdlib.h>
#include "../otros/handshake.h"
#include "../otros/sockets/cliente-servidor.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <commons/string.h>
#include <string.h>
#include "../otros/handshake.h"
#include "../otros/header.h"
#include "../otros/sockets/cliente-servidor.h"
int cliente;

void conectarANucleo()
{
	direccion = crearDireccionParaCliente(8080);
	cliente = socket_w();
	connect_w(cliente, &direccion);
}

int getHandshake()
{
	char* handshake = recv_nowait_ws(cliente,1);
	return charToInt(handshake);
}

void handshakear()
{
	char *hand = string_from_format("%c%c",HeaderHandshake,SOYCONSOLA);
	send_w(cliente, hand, 2);

	printf("Consola handshakeo\n");
	if(getHandshake()!=SOYNUCLEO)
	{
		perror("Se esperaba que la consola se conecte con el nucleo.\n");
	}
	else
	printf("Consola recibio handshake de Nucleo.\n");
}

int main(int argc, char* argv[])
{
	FILE* programa;
	char* path=NULL;
	printf("soy consola\n");
	if(argc==1)
	{
		printf("Ingresar archivo ansisop: ");
		scanf("%s",path);
	}
	else if(argc==2)
	{
		path = argv[1];
		free(argv[1]);
	}
	else
	{
		printf("Muchos parametros :C\n");
		printf("No poner parametros o poner solo el nombre del archivo a abrir");
		return 1;
	}
	programa = fopen(path,"r");
	free(path);

	conectarANucleo();
	printf("Conexion al nucleo correcta :).\n");
	handshakear();
	printf("Fin exitoso");
	fclose(programa);
	return 0;
}

