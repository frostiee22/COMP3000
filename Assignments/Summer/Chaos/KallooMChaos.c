/*
 * main.c
 *
 *  Created on: Jun 29, 2016
 *      Author: Mitra
 */

#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#define Word_Size 10

void ReadInData();
void combinationUtil(int n,int r,int index,int data[],int i);
void printCombination(int n, int r);


char** WORDS;
char** ReverseWords;
int CHAOS = 0;

int main(){
    FILE * out = fopen("output.txt","w");
    FILE* in = fopen("input.txt","r");
    
    int n, r = 2;;
    fscanf(in,"%d",&n);
    fclose(in);



   int a;

   WORDS = (char**)malloc((n+1) * sizeof(char*));
   			for( a = 0; a <= n; a++){
   				WORDS[a] = (char*)malloc((Word_Size+1)*sizeof(char*));
			   }
   ReverseWords  = (char**)malloc((n+1) * sizeof(char*));
		for( a = 0; a <= n; a++){
			ReverseWords[a] = (char*)malloc((Word_Size+1)*sizeof(char*));
	   }

    ReadInData();
    printCombination(n, r);
    
    fprintf(out,"%d\n",CHAOS);

	
	fclose(out);
 return 0;
}


void ReadInData(){
	int amt_words,i;
	FILE*in = fopen("input.txt","r");
	fscanf(in,"%d",&amt_words);

	char temp_word[Word_Size+1];
	for(i=1;i <= amt_words;i++){
		fscanf(in,"%s",temp_word);
		strcpy(WORDS[i],temp_word);
		strcpy(ReverseWords[i],strrev(temp_word));
	}
	fclose(in);

}


void printCombination(int n, int r)
{
    int data[r];
    combinationUtil(n, r, 0, data, 1);
}


void combinationUtil(int n, int r, int index, int data[], int i){
    if (index == r){
    	
    	if (strcmp(WORDS[data[0]], WORDS[data[1]]) < 0){
    		if (strcmp(ReverseWords[data[1]], ReverseWords[data[0]]) < 0){
    			CHAOS++;
			}
		}
    	
    	if (strcmp(WORDS[data[1]], WORDS[data[0]]) < 0){
    		if (strcmp(ReverseWords[data[0]], ReverseWords[data[1]]) < 0){
    			CHAOS++;
			}
		}
        return;
    }

    if (i > n)
        return;

 	data[index] = i;
    combinationUtil(n, r, index+1, data, i+1);

    combinationUtil(n, r, index, data, i+1);
}



