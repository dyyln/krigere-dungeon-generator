#include "Dungeon.h"

Dungeon::Dungeon(int width, int height){
    this->width = width;
    this->height = height;
    
    tiles = new int * [width];
    for(int i = 0; i < width; i++){
        tiles[i] = new int [height];
        for(int j = 0; j < height; j++){
            tiles[i][j] = 0;
        }
    }
}

void Dungeon::generate(){
    printf("Width : %d, Height : %d\n", width, height);
}

void Dungeon::print_dungeon(){
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            printf("%d ", tiles[i][j]);
        }
        printf("\n");
    }
}

int main(){
    
    printf("Creating dungeon\n");
    Dungeon dungeon = Dungeon(48, 32);
    
    printf("Generating dungeon\n");
    dungeon.generate();
    
    printf("Printing dungeon\n");
    dungeon.print_dungeon();
    
    return 0;
}