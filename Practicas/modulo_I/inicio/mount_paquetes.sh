#!/bin/bash
#esto realizar manualmente en uml
#mkdir paquetes
#sudo mount none paquetes -t hostfs -o <directorio donde estan los paquetes pc anfitrion>
#sudo mount none paquetes -t hostfs -o /home/marlen/A_SO/paquetes
#cd paquetes 
# en pc anfitrion copiar este script en paquetes y ejecutarlo en UML

##################################
#instalar quota
echo "==================================";
echo "instalando QUOTA";
echo "==================================";
rpm -ivh ~/paquetes/libnl-1.1-12.fc14.i686.rpm
rpm -ivh ~/paquetes/tcp_wrappers-7.6-59.fc14.i686.rpm
rpm -ivvh ~/paquetes/quota-3.17-13.fc14.i686.rpm
#instalar systat (mpstat)
echo "==================================";
echo "instalando SYSTAT";
echo "==================================";
rpm -ivh ~/paquetes/sysstat-9.0.6-3.fc13.i686.rpm
# instalar at
echo "==================================";
echo "instalando AT";
echo "==================================";
rpm -ivh ~/paquetes/at-3.1.12-5.fc14.i686.rpm
#arrancar el servicio
service atd start

# Preparación previa a la partición de un dispositivo simulado mediante un archivo
# especial de dispositivo.
#mknod /dev/loop0 b 7 0
#mknod /dev/loop1 b 7 1

#dd if=/dev/zero of=/root/archivo_SA20 bs=2k count=10000
#dd if=/dev/zero of=/root/archivo_SA30 bs=3k count=10000

#losetup /dev/loop0 /root/archivo_SA20
#losetup /dev/loop1 /root/archivo_SA30

#fdisk -l /dev/loop0 /dev/loop1




