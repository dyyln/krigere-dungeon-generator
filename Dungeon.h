#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <vector>

struct Dungeon{
    static const int MIN_WIDTH = 16, MIN_HEIGHT = 16;
    
    char** tiles;
    int width, height;
    
    Dungeon(int width, int height);
    
    char get(int x, int y);
    
    void generate();
    
    void print_dungeon();
};

struct Room{
    int x;
    int y;
    int w;
    int h;
    
    Room(){
        x = y = w = h = 0;
    }
    
    Room(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_){
        
    }
};