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
    struct Nodo *Siguiente;
} Nodo;
    
//Declaro las funciones
Nodo *crearListaVacia();
Nodo *cargarTareaPendiente(Tarea t);
void agregarTareaPendiente(Nodo **inicio, Nodo *nodo);
void mostrarLista(Nodo **inicio);
Nodo *eliminarTareaPorID(Nodo **inicio, int id);
Nodo *buscarTareaPorID(Nodo *inicio, int id);
Nodo *buscarTareaPorPalabraClave(Nodo *inicio, char *palabra);
void liberarLista (Nodo **inicio);

//Programa principal
int main() {
    Nodo *listaDePendientes = crearListaVacia();
    Nodo *listaDeTareasRealizadas = crearListaVacia();

    //Declaro variables
    Tarea tarea;
    int confirmacion = 0, autoincremental = 1000, ID = 0, eleccion;
    char Buff[MAX], Buff1[MAX];

    //Interfaz de carga de tareas pendientes
    do
    {
        printf("Ingrese los datos de la tarea pendiente: \n");

        printf(" Descripción: ");
        gets(Buff);
        tarea.Descripcion = (char *) malloc ((strlen(Buff) + 1) * sizeof(char));
        strcpy(tarea.Descripcion, Buff);

        do
        {
            printf("\n Duracion (10 - 100): ");
            scanf("%d", &tarea.Duracion);
            getchar();
        } while (tarea.Duracion < 10 || tarea.Duracion > 100);
        
        tarea.TareaID = autoincremental++;

        //Creo el un nodo y lo agrego a la lista de pendientes
        Nodo *nuevoNodo = cargarTareaPendiente(tarea);
        agregarTareaPendiente(&listaDePendientes, nuevoNodo);
        
        printf("\nDesea ingresar otra tarea pendiente (SI = 1, NO = 0): ");
        scanf("%d", &confirmacion);
        getchar();

    } while (confirmacion == 1);

    //Interfaz para elegir qué tareas de pendientes pasar a realizadas
    confirmacion = 0;
    do
    {
        if (listaDePendientes != NULL)
        {
            printf("\nTareas pendientes: \n");
            mostrarLista(&listaDePendientes);
            printf("\nIngrese el ID de la tarea que quiere marcar como realizada: ");
            scanf("%d", &ID);
            
            Nodo *encontrado = eliminarTareaPorID(&listaDePendientes, ID);
            if (encontrado != NULL)
            {
                agregarTareaPendiente(&listaDeTareasRealizadas, encontrado);
            } else
            {
                printf("\nNo se ha encontrado la tarea con el ID ingresado.\n");
            }
        } else
        {
            printf("\nNo hay tareas pendientes.\n");
        }

        printf("¿Quiere marcar como realizada otra tarea? (SI = 1, NO = 0): ");
        scanf("%d", &confirmacion);
        getchar();

    } while (confirmacion != 0);
    
    //Mostrar las listas de tareas pendientes y la de tareas realizadas
    printf("\nTareas pendientes: \n");
    mostrarLista(&listaDePendientes);

    printf("\nTareas realizadas: \n");
    mostrarLista(&listaDeTareasRealizadas);

    //Consultar tareas
    printf("\n¿Como quiere consultar la tarea? (ID = 1, Palabra Clave = 2): \n");
    scanf("%d", &eleccion);
    getchar();
    Nodo *tareaConsultada;

    if (eleccion == 1)
    {
        printf("\nIngrese el ID de la tarea: ");
        scanf("%d", &ID);
        tareaConsultada = buscarTareaPorID(listaDePendientes, ID);

        if (tareaConsultada != NULL)
        {
            printf("\nInfo de la tarea encontrada en pendientes: \n");
            printf("  Descripcion: %s \n", tareaConsultada->T.Descripcion);
            printf("  ID: %d \n", tareaConsultada->T.TareaID);
            printf("  Duración: %d \n", tareaConsultada->T.Duracion);
        } else
        {
            tareaConsultada = buscarTareaPorID(listaDeTareasRealizadas, ID);
            if (tareaConsultada != NULL)
            {
                printf("\nInfo de la tarea encontrada en realizadas: \n");
                printf("  Descripcion: %s \n", tareaConsultada->T.Descripcion);
                printf("  ID: %d \n", tareaConsultada->T.TareaID);
                printf("  Duración: %d \n", tareaConsultada->T.Duracion);
            } else
            {
                printf("No se ha encontrado ninguna tarea con el ID ingresado. \n");
            }
            
        }
    } else if (eleccion == 2)
    {
        printf("Ingrese la palabra clave: ");
        gets(Buff1);
        tareaConsultada = buscarTareaPorPalabraClave(listaDePendientes, Buff1);

        if (tareaConsultada != NULL)
        {
            printf("\nInfo de la tarea encontrada en pendientes: \n");
            printf("  Descripcion: %s \n", tareaConsultada->T.Descripcion);
            printf("  ID: %d \n", tareaConsultada->T.TareaID);
            printf("  Duración: %d \n", tareaConsultada->T.Duracion);
        } else
        {
            tareaConsultada = buscarTareaPorPalabraClave(listaDeTareasRealizadas, Buff1);
            if (tareaConsultada != NULL)
            {
                printf("\nInfo de la tarea encontrada en realizadas: \n");
                printf("  Descripcion: %s \n", tareaConsultada->T.Descripcion);
                printf("  ID: %d \n", tareaConsultada->T.TareaID);
                printf("  Duración: %d \n", tareaConsultada->T.Duracion);
            } else
            {
                printf("No se ha encontrado ninguna tarea con la palabra ingresada. \n");
            }
        }
    }
    
    //Libero la memoria
    liberarLista(&listaDePendientes);
    liberarLista(&listaDeTareasRealizadas);
    
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
    if (*inicio == NULL)
    {
        *inicio = nodo;
    } else
    {
        Nodo *aux = *inicio;
        while (aux->Siguiente != NULL)
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = nodo;
    }  
}

