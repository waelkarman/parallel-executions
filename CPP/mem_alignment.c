#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define ALIGNMENT 32
/*
    32 = 100000
    31 =  11111 
*/


void* mallo_32_aligned(size_t size){

    void *ptr = malloc(size + sizeof(void*) + ALIGNMENT-1);

/*
    Allocated Memory with malloc.
    ^                                                $
    |<--------------------->|<----->|<-------------->| 
    |         size         sizeof(void*) alignment-1 |
   ptr*
   4097
*/

    printf("Original pointer: %p \n",ptr);

/*
   4096 is aligned.
   +31 For ensuring to reach the next aligned address.
   4097 + 31 = 4128  ->  0001000000100000
   4100 + 31 = 4131  ->  0001000000100011

    Aligned address to 2^n should have last n-1 bit to zero counting from zero: 
   0001000000100000
              11111  <- AND mask
   0001000000100000  <- aligned addr : 4128
   
   0001000000100011
              11111  <- AND mask
   0001000000100000  <- aligned addr : 4128

    Aligned memory
    ^                                          $
    |<--------->|<-------->|<----------------->| 
    |           |          |       size     
   ptr*   sizeof(void*)  aligned
                          addr
   4097                   4128

*/
    /* masking */
    uintptr_t aligned = ((uintptr_t)ptr + 31 + sizeof(void*)) & ~(uintptr_t)31;
    /* saveptr */
    void *align_p = (void*)aligned;
    void **align_pp = align_p;
    align_pp[-1] = ptr;

    
    return align_p;
}

void free_32_aligned(void* aligned_p){
    void** p = aligned_p;
    aligned_p = NULL;
    void* notaligned_p = (void*)p[-1];
    printf("Restored pointer: %p \n",notaligned_p);
    free(notaligned_p);
}

int main() {
    printf("Size of size_t: %zu byte\n", sizeof(size_t));
    printf("Size of char: %zu byte\n", sizeof(char));
    printf("Size of short: %zu byte\n", sizeof(short));
    printf("Size of int: %zu byte\n", sizeof(int));
    printf("Size of long: %zu byte\n", sizeof(long));
    printf("Size of long long: %zu byte\n", sizeof(long long));
    
    size_t size = 100;
    void* p = mallo_32_aligned(100);

    free_32_aligned(p);

    return 0;
}
