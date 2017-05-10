# !/bin/bash
#Nombre: actividad_4.10a.sh
# autor: Marlene Vásquez
cd /tmp/varios
find ~ -mtime 1 > core_`date +%Y-%j-%T` 
find ~ -mtime 1 > otro_`date +%Y-%j-%T`
