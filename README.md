# TP1: Crypto-Sockets

## Ezequiel Zbogar - 102216

### Taller de Programación I



### Cliente

​	La primera acción que se lleva a cabo es establecer una conexión con el server (Según la dirección y el puerto que hayan sido especificados), luego se va leyendo la entrada estándar (stdin) de a chunks de 64 bytes los cuales se cargan en un buffer para acto seguido enviarlos al TDA *common_crypter*, que lo cifra dependiendo los argumentos con los que se haya ejecutado el programa (Según el *method* y la *key*). 

​	Una vez cifrado el chunk , se lo envía al server por la conexión previamente establecida, posteriormente se lee otro chunk y así sucesivamente hasta que nos encontramos el EOF. En este caso se cifran y envían los bytes que faltan (El buffer no va a estar lleno) para luego, por protocolo de comunicación, cerrar la conexión y el socket, dando por terminada la interacción entre cliente y servidor

![Client Sequence Diagram](https://github.com/ezezbogar/TP1-Taller/blob/main/Images/client_sequence_diagram.png)

### Server

​	El server comienza haciendo un "bind" del socket aceptador seguido de un "listen" para destinarlo a aceptar conexiones entrantes. Cuando esto ocurre, luego de establecer la conexión con el cliente, recibe mediante el socket peer los bytes que le son enviados por el cliente. De igual forma que con este, los bytes recibidos se guardan en un buffer de 64 bytes que es enviado al TDA *common_crypter* que se encarga de descifrarlos (Segun el *method* y la *key* que hayan sido especificados) y escribirlos en el `stdout` . 

![Server Sequence Diagram](https://github.com/ezezbogar/TP1-Taller/blob/main/Images/server_sequence_diagram.png)

​	Tanto para el cliente como para el servidor el hecho de que el texto se lea de a chunks genera la necesidad de almacenar el "estado" del cifrado, que varia con cada método. Con Vigenere es necesario guardar que posición del la key se sumo/resto al ultimo byte cifrado ya que seria un error comenzar desde la posición cero con cada chunk que se quiere cifrar/descifrar. Con RC4 sucede lo mismo, es necesario almacenar el valor de `i` y `j` para partir de ese estado cuando se quiere comenzar a cifrar un chunk nuevo. 

