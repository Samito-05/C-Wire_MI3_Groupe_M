#!/bin/bash

# tmp & graphs folder setup
mkdir -p tmp
mkdir -p graphs


# Help function
function help {
    echo "==================================================================================="
    echo ""
    echo "Data file location : Input/c-wire_v00.dat"
    echo "Station type possibilities : hvb, hva, lv"
    echo "Consumer type possibilities : comp, indiv, all (hvb all; hvb indiv; hva all; hva indiv forbidden)"
    echo "ID : Optional"
    echo "Help function : -h"
    echo "Order of implementation : file_location station_type consumer_type ID(optional)"
    echo ""
    echo "==================================================================================="
    exit 0
}
if [[ "$1" == "-h" || $# -lt 3 ]]; then
    help
fi


# Default ID function
function set_default_id {
    if [[ -z "$1" ]]; then
        echo "0"
    else
        echo "$1"
    fi
}


# Validate ID function
function validate_id {
    if [[ "$1" =~ ^[0-9]+$ ]]; then
        echo "$1"
    else
        echo "Error: ID must be a numeric value."
        exit 1
    fi
}

# Parameters 
data=$(realpath "$1")
station_type=$2
consumer_type=$3
id=$(set_default_id "$4")
id=$(validate_id "$id")


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


# Define column indices based on the input
if [[ "$station_type" == "hvb" ]]; then
    column1=2
elif [[ "$station_type" == "hva" ]]; then
    column1=3
elif [[ "$station_type" == "lv" ]]; then
    column1=4
fi

if [[ "$consumer_type" == "comp" ]]; then
    column2=5
elif [[ "$consumer_type" == "indiv" ]]; then
    column2=6
fi


# Parameter to exlude

parameter="-"

# ID to include

parameter2=$id

# Output CSV file
output=$(realpath tmp/data_sorted.csv)

if [[  "$id" == "0" ]]; then

    # Extract wanted lines
    awk -F';' -v col1="$column1" -v col2="$column2" -v param="$parameter" \
        'NR == 1 {print; next} # Print header
        NR > 1 && $col1 && $col2 && $col1 != param && $col2 != param {print}' \
        "$data" > "$output"

elif [[ "$id" -gt 0 ]]; then

   awk -F';' -v col1="$column1" -v col2="$column2" -v col_id=1 -v param="$parameter" -v param2="$id" \
    'NR == 1 {print; next} # Print header
     NR > 1 && $col1 && $col2 && $col_id == param2 && $col1 != param && $col2 != param {print}' \
    "$data" > "$output"
fi



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


rm -rf tmp