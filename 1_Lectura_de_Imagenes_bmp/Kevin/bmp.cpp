#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
    
    //la información del header está en los primeros 54 bytes
    unsigned char header[54];
    
    char *archivo=argv[1];
    cout<<"Archivo: "<<archivo<<"\n";

    FILE *arch;
    arch=fopen(archivo,"r+");
    
    //leemos los primeros 54 bytes    
    if(arch!=NULL){
    
        int byte, i=0;
        byte = fgetc(arch);
        header[i++] = byte;
        
        while(byte!=EOF && i<54){        
            byte = fgetc(arch);
            header[i++] = byte;            
        }
         
    }
    else
        cout<<"No se pudo abrir el archivo\n";
    
    //para modificar el contenido necesitamos:
    
    // width está en los bytes 19 y 20 (dejando 2 bytes)
    // heigth en los bytes 23 y 24 (dejando 2 bytes)
    // bitsPerPixel en el 29 (dejando 1 byte)
    
    int width = header[19]*256+header[18];//indice+1 es la posicion 20 y 19
    int height = header[23]*256+header[22];
    int bitsPerPixel = header[28];
    
    //imageSize, byte 35 y 36
    unsigned int imageSize = header[35]*256+header[34];
    //offste, byte 11 y 12
    unsigned int offset = header[11]*256+header[10];
    
    cout<<"Width: "<<width<<"\n";
    cout<<"Height: "<<height<<"\n";
    cout<<"bitsPerPixel: "<<bitsPerPixel<<"\n";           
    
    unsigned char *imgData = (unsigned char*)malloc(imageSize);
    fseek(arch,offset, SEEK_SET);
    fread(imgData,imageSize,1,arch);
    
    //cambiamos a blanco y negro
    
    unsigned char *image = new unsigned char [height*width];
    unsigned char *BMPptr = imgData, *imageptr = image;
    for ( int row = 0; row <height; row++ ){
        for ( int col = 0; col < width; col++ ){
            *imageptr++ = 0.30 * BMPptr[0] + 0.59 * BMPptr[1] + 0.11 * BMPptr[2] + 0.5;
            BMPptr += 3;
        }
    }

    imgData=imageptr;
    fseek(arch,offset, SEEK_SET);
    fwrite(imgData,imageSize,1,arch);
    
    fclose(arch);
    
    
    
    return 0;
    /*
    int r,g,b;
    for(int y=height;y>0;y--){
        for(int x=0; x<width; x++){
            b=(imgData[3*(x+y*width)]);
            g=(imgData[3*(x+y*width)+1]);
            r=(imgData[3*(x+y*width)+2]);
            
        }
    }
        
            b=(imgData[3*(x+y*width)]);
            g=(imgData[3*(x+y*width)+1]);
            r=(imgData[3*(x+y*width)+2]);

            if(r==255 && g==255 && b==255){
            printf(" ");
            }else if(r==255 && g==255 && b==255){
        printf(" ");
      }else{
        if(r>g && r>b){
            printf("r");
        }
        if(g>r && g>b){
            printf("g");
        }else{
            printf("b");
        }
      }
    }
      printf("\n");
        
        }*/
        
        
           
    
   
    
}















