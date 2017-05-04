#!/bin/bash

METHODS=("--otsu" "--balanced" "--adaptiveGauss" "--adaptiveMeanC"  "--iterative");
RESULT=0;
mkdir -p result;
p=0;

iterations=50

rm -f time.txt

for method in ${METHODS[@]}; do
    echo "Trying method ${method}"
    RESDIR=$(echo $method | sed -e 's/--//g')

    mkdir -p result/$RESDIR

    for dir in $(ls data); do
        if [ ! -d data/${dir} ]; then
            continue;
        fi;

        for image in $(ls data/${dir}/); do
            echo "  .. image ${image}"
            PASSCOUNT=0
            for i in $(seq 1 1 $iterations); do

                TIME=$(./zpo $method data/${dir}/$image result/$RESDIR/$image | sed -n '$p');
                if [ $? -ne 0 ]; then
                    continue;
                fi

                PASSCOUNT=$(($PASSCOUNT + 1))

                RESULT=$(($RESULT + $TIME));
            done;
            RESULT=$(($RESULT / $PASSCOUNT));
            PIXELS=($(identify -format '%w %h\n' data/${dir}/${image}));
            echo "$method $dir $((${PIXELS[0]} * ${PIXELS[1]})) $RESULT $PASSCOUNT" >> time.txt
            RESULT=0;
        done;
    done;
done;

