# !/bin/sh
#Nombre: actividad_4.13a.sh
# autor: Marlene Vásquez
echo "SHELL=/bin/sh" > ~/SO/crontab-reducelista
echo "PATH=$HOME/SO:$PATH">>~/SO/crontab-reducelista
echo "* * * * *  reducelista.sh">>~/SO/crontab-reducelista
echo '----------------------------------'
echo '     Lanzando CRON'
echo '----------------------------------'
crontab  ~/SO/crontab-reducelista
echo '=========== crontab -l ==========='
crontab -l
echo '----------------------------------'
echo 'contenido de crontab-reducelista'
echo '----------------------------------'
head ~/SO/crontab-reducelista
