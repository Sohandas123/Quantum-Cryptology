#include <stdio.h>
#include <stdlib.h>

void bitpattern(int , int, unsigned char* );

int main()
{
    int n = 5 ;
    long long int N;
    //printf("\n Enter any positive integer : ");
    //scanf("%d",&n);
    N = 1<<n ;  // It gives N = pow(2,n)
    unsigned char *bitpatt;
    bitpatt = (unsigned char*)malloc(n*sizeof(char));
    for(int i = 0; i < N ; i++)
    {
        bitpattern(i,n,bitpatt);
        printf("\n %d. ",i);
        for(int j = 0 ; j < n ; j++)
            printf(" %hhu",bitpatt[j]);
    }
    
    return 0;
}

/*  This function returns n-bit long bit pattern of integer i ,(0 <= i <= n) */
void bitpattern(int i, int n, unsigned char *patt)  
{
    for(int k = n-1 ; k>=0 ; k--)
    {
        patt[k] = i&1 ;
        i = i>>1 ;
    }
}