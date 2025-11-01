# Programa de Árbol Binario de Búsqueda (ABB)

## Autor
Alejandro Longoria Gonzalez  
Matrícula: 644168

## Descripción
Este programa implementa una estructura de datos de Árbol Binario de Búsqueda (ABB) con todas las operaciones fundamentales y funcionalidades avanzadas, usando recursividad en todas las operaciones.

## Características Implementadas

### 1. Operaciones Fundamentales

#### Inserción
- Inserción recursiva manteniendo la propiedad de ABB
- Los valores menores van al subárbol izquierdo
- Los valores mayores van al subárbol derecho
- Maneja valores duplicados correctamente

#### Búsqueda
- Búsqueda recursiva de un valor específico
- Retorna true si encuentra el valor, false en caso contrario
- Optimizada utilizando la propiedad del ABB

#### Eliminación
Implementa los tres casos de eliminación:
1. **Nodo hoja**: Eliminación directa
2. **Un solo hijo**: Reemplazo por el hijo
3. **Dos hijos**: Reemplazo por el sucesor inorden (mínimo del subárbol derecho)

### 2. Recorridos del Árbol

#### Preorden (Raíz, Izquierda, Derecha)
- Visita primero la raíz
- Útil para copiar árboles o expresiones

#### Inorden (Izquierda, Raíz, Derecha)
- Produce los nodos en orden ascendente
- Característica fundamental de los ABB

#### Postorden (Izquierda, Derecha, Raíz)
- Visita primero los hijos
- Útil para liberar memoria o calcular expresiones

#### Por Amplitud (Nivel por Nivel)
- Usa una cola (queue) para visitar nodos nivel por nivel
- Implementación iterativa

### 3. Propiedades y Métricas

#### Altura
- Calcula la altura del árbol (longitud del camino más largo)
- Usa recursividad para encontrar la altura máxima

#### Conteo de Nodos
- **Total**: Cuenta todos los nodos del árbol
- **Hojas**: Cuenta nodos sin hijos (nodos hoja)
- **Internos**: Cuenta nodos con al menos un hijo

#### Valores Extremos
- **Mínimo**: Valor más pequeño (siempre en el extremo izquierdo)
- **Máximo**: Valor más grande (siempre en el extremo derecho)

### 4. Funciones Avanzadas

#### Verificación ABB
- Verifica si el árbol cumple con la propiedad de ABB
- Valida que todos los nodos cumplan: hijo izquierdo < nodo < hijo derecho

#### Balanceo
- Convierte un árbol desequilibrado en uno balanceado
- Utiliza recorrido inorden para obtener valores ordenados
- Construye un ABB perfectamente balanceado a partir de la lista ordenada
- **Método**: Toma el valor medio como raíz y construye recursivamente los subárboles

#### Visualización
- Muestra la estructura del árbol de forma jerárquica
- Útil para debugging y comprensión del árbol

## Uso del Programa

### Compilación
```bash
g++ -o M644168P1 M644168P1.cpp -std=c++11
```

### Ejecución
```bash
./M644168P1
```

### Menú Principal
1. Insertar elemento
2. Buscar elemento
3. Eliminar elemento
4. Mostrar recorridos
5. Mostrar propiedades del árbol
6. Visualizar árbol
7. Balancear árbol
8. Verificar si es ABB válido
9. Salir

## Ejemplo de Salida

### Árbol Inicial
```
Insertando valores iniciales para demostración...
Insertado: 50
Insertado: 30
Insertado: 70
Insertado: 20
Insertado: 40
Insertado: 60
Insertado: 80
Insertado: 10
Insertado: 35
Insertado: 45
```

### Visualización del Árbol
```
Estructura del Árbol (visualización simple):
        80
    70
        60
50
            45
        40
            35
    30
        20
            10
```

### Recorridos
- **Preorden**: 50 30 20 10 40 35 45 70 60 80
- **Inorden**: 10 20 30 35 40 45 50 60 70 80 (ordenado)
- **Postorden**: 10 20 35 45 40 30 60 80 70 50
- **Por Amplitud**: 50 30 70 20 40 60 80 10 35 45

### Propiedades
- **Altura**: 3
- **Total de nodos**: 10
- **Nodos hoja**: 5
- **Nodos internos**: 5
- **Valor mínimo**: 10
- **Valor máximo**: 80
- **¿Es ABB válido?**: Sí

## Estructura del Código

### Estructura Nodo
```cpp
struct Nodo {
    int valor;
    Nodo* izquierdo;
    Nodo* derecho;
}
```

### Clase ABB
- **Métodos privados**: Funciones recursivas auxiliares
- **Métodos públicos**: Interfaz para el usuario
- **Destructor**: Libera toda la memoria automáticamente

## Complejidad Temporal

| Operación | Complejidad |
|-----------|-------------|
| Insertar | O(h) donde h es la altura |
| Buscar | O(h) donde h es la altura |
| Eliminar | O(h) donde h es la altura |
| Recorridos | O(n) donde n es el número de nodos |
| Altura | O(n) donde n es el número de nodos |
| Conteo | O(n) donde n es el número de nodos |

En el peor caso (árbol degenerado): O(n)
En el mejor caso (árbol balanceado): O(log n)

## Características de Implementación

- ✅ Uso extensivo de recursividad
- ✅ Gestión automática de memoria
- ✅ Validación de operaciones
- ✅ Interfaz de usuario intuitiva
- ✅ Función de visualización
- ✅ Balanceo de árboles
- ✅ Verificación de validez ABB
- ✅ Modo DEBUG activable

## Ventajas de la Implementación

1. **Recursividad**: Código más limpio y fácil de mantener
2. **Gestión de Memoria**: Destructor automático previene memory leaks
3. **Flexibilidad**: Todos los recorridos disponibles
4. **Robustez**: Verificación de validez del ABB
5. **Balanceo**: Capacidad de optimizar la estructura del árbol
6. **Visualización**: Herramienta útil para debugging

## Observaciones

- El programa inicia con valores de demostración (DEBUG = true)
- Todas las operaciones usan recursividad
- La estructura mantiene la propiedad ABB en todas las operaciones
- El balanceo transforma cualquier árbol en uno balanceado
- La verificación ABB asegura la integridad de la estructura

## Notas de Diseño

El diseño sigue los principios SOLID:
- **Single Responsibility**: Cada función tiene una responsabilidad única
- **Open/Closed**: Extensible para nuevas funcionalidades
- **Polimorfismo**: Compatible con diferentes tipos de árboles

La implementación es robusta y maneja todos los casos edge correctamente.
