#!/bin/bash
echo "Tworzenie linkowania z irrKlang.h"
sudo ln -s $PWD/include/irrKlang.h /usr/include/irrKlang.h
echo "Tworzenie linkowania z libIrrKlang.so"
sudo ln -s $PWD/bin/linux-gcc-64/libIrrKlang.so /usr/lib/libIrrKlang.so
echo "Koniec skryptu"
