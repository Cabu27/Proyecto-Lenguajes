#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

/**********************************Lista de  Usuarios***********************************/

/* Entradas: No resive ningún argumento.
 * Salidas: Retorna 0 si se ejecutó correctamente.
 * Restricciones: El archivo que se va a leer debe estar guardado en la misma ubicación
 * que el código, y con el nombre de "configuración.txt".
 * Función: Imprimir en pantalla los nombres de los usuarios con los que se permite iniciar seción.
*/

int ListaUsuarios()
{
	//Variables locales que se van a utilizar para almacenar y manejar los datos.
	char linea [100];
	char usuario[10];
	int puerto;
	int s = 1; //Contador.

	//Perimite abrir el archivo de configuración.
	FILE *archivo;
	archivo = fopen("configuración.txt","r");
	if (archivo == NULL){
		printf("No se pudo abrir el archivo de configuración.");
		exit(1);
	}
	
	printf("\nUsuarios: \n");
	rewind(archivo);
	
	//Ciclo que almacena los datos en variables y luego las imprime en pantalla.
	do{
		fscanf(archivo,"%s %d",usuario,&puerto );
		printf("  %d.  %s\n",s,usuario); s++;
	
	}while(fgets(linea,100,archivo)!= NULL);

	fclose(archivo); //Cierra el archivo de configuración.
	return 0;
}

/**********************************Buscar un Usuario**********************************/

// Variables Globales para manejar los datos del Usuario que Inició Seción.
char nombreU[10];
int puertoU;

/* Entradas: Recibe un int como argumento que representa el nombre del Usuario que
 *  quiere Iniciar Seción.
 * Salidas: Retorna 0 si se ejecutó correctamente.
 * Restricciones: El archivo que se va a leer debe estar guardado en la misma ubicación
 * que el código, y con el nombre de "configuración.txt".
 * Función: Almacenar los datos del usuario (nombre y puerto) en las variables globales 
 * para la utilización de las mismas en el resto del código. 
*/

int BuscaUsuario(int NombUsuario )
{
	char linea [100];

	//Perimite abrir el archivo de confuración.
	FILE *archivo;
	archivo = fopen("configuración.txt","r");
	if (archivo == NULL){
		printf("No se pudo abrir el archivo de configuración");
		exit(1);
	}

	rewind(archivo);
	int s = 1; // Contador.
	
	/*Ciclo que almacena los datos en variables, esos datos se modifican por cada 
	* itereción del ciclo,en caso de encontrar al usuario se hace un break y las 
	* variables globales mantendrán los datos del usuario de la última iteración.*/
	
	do{
		fscanf(archivo,"%s %d",nombreU, &puertoU );
		if (NombUsuario == s){
			break;}
		s++;
		}while(fgets(linea,100,archivo)!= NULL);

	fclose(archivo); //Cierra el archivo de configuración.
return 0;
}

/*********************************Agregar un Contacto************************************/

/* Entradas: No resive ningún argumento.
 * Salidas: Retorna 0 si se ejecutó correctamente.
 * Restricciones: El puerto que se ingresa debe ser un int.
 * Función: Agregar un contacto nuevo a la lista de contactos, solicita los 
 * datos necesarios del contacto.
 */

int AgregarContacto()
{
	//Variable locales para almacenar los datos del contacto.
	char NombContacto[50];
	char IPcontacto[50];
	int PuertoContacto;
	
	//Solicitud y almacenamiento de los datos del contacto.
	printf("%c[%d;%d;%dm\n\tAÑADIR CONTACTO.!!\n", 0x1B, 34,33,32);
	printf("%c[%dm", 0x1B, 0);
	printf("Ingrese el nombre de usuario:   ");
	scanf("%s",NombContacto);
	printf("Ingrese la IP:   ");
	scanf("%s",IPcontacto);
	printf("Ingrese el puerto:   ");
	scanf("%d",&PuertoContacto);

	//Guarda los datos del contacto en el archivo para no perderlos.
	FILE *archivo1;
	archivo1 = fopen("contactos.txt","a");
	fprintf(archivo1,"%s %s %d\n",NombContacto,IPcontacto,PuertoContacto);
	FILE *archivo2;
	archivo2 = fopen("configuración.txt","a");
	fprintf(archivo2,"%s %d\n",NombContacto,PuertoContacto);
	
	fclose(archivo1);//Cierra el archivo de contactos.
	fclose(archivo2);//Cierra el archivo de configuración.
	
	printf("%c[%d;%d;%dm\n\t%s es ahora tu Amigo.!\n",0x1B, 34,33,32,NombContacto);
	printf("%c[%dm", 0x1B, 0);
	
return 0;
}

