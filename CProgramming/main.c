#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>


#define amtofnumbers  100

// libraries
#include "library/heap.h"
// end libraries

// Header Files
#include "years/2014-3.h"
// end Header Files


//Function Prototypes
bool Found(FILE*); // check to see if a file is there or not


//end Function Prototypes

int main()
{

    // 2014 - 3
        printf("2014 - 3\n");
            // : 1(a)
            printf("1(a)\n");
            int stamps[] = {2,1,3};
            printf("\tF is : %d\n",findF(stamps,stamps[0],5));


            // : 1(b)
            // knapsack problem

    printf("\n\n\n\n\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 2014 -2
    printf("2014 - 2\n");


    printf("\n\n\n\n\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 2013 - 2
    printf("2013 - 2\n");
        // : 3 (c)(iii)
         printf("3(c)(iii)\n");
        srand(time(0));
        int* numbers = (int*)malloc((amtofnumbers) * sizeof(int*));
        numbers[0] = 0;
        int i;
        for (i=0;i<amtofnumbers;i++){
            numbers[i] = rand()%100;
        }
        heapSort(numbers, amtofnumbers);
        printf("\n\tbiggest difference between two numbers is %d\n",abs(numbers[0] - numbers[amtofnumbers-1]));


    printf("\n\n\n\n\n");
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return 0;

}


// FUNCTIONS


// if a file exist
bool Found(FILE*in)
{
    if(in == NULL)
    {
        printf("File was not found!\n");
        return false;
    }
    return true;
}

