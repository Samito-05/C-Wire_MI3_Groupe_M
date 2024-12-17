#include "station.h"

int main (int argc, char *argv[]){

    int power_plant_id, hvb, hva, lv, comp, indiv, *height;
    long long int capacity, load;
    pTree new_node = NULL, tree = NULL;
    char* type = argv[1];

    printf("***%s***\n", type);
    
    FILE* file = fopen("tmp/data_sorted.csv", "r");
        if (file == NULL){
            printf("Error opening file\n");
            return 1;
        }
    printf("File opened sucessfully\n");

    char line[1024];

    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        // Tokenize and parse each line
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

        // Create tree nodes based on type
        if (strcmp(type, "hvb") == 0) {
            new_node = createTree(capacity, load, hvb);
        } else if (strcmp(type, "hva") == 0) {
            new_node = createTree(capacity, load, hva);
        } else if (strcmp(type, "lv") == 0) {
            new_node = createTree(capacity, load, lv);
        } else {
            printf("Invalid type: %s\n", type);
            fclose(file);
            return 1;
        }

        if (new_node == NULL) {
            printf("Error creating tree node\n");
            fclose(file);
            return 1;
        }


        printf("%d,%lld,%lld \n",new_node->id,new_node->capacity, new_node->consumption);
        
            
    }

    return 0;

}