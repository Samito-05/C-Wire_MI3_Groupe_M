#!/bin/bash

#To run program : ./c-wire.sh -h

cat << "EOF"


#################################################################################################################################################

                                                                                                                                 
        CCCCCCCCCCCCC                  WWWWWWWW                           WWWWWWWW   iiii                                          
     CCC::::::::::::C                  W::::::W                           W::::::W  i::::i                                         
   CC:::::::::::::::C                  W::::::W                           W::::::W   iiii                                          
  C:::::CCCCCCCC::::C                  W::::::W                           W::::::W                                                
 C:::::C       CCCCCC                   W:::::W           WWWWW           W:::::W  iiiiiii  rrrrr   rrrrrrrrr        eeeeeeeeeeee    
C:::::C                                  W:::::W         W:::::W         W:::::W   i:::::i  r::::rrr:::::::::r     ee::::::::::::ee  
C:::::C                                   W:::::W       W:::::::W       W:::::W     i::::i  r:::::::::::::::::r   e::::::eeeee:::::ee
C:::::C                ---------------     W:::::W     W:::::::::W     W:::::W      i::::i  rr::::::rrrrr::::::r e::::::e     e:::::e
C:::::C                -:::::::::::::-      W:::::W   W:::::W:::::W   W:::::W       i::::i   r:::::r     r:::::r e:::::::eeeee::::::e
C:::::C                ---------------       W:::::W W:::::W W:::::W W:::::W        i::::i   r:::::r     rrrrrrr e:::::::::::::::::e 
C:::::C                                       W:::::W:::::W   W:::::W:::::W         i::::i   r:::::r             e::::::eeeeeeeeeee  
 C:::::C       CCCCCC                          W:::::::::W     W:::::::::W          i::::i   r:::::r             e:::::::e           
  C:::::CCCCCCCC::::C                           W:::::::W       W:::::::W          i::::::i  r:::::r             e::::::::e          
   CC:::::::::::::::C                            W:::::W         W:::::W           i::::::i  r:::::r              e::::::::eeeeeeee  
     CCC::::::::::::C                             W:::W           W:::W            i::::::i  r:::::r               ee:::::::::::::e  
        CCCCCCCCCCCCC                              WWW             WWW             iiiiiiii  rrrrrrr                 eeeeeeeeeeeeee  
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
                                                                                                                                                                                                                                                                                                                                                                                    
By PROCOPPE Sam, TRAN-PHAT Hugo and PELISSIER Jules

#################################################################################################################################################





EOF


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


output=$(realpath tmp/raw_data.csv)



function process_to_raw_data() {
    local col_station="$1"
    local col_consumer="$2"
    local col_capacity="$3"
    local col_station_ex1="$4"
    local col_load="$5"

    if [[ "$id" == "0" ]]; then
        
        awk -F';' -v col_station="$col_station" -v col_station_ex1="$col_station_ex1" -v col_consumer="$col_consumer" -v col_capacity="$col_capacity" -v param="$parameter" -v col_load="$col_load" \
            'NR > 1 && $col_station && $col_consumer && ($col_station != param) && ((!col_consumer || $col_consumer != param) || $col_capacity != param) && (!col_station_ex1 || $col_station_ex1 == param) {print $col_station ";" $col_capacity ";" $col_load}' \
            "$data" | sort -t';' -k2,2nr | sed '/;0;/!b; $!{h;d}; x' > "$output"
            
    elif [[ "$id" -gt 0 ]]; then
        
        awk -F';' -v col1="$column1" -v col_station="$col_station" -v col_consumer="$col_consumer" -v col_capacity="$col_capacity" -v col_station_ex1="$col_station_ex1" -v param="$parameter" -v param2="$id" -v col_load="$col_load" \
            'NR > 1 && $col_station && $col_consumer && $col1 == param2 && ($col_station != param) && ((!col_consumer || $col_consumer != param) || $col_capacity != param) && (!col_station_ex1 || $col_station_ex1 == param) {print $col_station ";" $col_capacity ";" $col_load}' \
            "$data" | sort -t';' -k2,2nr | sed '/;0;/!b; $!{h;d}; x' > "$output"
    fi
}



