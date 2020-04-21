#include <iostream>
#include <string>
#include "func_replica.h"
using namespace std;

struct orang{
	string nama;
	int id_ayah;
};

orang CsvToArr (FILE* file, bool *stop){
	orang array;
	string buffer;
	int stop1;
	
	buffer = rep_getline(file, &stop1);
	if (stop1==EOF){
		*stop=false;
	}
	else{
		int comma1 = rep_find(buffer,',', 0),
    	comma2 = rep_find(buffer,',', comma1+1),
    	line = rep_find(buffer,'\n',comma2+1);
    
    	array.nama=rep_substr(buffer,comma1+1, comma2-(comma1+2));
    	string Strid = rep_substr(buffer, comma2+1, line-(comma2+2));
    	array.id_ayah=atoi(&Strid[0]);
    
		return array;
	}

}

int ID_tracker(orang Ftree[], int index){
	int decendant=0;

	for(int i=0;i<50;i++){
		if (Ftree[i].id_ayah == index){
			cout<<Ftree[i].nama<<endl;
			decendant++;
			int child = ID_tracker(Ftree,i);
			decendant += child;
		} 
	}
	return decendant;
}

int main(){
	FILE* Ftree;
	Ftree = fopen("norse gods family tree.csv","r");
	int stop1, decendant;
	orang norse_god[50];
	bool stop=true;
	rep_getline(Ftree, &stop1);
	
	int index=0;
	
	while (stop){
        norse_god[index] =CsvToArr(Ftree,&stop);
		index++;
    }   

	cout << "masukan index: ";
	cin >> index;
	cout << "keturunan "<<norse_god[index].nama<<" :"<<endl;
	decendant = ID_tracker(norse_god, index);
	cout << " jumlah keturunan :"<<decendant<<endl;
	
	return 0;
}
