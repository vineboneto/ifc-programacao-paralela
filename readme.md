## Requerimentos
 - NodeJS 16.x
 - Python 3.10.x
 - Docker

## Configurar

Instalar rabbit

```
$ docker run -it --rm --name rabbitmq -p 5672:5672 -p 15672:15672 rabbitmq:3.10-management
```

## Soluções

 - (Python) Jogar para uma fila em memória e criar 10 threads para conseguir consumir essa fila em memória
 - (NodeJS) Criar 10 Channels no RabbitMQ, onde cada Channel é uma thread e criar um consumidor para channel
