#!/bin/bash

service_dir=$(realpath ${PWD}/..)

docker_run()
{
    name=$1
    docker stop ${name} || true
    docker rm ${name} || true
    docker run --name=${name}\
               --network=host \
               -v ${service_dir}:${service_dir} \
               -w ${PWD} \
                golang \
                go run player.go
}

client_run()
{
    ./client
}

dockers()
{
    for ((i=0;i<50;i++))
    do
        name=token_client${i}
        docker_run ${name} &
    done
    
    wait
}

clients()
{
    go build .
    for ((i=0;i<50;i++))
    do
        client_run &
    done
    
    wait
}

clients
