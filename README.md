# ArbolBinario

Una familia de un reino ha estado manteniendo registro de los descendientes del primer rey desde hace años. Cada rey solo ha generado un maximo de dos herederos en todo su reinado, siendo siempre el primogénito en heredar el trono, con casos donde si toda la rama del rey actual llega a desaparecer entonces se asigna como rey el primer primogénito de la rama de su hermano.

La tarea es realizar un programa que permita  realizar las siguientes funciones:

1. Convertir desde un .csv los datos en un arbol binario, el .csv tiene las siguientes columnas:

id,name, last_name, gender, age, id_father, is_dead, was_king, is_king.
Solo hay hombres o mujeres (H o M).
Los valores para was_king, is_king, is_dead es cero o uno. Uno, afirmativo; 0, negativo
2. Mostrar la linea de sucesión actual (solo a los vivos).
3. Asignar un nodo como rey de manera automática en caso de morir el rey actual, las condiciones de asignación son:
Si el rey murió y tiene hijos, el rey es el primer primogénito vivo encontrado en su árbol.
Si el rey murió y no tiene hijos, el rey es el primer primogénito vivo encontrado del árbol de su hermano.
Si el hermano esta vivo y no tiene hijos, el hermano se vuelve rey.
Si el rey murió y no tiene hermanos ni hijos, el rey es el primer primogénito vivo encontrado del árbol de su tío.
si su tío esta vivo y no tiene hijos, su tío se vuelve rey.
Si el rey murió y no se puede hallar ni su tío ni su hermano, buscar el primer ancestro con dos hijos y elegir como rey el primer primogénito vivo del árbol del ancestro.
Si todos los primogénitos están muertos, seguir las mismas reglas para los hijos segundos, empezando desde el primero hallado desde el rey actual, es decir, tratar a los segundos como primogénitos, hasta que se logre cumplir otra vez la condición de existir un primogénito puro.
Si un rey paso de los 70 años, la corona se pasa al primer primogénito vivo de su árbol.
4. Cambiar los datos de cualquier nodo del árbol, menos el id y id del padre.
