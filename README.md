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

## Licença e Citação

@INPROCEEDINGS{9073958,<br>
author={J. C. {de Lima Costa} and L. N. {de Castro} and C. {de Paula Bianchini}},<br>
booktitle={2019 XLV Latin American Computing Conference (CLEI)},<br>
title={Sensitivity Analysis of the Negative Selection Algorithm Applied to Anomalies Identification in Builds},<br>
year={2019},<br>
volume={},<br>
number={},<br>
pages={1-6},<br>
}