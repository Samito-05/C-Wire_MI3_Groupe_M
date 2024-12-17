#!/bin/bash

#To run program : ./c-wire.sh -h

# tmp & graphs folder setup
rm -rf tmp
mkdir -p tmp
mkdir -p graphs

EXE="./codeC/c-wire"

if [[ ! -x "$EXE" ]]; then
    echo "Compiling code..."
    (cd ./codeC && make all)
    if [[ $? -ne 0 ]]; then
        echo "Error compiling C code"
        exit 1
    fi
    echo "Compilation sucessfull"
fi

start_time=$(date +%s.%N)

# Help function
function help {
    echo "==================================================================================="
    echo ""
    echo "Data file location : Input/<FILENAME>"
    echo "Station type possibilities : hvb, hva, lv"
    echo "Consumer type possibilities : comp, indiv, all (hvb all; hvb indiv; hva all; hva indiv forbidden)"
    echo "ID : Optional"
    echo "Help function : -h"
    echo "Order of implementation : file_location station_type consumer_type power_plant_ID(optional)"
    echo ""
    echo "==================================================================================="
    exit 0
}
if [[ "$1" == "-h" || $# -lt 3 ]]; then
    help
fi

if [[ "$1" == "-h" || "$2" == "-h" || "$3" == "-h" ]]; then
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
     [[ "$station_type" == "hvb" && "$consumer_type" == "all" ]] || 
     [[ "$station_type" == "hva" && "$consumer_type" == "indiv" ]] ||
     [[ "$station_type" == "hva" && "$consumer_type" == "all" ]]; }; then
    echo "Error: Invalid consumer and station combination."
    help
fi



column1=1   # id
column2=2   # hvb
column3=3   # hva
column4=4   # lv
column5=5   # comp
column6=6   # indiv
column7=7   # capacity
column8=8   # load


parameter="-"


parameter2=$id


output=$(realpath tmp/data_sorted.csv)



function process_data() {
    local col_station="$1"
    local col_consumer="$2"
    local col_capacity="$3"
    local col_station_ex1="$4"

    if [[ "$id" == "0" ]]; then
        # No specific ID filter
        awk -F';' -v col_station="$col_station" -v col_station_ex1="$col_station_ex1" -v col_consumer="$col_consumer" -v col_capacity="$col_capacity" -v param="$parameter" \
            'NR == 1 {print; next} # Print header
            NR > 1 && $col_station && $col_consumer && ($col_station != param) && ((!col_consumer || $col_consumer != param) || $col_capacity != param) && (!col_station_ex1 || $col_station_ex1 == param) {print}' \
            "$data" > "$output"
    elif [[ "$id" -gt 0 ]]; then
        # Specific ID filter
        awk -F';' -v col1="$column1" -v col_station="$col_station" -v col_consumer="$col_consumer" -v param="$parameter" -v param2="$id" \
            'NR == 1 {print; next} # Print header
            NR > 1 && $col1 == param2 && ($col_station != param) && ($col_consumer != param || $col_capacity != param) && ($col_station_ex1 == param) {print}' \
            "$data" > "$output"
    fi
}


#hvb comp
if [[ "$station_type" == "hvb" ]]; then
    if [[ "$consumer_type" == "comp" ]]; then
        process_data "$column2" "$column5" "$column7" "$column3"
    fi
#hva comp
elif [[ "$station_type" == "hva" ]]; then
    if [[ "$consumer_type" == "comp" ]]; then
        process_data "$column3" "$column5" "$column7" "$column4"
    fi
#lv
elif [[ "$station_type" == "lv" ]]; then
    #comp
    if [[ "$consumer_type" == "comp" ]]; then
        process_data "$column4" "$column5" "$column7" "$column6"
    #indiv
    elif [[ "$consumer_type" == "indiv" ]]; then
        process_data "$column4" "$column6" "$column7" "$column5"
    #all
    elif [[ "$consumer_type" == "all" ]]; then
        process_data "$column4" "" "$column7" ""
    fi
fi

"$EXE" "$station_type"
if [[ $? -ne 0 ]]; then
    echo "Error running the program."
    exit 1
fi

end_time=$(date +%s.%N)
execution_time=$(awk "BEGIN {print $end_time - $start_time}")

echo "The file has been sorted in ${execution_time} seconds"

# rm -rf tmp

cd ./codeC && make empty