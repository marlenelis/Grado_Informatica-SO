# !/bin/bash
#Nombre: reducelista
#Autor: Marlene Vásquez
head -10 /tmp/listacores >/tmp/aux
head -10 /tmp/aux > /tmp/listacores
rm -f /tmp/aux
