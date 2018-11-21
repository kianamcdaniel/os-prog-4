//
//  os-prog-4.c
//  
//
//  Created by Kiana McDaniel on 11/21/18.
//

#include <stdio.h>

int main(){
    int pages[30], frames[30], futurePages[30];
    char space;
    int i = 0;
    int j = 0;
    int k = 0;
    int numPages = 0;
    int numFrames = 0;
    int faults = 0;
    int full, found, pageExists, position, farthest;
    
    //get reference string
    printf("Enter a reference string of numbers with maximum length 30\n");
    for(i = 0; i < 30; i++){
        if(space != '\n'){
            scanf("%d%c", &pages[i], &space);
            numPages++;
        }
    }

    //get number of pages
    printf("Enter the number of frames\n");
    scanf("%d", &numFrames);

    //initialize frame array to empty (-1)
    for(i = 0; i < numFrames; i++){
        frames[i] = -1;
    }
    
    //OPTIMAL ALGORITHM
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
                    faults++;
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
                    position = j;
                    pageExists = 0;
                    break;
                }
            }
            
            //if page exists in the future, find the one that is farthest and
            //save it's position
            if(pageExists == 1){
                farthest = futurePages[0];
                position = 0;
                for(j = 1; j < numFrames; j++){
                    if(futurePages[j] > farthest){
                        farthest = futurePages[j];
                        position = j;
                    }
                }
            }
            
            //make replacement based on previous logic
            frames[position] = pages[i];
            faults++;
        }
        
        printf("\n");
        for(j = 0; j < numFrames; j++){
            printf("%d ", frames[j]);
        }
    }
    
    printf("\n\nTotal Page Faults w/ OPTIMAL ALGORITHM: %d\n\n", faults);

    return 0;
}
