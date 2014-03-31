#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
char linea [100];
char usuario[10];
char IP[20];
int puerto;
int contador;
int seleccionado;
FILE *archivo;
archivo = fopen("contactos.txt","r");
if (archivo == NULL){
	printf("no se pudo");
	exit(1);
}
rewind(archivo);
contador = 1;
do{
	fscanf(archivo,"%s %s %d",usuario, IP, &puerto );
	printf("%d. Usuario %s IP %s Puerto %d\n",contador,usuario, IP, puerto);
	contador++;
}while(fgets(linea,100,archivo)!= NULL);



printf("Seleccione un numero ");
scanf("%d",&seleccionado );
contador = 1;
rewind(archivo);
do{
	fscanf(archivo,"%s %s %d\n",usuario, IP, &puerto );
	if(seleccionado == contador){
		printf("%d. Usuario %s IP %s Puerto %d\n",contador, usuario, IP, puerto);
		
		

		
	}
	contador++;
}while(fgets(linea,100,archivo)!= NULL);

fclose(archivo);
return 0;
}
