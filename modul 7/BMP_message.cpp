#include <iostream>
#include <string>
using namespace std;

bool check_file(string fname);
unsigned char mergebit(char image, char text2bit);
void header(FILE *image, FILE *copy_image, unsigned int* width);
void Encode(string text_file, string BMP_file);
unsigned char merge4byte(unsigned char text_byte[]);
void Decode(string BMP_message);
void put_lrc(string fname);
bool valid_lrc(string fname);

int main(int argc, char *argv[]){
    if (argc == 1){
        cout << "pilih salah satu perintah:" << endl
            << "   1. Encode" << endl
            << "   2. Decode" << endl;
        
        short opt;
        cout << "Input :";
        cin >> opt;

        switch (opt){
            case 1: {
                
                char str[30];
                cout << "nama file BMP :";
                scanf(" %[^\n]%*c", str);
                string BMP_file(str);
                /*i always prefer string than literal array of char.
                but, unfortunately in this course i'm not allowed to use OOP*/

                cout << "nama file TXT :";
                scanf(" %[^\n]%*c", str);
                string text_file(str);

                if (check_file(BMP_file)){
                    if (check_file(text_file)){
                    Encode(text_file, BMP_file);//#####
                    put_lrc(BMP_file);
                    }
                    else{
                        cout << "ERROR : File "<< text_file << " tidak ditemukan";
                    }
                }
                else{
                    cout << "ERROR : File " << BMP_file << " tidak ditemukan";
                }
                break;
            }
            case 2:{
                char str[30];
                cout << "nama file BMP :";
                scanf(" %[^\n]%*c", str);
                string BMP_file(str);
                
                if (check_file(BMP_file)){
                    if(valid_lrc(BMP_file)){
                        cout << "PESAN VALID" << endl ;
                    }
                    else{
                        cout << "PESAN TIDAK VALID" << endl;
                    }
                    Decode(BMP_file);//#######
                }
                else{
                      cout << "ERROR : File " << BMP_file << " tidak ditemukan";
                }
                break;
            }    
            default:{
                cout << "INVALID INPUT" << endl;
                break;
            }
        }
    }

    else if(argc == 4){
        string command(argv[1]);
        string BMP_file(argv[2]);
        string text_file(argv[3]);

        if ((command == "Encode") || (command == "encode")){
            if (check_file(BMP_file)){
                    if (check_file(text_file)){
                    Encode(text_file, BMP_file);//#####
                    put_lrc(BMP_file);
                    }
                    else{
                        cout << "ERROR : File "<< text_file << " tidak ditemukan";
                    }
                }
                else{
                    cout << "ERROR : File " << BMP_file << " tidak ditemukan";
                }
        }
        else{
            cout << "INVALID INPUT" << endl;
        }
    }
    else if(argc == 3){
        string command(argv[1]);
        string BMP_file(argv[2]);

        if ((command == "Decode") || (command == "decode")){
            if (check_file(BMP_file)){
                if(valid_lrc(BMP_file)){
                    cout << "PESAN VALID" << endl ;
                }
                else{
                    cout << "PESAN TIDAK VALID" << endl;
                }
                Decode(BMP_file);
            }
           else{
                cout << "ERROR : File " << BMP_file << " tidak ditemukan";
            } 
        }
        else{
            cout << "INVALID INPUT" << endl;
        }
    }

    else if(argc == 2) {
        string str(argv[1]);
        if( str == "-credit"){
            cout << "PRAKTIKUM ALPRO MODUL VII"<<endl
                 << "Putu Andika Eka Putra" << endl
                 << "1915101029" << endl
                 << "Ilmu Komputer II A"<<endl;
        }
        else{
            cout << "INVALID INPUT" << endl;
        }
    }

    else{
        cout << "INVALID INPUT" << endl;
    }
}

bool check_file(string fname){ //menguji keberadaan file
    
    const char *filename = &fname[0];
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return true;
    }
    else{
        return false;
    }
}

