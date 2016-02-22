#include <stdio.h>
#include <string.h>

// function prototypes
void Decrypt(int , char [], int );

int main(){
	int lines; char ciphertext[100010];
	
	FILE*in = fopen("input.txt","r");
	fscanf(in,"%d %s",&lines,ciphertext);
	fclose(in);
	
	Decrypt(lines,ciphertext ,strlen(ciphertext));
	return 0;
}

void Decrypt(int key, char ciphertext[], int length) {
      char phrase[length];
	  int k=0, line, skip, i, j;
      
      for(line=0; line<key-1; line++){
    	  skip=2*(key-line-1);	 
		  j=0;
        for(i=line; i<length;){
            phrase[i] = ciphertext[k++];
       	    if((line==0) || (j%2 == 0)) i+=skip;
        	  else i+=2*(key-1) - skip;  
        	  j++;        
        }
      }
      for(i=line; i<length; i+=2*(key-1)) phrase[i] = ciphertext[k++];
		FILE*out= fopen("output.txt","w");
		for(i=0;i<length;i++) fprintf(out,"%c",phrase[i]);
      	fclose(out);
}
