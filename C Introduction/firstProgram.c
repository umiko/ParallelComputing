#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    printf("Hello World!\nMy Arguments are:\n");
    int i;
    for(i = 0; i < argc; i++){
        printf("%d of %d: %s\n", i, argc, argv[i]);
    }
    
    return 0;
}