void mostrarLista(Nodo **inicio)
{
    Nodo *actual = *inicio;
    int numeracion = 1;

    while (actual != NULL)
    {
        printf(" %d. Descripcion: %s \n", numeracion, actual->T.Descripcion);
        printf("     ID: %d \n", actual->T.TareaID);
        printf("     Duración: %d \n", actual->T.Duracion);

        actual = actual->Siguiente;
        numeracion++;
    }
}

Nodo *eliminarTareaPorID(Nodo **inicio, int id)
{
    Nodo *nodoAux = (*inicio);
    Nodo *nodoAnt = NULL;
    
    while (nodoAux != NULL && nodoAux->T.TareaID != id)
    {
        nodoAnt = nodoAux;
        nodoAux = nodoAux->Siguiente;
    }
    
    if (nodoAux != NULL)
    {
        if (nodoAux == (*inicio))
        {
            (*inicio) = nodoAux->Siguiente;
        }
        else
        {
            nodoAnt->Siguiente = nodoAux->Siguiente;
        }
        nodoAux->Siguiente = NULL;
    }
    return (nodoAux);
}

Nodo *buscarTareaPorID(Nodo *inicio, int id)
{
    Nodo *aux = inicio;

    while (aux && aux->T.TareaID != id)
    {
        aux = aux->Siguiente;
    }
    return aux;
}

Nodo *buscarTareaPorPalabraClave(Nodo *inicio, char *palabra)
{
    Nodo *aux = inicio;

    while (aux != NULL && strstr(aux->T.Descripcion, palabra) == NULL)
    {
        aux = aux->Siguiente;
    }
    return aux;
}

void liberarLista(Nodo **inicio)
{
    Nodo *actual = *inicio;
    Nodo *aux;

    while (actual != NULL)
    {
        aux = actual;
        actual = actual->Siguiente;
        free(aux->T.Descripcion);
        free(aux);
    }
    *inicio = NULL;
}