#include <stdio.h>

typedef struct Network {

    int power_plant_id;
    int hvb;
    int hva;
    int lv;
    int comp;
    int indiv;
    long capacity;
    long load;

} Network;


int main(){

    Network* tab = NULL;
    int size = 0;

    FILE *file = fopen("../tmp/data_sorted.csv", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    printf("The file was sucessfully opened\n");

     char line[1024];
    while (fgets(line, sizeof(line), file)) {
        Network s;
        
        sscanf(line, "%d;%d;%d;%d;%d;%d;%ld;%ld", &s.power_plant_id, &s.hvb, &s.hva, &s.lv, &s.comp, &s.indiv, &s.capacity, &s.load);

        tab = add_elmt(tab, &size, s);

    }

    fclose(file);

    return 0;

}