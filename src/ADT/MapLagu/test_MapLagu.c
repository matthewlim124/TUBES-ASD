#include "map.h"

#include <stdio.h>


int main(){

    Map penyanyi_album;

    CreateEmptyMap(&penyanyi_album);
    
    Insert(&penyanyi_album, "BLACKPINK", "BORNPINK");
    Insert(&penyanyi_album, "BLACKPINK", "THE ALBUM");
    Insert(&penyanyi_album, "TEST", "ALBUM");
    Insert(&penyanyi_album, "Artic Monkey", "AM");
    Delete(&penyanyi_album, "TEST", "ALBUM");
    int i = 0;
    int counter = 0;
    boolean isFinished= false;
    while(!(isFinished)){
        
        printf("Penyanyi: %s Album: ", penyanyi_album.Elements[i].Key);
        int j = 0;
        if(!(isElEmpty(penyanyi_album, i))){
            while(penyanyi_album.Elements[i].Value[j][0] != '\0'){
                printf("%s; ", penyanyi_album.Elements[i].Value[j]);
                j++;
            }
            printf("\n");
            counter++;
        }
        if(counter == penyanyi_album.Count){
            isFinished = true;
        }else{
            i++;
        }
        
        
    }

    /*
    CONTOH OUTPUT: 
    Penyanyi: BLACKPINK Album: BORNPINK; THE ALBUM; 
    Penyanyi:  Album: Penyanyi: Artic Monkey Album: AM;
    
    
    
    
    */
    
    

    return 0;
}