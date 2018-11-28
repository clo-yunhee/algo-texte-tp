#!/bin/sh

if [ -f src/test.c ];
then
    mv src/test.c src/test.c.bak;
    mv src/main.c.bak src/main.c;
    echo "Enabled main"
elif [ -f src/main.c ];
then
    mv src/main.c src/main.c.bak;
    mv src/test.c.bak src/test.c;
    echo "Enabled test"
fi
