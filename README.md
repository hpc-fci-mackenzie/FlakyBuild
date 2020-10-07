# Flask-build

Este projeto usa [Cmake](www.cmake.org) para sua configuração.

## Instruções

É recomendável criar um diretório específico para seu `build`

```bash
$ mkdir build
$ cd build
```

Estando nele, você deve executar um desses dois comandos:

* Para configurar um ambiente de compilação para release:

```bash
$ cmake ..

```

* Para configurar um ambiente de compilação para debug:

```bash
$ cmake -DCMAKE_BUILD_TYPE=Debug ..

```

Feito uma dessas duas operações, o próximo passo agora é gerar os binários:


```bash
$ make
```

Para executar o programa basta inserir o comando "./nsa" seguido do arquivo de configuração desejado:
Exemplo:

```bash
$ ./nsa ../data/dataset.conf

```
