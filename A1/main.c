#include <stdio.h>
char dash = '-';
char space = ' ';

/*
 * This function prints an empty rectangle of the specified width and height. 
 */
int PrintRectangle(int width, int height){
    char line_for_top_and_bottom[width + 1];
    char line_for_body[width + 1];

    for(int i = 0; i < width; i++){
        line_for_top_and_bottom[i] = dash;
        line_for_top_and_bottom[width] = '\0';
    }
    
    line_for_body[0] = dash;
    line_for_body[width-1] = dash;
    line_for_body[width] = '\0';
    for(int j = 1; j < width-1; j++){
        line_for_body[j] = space; 
    }

    for(int k = 0; k < height; k++){
        if(k == 0 || k == height-1){
            printf("%s\n", line_for_top_and_bottom);
        }
        else{
            printf("%s\n", line_for_body);
        }
    }
    return 0; 
}


/*
 * This function prints a fancy rectangle. 
 */
int PrintFancyRectangle(int width, int height, char symbol, int fill){
    char line_for_top_and_bottom[width + 1];
    line_for_top_and_bottom[width] = '\0';
    char line_for_body[width + 1];
    line_for_body[width] = '\0';
    line_for_body[width-1] = symbol;

    for(int i = 0; i < width; i++){
        line_for_top_and_bottom[i] = symbol;
    }
    for(int j = 1; j < width-1; j++){
        line_for_body[0] = symbol;
        
        line_for_body[j] = space;
    }
    if(fill == 0){
        for(int k = 0; k < height; k++){
            if(k == 0 || k == height-1){
                printf("%s\n", line_for_top_and_bottom);
            }
            else{
                printf("%s\n", line_for_body);
            }
            
        }
    }
    else{
        for(int k = 0; k < height; k++){
            printf("%s\n", line_for_top_and_bottom);
        }
    }
    return 0;
}

int main(){
    //PrintRectangle(5,4);
    //PrintFancyRectangle(5, 4,'*', 1);
    PrintFancyRectangle(5, 4, '+', 0);
    return 0;
}