#hvb comp
if [[ "$station_type" == "hvb" ]]; then
    if [[ "$consumer_type" == "comp" ]]; then
        process_to_raw_data "$column2" "$column5" "$column7" "$column3" "$column8"
    fi
#hva comp
elif [[ "$station_type" == "hva" ]]; then
    if [[ "$consumer_type" == "comp" ]]; then
        process_to_raw_data "$column3" "$column5" "$column7" "$column4" "$column8"
    fi
#lv
elif [[ "$station_type" == "lv" ]]; then
    #comp
    if [[ "$consumer_type" == "comp" ]]; then
        process_to_raw_data "$column4" "$column5" "$column7" "$column6" "$column8"
    #indiv
    elif [[ "$consumer_type" == "indiv" ]]; then
        process_to_raw_data "$column4" "$column6" "$column7" "$column5" "$column8"
    #all
    elif [[ "$consumer_type" == "all" ]]; then
        process_to_raw_data "$column4" "" "$column7" "" "$column8"
    fi
fi

if [[ "$id" == "0" ]]; then
    sorted_file="tests/${station_type}_${consumer_type}.csv"
elif [[ "$id" -gt 0 ]]; then
    sorted_file="tests/${station_type}_${consumer_type}_${$id}.csv"
fi

function process_to_sorted_data() {
    local station_type="$1"

    # Write the header with the station type
    echo "$station_type-Station: Capacity : Load" > $sorted_file
    
    # Sort the data and append it to the sorted file
    sort -t';' -k2,2n tmp/unsorted_tree.csv >> $sorted_file
}

function process_to_sorted_data_min_max() {
    local station_type="$1"

    echo "$station_type-Station: Capacity : Load" > $sorted_file

    {
        sort -t';' -k2,2n tmp/unsorted_tree.csv | head -n 10
        sort -t';' -k2,2n tmp/unsorted_tree.csv | tail -n 10
    } | sort -t';' -k2,2n >> $sorted_file
}




generate_bargraph() {
    local input_csv=$1
    local output_png=$2

    # Generate the gnuplot script
    cat <<EOF > plot.gp
        set terminal png size 12000,8000
        set output '$output_png'
        set datafile separator ";"
        set title 'Energy Usage per Station'
        set ylabel 'Energy (Kwh)'
        set xlabel 'Station'
        set style data histogram
        set style histogram cluster gap 1
        set style fill solid border -1
        set boxwidth 0.9
        set xtics rotate by -90 font ",25"
        unset grid
        set border lw 0
        set key font ",75"
        set bmargin 10

        plot '$sorted_file' every ::1 using 2:xtic(1) title "Capacity" lc rgb "blue", \
             '$sorted_file' every ::1 using 3 title "Load" lc rgb "red"

EOF

    # Run gnuplot
    gnuplot plot.gp

    # Clean up temporary file
    rm plot.gp

    echo "Bar graph generated as $output_png"
    return 0
}


"$EXE" "$station_type" "$consumer_type" "$id"
if [[ $? -ne 0 ]]; then
    echo "Error running the program."
    exit 1
fi


if [[ "$station_type" == "lv" && "$consumer_type" == "all" ]]; then
    process_to_sorted_data_min_max "$station_type"
elif [[ "$consumer_type" != "all" && ("$station_type" == "hvb" || "$station_type" == "hva" || "$station_type" == "lv") ]]; then
    process_to_sorted_data "$station_type"
fi


output_image="graphs/${station_type}_${consumer_type}.png"
generate_bargraph "$sorted_file" "$output_image"


end_time=$(date +%s.%N)
execution_time=$(awk "BEGIN {print $end_time - $start_time}")

echo "The file has been sorted in ${execution_time} seconds"

rm -rf tmp

cd ./codeC && make empty