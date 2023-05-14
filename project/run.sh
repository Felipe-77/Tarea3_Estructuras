#!/bin/bash

echo "compilation with gcc -Wall -Wextra -Werror backend.c mainc -o output"
gcc -Wall -Wextra -Werror backend.c main.c lista/list.c map/map.c -o output


echo "execution..."
./output