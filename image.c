#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

ImagePPM *readPPM(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        return NULL;
    }

    else if(fp != NULL){

    }
    int d = 3;
    int width, height, max_value;
	char magic[d];
    fscanf(fp, "%s", magic);
    fscanf(fp, "%d%d%d", &width, &height, &max_value);
   // ImagePPM *ppm=malloc(sizeof(ImagePPM));
    //ppm->pixels = malloc(sizeof(Pixel *) * 6);
    //ppm->pixels[i] = malloc(sizeof(Pixel) * 4);
    //fscanf(fp, "%d", &ppm->pixels[i][j].red);
    ImagePPM *ppm = malloc(sizeof(ImagePPM));
    if(width + height > 0){
    ppm->width = width;
    ppm->height = height;
    }

    else{
        ppm->width = height;
        ppm->height = width;
    }

    ppm->pixels = malloc(sizeof(int *) * height);
    
    for(int b = 0; b < height;){
        ppm->pixels[b]= malloc(sizeof(Pixel) * width);
        b = b +1;
    }

    strcpy(ppm->magic, magic);
    int b = max_value;
    ppm->max_value = b;

    int col = ppm->width;
    int row = ppm->height;
    
    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
            fscanf(fp, "%d%d%d", &ppm->pixels[i][j].red, &ppm->pixels[i][j].green, &ppm->pixels[i][j].blue);
            j = j+1;
        }
        i = i +1;
    }
    fclose(fp);
    return ppm;

}

int writePPM(ImagePPM *ppm, char *filename)
{
    FILE *fp = fopen(filename, "w");
    if(fp == NULL){
        return 0;
    }
    fprintf(fp, "%s ", ppm->magic);
    fprintf(fp, "%d %d %d ", ppm->width, ppm->height, ppm->max_value);

    int col = ppm->width;
    int row = ppm->height;
    

    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
            fprintf(fp, "%d %d %d ", ppm->pixels[i][j].red, ppm->pixels[i][j].green, ppm->pixels[i][j].blue);
            int a = 1;
            j = j + a;
        }
        fprintf(fp, "\n");
        int b = 1;
        i = i+b;
    }

    fclose(fp);
	return 1;

}

ImagePPM *rotatePPM(ImagePPM *ppm)
{
    ImagePPM *ppm2 = malloc(sizeof(ImagePPM));
    if(ppm->height + ppm->width > 0){
    ppm2->width = ppm->height;
    ppm2->height = ppm->width;
    }
    else{
        ppm2->width = ppm->width;
        ppm2->height = ppm->height;
    }

    ppm2->pixels = malloc(sizeof(int *) * ppm->width);
    
    for(int b = 0; b < ppm->width;){
        ppm2->pixels[b]= malloc(sizeof(Pixel) * ppm->height);
        b = b +1;
    }
    strcpy(ppm2->magic, ppm->magic);
    int b = ppm->max_value;
    ppm2->max_value = b;
    
    int col = ppm->width;
    int row = ppm->height;

    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
        ppm2->pixels[j][row-(i+1)].red = ppm->pixels[i][j].red;
        ppm2->pixels[j][row-(i+1)].green = ppm->pixels[i][j].green;
        ppm2->pixels[j][row-(i+1)].blue = ppm->pixels[i][j].blue;
        j = j +1;
        }
        i = i +1;
    }
    return ppm2;

}

ImagePPM *flipPPM(ImagePPM *ppm)
{
    ImagePPM *ppm2 = malloc(sizeof(ImagePPM));
    if(ppm->width + ppm->height > 0){
    ppm2->width = ppm->width;
    ppm2->height = ppm->height;
    }
    else{
        ppm2->width = ppm->height;
        ppm2->height = ppm->width;
    }

    ppm2->pixels = malloc(sizeof(int *) * ppm->height);
    
    for(int b = 0; b < ppm->height;){
        ppm2->pixels[b]= malloc(sizeof(Pixel) * ppm->width);
        b = b +1;
    }
    strcpy(ppm2->magic, ppm->magic);
    int b = ppm->max_value;
    ppm2->max_value = b;
    
    int col = ppm->width;
    int row = ppm->height;
    if(col + row >0){
    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
        int a = j + 1;
        int b = col - a;
        ppm2->pixels[i][j].red = ppm->pixels[i][b].red;
        ppm2->pixels[i][j].green = ppm->pixels[i][b].green;
        ppm2->pixels[i][j].blue = ppm->pixels[i][b].blue;
        j = j+1;
        }
        i = i +1;
        }
    }
    return ppm2;

}

