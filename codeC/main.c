#include "station.h"

int main (int argc, char *argv[]){ 
    
     // Ensure the program receives at least 4 arguments (program name + 3 arguments).
     if (argc < 4) {
        return 1;
    }
    // Declare necessary variables.
    int station_num, height = 0;
    long long int capacity, load;
    pTree new_node = NULL, tree = NULL;
    char* station = argv[1];
    char* consumer = argv[2];
    char* id = argv[3];
    char adress[50];

    // Declare necessary variables.
    FILE* file = fopen("tmp/raw_data.csv", "r");
        if (file == NULL){
            printf("Error opening file\n");
            return 1;
        }
    
    // Declare necessary variables.
    FILE *file2 = fopen("tmp/unsorted_tree.csv", "w");
    if (file2 == NULL) {
        printf("Error opening output file: %s\n", adress);
        fclose(file);
        return 1;
    }

    char line[1024];
     
    // Read the data line by line from the input file.
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
    
        // Create a new tree node with the parsed data.
        new_node = createTree(capacity, load, station_num);
        

        if (new_node == NULL) {
            printf("Error creating tree node\n");
            fclose(file);
            fclose(file2);
            return 1;
        }

        // Insert the new node into the AVL tree.
        tree = insert(tree,new_node,&height);
 
    }

    // Traverse the AVL tree and write its content to the output file.
    traversal(tree,file2);

    // Close both input and output files after processing.
    fclose(file);
    fclose(file2);

    // Free the dynamically allocated memory for the AVL tree.
    freeTree(tree);
    
    return 0;

}
