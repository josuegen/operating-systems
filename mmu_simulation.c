#include <stdio.h>

int direccionVirtual[5]={0,0,0,0,0};
int direccionFisica[3]={0,0,0};
int direccionContenido[7]={0,0,0,0,0,0,0};
void imprimirTablas();
void convertirDirecciones(int paginaVirtual,int paginaFisica);
void binarioDirVirtual(int num,int contador);
void binarioDirFisica(int num,int contador);
void binarioContenido(int num,int contador);

int main(){
	int paginaVirtual=0;
	int paginaFisica=0;
	int j=0;
	imprimirTablas();
	printf("--> Pagina a mover de la memoria virtual a la memoria fisica :");
	scanf("%i",&paginaVirtual);
	printf("\n--> Pagina a desalojar de la RAM :");
	scanf("%i",&paginaFisica);
	printf("\n\n    --------------------------------------------------\n");
	printf("   |                  CONVERSIONES                    |\n");
	printf("    --------------------------------------------------\n");
	printf("\nDIRECCION MEMORIA VIRTUAL  ->   DIRECCION MEMORIA RAM\n");
	printf("______________________________________________________\n\n");
	for(j=0;j<128;j++){
		binarioDirVirtual(paginaVirtual,0);
		binarioContenido(j,0);
		printf("  ->  ");
		binarioDirFisica(paginaFisica,0);
		binarioContenido(j,0);
		printf("\n");
	}
}

void imprimirTablas(){
	int i=0;
	printf("\n\n    MEMORIA VIRTUAL\n\n");
	for(i=0;i<32;i++){
		if(i<24){
			if(i==22){
				printf("    --------------\n");
				printf("%i  |              |\n",31-i);
			}
			else if(i==23){
				printf("    --------------             MEMORIA FISICA\n");
				printf("%i  |              |\n",31-i);
			}
			else{
				printf("    --------------\n");
				printf("%i |              |\n",31-i);
			}
		}
		else if(i>=24){
			printf("    --------------              -------------\n");
			printf("%i  |              |         %i  |             |\n",31-i,31-i);
		}
	}
	printf("    --------------              -------------\n");
}

void binarioDirVirtual(int num,int contador){
	int aux;
	if(num==0){
		int i=0;
		printf("            ");
		for(i=0;i<5;i++){
			printf("%d",direccionVirtual[i]);
		}
		printf(" ");
		return;
	}
	aux=num%2;
	num=num/2;
	direccionVirtual[4-contador]=aux;
	binarioDirVirtual(num,contador+1);
	//printf("%d",aux);
}

void binarioDirFisica(int num,int contador){
	int aux;
	if(num==0){
		int i=0;
		for(i=0;i<3;i++){
			printf("%d",direccionFisica[i]);
		}
		printf(" ");
		return;
	}
	aux=num%2;
	num=num/2;
	direccionFisica[2-contador]=aux;
	binarioDirFisica(num,contador+1);
	//printf("%d",aux);
}

void binarioContenido(int num,int contador){
	int aux;
	if(num==0){
		int i=0;
		for(i=0;i<7;i++){
			printf("%d",direccionContenido[i]);
		}
		return;
	}
	aux=num%2;
	num=num/2;
	direccionContenido[6-contador]=aux;
	binarioContenido(num,contador+1);
	//printf("%d",aux);
}