ImagePPM *enlargePPM(ImagePPM *ppm)
{
    int col = ppm->width;
    int row = ppm->height;
    ImagePPM *ppm2 = malloc(sizeof(ImagePPM));
    if(ppm->width + ppm->height > 0){
    ppm2->width = ppm->width;
    ppm2->height = ppm->height;
    }
    else{
        ppm2->width = ppm->height;
        ppm2->height = ppm->width;
    }

    ppm2->pixels = malloc(sizeof(int *) * ppm->height);
    
    for(int b = 0; b < ppm->height;){
        ppm2->pixels[b]= malloc(sizeof(Pixel) * ppm->width);
        b = b +1;
    }
    if(col*(2) + row*(2) > 0){
    ppm2->width = col*(2);
    ppm2->height = row*(2);
    }
    else{
        ppm2->width = row*(2);
        ppm2->height = col*(2);
    }

    ppm2->pixels = malloc(sizeof(int *) * row*(2));
    
    for(int b = 0; b < row*(2);){
        ppm2->pixels[b]= malloc(sizeof(Pixel) * col*(2));
        b = b +1;
    }
    strcpy(ppm2->magic, ppm->magic);
    int b = ppm->max_value;
    ppm2->max_value = b;

    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
        ppm2->pixels[2*i][2*j].red = ppm->pixels[i][j].red;
        ppm2->pixels[2*i+1][2*j].red = ppm->pixels[i][j].red;
        ppm2->pixels[2*i][2*j+1].red = ppm->pixels[i][j].red;
        ppm2->pixels[2*i+1][2*j+1].red = ppm->pixels[i][j].red;

        ppm2->pixels[2*i][2*j].green = ppm->pixels[i][j].green;
        ppm2->pixels[2*i+1][2*j].green = ppm->pixels[i][j].green;
        ppm2->pixels[2*i][2*j+1].green = ppm->pixels[i][j].green;
        ppm2->pixels[2*i+1][2*j+1].green = ppm->pixels[i][j].green;

        ppm2->pixels[2*i][2*j].blue = ppm->pixels[i][j].blue;
        ppm2->pixels[2*i+1][2*j].blue = ppm->pixels[i][j].blue;
        ppm2->pixels[2*i][2*j+1].blue = ppm->pixels[i][j].blue;
        ppm2->pixels[2*i+1][2*j+1].blue = ppm->pixels[i][j].blue;

         j = j+1;

        }

        i = i+1;

    }
    return ppm2;

}

//(both width and height) into the half, and return the new ppm image. 
//If the original height or width is odd, discard the last row or column. 
//The intensity of the new image pixel located at (i, j) will be the average of 4 pixels located at 
//(2*i, 2*j),  (2*i+1, 2*j), (2*i, 2*j+1), and (2*i+1, 2*j+1) in the existing image. 
//Please use the round function when colnverting a double to an integer.
ImagePPM *shrinkPPM(ImagePPM *ppm)
{
    int col = ppm->width;
    int row = ppm->height;
    if(col%2 == 1){
        col = col -1;
    }
    if(row%2 == 1){
        row = row - 1;
    }
    col = col/2;
    row = row/2;
    ImagePPM *ppm2 = malloc(sizeof(ImagePPM));
    if(col + row > 0){
    ppm2->width = col;
    ppm2->height = row;
    }
    else{
        ppm2->width = row;
        ppm2->height = col;
    }

    ppm2->pixels = malloc(sizeof(int *) * row);
    
    for(int b = 0; b < row;){
        ppm2->pixels[b]= malloc(sizeof(Pixel) * col);
        b = b +1;
    }
    strcpy(ppm2->magic, ppm->magic);
    int b = ppm->max_value;
    ppm2->max_value = b;

    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
        ppm2->pixels[i][j].red = round((ppm->pixels[2*i][2*j].red + ppm->pixels[2*i+1][2*j].red + ppm->pixels[2*i][2*j+1].red + ppm->pixels[2*i+1][2*j+1].red)/4.0);

        ppm2->pixels[i][j].green = round((ppm->pixels[2*i][2*j].green + ppm->pixels[2*i+1][2*j].green + ppm->pixels[2*i][2*j+1].green + ppm->pixels[2*i+1][2*j+1].green)/4.0);

        ppm2->pixels[i][j].blue = round((ppm->pixels[2*i][2*j].blue + ppm->pixels[2*i+1][2*j].blue + ppm->pixels[2*i][2*j+1].blue + ppm->pixels[2*i+1][2*j+1].blue)/4.0);
        j = j+1;
        }
        i = i+1;
    }

    return ppm2;

}

