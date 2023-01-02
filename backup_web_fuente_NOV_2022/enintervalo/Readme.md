Desde la rama Ale, para hacer funcionar las peticiones al servidor

Entrais a la carpeta backup

Entrais en la carpeta enintervalo
Ejecutais el siguiente comando

`make`

Posteriormente
`cp makefile makesol`
`cp makeluna makefile`

Volveis a hacer el make
Finalmente `sudo cp andi.cgi /usr/lib/cgi-bin/ && sudo cp andiluna.cgi /usr/lib/cgi-bin`
Si os da un error de acceso entrais a `/usr/lib/cgi-bin/` y le dais permiso de ejecucion a otros `chmod 701 andi.cgi andiluna.cgi`
Avisadme si teneis algun problema