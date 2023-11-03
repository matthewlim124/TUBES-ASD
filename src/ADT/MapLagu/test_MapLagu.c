#include "map.h"
#include "map.c"
#include <stdio.h>


int main(){

    Map penyanyi_album;

    CreateEmpty(&penyanyi_album);

    Insert(&penyanyi_album, "BLACKPINK", "BORNPINK");
    Insert(&penyanyi_album, "BLACKPINK", "PINK");
    Insert(&penyanyi_album, "TEST", "ALBUM");
    

    for(int i = 0; i < penyanyi_album.Count; i++){
        int j = 0;
        while(penyanyi_album.Elements[i].Value[j][0] != '\0'){
            printf("Penyanyi: %s Album: %s\n", penyanyi_album.Elements[i].Key, penyanyi_album.Elements[i].Value[j]);
            j++;
        }
        
    }

    /*
    CONTOH OUTPUT: 
    Penyanyi: BLACKPINK Album: BORNPINK
    Penyanyi: BLACKPINK Album: PINK
    Penyanyi: TEST Album: ALBUM
    
    
    */
    

    return 0;
}