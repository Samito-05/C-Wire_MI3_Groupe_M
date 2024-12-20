#include "station.h"

int main (int argc, char *argv[]){  // Vérification que le programme reçoit suffisamment d'arguments (station, consommateur, identifiant).

     if (argc < 4) {
        return 1;
    }
      // Déclaration des variables nécessaires au traitement
    int station_num, height = 0;
    long long int capacity, load;
    pTree new_node = NULL, tree = NULL;
    char* station = argv[1];
    char* consumer = argv[2];
    char* id = argv[3];
    char adress[50];

     // Ouverture du fichier source contenant les données brutes.
    FILE* file = fopen("tmp/raw_data.csv", "r");
        if (file == NULL){
            printf("Error opening file\n");
            return 1;
        }
    
     // Ouverture du fichier de sortie pour stocker l'arbre non trié.
    FILE *file2 = fopen("tmp/unsorted_tree.csv", "w");
    if (file2 == NULL) {
        printf("Error opening output file: %s\n", adress);
        fclose(file);
        return 1;
    }

    char line[1024];
     
     // Lecture des données ligne par ligne depuis le fichier source.
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
    
         // Création d'un nouveau noeud pour l'arbre AVL avec les données extraites.
        new_node = createTree(capacity, load, station_num);
        

        if (new_node == NULL) {
            printf("Error creating tree node\n");
            fclose(file);
            fclose(file2);
            return 1;
        }

          // Insertion du noeud dans l'arbre AVL.
        tree = insert(tree,new_node,&height);
 
    }

 // Parcours de l'arbre et écriture des données dans le fichier de sortie.
    traversal(tree,file2);

     // Fermeture des fichiers après traitement.
    fclose(file);
    fclose(file2);

// Libération de la mémoire allouée pour l'arbre AVL
    freeTree(tree);
    
    return 0;

}
