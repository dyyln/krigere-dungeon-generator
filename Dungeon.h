#pragma once

#include <stdio.h>

struct Dungeon{
    int** tiles;
    int width, height;
    
    Dungeon(int width, int height);
    
    void generate();
    
    void print_dungeon();
};