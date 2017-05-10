#!/bin/bash
# Autor: Marlene Vásquez

#----------------Aulas-----------------------------
# Creamos un directorio en /tmp donde almacenar  
#mkdir /tmp/UML 
# Copiamos los archivos del servidor al directorio temporal
#cp /fenix/depar/lsi/UML/*.gz /tmp/UML
# Extraemos los archivos mediante la herramienta gunzip
#gunzip  /tmp/UML/*.gz
# Cambiamos al directorio /tmp/UML
#cd /tmp/UML
# cambiamos los permisos
#chmod 700 kernel32-3.0.4
# Ejecutamos 
#./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
# -----------------pc personal---------------------------------
echo "creando la carpeta tmp/UML"
mkdir /tmp/UML 
echo "realizando la copia"
cp UML/*.gz  /tmp/UML
echo "realizando la extraccion de archivos"
gunzip  /tmp/UML/*.gz
#este paso no es necesario para la actividad 
unzip  paquetes 
cp mount_paquetes.sh paquetes
mkdir paquetes/script
cp script/* paquetes/script
#------------------------------------------

echo "Cambio de directorio /tmp/UML"
cd /tmp/UML
echo "ejecutando"
chmod 700 kernel32-3.0.4
./kernel32-3.0.4  ubda=./Fedora14-x86-root_fs mem=1024m

#root sin contraseña
