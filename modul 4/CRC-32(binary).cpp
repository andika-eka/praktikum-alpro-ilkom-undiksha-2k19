#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

int main(){
	cout <<"MODUL 4:"<<endl<<"	CRC 32";
	char repeat;
	string filestr;
	const char *file;
	do{	
		cout<< "masukan nama file :";
		
		cin >> filestr;
		file=&filestr[0];
		FILE*fp,*count;
		fp = fopen(file, "rb");
		count = fopen(file, "rb");
		unsigned int crc=0xffffffff, data=0;
		int stop;
		int endbyte;
		// bool end_of=false;
		
		if (fp!=NULL){
			while(stop!=EOF){

				endbyte=0;
				for(int i=0;i<4;i++){
					stop = fgetc(count);
					// cout <<stop<<endl;
					if (stop == EOF){
						break;
					}
					endbyte++;
				}
				fread(&data,sizeof(int),1,fp);
				
				// cout<< data <<":::"<<crc<<endl;

				if (endbyte<4){
					data = data<<(32-(endbyte*8));
				}

				crc^=data;
				// cout << data<<"___"<<crc<<endl;
			}
			// cout << data<<"___"<<crc<<"_____"<<endbyte<<endl;
			cout <<"CRC 32 ="<<crc<<endl;
		}
		fclose(fp);
		fclose(count);

		cout<<"ketik 'y' untuk mengulang :";
		cin >> repeat;
	}while ((repeat=='y')||(repeat=='Y'));

}
