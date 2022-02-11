# Prt
A small program to easely extract prototypes from .c files.

_Typing this in vim will include every prototypes from srcs/*.c in a .h file, for exemple_
>:r !prt srcs/*.c

## Installation
clone this repository:
```bash
git clone https://github.com/agiraudet/prt
```
compile:
```bash
cd prt
make
```
create a symoblic link for ease of access
```bash
sudo ln -s $PWD/prt /usr/local/bin
```

## Usage
```bash
prt [OPTIONS]... [FILE.C]...
```
|Option|Description|
|------|-----------|
|-s|indent with spaces instead of tabs|
|-n|add a newline between prototypes of differents files|
|-f|print filename before protoypes, adding '//' before it|
|-a|print static fonctions prototype as well|
|-h|display help and exit|

## Exemple
```bash
prt -h
prt -sn foo.c
```
