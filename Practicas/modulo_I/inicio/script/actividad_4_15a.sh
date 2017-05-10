# !/bin/sh
#Nombre: actividad_4_15a.sh
#Autor: Marlene Vásquez
find ~ -mtime 1 | cpio -pmduv /tmp/salvados$HOME

