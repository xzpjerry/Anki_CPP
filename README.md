# Anki Flashcards in CPP
Group project for CIS 330

Coe Daly, Patrick Higgins, Zhipeng Xie

To build and run (using docker):
$ docker pull xzpjerry/mongocxx
$ docker run -it xzpjerry/mongocxx /bin/bash
once in the container:
```
cd root/anki-cpp
git pull
make clean
make all
./study.exe
```
To build and run in your local environment:
Install MongoDB driver (mongocxx) via these instructions

Also requires ncurses, install with package manager: libncurses5-dev libncursesw5-dev

Clone and build the project with make:
```
git clone
make clean
make all
./study.exe
```
