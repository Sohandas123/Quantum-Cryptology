/* Binary Hamming code. Creating Hamming-code from message.
Enter the value l = 3 to get Binary (7,4,3) Hamming Code  */
/* Sohan Das, CRS - 2119 , ISI, Kolkata*/

#include <stdio.h>
#include <stdlib.h>

int **G, *msg, *code;
int weight(int);
void matrix_mult(int **, int *, int *, int, int);

int main()
{
	int l;
	printf("\nPut the value of l :");
	scanf("%d", &l);
	int n = (1 << l) - 1; // = 2^l - 1  ,length of the Hamming code
	int k = n - l;		  // = 2^l - l - 1 ,number of information bits
	int d = 3;			  // minimum distance
	printf("\n We are going to build Binary(%d , %d ) Hamming code.\n", n, k);
	printf("\n msg text (%d-bit string) : ", k);
	msg = (int *)malloc(k * sizeof(int));
	for (int i = 0; i < k; i++)
		scanf("%d", &msg[i]);

	printf("\n Your %d-bit msg is :", k);
	for (int i = 0; i < 4; i++)
		printf(" %d", msg[i]);

	// Creating memory spaces for Generator matrix
	G = (int **)malloc(k * sizeof(int *));
	for (int i = 0; i < k; i++)
		G[i] = (int *)malloc(n * sizeof(int));

	/* G = [ I_k | A_{k*(n-k)}] */
	// Building I_k
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			G[i][j] = (i == j);

	// Building A_{k*(n-k)}
	int i = 0;
	for (int v = 0; v <= n; v++)
	{
		if (weight(v) > 1)
		{
			int vector = v;
			// printf("vector %d: ", v);
			// printf("\n");

			for (int j = k; j < n; j++)
			{
				G[i][j] = vector & 1;
				vector = vector >> 1;
			}
			i++;
		}
	}
	printf("\nThe Generator matrix is :\n");
	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < n; j++)
			printf(" %d ", G[i][j]);
		printf("\n");
	}
	/* Creating memory spaces for code */
	code = (int *)malloc(n * sizeof(int));
	matrix_mult(G, msg, code, k, n); /* k = length of msg and n = length of code */

	/* Display the code */
	printf("The Binary (%d , %d ) Hamming code \n for the above %d-bit msg is :", n, k, k);
	for (int i = 0; i < n; i++)
		printf(" %d", code[i]);
	printf("\n");
	return 0;
}

/* ---------------------------- Function definitions ------------------------------*/
int weight(int v)
{
	int count = 0;
	while (v != 0)
	{
		if (v & 1 == 1)
			count += 1;
		v = v >> 1;
	}
	return count;
}

void matrix_mult(int **M, int *message, int *cd, int k, int n)
{
	for (int j = 0; j < n; j++)
	{
		cd[j] = 0;
		for (int i = 0; i < k; i++)
			cd[j] += message[i] * G[i][j];
		cd[j] = cd[j] & 1; /* If cd[j] is odd then it will output 1 ,else 0 */
	}
}
