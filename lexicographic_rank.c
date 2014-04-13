#include "stdio.h"
#include "stdlib.h"

//author Mark Bowden

// return map of factorials up to n
int *factorial(int n);
// lexicographically rank a permutation in ascending order
int lex_rank(const int *permutation, const int length);

//return an array mapped to factorial at index
int *factorial(int n){
    static int* arr = NULL;
    static unsigned int size;
    //move off zero based indexing
    n = n + 1;
    if( n > size || arr == NULL){
        if(arr == NULL){
            //size is where we are going to start calculating from
            size = 1;
            arr = malloc(sizeof(int) * n);
            arr[0] = 1;
        }
        else{
            arr = realloc(arr, sizeof(int) * n);
        }
        //note we are increasing size to equal n
        for(;size < n; size++){
            //set each position to it's index times the computed factorial at one less index
            arr[size] = size * arr[size - 1];
        }
    }
    return arr;
}

/* lexicographically rank a permutation of (1 .. length) inclusive */
/* used to find the perfect hash of a permutation */
int lex_rank(const int *permutation, const int length){
    int pos;
    int rank = 0;
    int mask[length];
    /* get an array with a map of factorials */
    int* fact = factorial(length);
    /* initialize mask */
    for(pos = 0; pos < length; pos++){
        mask[pos] = 1;
    }
    /* add offset at each position to rank */
    /* note that the final position always produces a count of 0 so we skip it */
    for(pos = 0; pos < length - 1; pos++){
        /* use reference and mask to count how many remaining integers are less than permutation[pos] */
        /* remove used integer from reference from mask */
        mask[ permutation[pos] ] = 0;
        /* count how many remaining integers are less than permuation[pos] */
        int x;
        int count = 0;
        for(x = 1; x < length + 1; x++){ /* 1 .. length inclusive */
            if(x >= permutation[pos]){
                break;
            }
            if(mask[x] == 1){
                count++;
            }
        }/* end counting */
        /* use the count to determine how much offset there is */
        if(count == 0){
            continue;
        }
        /* add offset */
        /* (n! / length) * count == (n - 1)! * count */
        rank += fact[length - pos - 1] * count;
    }
    return rank;
}

void test_lex_rank(){
    int a[6][3] = {
    {1,2,3},
    {1,3,2},
    {2,1,3},
    {2,3,1},
    {3,1,2},
    {3,2,1}};
    int x;
    for(x = 0; x < 6; x ++){
        printf("%d == %d\n", x, lex_rank(a[x], 3));
    }
    
    int * fact = factorial(10);    
    int b[10] = {10,9,8,7,6,5,4,3,2,1};
    int c[10] = {10,9,8,7,6,5,4,3,1,2};
    
    printf("10! - 1 == %d\n", lex_rank(b, 10));
    printf("correct if 1 -> %d\n", lex_rank(b,10) == fact[10] - 1);
    
    printf("10! - 2 == %d\n", lex_rank(c, 10));
    printf("correct if 1 -> %d\n", lex_rank(c, 10) == fact[10] - 2);
}


int main(int argc, char** argv){
    test_lex_rank();
    return 0;
    
    
}
