#include <stdio.h> 
#include <stdlib.h>

#define ITERMAX 1 //The maximum number of iterations
#define Alfa 8 //nr bits of Grey Level
#define Upper 255 //the maximum value of grey levels
#define M 8 //Length of the Image
#define N 8 //Width of the Image

unsigned char imgInput[M * N];
unsigned char imgScr_enc[M * N];
unsigned char imgEnc[M * N]; // M x N
unsigned char imgScr_dec[M * N];
unsigned char imgDec[M * N];
unsigned char kr[M];
unsigned char kc[N];

void Generate_Keys(void);

void Sum_Rows(unsigned char *input, unsigned int *a, unsigned char *Ma);
void Rotate_Row(unsigned char *input, unsigned int pos, unsigned char dir);
void Circular_Shift_Rows(unsigned char *input, unsigned char *Ma);

void Sum_Columns(unsigned char *input, unsigned int *b, unsigned char *Mb);
void Rotate_Column(unsigned char *input, unsigned int pos, unsigned char dir);
void Circular_Shift_Columns(unsigned char *input, unsigned char *Mb);

void Rows_XOR(unsigned char *matrix);
void Columns_XOR(unsigned char *matrix);

void Not_vector(unsigned char *vector, unsigned int dim);

void Generate_Ienc(void);

void Generate_Idec(void);

//void print_matrix(unsigned char *matrix);

void main(void)
{
	Generate_Keys();
	Generate_Ienc();
	Generate_Idec();
}


void Generate_Keys()
{
	unsigned char i; 
	
	for (i = 0; i < M; i++)
	{
		kr[i] = (rand()% Upper + 1);
	}
	
	for (i = 0; i < N; i++)
	{
		kc[i] = (rand()% Upper + 1);
	}
}

void Sum_Rows(unsigned char *input, unsigned int *a, unsigned char *Ma)
{
	unsigned int sum;
	
	unsigned char i , j;
	for (i = 0; i < M; i++)
	{
		sum = 0;
		for (j = 0; j < N; j++)
		{
			sum += input[i * M + j];
		}
		*a = sum;
		*Ma = sum % 2;
		a++;
		Ma++;
	}
}

void Rotate_Row(unsigned char *input, unsigned int pos, unsigned char dir)
{
	unsigned int j;
	unsigned int aux;
	
	
	if (dir == 0)
	{
		aux = input[pos * M + (N - 1)];
		for (j = N - 1; j > 0 ; j--)
		{
			input[pos * M + j] = input[pos * M + j - 1];
		}
		input[pos * M] = aux;
	}
	else
	{
		aux = input[pos * M];
		for (j = 0; j < N - 1; j++)
		{
			input[pos * M + j] = input[pos * M + j + 1];
		}
		input[pos * M + (N - 1)] = aux;
	}
}

void Circular_Shift_Rows(unsigned char *input, unsigned char *Ma)
{
	unsigned int i, j;
	unsigned char dir;
	
	for (i = 0; i < M; i++)
	{
		dir = *Ma;
		for (j = 0; j < kr[i] % M; j++)
		{
			Rotate_Row(input, i, dir);
		} 
		Ma++;
	}
}

void Sum_Columns(unsigned char *input, unsigned int *b, unsigned char *Mb)
{
	unsigned int sum;
	
	unsigned char i , j;
	for (j = 0; j < N; j++)
	{
		sum = 0;
		for (i = 0; i < M; i++)
		{
			sum += input[i * M + j];
		}
		*b = sum;
		*Mb = sum % 2;
		b++;
		Mb++;
	}
}

void Rotate_Column(unsigned char *input, unsigned int pos, unsigned char dir)
{
	unsigned int i;
	unsigned int aux;
	
	if (dir == 0)
	{
		aux = input[pos];
		for (i = 0; i < M - 1; i++)
		{
			input[i * M + pos] = input[(i + 1) * M + pos];
		}
		input[(M - 1) * M + pos] = aux;
		
	}
	else
	{
		aux = input[(M - 1) * M + pos];
		for (i = M - 1; i > 0; i--)
		{
			input[i * M + pos] = input[(i - 1) * M + pos];
		}	
		input[pos] = aux;
	}
}

void Circular_Shift_Columns(unsigned char *input, unsigned char *Mb)
{
	unsigned int i, j;
	unsigned char dir;
	
	for (i = 0; i < N; i++)
	{
		dir = *Mb;
		for (j = 0; j < kc[i] % M; j++)
		{
			Rotate_Column(input, i, dir);
		} 
		Mb++;
	}
}

void Rows_XOR(unsigned char *matrix)
{
	unsigned int i, j;
	
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (i % 2)
			{
				matrix[i * M + j] = matrix[i * M + j] ^ kc[j];
			}
			else
			{
				matrix[i * M + j] = matrix[i * M + j] ^ kc[N - 1 - j];
			}
		}
	}
}

void Columns_XOR(unsigned char *matrix)
{
	unsigned int i, j;
	
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			if (j % 2)
			{
				matrix[i * M + j] = matrix[i * M + j] ^ kr[i];
			}
			else
			{
				matrix[i * M + j] = matrix[i * M + j] ^ kr[M - 1 - i];
			}
		}
	}
}


void Generate_Ienc(void)
{
	unsigned char ITERenc = 0;
	unsigned int a[M], b[N];
	unsigned char Ma[M], Mb[N];
	unsigned int i, j;
	
	
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			imgEnc[i * M + j] = imgInput[i * M + j];
		}
	}
	
	while (ITERenc < ITERMAX)
	{
		ITERenc++;
		
		Sum_Rows(imgEnc, a, Ma);
	
		Circular_Shift_Rows(imgEnc, Ma);
		
		Sum_Columns(imgEnc, b, Mb);
	
		Circular_Shift_Columns(imgEnc, Mb);
		
		
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				imgScr_enc[i * M + j] = imgEnc[i * M + j];
			}
		}
		
		Rows_XOR(imgEnc);
		Columns_XOR(imgEnc);
		
	}
	printf ("\nEncryption done!");
}

void Generate_Idec(void)
{
	unsigned char ITERdec = 0;
	unsigned int a[M], b[N];
	unsigned char Ma[M], Mb[N];
	unsigned int i, j;
	
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			imgDec[i * M + j] = imgEnc[i * M + j];
		}
	}
	while (ITERdec < ITERMAX)
	{
		ITERdec++;
		
	
		Columns_XOR(imgDec);
		Rows_XOR(imgDec);
		
		for (i = 0; i < M; i++)
		{
			for (j = 0; j < N; j++)
			{
				imgScr_dec[i * M + j] = imgDec[i * M + j];
			}
		}
		
		
		Sum_Columns(imgDec, b, Mb);
		
		Not_vector(Mb, N);
		
		Circular_Shift_Columns(imgDec, Mb);
		
		Sum_Rows(imgDec, a, Ma);
		
		Not_vector(Ma, M);

		Circular_Shift_Rows(imgDec, Ma);
		
	}
	printf ("\nDecryption done!");
}

void Not_vector(unsigned char *vector, unsigned int dim)
{
	unsigned int i;
	
	for (i = 0; i < dim; i++)
	{
		vector[i] ^= 0x01;
			
	}
}

/*void print_matrix(unsigned char *matrix)
{
	unsigned int i, j;
	unsigned char aux;
	
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N ; j++)
		{
			aux = *matrix;
			printf(" %d", aux);
			matrix++;
		}
	}
}*/
