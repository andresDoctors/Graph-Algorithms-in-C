# Graph-Algorithms-in-C

El objetivo de este proyecto es conseguir soluciones eficientes para los dos siguientes problemas sobre grafos:
- Asignar a cada vertice v un color c(v) de forma tal que no exista ninguna arista xy en el grafo para la cuál se cumpla c(x) == c(y), minimizando en la medida de lo posible la cantidad de colores usados. Complejidad: O(V+E)
- Determinar si el grafo es bipartito o no. Complejidad: O(V+E)

## input

El programa toma grafos expresados en un formato DIMACS simplificado de la siguiente manera:
 
 Las primeras lineas permite de forma opcional tener comentarios empezando con el caracter c
 ```
  c This line is a comment.
  c This one too
  ```
 
 Luego se deben especificar el número de vertices n y el numero de aristas m con el formato `p edge n m`, por ejemplo para un vertice con 6 vertices y 8 aristas:

```
p edge 6 8
```

Por último se deben incluir las aristas siguiendo el formato `e vertice1 vertice2` en donde vertice1, vertice2 son naturales que representan vertices
```
e  1  2
e  1  3
e  2  3
e  2  4
e  3  5
e  4  5
e  4  6
e  5  6
```

Poniendolo todo junto el siguiente archivo
```
c This line is a comment.
c This one too
p edge 6 8
e  1  2
e  1  3
e  2  3
e  2  4
e  3  5
e  4  5
e  4  6
e  5  6
```

representa al siguiente grafo
![alt text](https://raw.githubusercontent.com/andresDoctors/Graph-Algorithms-in-C/main/ExampleFlowNetwork.png)
Los archivos que representan a los grafos se deberán guardar en el directorio `/graphs` con cualquier nombre.

## Output

El programa puede ser compilado ejecutando `>make` desde la terminal de bash y luego ejecutarse con `> ./executable`

Una vez ejecutado el programa se generara dos archivos, en los directorios `\testing\tests.results\greedy`, `testing\tests.results\bipartite` con la solución del primer y segundo problema respectivamente aplicada a cada uno de las entradas en el directorio `\graphs`. Dichos archivos tendrán como nombre la fecha y hora actual con el formato `YYYY-MM-DD.hh-mm-ss`



