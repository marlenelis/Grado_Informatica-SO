#!/bin/bash 
# actividad 3.2 
#Nombre: prueba_proceso.sh
#Autor: Marlene Vásquez
#echo "parametro : $*" 
x=0 
while [[ $x -lt 100000000 ]]; do 
	let aux=823*746 
	let x=x+1 
done 
echo "el valor de la variable es:  $x"
