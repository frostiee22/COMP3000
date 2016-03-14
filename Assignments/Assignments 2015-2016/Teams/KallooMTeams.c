#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WordSize 199999


/*  
	This program scans an entire line and puts a interger values that indicates the teams
	using those intergers i was able to traverse the binary tree and do the  appropriate operations
*/


struct treeNode {
	struct treeNode *leftPtr;
	char data[WordSize];
	int num;
	struct treeNode *rightPtr;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;





// function prototypes
void setup();
void insertNode( TreeNodePtr *treePtr, char * value, int n);
void ChangeTeamNumber(TreeNodePtr treePtr,int current,int new);
void inOrder(FILE*out,TreeNodePtr treePtr);
void Members(FILE*out,TreeNodePtr treePtr,char *word,int number);

TreeNodePtr rootPtr = NULL;
int team = 1;



int main() {
	printf("\nCOMP3000 Assignment 3\n\nStudent # : 812000767\n\n\n\n********** Teams ************* \n\n\n");
		
	setup();
	FILE*out = fopen("output.txt","w");
	inOrder(out,rootPtr);
		
fclose(out);
return 0;

}



// scanning names from file and assiging a number to the
// name to represent their team
void setup(){
	
	char word[WordSize];
	char tempword[WordSize];
	
	int x = 0, i = 0, j=0, k=0, count=0;
	FILE*in = fopen("input.txt","r");
	
	 while(fgets(word,WordSize,in) != NULL){
     	i=0;
     
 			x = strlen(word);

			if (word[i] != '\n' ){

				while ( i <= x && j < x ){
					if (word[i] >= 'A' && word[i] <= 'z'){
						tempword[j] = tolower(word[i]);
						j++;
					}

					else {
						if (tempword[0] != '\0'){

							int x=0; 
								x = strlen(tempword);
								tempword[0] = toupper(tempword[0]);
							
							    insertNode(&rootPtr,tempword,count);

						}
							for (j=0;j<x+1;j++){
								tempword[j] = '\0';
							}
							j=0;
					}
					i++;
				}
			}
		
		// reset arrays 
		for (i=0;i<x+1;i++){
			word[i] = '\0';
			tempword[i] = '\0';
		}

		count++;	
	}
	
	fclose(in);
}



// FUNCTIONS

// insert node in to tree

void insertNode( TreeNodePtr *treePtr, char * value ,int n)
{
	// if tree is empty
	if (*treePtr == NULL){
		*treePtr = malloc(sizeof(TreeNode));
		
		// if memory was allocated,then assign data
		if (*treePtr != NULL){
			strcpy((*treePtr)->data,value);
			(*treePtr)->num = n;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else {
			printf("%s not inserted, out off memory.\n",value);
		} 
	}
	else { // tree not empty
		// data to insert is less than data in current node
		if (strcmp(value,(*treePtr)->data) < 0){
			insertNode( &((*treePtr)->leftPtr),value,n);
		}
		// data to insert is greater than data in current node
		else if( strcmp(value,(*treePtr)->data) > 0 ) {
			insertNode( &((*treePtr)->rightPtr),value,n);
		}
		else{
			// this line changes the words from before in the binary tree
			// to have the same value as these words being entered
			// therefore they are synonyms
			ChangeTeamNumber(rootPtr,(*treePtr)->num,n);
		}
	}
}


// groupping all synonyms together 

void ChangeTeamNumber(TreeNodePtr treePtr,int current,int new)
{
	char temp[WordSize];
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		ChangeTeamNumber(treePtr->leftPtr,current,new);
		
		strcpy(temp,treePtr->data);
		if(treePtr->num == current )
			treePtr->num = new;
	
		ChangeTeamNumber(treePtr->rightPtr,current,new);
	}
}



// Getting Name in alphabetical order
void inOrder(FILE*out,TreeNodePtr treePtr)
{
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		inOrder(out,treePtr->leftPtr);
		
			if(treePtr->num != -1){
				fprintf(out,"Team %d",team);
				fprintf(out,"\n%s ",treePtr->data);
				Members(out,rootPtr,treePtr->data,treePtr->num);
				fprintf(out,"\n\n");
				team++;
			}	
		inOrder(out,treePtr->rightPtr);
	}
	
}


// Printing Members that belong to this member team
void Members(FILE*out,TreeNodePtr treePtr,char *word,int number)  
{
	// if tree is not empty, traverse
	if (treePtr != NULL) {
		Members(out,treePtr->leftPtr,word,number);
		
		if ( (strcmp(word,treePtr->data) != 0) && (treePtr->num == number) && (treePtr->num != -1)){
			fprintf(out,"%s ",treePtr->data);
			treePtr->num = -1;
			
		}
		Members(out,treePtr->rightPtr,word,number);
	}
}