void header(FILE *image, FILE *copy_image, unsigned int* width){// menyalin header dan menyimpan width
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

unsigned char mergebit(char image, char text2bit){//memasukan 2 bit txt kedalam byte pixel
    /*
    image       = 123456__
    text2bit    = ______78
    return      = 12345678
    */
   
    unsigned char merged_byte = 0;
    unsigned char test_byte = 1;

    for(int i = 0; i < 2; i++){
        if ((text2bit & test_byte) == test_byte){
            merged_byte += test_byte;
        }
        test_byte <<= 1;
    }
    for(int i = 0; i < 6; i++){
        if ((image & test_byte) == test_byte){
            merged_byte += test_byte;
        }
        test_byte <<= 1;
    } 
    
    return merged_byte;
}

void Encode(string text_file, string BMP_file){// memasukan text kedalam pixel array bmp
    /*
    file txt dipecah per dua bit yang digunakan untuk mengganti 2 bit terakhir 
    dari setiap byte pada pixel array di file BMP

    hasilnya nilai RGB pada pixel akan berubah 0-3 point (test dengan photoshop)
    */
    
    FILE *input_image, *input_text, *output_image;

    const char *file = &BMP_file[0];
    input_image     = fopen(file, "rb");

    file = &text_file[0];
    input_text      = fopen(file, "rb");

    BMP_file = "Encoded_"+BMP_file;
    file = &BMP_file[0];
    output_image    = fopen(file, "wb");

    unsigned int width;
    unsigned char data;
    unsigned char padding;
    char data_text;
    header(input_image, output_image, &width);
    int padding_size = width % 4;
    unsigned char text2bit[width*3];
    bool text_left = true;
    int last_row;

    while (true){
        if (!(feof(input_text))){
            for (int i = 0 ; i < width*3; i += 4){ 
            
                fread(&data_text, sizeof(char), 1, input_text);
                if (feof(input_text)){
                    break;
                }
            
                unsigned char testbit = 1;
                for(int j = i ; j < 4 + i; j++ ){
                    unsigned char lastbit = 0;

                    if ((data_text & testbit) == testbit){
                        lastbit += 1;
                    }
                    testbit <<= 1;
                    
                    if ((data_text & testbit) == testbit){
                        lastbit += 2;
                    }
                    testbit = testbit << 1;
  
                    text2bit[j] = lastbit;   
                    last_row = j; 
                }
               
            }  
    
        }
        
        if (!(feof(input_image))){
            for (int i = 0 ; i < 3*width; i++){
                
                fread(&data, sizeof(char), 1, input_image);
                
                if (feof(input_image)){
                    break;
                }
                
                if  (text_left){
        
                    unsigned char write;
                    write = mergebit(data, text2bit[i]);
                    
                    fwrite(&write, 1 , sizeof(char) ,  output_image );
                    
                    if (feof(input_text)&& i ==last_row){
                        text_left = false;
                       
                        // menandai akhir dari text
                        unsigned char ETX[4] = {3, 0, 0, 0};// nilai end of text dalam ascii = 00000011
                        for( int j = 0; j < 4; j++){
                            fread(&data, sizeof(char), 1, input_image);
                            write = mergebit(data, ETX[j]);
                        
                            fwrite(&write, 1 , sizeof(char) ,  output_image );
                        }
                        i +=4;
                    }
                }
                else{
                    fwrite(&data, 1, sizeof(char), output_image);
                }

                
            }
            for(int i = 0; i< padding_size; i++){
                fread(&padding, sizeof(char), 1, input_image);
                fwrite(&padding, 1 ,sizeof(char),  output_image);
            }

        }
        else {
            break;
        }
        
    }
    
    fclose(input_image);
    fclose(input_text);
    fclose(output_image);
    cout << "Output :" << BMP_file << endl;
}

unsigned char merge4byte(unsigned char text_byte[]){//menyatukan 2bit terakhir dari 4 byte;
    /*
    arr[0] = ______78
    arr[1] = ______56
    arr[2] = ______34
    arr[3] = ______12

    return = 12345678
    */
    
    unsigned char add_byte = 1;
    unsigned char result_byte = 0;

    for (int i = 0 ; i < 4 ; i++){
        unsigned char tester = 1;
        if ((text_byte[i] & tester) == tester){
            result_byte += add_byte;
        }
        
        tester <<= 1;
        add_byte <<= 1;

        if ((text_byte[i] & tester) == tester){
            result_byte += add_byte;
        }
        add_byte <<= 1;
    }
    
    return result_byte;
}

void Decode(string BMP_message){//membaca pesan yang tersembunyi dalam file bmp
    FILE *message_image, *output_text;
    
    const char* file = &BMP_message[0];
    message_image   = fopen(file, "rb");

    BMP_message += "_Decoded.txt";
    file = &BMP_message[0];
    output_text     = fopen(file, "w");

    unsigned char OneByteText[4];
    unsigned int width;
    bool text_left = true;
   
    FILE *temp_header = fopen("temp","w");
    header(message_image, temp_header, &width);
    fclose(temp_header);
    remove("temp");
    int padding_size = width % 4;
    char padding ;
    //skip 54 byte sebagai header

    while((!feof(message_image) )&& (text_left)){
        for (int i = 0; i < width*3; i += 4){
            for (int j = 0; j < 4; j++ ){
                fread(&OneByteText[j], 1, sizeof(char), message_image);
              
            }
            unsigned char write = merge4byte(OneByteText);
            if (write == 3){
                text_left = false;
                break;
            }
            if (write == 13){
                continue;
            }
            cout<<write;
            fwrite(&write, sizeof(char), 1, output_text);
        }

        for(int i = 0; i < padding_size; i++ ){
            fread(&padding, 1, sizeof(char), message_image);
        }
    }
    fclose(message_image);
    fclose(output_text);
}

void put_lrc(string fname){
    fname = "Encoded_"+fname;
    const char* file = &fname[0];
    FILE *BMP_file = fopen(file, "rb");
    unsigned short lrc = 0xffff;

    unsigned int width;
    FILE *temp_header = fopen("temp", "w");
    header(BMP_file, temp_header, &width);
    fclose(temp_header); 
    remove("temp");


    while(!feof(BMP_file)){
        unsigned short data;
        fread(&data, sizeof(short), 1, BMP_file);
        lrc^=data;
    }

    fseek(BMP_file, 0, SEEK_SET);

    FILE *temp = fopen("temp.bmp", "wb");

    unsigned char data;
    for(int i = 0; i < 6; i++){
        fread(&data, sizeof(char), 1, BMP_file);
        fwrite(&data,1 , sizeof(char), temp);
    }

    fread(&data, sizeof(short), 1, BMP_file);
    cout << "lRC16 = " << lrc<<endl;
    fwrite(&lrc, 1, sizeof(short), temp);

    while(!feof(BMP_file)){
        fread(&data, sizeof(char), 1, BMP_file);
        fwrite(&data,1 , sizeof(char), temp);
    }

    fclose(BMP_file);
    fclose(temp);
    remove(file);
    rename("temp.bmp", file);

}

bool valid_lrc(string fname){
    const char* file = &fname[0];
    FILE *BMP_file = fopen(file, "rb");
    unsigned short crc = 0xffff;

    unsigned short offcrc;
    unsigned char header;

    fseek(BMP_file, 6, SEEK_SET);

    fread(&offcrc, sizeof(short), 1, BMP_file);

    fseek(BMP_file, 54, SEEK_SET);

    while(!feof(BMP_file)){
        unsigned short data;
        fread(&data, sizeof(short), 1, BMP_file);
        crc^=data;
    }
    fclose (BMP_file);

    if (offcrc == crc){
        return true;
    }
    else {
        return false;
    }

}