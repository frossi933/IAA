#!/bin/bash

echo "set pointsize 3;plot "< awk '{if($3 == \"red\") print}' $1" u 1:2 t "red" w p pt 2, \
     "< awk '{if($3 == \"green\") print}' $1" u 1:2 t "green" w p pt 2"
