#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (a>b) ? a:b


//function Prototypes
void readData();
void Compute(int *, int, int);
void printAnswer(int *, int, int,int, int);

int main(){
    
    readData();
    return 0;
}

//functions

void readData(){
    FILE *in = fopen("input.txt","r");
    int m,n,i,j;
    fscanf(in,"%d %d",&m,&n);
    int Data[m+1][n+1];
    
    for (i=0; i<m;i++)
    	for(j=0; j<n;j++)
    		fscanf(in,"%d",&Data[i][j]);
    		
	// pad data		
	for(i=0;i<=m;i++)
		Data[i][n] = 0;
	for(j=0;j<=n;j++){
		Data[m][j] = 0;
	}
	
    fclose(in);
    Compute((int*)Data,m,n);
}


void Compute(int * Data, int m, int n){
	int i,j;	
    for (i=m-1; i>=0;i--){
    	for(j=n-1; j>=0;j--){
    		if (*((Data+i*(n+1)) + j) == -1){
    			*((Data+i*(n+1)) + j )= -1;
			}
			else{
				int max = MAX(*((Data+i*(n+1)) + j+1) , *((Data+(i+1)*(n+1)) + j));
				*((Data+i*(n+1)) + j) =  *((Data+i*(n+1)) + j) + max;	
			}
    	}
	}
	
	printf("%d\n",*(Data));
	
	for(i=0;i<=m;i++)
		*((Data+i*(n+1)) + n) = -1;
	for(j=0;j<=n;j++){
		*((Data+m*(n+1)) + j) = -1;
	}
	
	
//	for (i=0; i<=m;i++){
//    	for(j=0; j<=n;j++){
//    		printf("%d ",*((Data+i*(n+1)) + j));
//		}
//		printf("\n");
//    }
	
	printAnswer((int*)Data,m,n,0,0);
}

void printAnswer(int * Data, int m, int n,int i, int j){
	if(i==m || j+1==n) return;
	int east = *((Data+(i)*(n+1)) + (j+1));
	int south = *((Data+(i+1)*(n+1)) + (j));
	
	if(east > south){
		printf("E");
		printAnswer((int*)Data,m,n,i,j+1);
	}
	else{
		printf("S");
		printAnswer((int*)Data,m,n,i+1,j);
	}
}



