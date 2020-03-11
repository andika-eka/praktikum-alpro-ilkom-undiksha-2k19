#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void input(int num, string fname, string arg){
    fstream CsvFile ;
    CsvFile.open(fname, ios::out|ios::app);
    string nama, nis, text, numStr, thlStr;
    int thl;
    char jkl;

    cout <<"nama :";
    getline(cin,nama);
    
    cout <<"nis :";
    cin>>nis;
    cout <<"jenis kelamin [L/P]:";
    cin>>jkl;
    cout <<"tahun lahir :";
    cin>>thl;

    if((nis.size()!=7)||(!((jkl=='L')||(jkl=='l')||(jkl=='p')||(jkl='P')))){
        cout<<endl<<"input tidak valid"<<endl
            <<"nis harus tujuh digit"<<endl
            <<"jenis kelamin L/P";
        input(num,fname,arg);
    }
    else{
        numStr=to_string(num);
        thlStr=to_string(thl);

        if (arg=="a"){
            text= "\n"+numStr+"; "+nis+"; "+nama+"; "+jkl+"; "+thlStr;
        }
        else if(arg=="e"){
            text= numStr+"; "+nis+"; "+nama+"; "+jkl+"; "+thlStr; 
        }
        CsvFile<< text;
    }
}

void newCsv(string Fname){
    fstream CsvFile (Fname);
    if (CsvFile){
        cout << "FIlE dengan nama :"<< Fname << " sudah ada";
    }
    else{
        cout << " membuat file :"<< Fname;
        CsvFile.open(Fname, ios::out | ios::app);
        CsvFile<<"NO; NIS; NAMA; JENIS KELAMIN; TAHUN ";
    }
    CsvFile.close();
}

void appendCsv(string fname){
    fstream CsvFile;
    CsvFile.open(fname);
    if (CsvFile){
        cout << "menambah is file:" <<fname<<endl;
        string numStr, buffer;
        int num;

        while (!CsvFile.eof()){
            getline(CsvFile,buffer);
            int  Numcoma = buffer.find(";", 0);
            numStr = buffer.substr(0,Numcoma);
        }
        if(numStr=="NO"){num = 0;}
        else{num=stoi(numStr);}
        num++;
        input(num,fname,"a");
    }
    else{
        cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";
    }
    CsvFile.close();
}

void viewCsv(string fname){
    fstream CsvFile ;
    CsvFile.open(fname, ios::in);
    if (CsvFile){
        cout << "melihat is file :"<< fname << endl;
         string nis, nama, nama2, noStr, jklStr, thlStr;
        int thl, no;
        char jkl;

        string text,buffer;
         
        getline(CsvFile,buffer);
        while (!CsvFile.eof()){
            getline(CsvFile,buffer);
            
            int  Numcoma = buffer.find(";", 0);
            noStr = buffer.substr(0,Numcoma);
            if(noStr=="NO"){no = 0;}
            else{no=stoi(noStr);}

            nis = buffer.substr(Numcoma+2,7);

            int  coma = buffer.find(";", 11);
            nama = buffer.substr(11, coma-11);

            jklStr =buffer.substr(coma+2,1);
            jkl = jklStr[0];

            thlStr = buffer.substr(coma+5,4);
            thl = stoi(thlStr);
            
            cout << "no : "<<no<<endl
                 << "nama : "<<nama<<endl
                 << "NIS : "<<nis<<endl
                 << "jenis kelamin : "<< jkl<<endl
                 << "tahun lahir :" <<thl<< endl;
        }
    }
    else{
        cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";
    }
    CsvFile.close();
}

