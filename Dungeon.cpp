#include "Dungeon.h"

// Create a dungeon of certain dimensions
Dungeon::Dungeon(int width, int height){
    bool allowed = true;
    if(width < MIN_WIDTH){
        width = MIN_WIDTH;
        allowed = false;
    }
    if(height < MIN_HEIGHT){
        height = MIN_HEIGHT;
        allowed = false;
    }
    if(!allowed){
        printf("Could not create dungeon of required size (Minimum size is %d x %d)", MIN_WIDTH, MIN_HEIGHT);
    }
    
    this->width = width;
    this->height = height;
    
    tiles = new char * [width];
    for(int i = 0; i < width; i++){
        tiles[i] = new char [height];
        for(int j = 0; j < height; j++){
            tiles[i][j] = 0;
        }
    }
}

char Dungeon::get(int x, int y){
    if(x < 0 || y < 0 || x >= width || y >= height)return -1;
    
    return tiles[x][y];
}

// Generate the dungeon
void Dungeon::generate(){
    printf("Width : %d, Height : %d\n", width, height);
    
    // create a border for the dungeon
    for(int i = 0; i < width; i++){
        //tiles[i][0] = '#';
        //tiles[i][height - 1] = '#';
    }
    for(int j = 0; j < height; j++){
        //tiles[0][j] = '#';
        //tiles[width - 1][j] = '#';
    }
    
    std::vector<Room> rooms;
    
    // Begin splitting using BSP's
    Room start = Room(0, 0, width, height);
    
    rooms.push_back(start);
    // Perform splits
    for(int i = 0; i < 5; i++){
        std::vector<Room> rooms_to_add;
        for(int id = 0; id < rooms.size(); id++){
            Room r = rooms[id];
            if(r.w * r.h < 128 || r.w < 12 && r.h < 12)continue;
            if(i % 2 == 0){
                //Horizontal split
                int split_pos = r.w / 2 + rand() % (r.w / 2) - r.w / 4;
                r.w -= split_pos;
                Room r2 = Room(r.x + r.w, r.y, split_pos, r.h);
                rooms_to_add.push_back(r2);
                rooms[id] = r;
            }else{
                // Vertical split
                int split_pos = r.h / 2 + rand() % (r.h / 2) - r.h / 4;
                r.h -= split_pos;
                Room r2 = Room(r.x, r.y + r.h, r.w, split_pos);
                rooms_to_add.push_back(r2);
                rooms[id] = r;
                
                //r.h /= 2;
                //Room r2 = Room(r.x, r.y + r.h, r.w, r.h);
                //rooms.push_back(r2);
                //rooms[id] = r;
            }
        }
        for(int j = 0; j < rooms_to_add.size(); j++){
            rooms.push_back(rooms_to_add[j]);
        }
    }
    
    // Add the rooms to the tilemap
    for(int i = 0; i < rooms.size(); i++){
        Room r = rooms[i];
        int xo = rand() % r.w;
        int yo = rand() % r.h;
        
        if(r.w-xo < 4)xo = 0;
        if(r.h-yo < 4)yo = 0;
        
        r.x += xo;
        r.y += yo;
        r.w -= xo;
        r.h -= yo;
        
        printf("Room %d : (%d , %d) %d x %d\n", i, r.x, r.y, r.w, r.h);
        for(int i = 0; i < r.w; i++){
            for(int j = 0; j < r.h; j++){
                tiles[r.x+i][r.y+j] = '.';
                if(i == 0 || j == 0 || i == r.w-1 || j == r.h-1)tiles[r.x+i][r.y+j] = '#';
            }
        }
    }
}

// Print the dungeon to console
void Dungeon::print_dungeon(){
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            printf("%c ", get(i, j));
        }
        printf("\n");
    }
}

int main(){
    
    printf("Creating dungeon\n");
    Dungeon dungeon = Dungeon(64, 32);
    
    printf("Generating dungeon\n");
    dungeon.generate();
    
    printf("Printing dungeon\n");
    dungeon.print_dungeon();
    
    return 0;
}