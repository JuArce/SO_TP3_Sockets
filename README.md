# SO_TP3_Sockets
Trabajo Práctico Nr.3: Sockets - 72.11 - Sistemas Operativos - Primer Cuatrimestre 2021

## Autores:
-Arce Doncella , Julian Francisco 60509                         
-Domingues, Paula Andrea 60148                                
-Lombardi, Matias Federico 60527

## Instrucciones de Compilación
Ubicado dentro del directorio donde se descargaron los archivos, ejecutar el comando:

     $ make all 

Esto generará todos los archivos ejecutables necesarios.

## Instrucciones de Ejecución
Para iniciar el servidor, ejecutar:

     $ ./server

Para iniciar el cliente, ejecutar

     $ ./client

## Instrucciones de Testeo
En el caso de querer realizar testeos utilizando Valgrind, cppcheck y pvsStudio Analyzer, ejecutar:

     $ make test 

Lo cual generará tres archivos de lectura, uno para cada rutina de testeos ejecutada, master.valgrind el cual contará con el output de Valgrind, cppoutput.txt correspondiente al cppcheck y report.tasks, el cual corresponde a pvs-studio. Estos archivos se encontrarán en la carpeta "tests", ubicada en el directorio de trabajo.

## Instrucciones de Limpieza
Para eliminar los ejecutables:

     $ make clean 

Para eliminar los resultados de los testeos:

     $ make cleanTest
