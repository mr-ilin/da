#! /usr/bin/env bash

function main()
{
    local files=("main.cpp" "Makefile" "biggest_int.hpp" "biggest_int.cpp" "benchmark.cpp" "unit_tests.cpp")
    local dir="./solution_folder"

    if [ ! -d ${dir} ]; then
        mkdir ${dir}
    fi
    cp ${files[*]} ${dir}
    tar -czvf solution.tar ${dir}

    rm -r ${dir}
}

main $@