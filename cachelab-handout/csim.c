#include "cachelab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//each element of matrix has this struct
typedef struct {
    unsigned int tag;
    bool valid;
    int lruCounter;
} Way;

//finds out if address exists & is Valid in a set row
//param: matrix row, E (#ofcols), tag (unique block id)
//returns:
// 1 -> HIT       loaded/valid
// 0 -> MISS      not loaded/can load
//-1 -> EVICT     not loaded/CAN'T load
int rowTransverser(Way row[],int E,unsigned tag) {
    short validWays = 0;
    //first increment all valid line
    for (int i = 0; i < E; ++i) {
        if (row[i].valid == 1) {
            row[i].lruCounter++;
        }
    }



    for (int i = 0; i < E; ++i) {
        if (row[i].valid == 1 && row[i].tag == tag) {
            //address is already loaded/valid :) HIT!
            row[i].lruCounter = 0;
            return 1;
        } else if (row[i].valid == 1) {
            ++validWays;
        }
    }
    //no valid match. MISS!
    //UH OH EVICTION TIME if cols is full
    if (validWays == E) {
        //FIND A VICTIM
        int lruIndex = 0;
        //get index of LRU Way
        for (int i = 1;i < E; ++i) {
            if (row[i].lruCounter > row[lruIndex].lruCounter) {
                lruIndex = i;
            }
        }
        row[lruIndex].tag = tag;
        row[lruIndex].lruCounter = 0;
        row[lruIndex].valid = 1;

        return -1; //EVICTED
    } else {
        //miss - find garbage Way to replace
        for (int i = 0;i < E; ++i) {
            if (row[i].valid == 0) {
                row[i].tag = tag;
                row[i].lruCounter = 0;
                row[i].valid = 1;
                break; //leave for
            }
        }
    }
    return 0; //MISS
}


int main(int argc, char* argv[])
{   //(s,E,b) -> s=set bits,E=associativity
    //b=block offset bits (2^b) = B bytes for block size

    int s = -1;   //set bits -> rows = 2^s
    int E = -1;   //lines per set -> cols
    int b = 1;   //offset bits -> Blocksize Bytes B = 2^b
    int verbose = 0;
    char* t = NULL;
    //Process arguments
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
        } else if (strcmp(argv[i], "-v") == 0) {
            verbose = 1;
        }
    }
    int rowSize = (1 << s);
    //print arguments
    /*
    printf("s: %d -> %d rows\nE: %d -> %d cols\n" ,s,rowSize,E,E);
    printf("b: %d -> block size %d bytes\n%s\n"  ,b,(1 << b),t);
    //DONE VERIFYING INPUT
    */


    //Create Matrix of structs for the cache
    Way (*mymatrix)[E] = malloc( (1 << s) * sizeof(*mymatrix) );
    //verify matrix exists and set all valid bits to 0
    for (int i = 0; i < rowSize; ++i) {
        for (int j = 0; j < E; ++j) {
            mymatrix[i][j].valid = 0;
            mymatrix[i][j].lruCounter = 0;
            //printf("%d " ,mymatrix[i][j].valid);
        }
        //printf("\n");
    }


    //Read trace file
    FILE *file = fopen(t, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    //Parse each line
    char line[100];
    char operator = '\0';
    unsigned tag = 0;
    //cache stats
    unsigned hits = 0;
    unsigned misses = 0;
    unsigned evictions = 0;
    //designated row
    unsigned sIndex = 0;
    while (fgets(line, sizeof(line), file)) {
        if(line[0] == 'I') {
            continue; //don't count instructions
        }
        //extract line components (Operator & Address) & DO STUFF
        if (sscanf(line, " %c %x", &operator, &tag) == 2) {
            //What set does the Address belong to? (row) (CAN CONFLICT)
            sIndex = (tag >> b) & ((1 << s) - 1);

            //if cmd arg -v
            if (verbose) {
                printf("Address: 0x%x    %c\n", tag, operator);
            }
            //What is the tag for this address? (Unique id)
            tag = tag >> (s + b);

            //decide what to DO
            int rowResult = 0;
            switch (operator) {
                case 'L':
                    rowResult = rowTransverser(mymatrix[sIndex], E, tag);
                    //check if address is already loaded/valid in specific row
                    if (rowResult == 1) {
                        ++hits;
                    } else if (rowResult == 0) {
                        ++misses; //then load
                    } else {
                        ++misses; //not found
                        ++evictions; //then evict
                    }
                    break; //DONE CASE L
                case 'S':
                    rowResult = rowTransverser(mymatrix[sIndex], E, tag);
                    //check if address is already loaded/valid in specific row
                    if (rowResult == 1) {
                        ++hits;
                    } else if (rowResult == 0) {
                        ++misses; //then load
                    } else {
                        ++misses; //not found
                        ++evictions; //then evict
                    }

                    break; //DONE CASE S
                case 'M':
                    rowResult = rowTransverser(mymatrix[sIndex], E, tag);
                    //check if address is already loaded/valid in specific row
                    if (rowResult == 1) {
                        hits += 2;
                    } else if (rowResult == 0) {
                        ++misses; //then load
                        ++hits; //then modify
                    } else {
                        ++misses; //not found
                        ++evictions; //then evict
                        ++hits; //then modify
                    }
                //DONE CASE M

            }//end switch



        //DONE PARSING
        }

    }
    fclose(file);
    //Close file


    //deallocate
    free(mymatrix);


    printSummary(hits,misses,evictions);
    return 0;
}



