* Documentar brevemente TDAs (structs) además de los métodos.
* client_client.c: Falta loop entre candidatos de connect (ver ejemplo en `man getaddrinfo`)
* server_server.c: Idem anterior
* server_main.c: Quitar `#define _POSIX_C_SOURCE 200112L`
* client_main.c: Validar al menos que estén la cantidad de argumentos necesarios. Considerar mover loop de lectura de *stdin* a una función *client_run*
* Headers: incluir sólo los necesarios, sobre todos los includes dentro de headers, es preferible que estén en las unidades de compilación (ej: `#include <stdlib.h>` en `common_crypter.h`)
* Usar static en métodos "privados" del tda.

* **Reestructurar TDA socket**: Hay 2 tipos de sockets TCP: "escuchador" (*Listener*), y flujo de datos (*stream*). El escuchador es el del server, es el que hace `bind`, `listen` y `accept`, este último genera sockets Stream.
Los sockets stream son los que hacen comunicación, o sea, `send` y `receive`.
Dicho esto, el TDA socket tiene que tener primitivas `socket_send` y `socket_receive` que implementen los loops de send y recv.
Idealmente tendrían que ser 2 TDAs, pero no es necesario para este TP

