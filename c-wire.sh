#!/bin/bash

# Help function

if [[ "$1" == "-h" || $# -lt 3 ]]; then
    echo "Data file location : Input\c-wire_v00.dat"
    echo "Station type : hvb, hva, lv"
    echo "Consumer type : comp, indiv, all (hbv all; hvb indiv; hva all; hva indiv forbidden)"
    echo "ID"
    echo "help function -h"
    echo "Order of implementation : file_location station_type consumer_type ID"
    exit 0
fi

# Parameters 

data=$1
station_type=$2
consumer_type=$3
id=$4

# Parameters check

if [[ ! -f "$data" ]]; then
    echo "Error : The file '$data' doesn't exist."
fi

if [[ "$station_type" != "hvb" && "$station_type" != "hva" && "$station_type" != "lv" ]]; then
    echo "Error : invalid station type. Valid options : hvb, hva, lv."
fi

if [[ "$consumer_type" != "comp" && "$consumer_type" != "indiv" && "$consumer_type" != "all" ]]; then
    echo "Erreur : Invalid consumer type. Valid options : comp, indiv, all."
fi

if [["$station_type" == "hvb" && "$consumer_type" == "all"]||["$station_type" == "hvb" && "$consumer_type" == "indiv"]||["$station_type" == "hva" && "$consumer_type" == "all"]["$station_type" == "hva" && "$consumer_type" == "indiv"]]
    echo "Error : Invalid consumer and station combination."
fi
