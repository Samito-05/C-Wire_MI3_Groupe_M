#include "station.h"

int main (){
    
     FILE* file = fopen("../tmp/data_sorted.csv", "r");
        if (file == NULL){
            printf("Error opening file");
            return 1;
        }

    return 0;

}