/**********************************Lista de Contactos**********************************/

/* Entradas: No resive ningún argumento.
 * Salidas: Retorna 0 si se ejecutó correctamente.
 * Restricciones: El archivo que se va a leer debe estar guardado en la misma ubicación
 * que el código, y con el nombre de "contactos.txt".
 * Función: Imprimir en pantalla la lista de contactos con los que se puede conectar.
*/

int ListaContactos()
{
	//Variables locales que se van a utilizar para almacenar y manejar los datos.
	char linea [100];
	char usuario[10];
	char IP[20];
	int puerto;
	int s = 1; //Contador.

	//Perimite abrir el archivo de contactos.
	FILE *archivo;
	archivo = fopen("contactos.txt","r");
	if (archivo == NULL){
		printf("no se pudo");
		exit(1);
	}
	
	printf("%c[%d;%d;%dm\nLista de Contactos: \n", 0x1B, 34,33,33);
	printf("%c[%dm", 0x1B, 0);
	rewind(archivo);
	
	//Ciclo que almacena los datos en variables y los imprime en pantalla.
	do{
		fscanf(archivo,"%s %s %d",usuario, IP, &puerto );
		printf("  %d. Usuario: %s  IP: %s  Puerto: %d\n",s,usuario, IP, puerto); 
		s++;
	}while(fgets(linea,100,archivo)!= NULL);

	fclose(archivo); //Cierra el archivo de contactos.
	return 0;
}

/**********************************Buscar un Contacto************************************/

// Variables Globales para manejar los datos del Contacto con el que se va a conectar.
char usuario[10];
char IP[20];
int puerto;

/* Entradas: Recibe un int como argumento que representa el nombre del Contacto con el 
 * quiere conectar.
 * Salidas: Retorna 0 si se ejecutó correctamente.
 * Restricciones: El archivo que se va a leer debe estar guardado en la misma ubicación
 * que el código, y con el nombre de "contacto.txt".
 * Función: Almacenar los datos del contacto (nombre, IP y puerto) en las variables globales 
 * para la utilización de las mismas en el resto del código. 
*/

int BuscarContacto(int contacto)
{
	char linea [100];

	//Permite abrir el archivo de contactos.
	FILE *archivo;
	archivo = fopen("contactos.txt","r");
	if (archivo == NULL){
		printf("no se pudo");
		exit(1);
	}

	rewind(archivo);
	int s = 1;//Contador.
	
	/*Ciclo que almacena los datos en variables, esos datos se modifican por cada 
	* itereción del ciclo,en caso de encontrar al contacto se hace un break y las 
	* variables globales mantendrán los datos del contacto de la última iteración.*/
	
	do{
		fscanf(archivo,"%s %s %d",usuario, IP, &puerto );
		if (s == contacto){
			break;}
		s++;
	}while(fgets(linea,100,archivo)!= NULL);

	fclose(archivo);//Cierra el archivo de contactos.
return 0;
}

/*********************************** Código Sockets ************************************/

//Variables Globales para el manejo de los Sockets.
int Descriptor;
int DescripConect;

/************************************* SERVIDOR ***************************************/

/* Entradas: No recibe ningún argumento. 
 * Salidas: Retorna 1 si se ejecuta correctamente y -1 en caso de error.
 * Restricciones: Se debe conectar un cliente a la IP y puerto de servidor para 
 * que la conexión se realice.*/

 int Servidor(){
	 
	//Apertura del Socket Servidor.
	struct sockaddr_in direccion;
	Descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (Descriptor <0)
	{	perror ("Error.!");
	 	return -1; }
	
	direccion.sin_family = AF_INET; //Tipo de conexión.
	direccion.sin_port = htons (puertoU); //Número del puerto.
	direccion.sin_addr.s_addr =htonl(INADDR_ANY); //Dirección IP del cliente.
	//(INADRR_ANY: Atiende a cualquiera)

	//Avisa al SO que se ha abierto un socket y que se quiere asociar al programa.
	int Bind = bind(Descriptor, (struct sockaddr *)&direccion,sizeof (direccion));
	if (Bind<0)
	{	perror ("Error.!");
		return -1; }
		
	//Comienza a atender la conexión.
	listen (Descriptor, 3);
	
	//Tendrá la dirección y demás datos del cliente que se ha conectado.
	struct sockaddr_in Cliente;
	//La longuitud útil del struct.
	socklen_t cliente_largo;
	cliente_largo = sizeof (struct sockaddr_in); 
	
	//Pide y acepta las conexiones de clientes al sistema.
	DescripConect = accept (Descriptor, (struct sockaddr *)&Cliente, &cliente_largo);
	if (DescripConect < 0)
	{   perror ("Error.!");
		return -1; }
	printf("\nSe ha conectado..!\n");
	
return 1;
}

