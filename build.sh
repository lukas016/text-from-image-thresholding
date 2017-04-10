#!/bin/bash

case $1 in
    "clean")
        rm -rf ./build;
        ;;
    *)
        if [ ! -d build ]; then
            mkdir build;
        fi;
        cd build;
        cmake ..
        make -j8
        cp source/zpo ./
        ;;
esac
