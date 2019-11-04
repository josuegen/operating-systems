#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>

//You can modify this values, and them will be sorted
int t1=10;
int t2=1;
int t3=9;
int t4=8;
int t5=5;

typedef struct estructura_hilo{
	int tiempo_ejec;
	pthread_t hilo;
	struct Hilo *siguiente;
	struct Hilo *anterior;
}Hilo;

typedef struct lista{
	Hilo *primero;
	Hilo *ultimo;
}Lista;

void iniciarLista(Lista *l);
Hilo *crearHilo(int tiempo);
void anadirHilo(Lista *l,int tiempo);
void imprimirListaOrdenada(Lista *l);
Lista *ordenarLista(Lista *l);
void ejecutarHilos(Lista *l);

void *Codigo_HiloN(void *arg)
{
   int tiempo=(int *)arg;
   int i;
   for(i=0;i<tiempo;i++)
   {
      printf("Ejecutando (%d)\n",i+1);
      sleep(1);
   }
   pthread_exit(NULL);
}

int main()
{
	Lista l;
	iniciarLista(&l);
   anadirHilo(&l,t1);
   anadirHilo(&l,t2);
   anadirHilo(&l,t3);
   anadirHilo(&l,t4);
   anadirHilo(&l,t5);
   system("clear");
   printf("---------------------------------------------------\n");
   printf("|                Hilos ordenados                   |\n");
   printf("---------------------------------------------------\n");
   imprimirListaOrdenada(&l);
   printf("\n---------------------------------------------------\n");
   printf("|                Ejecutando Hilos                  |\n");
   printf("---------------------------------------------------\n");
   ejecutarHilos(&l);
   pthread_exit(NULL);
}

void iniciarLista(Lista *l){
   l->primero=NULL;
   l->ultimo=NULL;
}

Hilo *crearHilo(int tiempo){
   Hilo *h;
   h=(Hilo *)malloc(sizeof(Hilo));
   if(h==NULL){
        printf("NO_MEMORY");
    }
    else{
      h->tiempo_ejec=tiempo;
      h->anterior=NULL;
      h->siguiente=NULL;
    }
   return h;
}

void anadirHilo(Lista *l,int tiempo){
   Hilo *h;
   h=crearHilo(tiempo);
   Hilo *aux=l->primero;
   Hilo *aux2=NULL;
   if(aux==NULL){
      l->primero=h;
      l->ultimo=h;
   }
   else if(tiempo <= aux->tiempo_ejec){
      aux->anterior=h;
      h->siguiente=aux;
      l->primero=h;
   }
   else if(tiempo > aux->tiempo_ejec){
      while(aux->siguiente!=NULL){
         aux=aux->siguiente;
         if(aux->tiempo_ejec > tiempo){
            break;
         }
      }
      if(tiempo > aux->tiempo_ejec){
         aux->siguiente=h;
         h->anterior=aux;
         l->ultimo=h;
      }
      else if(tiempo < aux->tiempo_ejec){
         aux2=aux->anterior;
         aux2->siguiente=h;
         h->anterior=aux2;
         aux->anterior=h;
         h->siguiente=aux;
      }
   }
}

void imprimirListaOrdenada(Lista *l){
   Hilo *aux=l->primero;
   int contador=0;
   while(aux!=NULL){
      printf("\n-> Tiempo del proceso %d: %d\n",contador+1,aux->tiempo_ejec);
      sleep(1);
      aux=aux->siguiente;
      contador++;
   }
}

void ejecutarHilos(Lista *l){
   Hilo *aux=l->primero;
   int contador=0;
   while(aux!=NULL){
      printf("\n------ HILO %d ------\n",contador+1);
      pthread_create(&(aux->hilo),NULL,Codigo_HiloN,(void *)aux->tiempo_ejec);
      pthread_join(aux->hilo,NULL);
      sleep(1);
      aux=aux->siguiente;
      contador++;
   }
}
