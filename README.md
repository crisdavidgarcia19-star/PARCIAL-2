# Parcial 2 - Sistema de Gestión y Control de Contenedores Portuarios

Proyecto desarrollado en lenguaje C para el Taller 3 individual de Estructuras de Datos.

## Requisitos implementados
- Lista doblemente enlazada: cada contenedor apunta al anterior y al siguiente.
- Inserción con identificador único autoincremental.
- Búsqueda por ID.
- Actualización de tara, peso de carga y costo.
- Cálculo automático del peso total (tara + peso de carga).
- Eliminación con reconexión de enlaces y liberación de memoria (`free`).
- Recorrido desde el inicio hacia el final y desde el final hacia el inicio.
- Liberación de todos los nodos al salir.

## Archivos
- `main.c`: código fuente del programa.
- `README.md`: instrucciones y explicación.
- `Parcial2.pdf`: enunciado original del parcial.

## Cómo compilar y ejecutar

### Windows (MinGW / GCC)
Abre la terminal en esta carpeta y ejecuta:

```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o contenedores.exe
.\contenedores.exe
```

### Linux / macOS
```bash
gcc -std=c11 -Wall -Wextra -pedantic main.c -o contenedores
./contenedores
```

## Cómo probar
1. Selecciona `1` para registrar un contenedor.
2. Ingresa tara, peso de carga y costo. El peso total se calcula automáticamente.
3. Usa `5` y `6` para comprobar los recorridos en ambos sentidos.
4. Usa `2` para buscar por ID.
5. Usa `3` para actualizar los datos.
6. Usa `4` para eliminar un registro.
7. Selecciona `0` para salir y liberar la memoria.

## Estructura de la lista doblemente enlazada

Cada nodo almacena los datos del contenedor y dos enlaces:
- `anterior`: apunta al nodo previo.
- `siguiente`: apunta al nodo posterior.

Los punteros globales `inicio` y `fin` permiten recorrer la lista en ambos sentidos.

