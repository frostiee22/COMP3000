#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000


int genNumbers(int [][5],int);
int isPrime(int);
int SumToN(int, int);
void printArr();
void Index();
void fillGrid(int);


int Numbers[SIZE] [5],  // stores all prime numbers that add up to m
	STORE[5][5], // stores the grid solutions
	amtNumbers,  // amt of prime numbers stored in Numbers
	indexes[10], // keep track of the changes of the left most digit in the Numbers array
	solutions = 0; // number of solutions found

FILE*out;
FILE*in;


int main(){
	
	in = fopen("input.txt","r");
	out = fopen("output.txt","w");
	
	printf("\nCOMP3000 Assignment 4\n\nStudent # : 812000767\n\n\n\n********** Primes ************* \n\n\n");
	
	int n, m;
	fscanf(in,"%d %d",&m,&n);
	amtNumbers = genNumbers(Numbers,m);
	Index();
	int i,j;
	
	fillGrid(n);
	printf("# Solutions :%d\n", solutions);
	fclose(in);
	fclose(out);
	
	
	//system("PAUSE");
	return 0;		
}


void Index(){
	int i,pos=1;
	indexes[pos] = 0;
	for (i=0;i<amtNumbers;i++){
		if (Numbers[i][0] != pos){
			pos++;
			indexes[pos] = i;
		}		
	}
	indexes[10] = amtNumbers-1;	
}

int genNumbers(int Numbers[][5],int val){
	int i, count = 0;
	printf("building primes list...\n");
	for ( i = 10001; i< 99999;i+=2){
		if (isPrime(i)){
			if (SumToN(i,val)){
				int start = 4, num = i;
				while (num > 0){
					Numbers[count][start--] = num%10;
					num /= 10;	
				}
				count++;
			}
		}
	}
	printf("finish building primes list!\n");
	return count;
}

int isPrime(int n) {
	if (n <= 1) return 0;
	if (n == 2) return 1;
	if (n % 2 == 0) return 0;
	int h;
	for (h = 3; h*h <= n; h += 2)
		if (n % h == 0) return 0;
	return 1;
}

int SumToN(int num, int n){
	int sum = 0;
	while (num > 0){
		sum += num%10;
		num /= 10;
	}
	if (sum != n) return 0;
	return 1;	
}


void printArr(){
	int i,j;
	for (i=0;i<5; i++){
		for (j=0;j<5;j++){
			fprintf(out,"%d",STORE[i][j]);
		}
		fprintf(out,"\n");
	}
	fprintf(out,"\n");
}



void fillGrid(int n){
	void row1(int);
	STORE[0][0]  = n;
	row1(n);	
}

void row1(int n){
	void col1(int);
	int i,j;
	
	printf("Searching..\n");
	for (i=indexes[n];i<indexes[n+1];i++){
		int temp = (indexes[n+1] - indexes[n])/2;
		if (i == indexes[n] + temp){
			printf("Half Way done!\n");
		}	
	
		int check = 1;
		for(j=1;j<5;j++){
			if(Numbers[i][j] == 0) check = 0; 
		} 
		
		if (check){
			for(j=1;j<5;j++) STORE[0][j] = Numbers[i][j]; 
			col1(STORE[0][0]);
		} 
	}		
}

void col1(int n){
	void dig1(int);
	int i,j;
	
	for (i=indexes[n];i<indexes[n+1];i++){	
		int check = 1;
		for(j=1;j<5;j++){
			if(Numbers[i][j] == 0) check = 0; 
		} 
		if (check){
			for(j=1;j<5;j++) STORE[j][0] = Numbers[i][j]; 
			dig1(STORE[4][0]);
		} 	
	}	
}

void dig1(int n){
	void row2(int);
	int i,j;
	for (i = indexes[n]; i < indexes[n+1]; i++){	
		if(STORE[0][4] == Numbers[i][4]){
			STORE[3][1]	= Numbers[i][1];
			STORE[2][2]	= Numbers[i][2];
			STORE[1][3]	= Numbers[i][3];
			row2(STORE[1][0]);	
		}
	}
}


void row2(int n){
	void col2(int);
	int i;
	for (i=indexes[n];i<indexes[n+1];i++){
		if (STORE[1][3] == Numbers[i][3]){
			STORE[1][1] = Numbers[i][1];
			STORE[1][2] = Numbers[i][2];
			STORE[1][4] = Numbers[i][4];
			col2(STORE[0][1]);
		}	
	}	
}

void col2(int n){
	void row3(int);
	int i,j;
	for (i=indexes[n];i<indexes[n+1];i++){		
		if(STORE[1][1] == Numbers[i][1] && STORE[3][1] == Numbers[i][3]){	
				STORE[2][1]	= Numbers[i][2];
				STORE[4][1]	= Numbers[i][4];
				row3(STORE[2][0]);			
		}
	}
}

void row3(int n){
	void col3(int);
	int i;
	for (i=indexes[n];i<indexes[n+1];i++){
		if(STORE[2][1] == Numbers[i][1] && STORE[2][2] == Numbers[i][2]){
			STORE[2][3]	= Numbers[i][3];
			STORE[2][4]	= Numbers[i][4];			
			col3(STORE[0][2]);		
		}
	}		
}

void col3(int n){
	void row4(int);
	int i;
	for (i = indexes[n];i<indexes[n+1];i++){
		if (STORE[1][2] == Numbers[i][1] && STORE[2][2] == Numbers[i][2]){
			STORE[3][2] = Numbers[i][3];
			STORE[4][2] = Numbers[i][4];
			row4(STORE[3][0]);
		}
	}
}

void row4(int n){
	void col4(int);
	int i;
	for (i=indexes[n];i<indexes[n+1];i++){
		if(STORE[3][1] == Numbers[i][1] && STORE[3][2] == Numbers[i][2]){
			STORE[3][3]	= Numbers[i][3];
			STORE[3][4]	= Numbers[i][4];			
			col4(STORE[0][3]);		
		}
	}	
}

void col4(int n){
	void row5(int);
	int i;
	for (i = indexes[n];i<indexes[n+1];i++){
		if (STORE[1][3] == Numbers[i][1] && STORE[2][3] == Numbers[i][2] && STORE[3][3] == Numbers[i][3]){
			STORE[4][3] = Numbers[i][4];
			row5(STORE[4][0]);
		}
	}	
}

void row5(int n){
	void col5(int);
	int i;
	for (i=indexes[n];i<indexes[n+1];i++){
		if(STORE[4][1] == Numbers[i][1] && STORE[4][2] == Numbers[i][2] &&  STORE[4][3] == Numbers[i][3]){
			STORE[4][4]	= Numbers[i][4];			
			col5(STORE[0][4]);		
		}
	}
}

void col5(int n){
	void dig2(int);
	int i;
	for (i = indexes[n];i<indexes[n+1];i++){
		if ((Numbers[i][1]==STORE[1][4])&&
			(Numbers[i][2]==STORE[2][4])&&
			(Numbers[i][3]==STORE[3][4])&&
			(Numbers[i][4]==STORE[4][4])){
			dig2(STORE[0][0]);
		}
	}	
}

void dig2(int n){
	int i;
	for (i = indexes[n]; i < indexes[n+1]; i++){
		if ((Numbers[i][0]==STORE[0][0])&&
			(Numbers[i][1]==STORE[1][1])&&
			(Numbers[i][2]==STORE[2][2])&&
			(Numbers[i][3]==STORE[3][3])&&
			(Numbers[i][4]==STORE[4][4])){
			printArr();
			solutions++;
		}		
	}
}



