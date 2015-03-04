// Problem :
// 1st : to find the number of sections and the largest section 
// 2nd : finding if a path from a to b exist, if it does print the path


// Solution :
// 1st : move throught the 2D array and for every empty location make it as section one and count all the spaces 
// 		 bounded by #. then move to the next empty location and perform the same task
// 2nd : starting from a try all possible locations, if a possible location equal b return 1 for found else
//       return 0 for #. when a location is processed % is used to marked it so it wont be revisited.
//       lasty place X in the locations that returned 1
// 



#include <stdio.h>

#define xaxis 110
#define yaxis 110

char arr[yaxis][xaxis]; // array used to  store the maze
char B[yaxis][xaxis];
int temp;
int LargestSection = 0;
int NumOfSections = 0;
int path;

void InitializeArry(int m, int n, char array[yaxis][xaxis]);
void CreateMaze(FILE*in, int m, int n, char array[yaxis][xaxis]);
void PrintArray(FILE*out, int m, int n, char array[yaxis][xaxis]);
void FillGrid(int x, int i, int j, char array[yaxis][xaxis]);
void FindPath(int i, int j,int m, int n, char array[yaxis][xaxis]);
void compute (int m,int n,char array[yaxis][xaxis]);

int A2B(char array[yaxis][xaxis], int a, int b, int c, int d);
void copyMaze(char A[yaxis][xaxis], char B[yaxis][xaxis]);


int main(){
		srand(time(0));
		printf("\nCOMP3000 Assignment 3\n\nStudent # : 812000767\n\n\n\n********** Maze ************* \n\n\n");

	FILE*in = fopen("input.txt", "r");
	FILE*out = fopen("output.txt", "w");

	int m, n; // to create the array needed

		fscanf(in, "%d %d",&m, &n);

		m = m * 2;
		n = n * 2;

		InitializeArry(m, n, arr);

		CreateMaze(in, m, n, arr);

		copyMaze(arr,B);

		int a,b,c,d;
	
		fscanf(in,"%d %d %d %d",&a, &b, &c, &d);
		
		a = a*2-1;
		b = b*2-1;
		c = c*2-1;
		d = d*2-1;
		compute(m,n,arr);

		fprintf(out,"\nNumber of sections : %d \nSize of largest section : %d\n", NumOfSections, LargestSection);
		fprintf(out, "\n");
		A2B(B, a, b, c, d);
		if (path == 1){
			PrintArray(out, m, n, B);
		}
		else{
			fprintf(out,"No path from (%d,%d) to (%d,%d)\n",a,b,c,d);
		}



	fclose(in);
	fclose(out);
	printf("\n\n");
	//system("PAUSE");
	return 0;

}

// places * in the even places in the array
// this is where the walls will be place
// and inserts 0 in every other place
void InitializeArry(int m, int n, char array[yaxis][xaxis]){
	int i = 0, j = 0;

	for (i = 0; i <= m; i++){
		for (j = 0; j <= n; j++){
			array[i][j] = '0';
			if (i % 2 == 0)
				array[i][j] = '!';
			if (j % 2 == 0)
				array[i][j] = '!';
		}
	}
}

// creating by supplying the values to be used by the FillGrid function
void CreateMaze(FILE*in, int m, int n, char array[yaxis][xaxis]){
	int i, j,x;

	for (i = 1; i <= m / 2; i++){
		for (j = 1; j <= n / 2; j++){
			fscanf(in, "%d", &x);
			FillGrid(x, i, j, array);
		}
	}
}

// printing out the Maze to the output file
void PrintArray(FILE*out, int m, int n, char array[yaxis][xaxis]){
	int i = 0, j = 0;

	for (i = 0; i <= m; i++){
		fprintf(out, "\n");
		for (j = 0; j <= n; j++){
			if (array[i][j] == '!' || array[i][j] == '%')
				array[i][j] = ' ';
			if (array[i][j] != '0')
				fprintf(out, "%c", array[i][j]);
			else fprintf(out," ");

		}
	}
}


