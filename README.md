# 4 Preguntas de Pensamiento Crítico
## Memoria: ¿Por qué usar apuntadores reduce 75% de memoria con 10M registros?
Al usar apuntadores en vez de copiar los elementos varias veces, logramos reducir la memoria ya que los apuntadores a comparación de los objetos o structs personas siempre ocupa 8 bytes, mientras que hacer una copia de persona al guardar varios campos de multiples bytes ocupa más espacio en memoria.
## Datos: Si el calendario depende de dígitos del documento, ¿cómo optimizar búsquedas por grupo?
Ya que las busquedas de personas por grupo puede ser una operación que es probable que se repita más de una vez lo mejor es precalcular el grupo y guardarlo en un atributo de la persona, asi sacrificamos más uso de memoria a cambio de velocidad en la ejecución del código, esto nos permite acceder al grupo de cada persona accediendo a un atributo y no calcularlo cada que queramos ver los grupos de todas las personas.


## Localidad: ¿Cómo afecta el acceso a memoria al usar array de structs vs. vector de clases?

El acceso a las variables guardadas dentro de un array tanto como en un vector es igual, ya que ambas estructuras acceden a sus elementos a traves de aritmetica de punteros, por lo cual en ambos esta operación es constante O(1), la diferencia entre ambas estructuras de datos es que por lo general los arrays se guardan en la memoria stack(excepto si se inician con la palabra new), mientras que los vectores se guardan en la memoria heap. La diferencia entre los structs y las clases es el acceso a los atributos. En las structs los atributos son publicos, mientras que en las clases son privados y se utilizan getters y setters para acceder a dichos atributos, lo cual puede hacer que las clases ocupen un poco mas de memoria que las structs. 

## Escalabilidad (Consulta): Si los datos exceden la RAM, ¿cómo usar mmap o memoria virtual?
Cuando los datos exceden la RAM, usar (mmap) o memoria virtual, que permite mapear un archivo en el espacio de direcciones del proceso como si fuera un array en memoria; de esta forma, el sistema operativo solo carga en RAM las páginas del archivo que realmente se acceden, evitando cargar todo de una vez. Esto reduce el consumo de memoria, evita copias innecesarias a buffers intermedios y permite trabajar con archivos muy grandes (decenas de GB) sin sobrepasar la RAM, siempre que los accesos estén organizados (preferiblemente secuenciales) para minimizar page faults y no caer en thrashing. El flujo típico es abrir el archivo con open(), obtener su tamaño con fstat(), y luego mapearlo en memoria con mmap(), que devuelve un puntero void* al inicio del área mapeada. Ese puntero puede reinterpretarse como el tipo de dato deseado (por ejemplo, char* para recorrer el archivo como un arreglo de caracteres). Una vez mapeado, se accede al contenido como si fuera un array en RAM, pero en realidad el SO gestiona la carga de las páginas necesarias desde disco. Finalmente, se libera con munmap() y se cierra el descriptor de archivo. En proyectos modernos de C++, se suelen encapsular estas llamadas en clases RAII para asegurar el cierre y liberación correctos sin fugas de recursos.


## Analisis Resultados
| Función | Memoria (Struct) | Memoria (Class) | Tiempo (Struct) | Tiempo (Class) |
| --- | --- | --- | --- | --- |
| Crear datos | 316096 KB | 308948 KB | 1314.55 ms | 511.994 ms |
| Mostrar resumen | 0 KB | 0 KB | 20304.95 ms | 22021.70 ms |
| Mostrar personas más longeva del país(Referencia) | 0 KB | 0 KB | 68.90 ms | 16.47 ms |
| Mostrar personas más longeva del país(Valor): | 14460 KB | 14472 KB | 376.26 ms | 344.01 ms  |
| Mostrar personas más longevas por ciudad (Referencia): | 0 KB | 0 KB | 848.17 ms | 174.19 ms |
| Mostrar personas más longevas por ciudad (Valor): | 4 KB | 14520 KB | 1138.03 ms | 411.17 ms  |
| Mostrar personas más rica del país(Referencia) | 0 KB | 0 KB | 24.87 ms | 20.53 ms |
| Mostrar personas más rica del país(Valor) | 14472 KB | 14572 KB | 248.95 ms | 228.07 ms |
| Mostrar personas más ricas por ciudad (Referencia) | 0 KB | 0 KB | 585.14 ms | 92.58 ms |
| Mostrar personas más ricas por ciudad (Valor) | 8 KB | 8 KB | 862.84 ms | 327.53 ms |
| Mostrar personas más ricas por Grupo (Referencia) | 0 KB | 0 KB | 213.59 ms | 38.67 ms |
| Mostrar personas más ricas por Grupo (Valor) | 14548 KB | 14600 KB | 503.52 ms | 261.53 ms |
| Listar personas por Grupo (Referencia) | 8092 KB | 8820 KB | 21068.42 ms | 19249.19 ms |
| Listar personas por grupo (Valor) | 345920 KB | 345112 KB | 21818.12 ms | 20559.33 ms |
| Mostrar personas más endeudada del país(Referencia) | 0 KB | 0 KB | 19.22 ms | 12.41 ms  |
| Mostrar personas más endeudada del país(Valor) | 14516 KB | 14448 KB | 258.89 ms | 220.33 ms |
| Mostrar ciudad con mayor patrimonio(Referencia) | 0 KB | 0 KB | 563.08 ms | 123.89 ms |
| Mostrar ciudad con mayor patrimonio(Valor) | 14572 KB | 14508 KB | 781 ms | 289.657 ms |
| Personas tienen patrimonio superior a 1.000 millones(Referencia) | 0 KB | 0 KB | 6860.65 ms | 7246.99 ms |
| Personas tienen patrimonio superior a 1.000 millones(Valor) | 176292 KB | 175952 KB | 4856.37 ms | 7637.63 ms |
