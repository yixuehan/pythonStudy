#!/bin/bash

service_dir=$(realpath ${PWD}/..)

docker stop token_server || true
docker rm token_server || true

docker run -d --name=token_server \
           --network=host \
           -v ${service_dir}:${service_dir} \
           -w ${PWD} \
            golang \
            go run token.go
