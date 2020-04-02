#include <iostream>
#include <string>
using namespace std;

int kabisat(int start, int stop){
    int days = (stop/4)-(start/4);
    days-=(stop/100)-(start/100);
    days +=(stop/400)-(start/400);
    return days;
}
int Tahun(int start, int stop){
    int days = 365*(stop-start);
    days +=kabisat(start,stop-1);
    return days;
}

int Hari(int tgl, int bln, int tahun){
    bool kabisat;
    if (tahun %4 ==0){
        kabisat=true;
        if(tahun%100==0){
                kabisat=false;
                if (tahun%400==0){kabisat=true;}
            }
    }else  {kabisat=false;}

    int days;
    tgl--;
    int Days_month[12]={0,31,59,90,120,151,181,212,243,273,304,334};
    if (bln<=2){
        days = Days_month[bln-1]+tgl;
    }
    else{
        days= Days_month[bln-1]+tgl;
        if(kabisat){days++;}
    }
    days+=Tahun(1950,tahun);
    return days;
}
int bulan (string bln){
    string bulan_list[12]={"januari","februari","maret","april","mei","juni",
                        "juli","agustus","september","oktober","november","desember"};
    int bulan;
    for(int i=0;i<=12;i++){
        if (bln ==bulan_list[i]){
            bulan= i;
            break;
        }
        bulan =13;
    }
    return bulan+1;
}

int main(int argc, char *argv[]){
    bool valid_input=true;
    int tgl,bln,tahun;
    if (argc==1){
        string blnstr;
        cout<<"masukan tanggal lahir anda: "<<endl;
        cout<<"tanggal: ";
        cin >>tgl;
        cout<<"bulan :";
        cin >>blnstr;
        bln =bulan(blnstr);
        cout<<"tahun :";
        cin>>tahun;

        if((bln>12)||(tahun<1950)){
            valid_input=false;
        }
        
    }
    else if(argc=4){
        tgl=atoi(argv[1]);
        string blnstr(argv[2]);
        bln =bulan(blnstr);
        tahun=atoi(argv[3]);
        
        if((bln>12)||(tahun<1950)){
            valid_input=false;
        }
    }

    if(valid_input){
        int days = Hari(tgl,bln,tahun);
//         cout<< days;
        //harus dimulai dari 1 january 1950
        string wara_7List[7]={"radite","soma","anggara","budha","respati","sukra","saniscara"},
        wara_5List[5]={"wage", "kliwon","umanis","paing","pon"},
        wukuList[30]={"kuningan","langkir","medangsia","pujut","pahang","krulut","merakih","tambir","medangkungan","matal",
                "uye","menail","prangbakat","bala","ugu","wayang","kelawu","dukut","watugunung","sinta",
                "landep","ukir","kulantir","tolu","gumbreg","wariga","warigadean","julungwangi","sungsang","dungulan"};
        
        string wara_7, wara_5, wuku;
        int x = days%7;
        wara_7=wara_7List[x];
        
        x=days%5;
        wara_5=wara_5List[x];
        
        x=(days/7)%30;
        wuku=wukuList[x];

        cout<<"otonan : "<<wara_7<<" "<<wara_5<<" "<<wuku<<endl;
    }else{
        cout<<"INPUT TIDAK VALID"<<endl
            <<"hari di input seperti contoh : 1 januari 2000"<<endl
            <<"hari yang di input tidak boleh sebelum 1 januari 1950";
    }
    
    return 0;
}
//author : P andika EP 1915101029
