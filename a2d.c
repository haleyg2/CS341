#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//prints matrix (rows X cols)
void showMatrix(int **head, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("%d " ,head[i][j]);
        }
        printf("\n");
    }
}
//find item in Matrix
bool findMatrixElem(int *head, int rows, int cols, int key) {
    bool found = false;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            //check if found
            found = key == (*(head + i * cols + j));
            if(found) {
                return true;
            }
        }
    }
    //Not found :(
    return false;
}

//defaults all elements to 0
void fillMatrixZeros(int **head, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            head[i][j] = 0;
        }
    }
}

//deallocate matrix
void deallocateMatrix(int **matrixA, int rows) {
    // Later, free
    for (int i = 0; i < rows; i++) {
        free(matrixA[i]);
    }
    free(matrixA);
}





int main(int argc, char *argv[]) {
    int s = -1;
    int E = -1;
    int b = -1;
    char* t = NULL;
    //GET INPUT SIZE FROM TERMINAL
    //process arguments
    //arguments start at index 1
    //i+1 < argc ensures there's a next argument
    for (int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-s") == 0 && i + 1 < argc) {
            ++i;  //s is next input (sets)
            s = atoi(argv[i]); 
        } else if (strcmp(argv[i],"-E") == 0 && i + 1 < argc) {
            ++i;  //E is next input (Assoc.)
            E = atoi(argv[i]);
        } else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            ++i;  //b is next input (Bits.)
            b = atoi(argv[i]);
        } else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            ++i;  //t is next input (trace file)
            t = argv[i];
        } 
    }
    //print arguments
    printf("s: %d\nE: %d\nb: %d\n%s\n" ,s,E,b,t);
    
    //allocate first rows
    int **matrixA = malloc((1 << s) * sizeof(int*));
    for (int i = 0; i < (1<<s); ++i) {
        //allocate rest of each row
        matrixA[i] = malloc(E * sizeof(int)); 
    }
    fillMatrixZeros(matrixA,(1 << s), E);
    showMatrix(matrixA,(1 << s), E);
    deallocateMatrix(matrixA, (1<<s));

    return 0;
}