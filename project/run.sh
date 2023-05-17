#!/bin/bash

echo "compilation with gcc -Wall -Wextra -Werror backend.c mainc -o output"
gcc -Wall -Wextra -Werror backend.c main.c arraylist/arraylist.c map/map.c heap/heap.c -o output


echo "execution..."
./output