//find the location of where to place the # sign and places it there
void FillGrid(int x, int i, int j, char array[yaxis][xaxis]) {
	i = i * 2 - 1;
	j = j * 2 - 1;

	if (x >= 8)
		array[i + 1][j] = '#';
	x = x % 8;

	if (x >= 4)
		array[i][j + 1] = '#';
	x= x % 4;

	if (x>= 2)
		array[i - 1][j] = '#';
	x = x % 2;

	if (x == 1)
		array[i][j - 1] = '#';

	// placing # on the diagonals
	array[i + 1][j + 1] = '#';
	array[i + 1][j - 1] = '#';
	array[i - 1][j + 1] = '#';
	array[i - 1][j - 1] = '#';
	return;
}

// finds the 0s in the path the get the largest section
void FindPath(int i, int j,int m,int n, char array[yaxis][xaxis]){
	if (array[i][j] != '#'){

		if (array[i][j] == '1'){
				return;
		}
		else if ( (m<1)||(n<1)||(i>m)||(j>n)){
				return ;
			}

	    else if (array[i][j] == '0'){
			array[i][j] = '1';
			temp++;

			if (temp > LargestSection){
				LargestSection = temp;
			}
		}

			array[i][j] = '1';

			FindPath(i+1,j,m, n, array);
			FindPath(i,j+1,m, n, array);
			FindPath(i-1,j,m, n, array);
			FindPath(i,j-1,m, n, array);
	}
	else return;
}

// used to find the amount of sections there are
void compute (int m,int n,char array[yaxis][xaxis]){
		int i, j;
	for (i = 0; i < m; i++){
		for (j = 0; j < n; j++){
			if (array[i][j] == '0'){
				NumOfSections++;
				FindPath(i, j, m ,n ,array);
				temp = 0;
			}
		}
	}
}




int north=0,east=0,south=0,west=0;
int A2B(char array[yaxis][xaxis], int a, int b, int c, int d){
	if ( a == c && b == d) {
		path = 1;
		array[a][b] = 'X';
		return 1;
	}
	if (array[a][b] == '#') return 0;
	if (array[a][b] == '%') return 0;
	if (array[a][b] == 'X') return 0;
	
	
	array[a][b] = '%';

    if(path == 0){

    	int ran = (rand()%5)+1;

    	if(ran == 1){
    		north = north +  A2B(array,a-1,b,c,d);        	  
	    	south = south + A2B(array,a+1,b,c,d);
	    	east = east +  A2B(array,a,b+1,c,d); 
	    	west = west + A2B(array,a,b-1,c,d);
		}
		else if(ran == 2){ 	
	    	south = south + A2B(array,a+1,b,c,d);
	    	east = east +  A2B(array,a,b+1,c,d); 
	    	west = west + A2B(array,a,b-1,c,d);
	    	north = north +  A2B(array,a-1,b,c,d);   
		}
		else if(ran == 3){
	    	east = east +  A2B(array,a,b+1,c,d); 
	    	west = west + A2B(array,a,b-1,c,d);
	    	north = north +  A2B(array,a-1,b,c,d);
	    	south = south + A2B(array,a+1,b,c,d);
		}
		else if(ran == 4){      	  
	    	west = west + A2B(array,a,b-1,c,d);
	    	north = north +  A2B(array,a-1,b,c,d);
	    	south = south + A2B(array,a+1,b,c,d);
	    	east = east +  A2B(array,a,b+1,c,d);
		}
		else if (ran == 5){
			east = east +  A2B(array,a,b+1,c,d);
			west = west + A2B(array,a,b-1,c,d);
	    	north = north +  A2B(array,a-1,b,c,d);
	    	south = south + A2B(array,a+1,b,c,d);
		}
	        
	    if ((north + east + south + west) == 1)
	        array[a][b] = 'X';
    }
    return 0;
}





void copyMaze(char A[yaxis][xaxis], char B[yaxis][xaxis]){
    int i,j;

    for (i=0;i<yaxis;i++){
        for (j=0;j<xaxis;j++){
            B[i][j] = A[i][j];
        }
    }

}
