#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

//Estructuras necesarias para el ejercicio
typedef struct Tarea {
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;
    
typedef struct Nodo{
    Tarea T;
    Nodo *Siguiente;
} Nodo;
    
//Declaro las funciones
Nodo *crearListaVacia();
Nodo *cargarTareaPendiente(Tarea t);
void agregarTareaPendiente(Nodo **inicio, Nodo *nodo);

//Programa principal
int main() {
    Nodo *listaDePendientes = crearListaVacia();
    Nodo *listaDeTareasRealizadas = crearListaVacia();

    //Declaro variables
    Tarea tarea;
    int confirmacion = 0, autoincremental = 1000;
    char Buff[MAX];

    //Interfaz de carga de tareas pendientes
    do
    {
        printf("Ingrese los datos de la tarea pendiente: \n");

        printf(" Descripción: ");
        gets(Buff);
        tarea.Descripcion = (char *) malloc ((strlen(Buff) + 1) * sizeof(char));
        strcpy(tarea.Descripcion, Buff);

        printf("\n Duracion (10 - 100): ");
        scanf("%d", &tarea.Duracion);
        getchar();

        tarea.TareaID = autoincremental++;

        //Creo el un nodo y lo agrego a la lista de pendientes
        Nodo *nuevoNodo = cargarTareaPendiente(tarea);
        agregarTareaPendiente(&listaDePendientes, nuevoNodo);
        
        printf("\nDesea ingresar otra tarea pendiente (SI = 1, NO = 0): ");
        scanf("%d", &confirmacion);
        getchar();

    } while (confirmacion != 0);
    
    
    return 0;
}

//Desarrollo las funciones
Nodo *crearListaVacia()
{
    return NULL;
}

Nodo *cargarTareaPendiente(Tarea t)
{
    Nodo *nodo = (Nodo *) malloc (sizeof(Nodo));
    nodo->T = t;
    nodo->Siguiente = NULL;
    return nodo;
}

void agregarTareaPendiente(Nodo **inicio, Nodo *nodo)
{
    nodo->Siguiente = *inicio;
    *inicio = nodo;
}