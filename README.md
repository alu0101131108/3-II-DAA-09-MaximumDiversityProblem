# Maximum Diversiy Problem - Diseño y Análisis de Algoritmos.
### Sebastián Daniel Tamayo Guzman.

Compile with ```make``` at /build directory.
Executable will be located at /build under the name main.
Main will output a table with results.

Execute this way: ./main

## Results
Can be found at /output-results directory under the name {algorithm}.txt

## Conclusiones - GRASP
En comparación a la búsqueda local de la entrega anterior, no se aprecia una mejora muy significativa en cuanto a valor de diversidad (z), de hecho en la mayoria de casos se obtiene el mismo resultado. Esto puede deberse a que el espacio de soluciones con el que trata nuestro problema no es de gran tamaño y por tanto encuentra el óptimo global con búsquedas más sencillas. De hecho, noté que en las ejecuciones del GRASP tardaba dos o tres iteraciones en encontrar un valor inmejorable. Por otro lado, el tiempo de CPU si incrementa respecto al obtenido con los algoritmos anteriores. Cabe destacar que algunos resultados para el valor Z en la tabla aparecen con un ligero cambio en los decimales menos significativos, mientras que el subconjunto generado se mantiene igual. Intuyo que esto puede deberse a la precisión en punto flotante, ya que el valor Z es de este tipo.

Enlace al repo: https://github.com/alu0101131108/DAA-P09-MaximumDiversityProblem
