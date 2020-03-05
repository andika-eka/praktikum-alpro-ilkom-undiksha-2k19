#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;


int main( int argc, char *argv[] )  {
	if (argc == 1){
		printf("Putu Andika Eka Putra \n");
		printf("1915101029\n");
		printf("Praktikum algoritma dan pemrograman\n");
		printf("Ilmu komputer UNDIKSHA 2020");
	}
	else if (argc==4){
		char opr = *argv[1];
		
	   	int num1 = atoi(argv[2]),
	   		num2 = atoi(argv[3]);
	   	
	   	switch(opr){
	   		case 't':{
	   			printf("%d", num1+num2);
				break;
			   }
	   		case 'k':{
	   			printf("%d", num1-num2);
				break;
			   }
	   		case 'l':{
	   			printf("%d", num1*num2);
				break;
			   }
	   		case 'b':{
	   			if (num2 == 0){
	   				printf("tidak terdefinisi");
	   				break;
				   }
	   			float num= num1;
			    printf("%f", num/num2);
				break;
			   }
			case 'p':{
				int num =pow(num1,num2);
				printf("%d",num);
				break;
				}
			case 'o':{
				float hasil = log(num1)/log(num2);
				printf("%f",hasil);
				break;
				}
	   		default :printf("input tidak valid \n ketik \"kalkulator help\"untuk batuan");
		   }
	   
	}
	else if (argc ==3){
		char opr = *argv[1];
	   	int num = atoi(argv[2]);
	   	switch(opr){
	   		case 'a':{
	   			float hasil = sqrt(num);
				printf("%d", hasil);
				break;
				}
			case 's':{
				float sinus = sin (num*M_PI/180);
				printf("%f", sinus);
				break;
				}
			case 'c':{
				float cosinus = cos (num*M_PI/180);
				printf("%f", cosinus);
				break;
				}
			case 'g':{
				if ((num + 90)%180==0){
					printf("tidak terdefinisi");
					break;
				}
				float tangen = tan (num*M_PI/180);
				printf("%f", tangen);
				break;
				}
			case 'o':{
				float hasil = log(num)/log(10.0);
				printf("%f",hasil);
				break;
			}
			case 'e':{
				float hasil = log(num);
				printf("%f",hasil);
				break;
			}
	   		default :printf("input tidak valid \n ketik \"kalkulator help\"untuk batuan");
		   }
				
	}
	else if (*argv[1]== 'h'){
		printf("input : kakulator argument bilangan_1 bilangan_2");
		printf("\n daftar  argument:");
		printf("\n 	t : penjumlahan");
		printf("\n 	k : pengurangan");
		printf("\n 	l : perkalian");
		printf("\n 	b : pembagian");
		printf("\n 	p : perpankatan");
		printf("\n 	o : logaritma");
		printf("\n\ninput : kakulator argument bilangan");
		printf("\n daftar  argument:");
		printf("\n 	a : akar kuadrat");
		printf("\n 	s : sinus");
		printf("\n 	c : cosinus");
		printf("\n 	g : tangen");
		printf("\n 	o : logaritma 10");
		printf("\n 	e : logaritma e");
	}
	else if (*argv[1]== 'd'){
		printf("");
	}
	
	else{printf("input tidak valid \n ketik \"kalkulator help\"untuk batuan");}
	return 0;
}
//author : pt andika ep(1915101029)
