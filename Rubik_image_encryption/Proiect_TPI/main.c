#include <stdio.h> 
#include <stdlib.h>
#include <time.h>


#define ITERMAX 1 //The maximum number of iterations
#define Alfa 8 //nr bits of Grey Level
#define Upper 255 //the maximum value of grey levels
#define M 8 //Length of the Image
#define N 8 //Width of the Image

unsigned char imgInput[M * N];
unsigned char imgIscr[M * N];
unsigned char imgEnc[M * N]; // M x N

unsigned char imgDec[M * N];

//Key 1
unsigned char kr[M];
//Key 2
unsigned char kc[N];

unsigned int a_scr[M], b_scr[N];
unsigned char Ma_scr[M], Mb_scr[N];


void Generate_Keys(void);
void Sum_Rows(unsigned int *a, unsigned char *Ma);
void Rotate_Row(unsigned int pos, unsigned char dir);
void Circular_Shift_Rows(unsigned char *Ma);

void Sum_Columns(unsigned int *b, unsigned char *Mb);
void Rotate_Column(unsigned int pos, unsigned char dir);
void Circular_Shift_Columns(unsigned char *Mb);

void Generate_Iscr(void);

void Rows_XOR_enc(void);
void Columns_XOR_enc(void);

void Generate_Ienc(void);



void Rows_XOR_dec(void);
void Columns_XOR_dec(void);

void Sum_Rows_dec(unsigned int *a, unsigned char *Ma);
void Sum_Columns_dec(unsigned int *b, unsigned char *Mb);


void Generate_Idec(void);

/*
void main(void)
{
	
	Generate_Ienc();
	Generate_Idec();
}*/

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

void Sum_Rows(unsigned int *a, unsigned char *Ma)
{
	unsigned int sum;
	
	unsigned char i , j;
	for (i = 0; i < M; i++)
	{
		sum = 0;
		for (j = 0; j < N; j++)
		{
			sum += imgInput[i * M + j];
		}
		*a = sum;
		*Ma = sum % 2;
		a++;
		Ma++;
	}
}

void Rotate_Row(unsigned int pos, unsigned char dir)
{
	unsigned int j;
	unsigned int aux;
	
	
	if (dir == 0)
	{
		aux = imgIscr[pos * M + (N - 1)];
		for (j = N - 1; j > 0 ; j--)
		{
			imgIscr[pos * M + j] = imgIscr[pos * M + j - 1];
		}
		imgIscr[pos * M] = aux;
	}
	else
	{
		aux = imgIscr[pos * M];
		for (j = 0; j < N - 1; j++)
		{
			imgIscr[pos * M + j] = imgIscr[pos * M + j + 1];
		}
		imgIscr[pos * M + (N - 1)] = aux;
	}
}

void Circular_Shift_Rows(unsigned char *Ma)
{
	unsigned int i, j;
	unsigned char dir;
	
	for (i = 0; i < M; i++)
	{
		dir = *Ma;
		for (j = 0; j < kr[i] % M; j++)
		{
			Rotate_Row(i, dir);
		} 
		Ma++;
	}
}

void Sum_Columns(unsigned int *b, unsigned char *Mb)
{
	unsigned int sum;
	
	unsigned char i , j;
	for (j = 0; j < N; j++)
	{
		sum = 0;
		for (i = 0; i < M; i++)
		{
			sum += imgInput[i * M + j];
		}
		*b = sum;
		*Mb = sum % 2;
		b++;
		Mb++;
	}
}

void Rotate_Column(unsigned int pos, unsigned char dir)
{
	unsigned int i;
	unsigned int aux;
	
	if (dir == 0)
	{
		aux = imgIscr[pos];
		for (i = 0; i < M - 1; i++)
		{
			imgIscr[i * M + pos] = imgIscr[(i + 1) * M + pos];
		}
		imgIscr[(M - 1) * M + pos] = aux;
		
	}
	else
	{
		aux = imgIscr[(M - 1) * M + pos];
		for (i = M - 1; i > 0; i--)
		{
			imgIscr[i * M + pos] = imgIscr[(i - 1) * M + pos];
		}	
		imgIscr[pos] = aux;
	}
}

void Circular_Shift_Columns(unsigned char *Mb)
{
	unsigned int i, j;
	unsigned char dir;
	
	for (i = 0; i < N; i++)
	{
		dir = *Mb;
		for (j = 0; j < kc[i] % N; j++)
		{
			Rotate_Column(i, dir);
		} 
		Mb++;
	}
}


void Generate_Iscr(void)
{
	unsigned int i, j;
	unsigned int a[M], b[N];
	unsigned char Ma[M], Mb[N];
	
	
	Generate_Keys();
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			imgIscr[i * M + j] = imgInput[i * M + j];
		}
	}
	
	Sum_Rows(a, Ma);
	
	Circular_Shift_Rows(Ma);
	
	Sum_Columns(b, Mb);
	
	Circular_Shift_Columns(Mb);
	
}

void Rows_XOR_enc(void)
{
	unsigned int i, j;
	
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (i % 2)
			{
				imgEnc[i * M + j] = imgIscr[i * M + j] ^ kc[j];
			}
			else
			{
				imgEnc[i * M + j] = imgIscr[i * M + j] ^ kc[N - 1 - j];
			}
		}
	}
}

void Columns_XOR_enc(void)
{
	unsigned int i, j;
	
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			if (j % 2)
			{
				imgEnc[i * M + j] = imgEnc[i * M + j] ^ kr[i];
			}
			else
			{
				imgEnc[i * M + j] = imgEnc[i * M + j] ^ kr[M - 1 - i];
			}
		}
	}
}


void Generate_Ienc(void)
{
	unsigned char ITERenc = 0;
	
	while (ITERenc < ITERMAX)
	{
		ITERenc++;
		
		Generate_Iscr();
	
		Rows_XOR_enc();
		Columns_XOR_enc();
	}
	printf ("\nEncryption done!");
}

void Columns_XOR_dec(void)
{
	unsigned int i, j;
	
	for (j = 0; j < N; j++)
	{
		for (i = 0; i < M; i++)
		{
			if (j % 2)
			{
				imgDec[i * M + j] = imgEnc[i * M + j] ^ kr[i];
			}
			else
			{
				imgDec[i * M + j] = imgEnc[i * M + j] ^ kr[M - 1 - i];
			}
		}
	}
}

void Rows_XOR_dec(void)
{
	unsigned int i, j;
	
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (i % 2)
			{
				imgDec[i * M + j] = imgDec[i * M + j] ^ kc[j];
			}
			else
			{
				imgDec[i * M + j] = imgDec[i * M + j] ^ kc[N - 1 - j];
			}
		}
	}
}

void Sum_Rows_dec(unsigned int *a, unsigned char *Ma)
{
	;
}

void Sum_Columns_dec(unsigned int *b, unsigned char *Mb)
{
	;
}

void Generate_Idec(void)
{
	unsigned char ITERdec = 0;
	
	while (ITERdec < ITERMAX)
	{
		ITERdec++;
		
		Columns_XOR_dec();
		Rows_XOR_dec();
		
	}
	printf ("\nDecryption done!");
}
