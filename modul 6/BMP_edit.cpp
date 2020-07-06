#include <iostream>
#include <string>
using namespace std;

void copy_header(FILE *image, FILE *copy_image, unsigned int* width);
void To_negative(string fname);
void To_grayscale(string fname);
void swapRGB(string fname);


int main(int argc, char *argv[]){
    if (argc == 1){
        cout <<"PUTU ANDIKA EKA PUTRA"<<endl
             <<"1915101029"<<endl
             <<"ILMU KOMPUTER IIA"<<endl
             <<"PRAKTIKUM ALGORITMA DAN PEMROGRAMAN (MODUL 6)" <<endl ;

    }
    else if(argc == 3){
        string fname(argv[1]);
        string command(argv[2]);
        /*
        negative
        grayscale
        rgb
        */

        if(command == "negative"){
            cout << "membuat versi negative dari "<< fname <<endl;
            To_negative( fname);
        }
        else if(command == "grayscale"){
            cout << "membuat versi grayscale dari " << fname << endl;
            To_grayscale(fname);
        }
        else if(command =="rgb"){
            cout << "membuat versi RGB tertukar dari " << fname << endl;
            swapRGB(fname);
        }
        else{
             cout<<"INPUT INVALID"<<endl;
        }

    }

    else{
        cout<<"INPUT INVALID"<<endl;
    }
    
}
void copy_header(FILE *image, FILE *copy_image, unsigned int* width){
    /*
    file header:    bitmap type = 2 bytes
                    file size   = 4 bytes
                    reserved1   = 2 bytes
                    reserved2   = 2 bytes
                    offset bits = 4 bytes
        total = 14 bytes

    Dib header:     size header     = 4 bytes
                    width           = 4 bytes -> digunakan untuk menghitung padding (byte ke-19) tipe data= unsigned int
                    height          = 4 bytes
                    planes          = 2 bytes
                    bit count       = 2 bytes
                    compression     = 4 bytes
                    image size      = 4 bytes
                    ppm x           = 4 bytes
                    ppm y           = 4 bytes
                    clr used        = 4 bytes
                    clr important   = 4 bytes
        total = 40 bytes
    total = 54 byt
    */
    
    unsigned char data;
    for(int i = 0; i <18 ; i++){
       
        fread(&data, sizeof(char), 1, image);
        fwrite(&data, 1 , sizeof(char) , copy_image );
    }
    fread(width, sizeof(int), 1, image);
    fwrite(width, 1 , sizeof(int) , copy_image );
    
    for(int i = 0; i <32 ; i++){
       
        fread(&data, sizeof(char), 1, image);
        fwrite(&data, 1 , sizeof(char) , copy_image );
    }

}

void To_negative(string fname){
    FILE *image, *copy_image;
    
    const char *file = &fname[0];
    image = fopen(file, "rb");          //input

    fname = "negative_"+fname;
    file = &fname[0];
    copy_image = fopen(file, "wb");     //output
    
    unsigned int width;
    unsigned char data;
    unsigned char padding;
    
    copy_header(image, copy_image, &width);
    int padding_size = width % 4;
	//padding digunakan setiap baris bisa dibagi 4 byte
	//1 pixel megunakan 3 byte
	
    
    while(true){
        if (feof(image)){
            break;
        }

        for (int i = 0 ; i < 3*width; i++){
            
            fread(&data, sizeof(char), 1, image);
            if (feof(image)){
                break;
            }
            data = ~data;
            fwrite(&data, 1 , sizeof(char) , copy_image );
        }
        for(int i = 0; i< padding_size; i++){
			
            fread(&padding, sizeof(char), 1, image);
            fwrite(&padding, 1 ,sizeof(char), copy_image);
        }  
        
    }
    
    fclose(image);
    fclose(copy_image);
}
void To_grayscale(string fname){
    FILE *image, *image_count , *copy_image;

    const char *file = &fname[0];
    image = fopen(file, "rb");          //input

    fname = "grayscale_"+fname;
    file = &fname[0];
    copy_image = fopen(file, "wb");     //output
    
    unsigned int width;
    unsigned char data,padding;
    
    copy_header(image, copy_image, &width);
    int padding_size = width % 4;
    
    while(true){
        if (feof(image)){
            break;
        }

        for (int i = 0 ; i <width; i++){
            unsigned char red, green, blue;

            // urutan subpixel : 1byte merah, 1byte hijau, 1 byte biru

            fread(&red, sizeof(char), 1, image);
            fread(&green, sizeof(char), 1, image);
            fread(&blue, sizeof(char), 1, image);
            if (feof(image)){
                break;
            }
            data = (red + green + blue)/3;
             for (int i = 0 ; i <3; i++){
                fwrite(&data, 1 , sizeof(char) , copy_image );
             }
        }
        for(int i = 0; i< padding_size; i++){
            fread(&padding, sizeof(char), 1, image);
            fwrite(&padding, 1 ,sizeof(char), copy_image);
        }  
        
    }
    
    fclose(image);
    fclose(copy_image);
}

void swapRGB(string fname){
    FILE *image, *image_count , *copy_image;

    const char *file = &fname[0];
    image = fopen(file, "rb");          //input

    fname = "swapRGB_"+fname;
    file = &fname[0];
    copy_image = fopen(file, "wb");     //output
    
    unsigned int width;
    unsigned char data,padding;
    
    copy_header(image, copy_image, &width);
    int padding_size = width % 4;
    
    while(true){
        if (feof(image)){
            break;
        }

        for (int i = 0 ; i <width; i++){
            unsigned char red, green, blue;

            fread(&red, sizeof(char), 1, image);
            fread(&green, sizeof(char), 1, image);
            fread(&blue, sizeof(char), 1, image);
            
            if (feof(image)){
                break;
            }
            fwrite(&green, 1, sizeof(char) , copy_image);
            fwrite(&blue, 1 , sizeof(char) , copy_image );
            fwrite(&red, 1 , sizeof(char) , copy_image );
       
            
        }
        for(int i = 0; i< padding_size; i++){
            fread(&padding, sizeof(char), 1, image);
            fwrite(&padding, 1 ,sizeof(char), copy_image);
        }  
        
    }
    
    fclose(image);
    fclose(copy_image);
}
//author : P Andika EP