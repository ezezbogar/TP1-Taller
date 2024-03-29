# TP1: Crypto-Sockets

## Ezequiel Zbogar - 102216

### Taller de Programación I



### Cliente

​	La primera acción que se lleva a cabo es establecer una conexión con el server (Según la dirección y el puerto que hayan sido especificados), luego se va leyendo la entrada estándar (`stdin`) de a chunks de 64 bytes los cuales se cargan en un buffer que acto seguido se envia al TDA *common_crypter*, que lo cifra dependiendo los argumentos con los que se haya ejecutado el programa (Según el *method* y la *key*). 

​	Una vez cifrado el chunk , se lo envía al server por la conexión previamente establecida. Posteriormente se lee otro chunk, y así sucesivamente hasta que nos encontramos el EOF (End of File). En este caso se cifran y envían los bytes que faltan (El buffer no va a estar lleno) para luego, por protocolo de comunicación, cerrar la conexión y el socket, dando por terminada la interacción entre cliente y servidor.

![Client Sequence Diagram](https://github.com/ezezbogar/TP1-Taller/blob/main/Images/client_sequence_diagram.png)

### Server

​	El server comienza haciendo un "bind" del socket aceptador seguido de un "listen" y un "accept" para destinarlo a aceptar conexiones entrantes. Cuando aparece un cliente deseando establecer una conexion con el server esta se lleva a cabo y el server comienza a recibir mediante el socket peer los bytes que le son enviados por el cliente. De igual forma que con este ultimo, los bytes recibidos se guardan en un buffer de 64 bytes que es enviado al TDA *common_crypter* que se encarga de descifrarlos (Segun el *method* y la *key* que hayan sido especificados en los argumentos) y escribirlos en el `stdout` .  Este proceso se lleva a cabo hasta que el cliente finaliza la conexión (Cierra el socket).

![Server Sequence Diagram](https://github.com/ezezbogar/TP1-Taller/blob/main/Images/server_sequence_diagram.png)

​	Tanto para el cliente como para el servidor el hecho de que el texto se lea de a chunks genera la necesidad de almacenar el "estado" en el que se encuentra el cifrado, que varia con cada método. Con Vigenere es necesario guardar que posición del la key se sumo/resto al ultimo byte cifrado ya que seria un error comenzar desde la posición cero con cada chunk que se quiere cifrar/descifrar. Con RC4 sucede lo mismo, es necesario almacenar el valor de `i` y `j` para partir de ese estado cuando se quiere comenzar a cifrar un chunk nuevo. 

- Link al repositorio de GitHub: https://github.com/ezezbogar/TP0-Taller

#### Reentrega

A continuación se listan los cambios realizados para la reentrega:

##### Issue 1: Documentar TDAs y métodos

​	Se agrega documentación a los TDAs

##### Issue 2: Loop de getaddrinfo

​	El loop de candidatos a hacer connect y bind ya está implementado en la biblioteca `common_socket` en los respectivos métodos `socket_connect` y `socket_bind`. En las dos lineas citadas en las cuales solo se hace el getaddrinfo (Se encuentra en la función privada `_get_address` específica para eso, la cual devuelve un `struct addrinfo*`) luego se itera hasta encontrar un candidato para establecer la conexión.

##### Issue 3: No propagar POSIX_C_SOURCE

​	Si bien el issue dice "Quitar `#define _POSIX_C_SOURCE 200112L` del header" no hay ningún header que lo posea.

##### Issue 4: Validar argumentos de main

​	Tanto en `client_main.c` como en `server_main.c` se validan que estén la cantidad de argumentos necesarios. También se movió el loop de lectura de `stdin` a un método `client_run` y el loop de escritura de `stdout` a `server_run`.

##### Issue 5: No incluir headers innecesariamente

​	Se quitaron los headers innecesarios. Ademas se quitaron y se pasaron a las unidades de compilación todos los headers que fueron posibles.

##### Issue 6: Usar static en los métodos "privados"

​	Dentro de cada unidad de compilación se marcaron como "static" los métodos "privados" para que su scope este limitado a ese object file.

##### Issue 7: Reestructurar TDA socket

​	Ahora el TDA socket es el que implementa el `send` y `receive` en los métodos `socket_send` y `socket_recieve` respectivamente.