###
Запуск
4-5
```sh
gcc client.c -o client
gcc server.c -o server -lrt -lpthread

./server 8000 100 [порт для слиентов и общая сумма наследства]

./client 127.0.0.1 8000 0.1 100  [доля и общая сумма]

./client 127.0.0.1 8001 0.2 100  [доля и общая сумма]

[и так всего 8 клиентов надо запустить по условию] 
```
6-8
```sh
gcc external.c -o external
gcc client.c -o client
gcc server.c -o server -lrt -lpthread

./server 8000 8001 100 [порт для клиентов, порт для внешней программы, сумма наследства]

./external 127.0.0.1 8001 [наблюдатель, если задание на оценку 8 то сколько угодно наблюдателей]

./client 127.0.0.1 8000 0.1 100  [доля и общая сумма]

./client 127.0.0.1 8001 0.2 100  [доля и общая сумма]

[и так всего 8 клиентов надо запустить по условию]
```