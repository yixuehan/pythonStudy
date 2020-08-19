#!/bin/bash
if test $UID -ne 0
then
    echo Non root
else
    echo root user
fi
