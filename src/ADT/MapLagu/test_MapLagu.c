#include "map.h"

#include <stdio.h>


int main(){

    Map penyanyi_album;

    CreateEmptyMap(&penyanyi_album);
    
    //DUPLIKAT PENYANYI TIDAK DIMASUKKAN
    Insert(&penyanyi_album, "BLACKPINK", "BORNPINK");
    Insert(&penyanyi_album, "BLACKPINK", "THE ALBUM");

    Insert(&penyanyi_album, "TEST", "ALBUM");

    //DUPLIKAT LAGU TIDAK DIMASUKKAN
    Insert(&penyanyi_album, "Artic Monkey", "AM"); 
    Insert(&penyanyi_album, "Artic Monkey", "AM");

    //HAPUS PENYANYI ATAU LAGU
    Delete(&penyanyi_album, "TEST", NULL);
    Delete(&penyanyi_album, "BLACKPINK", "BORNPINK");
    int i = 0;
    int counter = 0;
    int count_value = 0;
    boolean isFinished= false;
    boolean isValue = false;
    while(!(isFinished)){
        
        
        int j = 0;
        if(!(isElEmpty(penyanyi_album, i))){
            printf("Penyanyi: %s Album: ", penyanyi_album.Elements[i].Key);
            count_value = 0;
            while(count_value < value_count(penyanyi_album, penyanyi_album.Elements[i].Key)){
                
                if(penyanyi_album.Elements[i].Value[j][0] != '\0'){
                    printf("%s; ", penyanyi_album.Elements[i].Value[j]);
                    count_value++;
                    j++;
                    
                }else{
                    j++;
                }

                
                
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
    Penyanyi: BLACKPINK Album: THE ALBUM; 
    Penyanyi: Artic Monkey Album: AM;
    
    
    
    
    */
    
    

    return 0;
}