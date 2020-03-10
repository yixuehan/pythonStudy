#!/bin/bash

images=uhub.service.ucloud.cn/safehouse/alpine:go1.12.6-alpine3.9
# images=centos

docker run -it \
           -v $(which docker):$(which docker) \
           -v /run/docker.sock:/run/docker.sock \
           -v ${HOME}/.docker:/root/.docker \
           -v /lib64:/lib64 \
           ${images} \
           sh