/************************************* CLIENTE ****************************************/

/* Entradas: No recibe ningún argumento. 
 * Salidas: Retorna 1 si se ejecuta correctamente y -1 en caso de error.
 * Restricciones: Debe haber un servidor esperando una conexión para que acepte al cliente.
*/

int Cliente(){
	
	struct sockaddr_in direccion;
	direccion.sin_family = AF_INET; //Tipo de conexión.
	direccion.sin_port = htons(puerto); //Número del puerto.
	direccion.sin_addr.s_addr = inet_addr(IP); //Dirección IP del servidor.
	//(inet_addr: conviere la direccion IP en un long int sin signo.)
	
	//Apertura del Socket Cliente
	Descriptor = socket (AF_INET, SOCK_STREAM, 0);
	if (Descriptor <0)
	{	perror ("Error.!");
	 	return -1; }
	
	int Connect;
	//Solicita conexión con el servidor.
	Connect=connect (Descriptor, (struct sockaddr *)&direccion, sizeof (direccion));
	if (Connect <0)
	{   perror ("Error.!");
	 	return -1; }
	 	
	printf ("\nSe ha Conectado.! \n");
return 1;
}

/*************************************** MENU ****************************************/

//Variables Globales para el manejo de mensajes.
char MsjSend [50];
char MsjRecv[50];
char* mens = "chao"; //Mensaje de salida.

