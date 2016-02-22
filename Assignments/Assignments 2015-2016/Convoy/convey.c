#include <stdio.h>
#include <stdlib.h>

#define INF 99999999999



// Function Prototypes
void Solve(int[], int, int);



int main(){
        FILE*in = fopen("input.txt","r");
        int c, amountItems;
        fscanf(in,"%d %d",&c,&amountItems);

        int size[amountItems],i;
        for(i=0;i<amountItems;i++){
            fscanf(in,"%d",&size[i]);
        }
        fclose(in);
        Solve(size,c ,amountItems);
}



 void Solve(int size[], int c, int MAX_SIZE) {

        int cost[MAX_SIZE][MAX_SIZE];
        int minCost[MAX_SIZE];
        int result[MAX_SIZE];

        int i,j;
        // adding items and subtracting their weight
        //from the total truck weight
        for(i=0 ; i < MAX_SIZE; i++){
            int val = c - size[i];
            cost[i][i] = val;
            for(j=i+1; j < MAX_SIZE; j++){
                val = cost[i][j-1] - size[j];
                cost[i][j] = cost[i][j-1] - size[j];
            }
        }

        // squaring the values that are >= 0 since  they can fit in a truck
        // and putting the items that < 0 to a large number since they cannot fit
        for(i=0; i < MAX_SIZE; i++){
            for(j=i; j < MAX_SIZE; j++){
                if(cost[i][j] < 0){
                    cost[i][j] = INF;
                }else{
                    cost[i][j] = cost[i][j] * cost[i][j];
                }
            }
        }

        // computing the minCost starting from the back-front
        for(i = MAX_SIZE-1; i >= 0 ; i--){
            minCost[i] = cost[i][MAX_SIZE-1];
            result[i] = MAX_SIZE;
            for(j=MAX_SIZE-1; j > i; j--){
                if(cost[i][j-1] == INF){
                    continue;
                }
                if(minCost[i] > minCost[j] + cost[i][j-1]){
                    minCost[i] = minCost[j] + cost[i][j-1];
                    result[i] = j; // items i to j-1 can fit in a truck
                }
            }
        }

        i=0;
        int k;
        int trucks = 0,amount_items = 0,temp[MAX_SIZE+1];



    for (i=0;i<MAX_SIZE;i++){
        temp[trucks] = result[i] - i;
        i = result[i] - 1;
        trucks++;
    }

      FILE*out = fopen("output.txt","w");
      fprintf(out,"%d\n",trucks);
      for (i=0;i<trucks;i++)
        fprintf(out,"%d ",temp[i]);
      fprintf(out,"\n%d\n", minCost[0]);
      fclose(out);

}

