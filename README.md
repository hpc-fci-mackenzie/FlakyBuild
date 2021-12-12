# FlaskBuild
* This solution uses the Negative Selection Algorithm to find Flask Builds.
* This project uses CMake for its configuration.

# Instructions
It is recommended to create a specific directory for your build.
```
$ mkdir build
$ cd build
```
Once there, you must execute one of these two commands:
* To set up a build environment for ```Intel``` compiler:
```
$ cmake ..
```
* To let the setup script decide the best environment for you:
```
$ cmake -DCMAKE_BUILD_TYPE=Debug ..
```
With onne of these two operations done, the next step now is to generate the binaries:
```
$ make
```
Done. Binaries should now be generated in the folders specified by ```Makefile```

To run, given this example setup, just insert any of these commands, in any order:
```
$ ./nsa ../data/dataset.conf
```

# Citação
Para citar o projeto, utilize uma das formas abaixo:
```
J. C. de Lima Costa, L. N. de Castro and C. de Paula Bianchini, "Sensitivity Analysis of the Negative Selection Algorithm Applied to Anomalies Identification in Builds," 2019 XLV Latin American Computing Conference (CLEI), Panama, Panama, 2019, pp. 1-6, doi: 10.1109/CLEI47609.2019.235087.
```

```
@INPROCEEDINGS{9073958,
author={J. C. {de Lima Costa} and L. N. {de Castro} and C. {de Paula Bianchini}},
booktitle={2019 XLV Latin American Computing Conference (CLEI)},
title={Sensitivity Analysis of the Negative Selection Algorithm Applied to Anomalies Identification in Builds},
year={2019},
volume={},
number={},
pages={1-6},}
```
https://doi.org/10.1109/CLEI47609.2019.235087
