#!/bin/bash

service_dir=$(realpath ${PWD}/..)

for ((i=0;i<10;i++))
do
    name=token_client${i}
    docker stop ${name} || true
    docker rm ${name} || true
    docker run -d --name=${name}\
               --network=host \
               -v ${service_dir}:${service_dir} \
               -w ${PWD} \
                golang \
                go run player.go
done
