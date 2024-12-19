#include "station.h"

int main (int argc, char *argv[]){

    int power_plant_id, hvb, hva, lv, comp, indiv, height;
    long long int capacity, load;
    pTree new_node = NULL, tree = NULL;
    char* station = argv[1];
    char* consumer = argv[2];
    char adress[50];
    
    FILE* file = fopen("tmp/data_sorted.csv", "r");
        if (file == NULL){
            printf("Error opening file\n");
            return 1;
        }
    //printf("File opened sucessfully\n");

    sprintf(adress, "tests/%s_%s.csv", station, consumer);

    FILE *file2 = fopen(adress, "w");

    fprintf(file2,"%s Station : Capacity : Load\n",station);

    char line[1024];

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        
        char *token = strtok(line, ";");
        if (token == NULL) continue;
        power_plant_id = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        hvb = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        hva = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        lv = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        comp = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        indiv = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        capacity = atoll(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        load = atoll(token);

        if (strcmp(station, "hvb") == 0) {
            new_node = createTree(capacity, load, hvb);
        } else if (strcmp(station, "hva") == 0) {
            new_node = createTree(capacity, load, hva);
        } else if (strcmp(station, "lv") == 0) {
            new_node = createTree(capacity, load, lv);
        } else {
            printf("Invalid station: %s\n", station);
            fclose(file);
            return 1;
        }

        if (new_node == NULL) {
            printf("Error creating tree node\n");
            fclose(file);
            return 1;
        }

        tree = insert(tree,new_node,&height);
 
    }

    infix(tree, file2);

    fclose(file);
    fclose(file2);

    freeTree(tree);
    
    return 0;

}