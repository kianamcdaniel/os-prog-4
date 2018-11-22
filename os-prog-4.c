//
//  os-prog-4.c
//  
//
//  Created by Kiana McDaniel on 11/21/18.
//

#include <stdio.h>

int main(){
    int pages[30], frames[30], futurePages[30], lru[30];
    char space;
    int i = 0;
    int j = 0;
    int k = 0;
    int numPages = 0;
    int numFrames = 0;
    int faultsOpt = 0;
    int faultsLru = 0;
    int full, found, pageExists, positionOpt, positionLru, farthest, least;
    int recent = 0;
    
    //get reference string
    printf("\nEnter a reference string of numbers with maximum length 30\n");
    for(i = 0; i < 30; i++){
        if(space != '\n'){
            scanf("%d%c", &pages[i], &space);
            numPages++;
        }
    }

    //get number of pages
    printf("Enter the number of frames\n");
    scanf("%d", &numFrames);

///////////////////////////OPTIMAL ALGORITHM////////////////////////////////////
    
    //initialize frame array to empty (-1)
    for(i = 0; i < numFrames; i++){
        frames[i] = -1;
    }
    
    printf("\nPage Replacement Process for OPTIMAL ALGORITHM: ");
    for(i = 0; i < numPages; i++){
        full = found = 0;
        
        //check if frames are empty
        //check if page is found
        for(j = 0; j < numFrames; j++){
            if(frames[j] == pages[i]){
                full = found = 1;
                break;
            }
        }
        
        //if frame array is empty, fill it
        if(full == 0){
            for(j = 0; j < numFrames; j++){
                if(frames[j] == -1){
                    faultsOpt++;
                    frames[j] = pages[i];
                    found = 1;
                    break;
                }
            }
        }
        
        //if page not found
        if(found == 0){
            pageExists = 1;
            
            //find if page in frame exists in the future and save it's position
            for(j = 0; j < numFrames; j++){
                futurePages[j] = -1;
                for(k = i + 1; k < numPages; k++){
                    if(frames[j] == pages[k]){
                        futurePages[j] = k;
                        break;
                    }
                }
            }
            
            //if page in frame doesn't exist in the future, save it's positon
            for(j = 0; j < numFrames; j++){
                if(futurePages[j] == -1){
                    positionOpt = j;
                    pageExists = 0;
                    break;
                }
            }
            
            //if page exists in the future, find the one that is farthest and
            //save it's position
            if(pageExists == 1){
                farthest = futurePages[0];
                positionOpt = 0;
                for(j = 1; j < numFrames; j++){
                    if(futurePages[j] > farthest){
                        farthest = futurePages[j];
                        positionOpt = j;
                    }
                }
            }
            
            //make replacement based on previous logic
            frames[positionOpt] = pages[i];
            faultsOpt++;
        }
        
        printf("\n");
        for(j = 0; j < numFrames; j++){
            printf("%d ", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults w/ OPTIMAL ALGORITHM: %d\n\n", faultsOpt);
    
//////////////////////////////LRU ALGORITHM/////////////////////////////////////

    //initialize frame array to empty (-1)
    for(i = 0; i < numFrames; i++){
        frames[i] = -1;
    }
    
    printf("\nPage Replacement Process for LRU ALGORITHM: ");
    for(i = 0; i < numPages; i++){
        full = found = 0;
        
        //check if frames are empty
        //check if page is found
        //if not, save it's position
        for(j = 0; j < numFrames; j++){
            if(frames[j] == pages[i]){
                recent++;
                lru[j] = recent;
                full = found = 1;
                break;
            }
        }
        
        //if frame array is empty, fill it
        //save position
        if(full == 0){
            for(j = 0; j < numFrames; j++){
                if(frames[j] == -1){
                    faultsLru++;
                    recent++;
                    frames[j] = pages[i];
                    lru[j] = recent++;
                    found = 1;
                    break;
                }
            }
        }
        
        //if page not found, find the lru frame in frame array and make
        //replacement based on it
        if(found == 0){
            least = lru[0];
            positionLru = 0;
            for(j = 0; j < numFrames; j++){
                if(lru[j] < least){
                    least = lru[j];
                    positionLru = j;
                }
            }
            recent++;
            faultsLru++;
            frames[positionLru] = pages[i];
            lru[positionLru] = recent;
        }
        
        printf("\n");
        for(j = 0; j < numFrames; j++){
            printf("%d ", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults w/ OPTIMAL ALGORITHM: %d\n\n", faultsLru);
    
    return 0;
}
