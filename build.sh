#!/bin/bash

name=$(echo $1 | sed "s/.c//")

z88dk-zcc +ti83 -lm -create-app $1 -o $name $2 $3 $4
r=$?
rm -f $name zcc_opt.def *~

exit $r;
