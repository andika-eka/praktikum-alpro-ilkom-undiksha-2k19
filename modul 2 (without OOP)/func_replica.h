#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

string rep_getline(FILE* file, int *c ) {
    int size = 1024, pos;
    char *buffer = (char *)malloc(size);
    pos = 0;
    do{ 
      *c = fgetc(file);

      if(*c != EOF) {buffer[pos++] = (char)*c;}
      
      if(pos >= size - 1) { 
        size *=2;
        buffer = (char*)realloc(buffer, size);
      }
    }while(*c != EOF && *c != '\n');   
    buffer[pos] = 0;
    string text = string (buffer);         
    free(buffer);
    return text;
}

int rep_find(string line, char target, int start){
    char temp;
    int count = start;
    do{
        temp = line[count];
        if (temp==target){break;}
        count++;

    }while (true);
    return count;
}

string rep_substr(string line, int start, int length){
    char substr[50];
    int count= 0;

    while (count <=length){
        substr[count]= line[start+count];
        count++;
    }
    substr[count]='\0';
    string text = string (substr);         
    return text;
}