#!/bin/bash
x=4
y=5
let result=x+y
echo $result
let x++
let ++x
echo $x
result=$[ $x + $y ]
echo $result
result=$(( $x + y ))
echo $result
result=$(expr $x + $y)
echo $result

