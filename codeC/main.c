#include "station.h"

int main (int argc, char *argv[]){

     if (argc < 4) {
        return 1;
    }

    int station_num, height = 0;
    long long int capacity, load;
    pTree new_node = NULL, tree = NULL;
    char* station = argv[1];
    char* consumer = argv[2];
    char* id = argv[3];
    char adress[50];

    
    FILE* file = fopen("tmp/raw_data.csv", "r");
        if (file == NULL){
            printf("Error opening file\n");
            return 1;
        }
    
    FILE *file2 = fopen("tmp/unsorted_tree.csv", "w");
    if (file2 == NULL) {
        printf("Error opening output file: %s\n", adress);
        fclose(file);
        return 1;
    }

    char line[1024];

    while (fgets(line, sizeof(line), file)) {
        
        char *token = strtok(line, ";");
        if (token == NULL) continue;
        station_num = atoi(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        capacity = atoll(token);

        token = strtok(NULL, ";");
        if (token == NULL) continue;
        load = atoll(token);

        new_node = createTree(capacity, load, station_num);
        

        if (new_node == NULL) {
            printf("Error creating tree node\n");
            fclose(file);
            fclose(file2);
            return 1;
        }


        tree = insert(tree,new_node,&height);
 
    }


    traversal(tree,file2);

    
    fclose(file);
    fclose(file2);

    freeTree(tree);
    
    return 0;

}