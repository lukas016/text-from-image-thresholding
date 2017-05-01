#!/bin/bash

METHODS=("--otsu" "--balanced" "--adaptiveGauss" "--iterative");
RESULT=0;
mkdir -p result;
p=0;
for method in ${METHODS[@]}; do
    for dir in $(ls data); do
        if [ ! -d data/${dir} ]; then
            continue;
        fi;
        for image in $(ls data/${dir}/); do
            for i in $(seq 1 1 10); do
                TIME=$(./zpo $method data/${dir}/$image result/$image | sed -n '$p');
                if [ $? -ne 0 ]; then
                    continue;
                fi;
                RESULT=$(($RESULT + $TIME));
            done;
            RESULT=$(($RESULT / 10));
            PIXELS=($(identify -format '%w %h\n' data/${dir}/${image}));
            echo "$method $dir $((${PIXELS[0]} * ${PIXELS[1]})) $RESULT" >> time.txt
            RESULT=0;
        done;
    done;
done;

