#include <stdio.h>
#include <string.h>

int resourceNum = 3;
int processNum = 5;

int main(int argc, char** argv) {
    int avail[resourceNum];
    int resource[resourceNum];
    int processMaxes[processNum][resourceNum];
    int processAllocations[processNum][resourceNum];
    int processNeeds[processNum][resourceNum];
    int processComplete[processNum];
    int safeSequence[processNum];
    int temp, seqNum = 0;

    FILE* pointer = fopen("in.txt", "r");

    for(int i = 0; i < resourceNum; i++){
        fscanf(pointer, "%d", &temp);
        avail[i] = temp;
    }

    for(int i = 0; i < resourceNum; i++){
        fscanf(pointer, "%d", &temp);
        resource[i] = temp;
    }

    for(int i = 0; i < processNum; i++){
        for(int j = 0; j < resourceNum; j++){
            fscanf(pointer, "%d", &temp);
            processMaxes[i][j] = temp;
        }
    }

    for(int i = 0; i < processNum; i++){
        for(int j = 0; j < resourceNum; j++){
            fscanf(pointer, "%d", &temp);
            processAllocations[i][j] = temp;
        }
    }

    fclose(pointer);

    for(int i = 0; i < processNum; i++){
        for(int j = 0; j < resourceNum; j++){
            processNeeds[i][j] = processMaxes[i][j] - processAllocations[i][j];
        }
    }

    for(int i = 0; i < processNum; i++){
        processComplete[i] = 0;
    }

    //loop terminates when all resources are made available (when available == resource)
    while(memcmp(avail, resource, resourceNum) != 0){ 
        for(int i = 0; i < processNum; i++){
            if(processComplete[i] == 0){
                int processBlock = 0;
                for(int j = 0; j < resourceNum; j++){
                    if(processNeeds[i][j] > avail[j]){
                        processBlock = 1;
                        break;
                    }
                }
                if(processBlock == 0){
                    safeSequence[seqNum] = i;
                    seqNum++;
                    for(int j = 0; j < resourceNum; j++){
                        avail[j] = avail[j] + processAllocations[i][j];
                    }
                    processComplete[i] = 1;
                }
            }
        }
    }

    printf("Safe sequence:\n");

    for(int i = 0; i < processNum; i++){
        printf("Process %d ", safeSequence[i]);
    }
    printf("\n");

    return (0);
}