ImagePPM *invertPPM(ImagePPM *ppm)
{
    ImagePPM *ppm2 = malloc(sizeof(ImagePPM));
    if(ppm->width + ppm->height > 0){
    ppm2->width = ppm->width;
    ppm2->height = ppm->height;
    }
    else{
        ppm2->width = ppm->height;
        ppm2->height = ppm->width;
    }

    ppm2->pixels = malloc(sizeof(int *) * ppm->height);
    
    for(int b = 0; b < ppm->height;){
        ppm2->pixels[b]= malloc(sizeof(Pixel) * ppm->width);
        b = b +1;
    }

    strcpy(ppm2->magic, ppm->magic);
    int b = ppm->max_value;
    ppm2->max_value = b;
    
    int col = ppm->width;
    int row = ppm->height;
    int z = 2;

    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
        int b = j/z;  
        int c = i/z;
        ppm2->pixels[i][j].red = ppm->max_value-ppm->pixels[i][j].red;
        ppm2->pixels[i][j].green = ppm->max_value-ppm->pixels[i][j].green;
        ppm2->pixels[i][j].blue = ppm->max_value-ppm->pixels[i][j].blue;
        j++;
        }
        i++;
    }
    return ppm2;
}

ImagePPM *cropPPM(ImagePPM *ppm, int r1, int c1, int r2, int c2)
{
    if(r1 < 0 || c1 < 0 || r2 < 0 || c2 < 0){
        return NULL;
    }

    if(r1 == r2 || c1 == c2){
        return NULL;
    }

    int z = 1;
    int col = abs(c2 - c1) + z;
    int row = abs(r2 - r1) + z;

    ImagePPM *ppm2 = malloc(sizeof(ImagePPM));
    if(col + row > 0){
    ppm2->width = col;
    ppm2->height = row;
    }
    else{
        ppm2->width = row;
        ppm2->height = col;
    }

    ppm2->pixels = malloc(sizeof(int *) * row);
    
    for(int b = 0; b < row;){
        ppm2->pixels[b]= malloc(sizeof(Pixel) * col);
        b = b +1;
    }

    strcpy(ppm2->magic, ppm->magic);
    ppm2->max_value = ppm->max_value;
    int a, b;

    if(c2 < c1){
    a = c2;
    b = r2;
    }

    else{
        a = c1;
        b = r1;
    }

    for(int i = 0; i < row;){
        for(int j = 0; j < col;){
        ppm2->pixels[i][j].red = ppm->pixels[i+b][j+a].red;
        ppm2->pixels[i][j].green = ppm->pixels[i+b][j+a].green;
        ppm2->pixels[i][j].blue = ppm->pixels[i+b][j+a].blue;
        j = j+1;
        }
        i = i+1;
    }
    return ppm2;

}

void freeSpacePPM(ImagePPM *ppm)
{
    int b = 0;
    while(b < ppm->height){
        free(ppm->pixels[b]);
        if(b < ppm->height + 1){
        int z = 1;
        b = b + z;
        }
        if(b > ppm->height){
            break;
        }
    }
    free(ppm->pixels);
    free(ppm);
}