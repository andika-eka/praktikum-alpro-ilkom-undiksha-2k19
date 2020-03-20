#include<iostream>
#include<string>
#include<cstring>
#include <stdio.h>
#include <stdlib.h>
#include "func_replica.h"

using namespace std;

void input (const char* fname, int num, char arg){
    FILE *CsvFile;
    CsvFile = fopen(fname, "a");
    string nis, text, numStr, thlStr;
    int thl;
    char jkl, nama[20];
    cout <<"nama :";
    scanf(" %[^\n]%*c",nama);
    cout <<"nis :";
    cin>>nis;
    cout <<"jenis kelamin [L/P]:";
    cin>>jkl;
    cout <<"tahun lahir :";
    cin>>thl;

    if(!((jkl=='L')||(jkl=='l')||(jkl=='p')||(jkl='P'))){
        fclose(CsvFile);
        cout<<endl<<"input tidak valid"<<endl
            <<"nis harus tujuh digit"<<endl
            <<"jenis kelamin L/P"<<endl;
        input(fname,num, arg);
    }
    else{
        numStr=to_string(num);
        thlStr=to_string(thl);

        if (arg=='a'){
            text= "\n"+numStr+", "+nis+", "+nama+", "+jkl+", "+thlStr;
        }
        else if(arg=='e'){
            text= numStr+", "+nis+", "+nama+", "+jkl+", "+thlStr+"\n"; 
        }
        const char *to_file= &text[0];
        fprintf(CsvFile, "%s", to_file);
        // cout << to_file;
        fclose(CsvFile);
    }
    
}

void newCsv(const char *fname){
    FILE* CsvFile;
    CsvFile = fopen(fname,"r");

    if (CsvFile){
        cout << "FIlE dengan nama :"<< fname << " sudah ada"<<endl;;
        fclose(CsvFile);
    }
    else{
        fclose(CsvFile);
        cout << " membuat file :"<< fname<<endl;
        CsvFile = fopen(fname,"w");
        fprintf(CsvFile,"NO, NIS, NAMA, JENIS KELAMIN, TAHUN LAHIR");
    }
    fclose(CsvFile);
}

