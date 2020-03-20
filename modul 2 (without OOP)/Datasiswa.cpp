#include <iostream>
#include <string>
#include "Csv_ops_noOOP.h"
// #include "Csv_Fops.h"
using namespace std;

int main(int argc, char *argv[]){
    if (argc == 1){
        cout << "Putu Andika Eka Putra"<<endl
             << "1915101029"<<endl
             << "Praktikum algoritma dan pemrograman"<<endl
             << "Ilmu komputer UNDIKSHA 2020"<<endl;
	}
    else if (argc == 3){
        string cmd(argv[1]);
        string file (argv[2]);
        file =file+".csv";
        const char *CsvFile= &file[0];
        if (cmd == "-n") {
            // cout << " membuat file :"<< CsvFile ;
            newCsv(CsvFile);
            char option;
            do{
                appendCsv(CsvFile);
                cout << "ketik Y/y untuk input data baru :";
                cin >>option;
            }while ((option == 'y')||(option =='Y'));
            
        }
        else  if (cmd == "-a") {
            // cout << "menambah is file:" <<CsvFile;
             char option;
             do{
                appendCsv(CsvFile);
                cout << "ketik Y/y untuk input data baru :";
                cin >>option;
            }while ((option == 'y')||(option =='Y'));
        }
        else  if (cmd == "-v") {
        //    cout << " melihat file :"<< CsvFile ;
           viewCsv(CsvFile);
        }
        else {cout << "INPUT TIDAK VALID"<< endl << " \"ketik Datasiswa -help\" untuk bantuan";}
        

    }
    else if (argc == 4){
        string cmd(argv[1]);
        string file (argv[2]);
        file =file+".csv";
        const char *CsvFile= &file[0];
        int NoS = atoi(argv[3]);

        if (cmd == "-e") {
            // cout << " mengubah data siswa no:"<< NoS <<" file :"<< CsvFile ;
            edit(CsvFile,NoS);
        }
        else  if (cmd == "-d") {
            // cout << " menghapus data siswa no:"<< NoS <<" file :"<< CsvFile;
            deleteCsv(CsvFile,NoS);
        }
        else if (cmd== "-v"){
            // cout << "melihat data siswa no :"<<NoS << "file :" << CsvFile;
            viewNo(CsvFile,NoS);
        }
        else {cout << "INPUT TIDAK VALID"<< endl << " \"ketik Datasiswa -help\" untuk bantuan";}
        
    }
    else if (argc == 2){
        string cmd(argv[1]);

        if (cmd =="-help")
        {
            cout<<"*****************HELP*****************"<<endl<<endl
                <<"datasiswa -n namafile = membuat file baru"<<endl
                <<"datasiswa -a namafile = menambah isi file"<<endl
                <<"datasiswa -v namafile = melihat isi file"<<endl<<endl
                <<"datasiswa -e namafile nomor = mengubah data salah satu siswa"<<endl
                <<"datasiswa -d namafile nomor = menghapus data salah satu siswa"<<endl
                <<"datasiswa -v namafile nomor = melihat data salah satu siswa";
        }
         else {cout << "INPUT TIDAK VALID"<< endl << " \"ketik Datasiswa -help\" untuk bantuan";}
    }
    
    else {cout << "INPUT TIDAK VALID"<< endl << " \"ketik Datasiswa -help\" untuk bantuan";}
}
//author : pt andika ep(1915101029)