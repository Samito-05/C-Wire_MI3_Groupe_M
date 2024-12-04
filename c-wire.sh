#!/bin/bash

# Help function
function help {
    echo "Data file location : Input\c-wire_v00.dat"
    echo "Station type : hvb, hva, lv"
    echo "Consumer type : comp, indiv, all (hvb all; hvb indiv; hva all; hva indiv forbidden)"
    echo "ID"
    echo "Help function : -h"
    echo "Order of implementation : file_location station_type consumer_type ID"
    exit 0
}

if [[ "$1" == "-h" || $# -lt 3 ]]; then
    help
fi

# Parameters 
data=$(realpath "$1")
station_type=$2
consumer_type=$3
id=$4

# Parameters check
if [[ ! -f "$data" ]]; then
    echo "Error: The file '$data' doesn't exist."
    help
fi

if [[ "$station_type" != "hvb" && "$station_type" != "hva" && "$station_type" != "lv" ]]; then
    echo "Error: Invalid station type. Valid options: hvb, hva, lv."
    help
fi

if [[ "$consumer_type" != "comp" && "$consumer_type" != "indiv" && "$consumer_type" != "all" ]]; then
    echo "Error: Invalid consumer type. Valid options: comp, indiv, all."
    help
fi

if { [[ "$station_type" == "hvb" && "$consumer_type" == "indiv" ]] || 
     [[ "$station_type" == "hva" && "$consumer_type" == "all" ]] || 
     [[ "$station_type" == "hva" && "$consumer_type" == "indiv" ]]; }; then
    echo "Error: Invalid consumer and station combination."
    help
fi

while IFS=';' read -r col1 col2 col3 col4 col5 col6 col7 col8; do
    echo "${col1}:${col2}:${col3}:${col4}:${col5}:${col6}:${col7}:${col8}"
done < "$data"


# Compilation of code
EXE="./codeC/c-wire"

if [[ ! -x "$EXE" ]]; then
    echo "Compiling code..."
    (cd ./codeC && make)
    if [[ $? -ne 0 ]]; then
        echo "Error compiling C code"
        exit 1
    fi
fi

# tmp & graphs folder setup
mkdir -p tmp
mkdir -p graphs
rm -rf tmp