void appendCsv(const char *fname){
    FILE* CsvFile;
    CsvFile = fopen(fname,"r");
    if (CsvFile){
        cout << "menambah isi file:" <<fname<<endl;
        string buffer;
        int stop, count=1;
        buffer=rep_getline(CsvFile,&stop);
  
        while (stop != EOF){
            buffer=rep_getline(CsvFile,&stop);
            count++;
        }
        input(fname, count,'a');
    }
    else{ cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";}
    fclose(CsvFile);
}

void viewCsv(const char*fname){
    FILE *CsvFile;
    CsvFile = fopen(fname,"r");
    if (CsvFile){
        cout << "melihat isi file :" <<fname<<endl;
         string buffer;
        int stop, count=1;
        buffer=rep_getline(CsvFile,&stop);
  
        while (stop != EOF){
            buffer=rep_getline(CsvFile,&stop);
            int comma1 = rep_find(buffer,',', 0),
                comma2 = rep_find(buffer,',', comma1+1),
                comma3 = rep_find(buffer,',', comma2+1);
            
            string  nis=rep_substr(buffer,comma1+1, comma2-(comma1+2)),
                    nama=rep_substr(buffer,comma2+1, comma3-(comma2+2)),
                    jkl=rep_substr(buffer,comma3+1,1),
                    thl=rep_substr(buffer,comma3+4,4);
            
            cout<<"\n\nNo: :"<<count<<endl
                <<"nama :"<< nama<<endl
                <<"nis  :"<<nis<<endl
                <<"jenis kelamin :"<<jkl<<endl
                <<"tahun lahir ;"<<thl<<endl;
            count++;
        }
    }
    else{cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";}
    fclose(CsvFile);
}

void viewNo(const char*fname, int num){
    FILE *CsvFile;
    CsvFile = fopen(fname,"r");
    if (CsvFile){
        cout << "melihat data siswa no :"<<num<<" pada file :"<<fname<<endl;
        string buffer;
        int stop, count=1;
        bool nofound= false;
        buffer=rep_getline(CsvFile,&stop);
        // string nis,nama,jkl,thl;
  
        while (stop != EOF){
            buffer=rep_getline(CsvFile,&stop);
            if (count==num){
                nofound= true;
                break;
                }
            count++;
        }
        if (nofound){
             int comma1 = rep_find(buffer,',', 0),
                comma2 = rep_find(buffer,',', comma1+1),
                comma3 = rep_find(buffer,',', comma2+1);
            
            string  nis=rep_substr(buffer,comma1+1, comma2-(comma1+2)),
                    nama=rep_substr(buffer,comma2+1, comma3-(comma2+2)),
                    jkl=rep_substr(buffer,comma3+1,1),
                    thl=rep_substr(buffer,comma3+4,4);

            cout<<"No: :"<<count<<endl
                <<"nama :"<< nama<<endl
                <<"nis  :"<<nis<<endl
                <<"jenis kelamin :"<<jkl<<endl
                <<"tahun lahir ;"<<thl<<endl;
        }else{cout<<"data siswa no : "<<num<<" tidak ditemukan dalam file ini";}
    }
    else{ cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";}
    fclose(CsvFile);
}

void edit(const char*fname, int num){
    FILE *CsvFile;
    CsvFile = fopen(fname,"r");
    remove("temp.csv"); 
    if (CsvFile){
        FILE *tempfile;
        tempfile = fopen("temp.csv","a+");
        cout<<"mengubah data siswa no :"<<num<<" pada file :"<< fname<<endl; 
        string buffer;
        int stop, count=1;
        bool nofound= false;
        buffer=rep_getline(CsvFile,&stop);
        const char *to_file= &buffer[0];
        fprintf(tempfile, "%s", to_file);
        while (stop !=EOF){
            buffer=rep_getline(CsvFile,&stop);
           
            if(count == num ){
                fclose(tempfile);
                nofound= true;
                break;
            }
            const char *to_file= &buffer[0];
            fprintf(tempfile, "%s", to_file);
            count++;
        }
        if(nofound){
            input("temp.csv ",num,'e');
            tempfile = fopen("temp.csv","a+");
            while (stop!=EOF){
                buffer=rep_getline(CsvFile,&stop);
                const char *to_file= &buffer[0];
                 fprintf(tempfile, "%s", to_file);
            }
        }else{cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";}
        fclose(tempfile);
        fclose(CsvFile);

        remove(fname);
        rename("temp.csv",fname);
    }
    else{ cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";}
}

void deleteCsv(const char*fname, int num){
    FILE *CsvFile;
    CsvFile = fopen(fname,"r");
    remove("temp.csv");
    if (CsvFile){
        cout<<"menghapus data siswa no :"<<num<<" pada file"<< fname<<endl;
        FILE *tempFile;
        tempFile = fopen("temp.csv","a+");
        string buffer;
        int stop, count=1;
        bool nofound= false;
        buffer=rep_getline(CsvFile,&stop);
        const char *to_file= &buffer[0];
        fprintf(tempFile, "%s", to_file);
        while (stop !=EOF){
            buffer=rep_getline(CsvFile,&stop);
           
            if(count == num ){
                // fclose(tempFile);
                nofound= true;
                break;
            }
            const char *to_file= &buffer[0];
            fprintf(tempFile, "%s", to_file);
            count++;
        }
        if (nofound){
            while (stop != EOF){
            buffer=rep_getline(CsvFile,&stop);
             int comma1 = rep_find(buffer,',', 0),
                comma2 = rep_find(buffer,',', comma1+1),
                comma3 = rep_find(buffer,',', comma2+1);
            
            string data = rep_substr(buffer,comma1+1,(comma3-comma1)+8);
            string num = to_string(count);
            data = num+","+data;
            const char *to_file = &data[0];
            fprintf(tempFile, "%s", to_file);
            count++;
            }
        }else{cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";}
        fclose(tempFile);
        fclose(CsvFile);

        remove(fname);
        rename("temp.csv",fname);

    }
    else{ cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";}

}