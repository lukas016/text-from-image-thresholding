#!/usr/bin/env bash

METHODS=("--all");

if [ ! -f ../build/zpo ]; then
    echo "Zpo executable needs to be in ../build/ directory!"
    echo "... or it was not build! Use build.sh."
    exit 1
fi

rm -rf results
mkdir results

for dir in $(ls data); do
    if [ ! -d data/${dir} ]; then
        continue
    fi;

    inputDir=data/${dir}

    for image in $(ls data/${dir}/); do
        filename="${image%.*}"
        echo "Testing data/${dir}/${image}"

        outputDir=results/${filename}
        mkdir -p ${outputDir}

        # First iteration from original
        inputFile=${inputDir}/${image}
        outputFile=${outputDir}/1/${filename}-
        mkdir -p ${outputDir}/1
        ../build/zpo --all ${inputFile} ${outputFile} --half &>/dev/null

        # Other iterations
        for i in 2 3; do
            iterInputDir=${outputDir}/$(expr ${i} - 1)
            mkdir -p ${outputDir}/${i}

            for iterImage in $(ls ${iterInputDir}/); do
                iterInputFile=${iterInputDir}/${iterImage}
                iterOutputFile=${outputDir}/${i}/${iterImage%.*}-

                ../build/zpo --all ${iterInputFile} ${iterOutputFile} --half &>/dev/null
            done;
        done;
    done;
done;

echo "Tests are done"
