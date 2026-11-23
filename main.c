/*
 * Parcial 2 - Sistema de Gestion y Control de Contenedores Portuarios
 * Estructura de datos: lista doblemente enlazada.
 * Lenguaje: C
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Contenedor {
    int id;
    float tara;
    float peso_carga;
    float peso_total;
    float costo;
    struct Contenedor *anterior;
    struct Contenedor *siguiente;
} Contenedor;

static Contenedor *inicio = NULL;
static Contenedor *fin = NULL;
static int siguiente_id = 1;

void limpiar_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

float leer_float(const char *mensaje) {
    float valor;
    int resultado;
    do {
        printf("%s", mensaje);
        resultado = scanf("%f", &valor);
        if (resultado != 1 || valor < 0) {
            printf("Dato invalido. Ingrese un numero mayor o igual a cero.\n");
            limpiar_entrada();
        }
    } while (resultado != 1 || valor < 0);
    return valor;
}

int leer_entero(const char *mensaje) {
    int valor;
    while (1) {
        printf("%s", mensaje);
        if (scanf("%d", &valor) == 1) return valor;
        printf("Opcion invalida. Intente nuevamente.\n");
        limpiar_entrada();
    }
}

void mostrar_contenedor(const Contenedor *c) {
    printf("\n----- CONTENEDOR #%d -----\n", c->id);
    printf("Peso vacio (tara): %.2f\n", c->tara);
    printf("Peso de carga:     %.2f\n", c->peso_carga);
    printf("Peso total:        %.2f\n", c->peso_total);
    printf("Precio/costo:      $%.2f\n", c->costo);
}

Contenedor *buscar_por_id(int id) {
    Contenedor *actual = inicio;
    while (actual != NULL) {
        if (actual->id == id) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

void insertar_contenedor(void) {
    Contenedor *nuevo = (Contenedor *)malloc(sizeof(Contenedor));
    if (nuevo == NULL) {
        printf("Error: no hay memoria disponible.\n");
        return;
    }

    nuevo->id = siguiente_id++;
    printf("\nRegistro del contenedor #%d\n", nuevo->id);
    nuevo->tara = leer_float("Ingrese el peso vacio (tara): ");
    nuevo->peso_carga = leer_float("Ingrese el peso de carga: ");
    nuevo->peso_total = nuevo->tara + nuevo->peso_carga;
    printf("Peso total calculado automaticamente: %.2f\n", nuevo->peso_total);
    nuevo->costo = leer_float("Ingrese el precio o costo asociado: ");

    nuevo->anterior = fin;
    nuevo->siguiente = NULL;

    if (inicio == NULL) {
        inicio = nuevo;
    } else {
        fin->siguiente = nuevo;
    }
    fin = nuevo;

    printf("Contenedor registrado correctamente. ID asignado: %d\n", nuevo->id);
}

void buscar_contenedor(void) {
    int id = leer_entero("Ingrese el ID que desea buscar: ");
    Contenedor *encontrado = buscar_por_id(id);
    if (encontrado == NULL) {
        printf("No existe un contenedor con el ID %d.\n", id);
    } else {
        mostrar_contenedor(encontrado);
    }
}

void actualizar_contenedor(void) {
    int id = leer_entero("Ingrese el ID que desea actualizar: ");
    Contenedor *c = buscar_por_id(id);
    if (c == NULL) {
        printf("No existe un contenedor con el ID %d.\n", id);
        return;
    }

    printf("\nDatos actuales:");
    mostrar_contenedor(c);
    printf("\nIngrese los nuevos datos:\n");
    c->tara = leer_float("Nuevo peso vacio (tara): ");
    c->peso_carga = leer_float("Nuevo peso de carga: ");
    c->peso_total = c->tara + c->peso_carga;
    c->costo = leer_float("Nuevo precio o costo: ");
    printf("Contenedor actualizado correctamente.\n");
}

void eliminar_contenedor(void) {
    int id = leer_entero("Ingrese el ID que desea eliminar: ");
    Contenedor *c = buscar_por_id(id);
    if (c == NULL) {
        printf("No existe un contenedor con el ID %d.\n", id);
        return;
    }

    if (c->anterior != NULL) {
        c->anterior->siguiente = c->siguiente;
    } else {
        inicio = c->siguiente;
    }

    if (c->siguiente != NULL) {
        c->siguiente->anterior = c->anterior;
    } else {
        fin = c->anterior;
    }

    free(c);
    printf("Contenedor eliminado y memoria liberada correctamente.\n");
}

void listar_adelante(void) {
    Contenedor *actual = inicio;
    if (actual == NULL) {
        printf("No hay contenedores registrados.\n");
        return;
    }
    printf("\n=== RECORRIDO DESDE EL INICIO ===\n");
    while (actual != NULL) {
        mostrar_contenedor(actual);
        actual = actual->siguiente;
    }
}

void listar_atras(void) {
    Contenedor *actual = fin;
    if (actual == NULL) {
        printf("No hay contenedores registrados.\n");
        return;
    }
    printf("\n=== RECORRIDO DESDE EL FINAL ===\n");
    while (actual != NULL) {
        mostrar_contenedor(actual);
        actual = actual->anterior;
    }
}

void liberar_memoria(void) {
    Contenedor *actual = inicio;
    while (actual != NULL) {
        Contenedor *temporal = actual;
        actual = actual->siguiente;
        free(temporal);
    }
    inicio = NULL;
    fin = NULL;
}

void mostrar_menu(void) {
    printf("\n==============================================\n");
    printf(" SISTEMA DE GESTION DE CONTENEDORES PORTUARIOS\n");
    printf("==============================================\n");
    printf("1. Insertar contenedor\n");
    printf("2. Buscar contenedor por ID\n");
    printf("3. Actualizar contenedor\n");
    printf("4. Eliminar contenedor\n");
    printf("5. Mostrar todos (inicio a fin)\n");
    printf("6. Mostrar todos (fin a inicio)\n");
    printf("0. Salir\n");
}

int main(void) {
    int opcion;
    do {
        mostrar_menu();
        opcion = leer_entero("Seleccione una opcion: ");
        switch (opcion) {
            case 1: insertar_contenedor(); break;
            case 2: buscar_contenedor(); break;
            case 3: actualizar_contenedor(); break;
            case 4: eliminar_contenedor(); break;
            case 5: listar_adelante(); break;
            case 6: listar_atras(); break;
            case 0:
                liberar_memoria();
                printf("Programa finalizado. Memoria liberada.\n");
                break;
            default:
                printf("Opcion no valida. Seleccione del 0 al 6.\n");
        }
    } while (opcion != 0);

    return 0;
}