void viewNo(string fname, int num){
    fstream CsvFile ;
    CsvFile.open(fname, ios::in);
    if (CsvFile){
        cout << "melihat data siswa no:"<<num <<" pada file :"<< fname << endl;
        string nis, nama, nama2, noStr, jklStr, thlStr;
        int thl, no;
        char jkl;
        bool noFound=false;

        string text,buffer;
         
        getline(CsvFile,buffer);
        while (!CsvFile.eof()){
            getline(CsvFile,buffer);

            int  Numcoma = buffer.find(";", 0);
            noStr = buffer.substr(0,Numcoma);
            if(noStr=="NO"){no = 0;}
            else{no=stoi(noStr);}

            nis = buffer.substr(Numcoma+2,7);

            int  coma = buffer.find(";", 11);
            nama = buffer.substr(11, coma-11);

            jklStr =buffer.substr(coma+2,1);
            jkl = jklStr[0];

            thlStr = buffer.substr(coma+5,4);
            thl = stoi(thlStr);
            if (no == num){
                noFound=true;
                break;
            }
        }
        if (noFound){
            cout << "no : "<<no<<endl
                 << "nama : "<<nama<<endl
                 << "NIS : "<<nis<<endl
                 << "jenis kelamin : "<< jkl<<endl
                 << "tahun lahir :" <<thl<< endl;
        }
        else{
            cout<< "data siswa no :"<<num<<" tidak ditemukan pada file ini";
        }
    }
    else{
        cout << "File dengan nama :"<< fname << " tidak ditemukan di dalam directory ini";
    }
    CsvFile.close();
}
void edit(string fname, int num){
    cout << " mengubah data siswa no:"<< num <<" file :"<< fname<<endl;
    remove("temp.csv");
    fstream CsvFile, tempFile ;
    CsvFile.open(fname, ios::in);
    tempFile.open("temp.csv", ios::app);

    string numStr, buffer;
    
    while (!CsvFile.eof()){
            getline(CsvFile,buffer);
            int  Numcoma = buffer.find(";", 0);
            numStr = buffer.substr(0,Numcoma);
    }
    int endnum;
    if(numStr=="NO"){endnum = 0;}
    else{endnum=stoi(numStr);}
    
    CsvFile.close();
    CsvFile.open(fname, ios::in);

    int fnum;
    bool Nofound = false;

    while (!CsvFile.eof()){
        getline(CsvFile,buffer);
        int  Numcoma = buffer.find(";", 0);
        numStr = buffer.substr(0,Numcoma);
        if(numStr=="NO"){fnum = 0;}
        else{fnum=stoi(numStr);}
        if(fnum==num){
            Nofound=true;
            break;
        }
        if(fnum==endnum){tempFile<<buffer;}
        else{tempFile<<buffer<<endl;}
    }
    if(Nofound){
        input(num,"temp.csv","e");
        while (!CsvFile.eof()){
            getline(CsvFile,buffer);
            tempFile<<endl<<buffer;
        }
    }else{cout<<"data siswa no: "<< num <<"tidak ditemukan pada file ini";}
    
    
    CsvFile.close();
    tempFile.close();

    remove(fname.c_str());
    rename("temp.csv",fname.c_str());
}
void deleteCsv(string fname, int num){
    cout << " menghapus data siswa no:"<< num <<" file :"<< fname<<endl;
    remove("temp.csv");
    fstream CsvFile, tempFile ;
    CsvFile.open(fname, ios::in);
    tempFile.open("temp.csv", ios::out);

    string numStr, buffer, buffer2;

    while (!CsvFile.eof()){
            getline(CsvFile,buffer);
            int  Numcoma = buffer.find(";", 0);
            numStr = buffer.substr(0,Numcoma);
    }
    int endnum;
    if(numStr=="NO"){endnum = 0;}
    else{endnum=stoi(numStr);}
    
    CsvFile.close();
    CsvFile.open(fname, ios::in);

    int fnum, Numcoma;
    bool Nofound = false;

    while (!CsvFile.eof()){
        getline(CsvFile,buffer);
        Numcoma = buffer.find(";", 0);
        numStr = buffer.substr(0,Numcoma);
        if(numStr=="NO"){fnum = 0;}
        else{fnum=stoi(numStr);}
        if(fnum==num){
            Nofound=true;
            break;
        }
        if(fnum==endnum){tempFile<<buffer;}
        else{tempFile<<buffer<<endl;}
    }
    if(Nofound){
        getline(CsvFile,buffer);
        Numcoma = buffer.find(";", 0);
        numStr = buffer.substr(0,Numcoma);
        buffer2 = buffer.substr(Numcoma+2);
        if(numStr=="NO"){fnum = 0;}
        else{fnum=stoi(numStr);}
        tempFile<<fnum-1<<"; "<<buffer2;
        
        while (!CsvFile.eof()){
            getline(CsvFile,buffer);
            Numcoma = buffer.find(";", 0);
            numStr = buffer.substr(0,Numcoma);
            buffer2 = buffer.substr(Numcoma+2);
            if(numStr=="NO"){fnum = 0;}
        else{fnum=stoi(numStr);}
            tempFile<<endl<<fnum-1<<"; "<<buffer2;
        }{cout<<"data siswa no: "<< num <<"tidak ditemukan pada file ini";}
    }
    CsvFile.close();
    tempFile.close();

    remove(fname.c_str());
    rename("temp.csv",fname.c_str());

}
//author : P ANDIKA EP(1915101029)