/* Entradas: No recibe ningún argumento.
 * Salidas: Retorna 1 si se ejecuta correctamente.
 * Restricciones: En los casos en que se solicita que se ingrese una opción,
 * o se realiza una pregunta, se debe digitar solo integers.
 * Función: Mostrar y ejecutar las diferentes opciones del CHAT.
*/ 

 int Menu()
{
	int opcion;
	printf("%c[%d;%d;%dm\n\tMENU Inicio:", 0x1B, 34,33,36);
	printf("%c[%dm", 0x1B, 0);
	printf("\n1. Conectarse con un amigo.\n");
	printf("2. Agregar contactos.\n");
	printf("3. Cerrar Seción.\n");
	printf("\nIngrese una opción: ");
	scanf("%d",&opcion);
	//Conectarse con un amigo.
	if (opcion == 1)
	{
		ListaContactos();
		int modo;
		printf("Como desea continuar?\n");
		printf("\t1. Servidor \n \t2. Cliente\n");
		scanf("%d",&modo);
		//Modo Servidor.
		if (modo == 1)
		{	int amigo;
			printf("\nCon quién se quiere conectar?  ");
			scanf("%d",&amigo);
			BuscarContacto(amigo);
			printf("\nTu amig@: %s",usuario);
			Servidor();
			// Implementación de la función FORK().
			int servicio= fork();
			while (servicio > 0)
			{	if (servicio != 0)
				{	//Recibe lo que envia el cliente.
					recv(DescripConect,MsjRecv,sizeof(MsjRecv),0);
					printf("%c[%d;%d;%dm\n-%s: %s ", 0x1B, 34,33,33,usuario, MsjRecv);
					printf("%c[%d;%d;%dm\n Mensaje recibido.! \n", 0x1B, 34,33,31);
					if ((strncmp(MsjRecv,mens,5))==0) //Si se recibe el mensaje de salida "chao".
					{	printf("%c[%d;%d;%dm\n %s se ha Desconectado.!\n", 0x1B, 34,33,31,usuario);
						printf("%c[%dm", 0x1B, 0);
						int elige;
						printf("\nQue desea hacer.?\n");
						printf("   1.Volver al Menu.\n   2.Salir. \n");
						printf("Ingrese una opción: ");
						scanf("%d",&elige);
						if (elige == 1) //Volver al menú.
						{	close(DescripConect);
							Menu();}
						else //Salir
						{	exit(1);}
					}
					//Envía el msj al cliente.
					printf("%c[%d;%d;%dm\n-%s: \t", 0x1B, 34,33,32,nombreU);
					scanf("%s",MsjSend);
					send(DescripConect, MsjSend, sizeof(MsjSend), 0);
					printf("%c[%d;%d;%dmMensaje enviado.!\n", 0x1B, 34,33,31);
					if ((strncmp(MsjSend,mens,5))==0)//Si envía el mensaje de salida "chao".
					{	printf("%c[%d;%d;%dm\n %s. Te has Desconectado.!\n", 0x1B, 34,33,31,nombreU);
						printf("%c[%dm", 0x1B, 0);
						int elige;
						printf("\nQue desea hacer.?\n");
						printf("   1.Volver al Menu.\n   2.Salir. \n");
						printf("Ingrese una opción: ");
						scanf("%d",&elige);
						if (elige == 1) //Volver al menú.
						{	close(DescripConect);
							Menu();}
						else //Salir
						{	exit(1);}
					}
				}
			}
		}
		//Modo Cliente
		else
		{	int amigo;
			printf("\nCon quién se quiere conectar?  ");
			scanf("%d",&amigo);
			BuscarContacto(amigo);
			printf("\nTu amig@: %s",usuario);
			Cliente();
			//Implementación de la función FORK().
			int servicio = fork();
			while(servicio > 0)
			{
				if (servicio != 0)
				{
					//Envía el mensaje al servidor.
					printf("%c[%d;%d;%dm\n-%s: \t", 0x1B, 34,33,32,nombreU);
					scanf("%s",MsjSend);
					send(Descriptor, MsjSend, sizeof(MsjSend), 0);
					printf("%c[%d;%d;%dmMensaje enviado.!\n", 0x1B, 34,33,31);
					if ((strncmp(MsjSend,mens,5))==0)//Si envía el mensaje de salida "chao".
					{	printf("%c[%d;%d;%dm\n %s. Te has Desconectado.!\n", 0x1B, 34,33,31,nombreU);
						printf("%c[%dm", 0x1B, 0);
						int elige;
						printf("\nQue desea hacer.?\n");
						printf("   1.Volver al Menu.\n   2.Salir. \n");
						printf("Ingrese una opción: ");
						scanf("%d",&elige);
						if (elige == 1) //Volver al menú.
						{	close(Descriptor);
							Menu();}
						else //Salir
						{	exit(1);}
					}
					//Recibe lo que envía el servidor.
					recv(Descriptor,MsjRecv,sizeof(MsjRecv),0); 
					printf("%c[%d;%d;%dm\n-%s: %s ", 0x1B, 34,33,33,usuario, MsjRecv);
					printf("%c[%d;%d;%dm\nMensaje recibido.!\n", 0x1B, 34,33,31);
					if ((strncmp(MsjRecv,mens,5))==0)//Si recibe el mensaje de salida "chao".
					{	printf("%c[%d;%d;%dm\n %s se ha Desconectado.!\n", 0x1B, 34,33,31,usuario);
						printf("%c[%dm", 0x1B, 0);
						int elige;
						printf("\nQue desea hacer.?\n");
						printf("   1.Volver al Menu.\n   2.Salir. \n");
						printf("Ingrese una opción: ");
						scanf("%d",&elige);
						if (elige == 1) //Volver al menú.
						{	close(Descriptor);
							Menu();}
						else //Salir
						{	exit(1);}
					}
				}
			}
		}
	}
	//Agregar Contactos
	else if (opcion == 2)
	{
		AgregarContacto();
		int elige;
		printf("\nQue desea hacer.?\n");
		printf("   1.Volver al Menu.\n   2.Salir. \n");
		printf("Ingrese una opción: ");
		scanf("%d",&elige);
		if (elige == 1) //Volver al menú.
		{	Menu();}
		else //Salir.
		{	exit(1);}
	}
	else
	{
		exit(1); //Salir.
	}
return 1;
}

/*************************************** MAIN ****************************************/

/* Entradas: Es la función principal, no recibe ningún argumento.
 * Salidas: Retorna 1 si se ejecuta correctamente.
 * Restricciones: En los casos en que se solicita que se ingrese una opción,
 * se debe digitar solo integers.
 * Función:Indica el proceso de ejecución del programa, donde inicia y donde finaliza.
 */

int main()
{
	printf("%c[%d;%d;%dmBienvenido al CHAT CAM..!\n", 0x1B, 34,33,36);
	printf("%c[%dm", 0x1B, 0);
	ListaUsuarios();
	int nombre;
	printf("\nSeleccione su Usuario: ");
	scanf("%d",&nombre);
	BuscaUsuario(nombre);
	printf("%c[%d;%d;%dm\n-Seción Iniciada..! \n \nHOLA %s.!!\n", 0x1B, 34,33,35,nombreU);
	Menu();
	return 1;
}
