#!/bin/bash

for ((i=1;i<100;i++))
do
    ./client &
done
wait
