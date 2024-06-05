/*****************************************************************************
 * Proiect_TPI_ASM.c
 *****************************************************************************/
#include <stdio.h> 
#include <stdlib.h>
#define ITERMAX 1 //The maximum number of iterations
#define Alfa 8 //nr bits of Grey Level
#define Upper 255 //the maximum value of grey levels
#define M 128	
#define N 128

int dim[2] = {M, N}; //The dimensions of the image

unsigned char imgInput[M * N];
unsigned char imgScr_enc[M * N];
unsigned char imgEnc[M * N]; // M x N
unsigned char imgScr_dec[M * N];
unsigned char imgDec[M * N];
unsigned char kr[M];
unsigned char kc[N];

extern void Sum_Rows_asm(unsigned char *input, unsigned char *Ma, int *dim);
extern void Sum_Columns_asm(unsigned char *input, unsigned char *Mb, int *dim);
extern void Rotate_Row_R_asm(void);
extern void Rotate_Row_L_asm(void);
extern void Rotate_Column_U_asm(void);
extern void Rotate_Column_D_asm(void);
extern void Circular_Shift_Rows_asm(unsigned char *input, unsigned char *Ma, unsigned char *key);
extern void Circular_Shift_Columns_asm(unsigned char *input, unsigned char *Mb, unsigned char *key);
extern void Rows_XOR_asm(unsigned char *input, int *dim, unsigned char *key);
extern void Columns_XOR_asm(unsigned char *input, int *dim, unsigned char *key);
extern void Save_addresses(unsigned char *input, int *dim, unsigned char *key);
extern void Save_addr1(unsigned char *input, int *dim);
extern void Save_addr2(unsigned char *Ma, unsigned char *Mb);
extern void Save_addr3(unsigned char *kr, unsigned char *kc);


void Generate_Keys(void);

void Rows_XOR(unsigned char *matrix);
void Columns_XOR(unsigned char *matrix);

void Not_vector(unsigned char *vector, unsigned int dim);

void Generate_Ienc(void);

void Generate_Idec(void);


void main( void )
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


void Generate_Ienc(void)
{
	unsigned char ITERenc = 0;
	unsigned char Ma[M], Mb[N];
	//t dim1[2] = {M, N};
	unsigned int i, j;
	
	Save_addr1(&imgEnc[0], &dim[0]);
	Save_addr2(&Ma[0], &Mb[0]);
	Save_addr3(&kr[0], &kc[0]);
	
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
		
		Sum_Rows_asm(&imgEnc[0], &Ma[0], &dim[0]);
		
		Circular_Shift_Rows_asm(&imgEnc[0], &Ma[0], &kr[0]);
		
		Sum_Columns_asm(&imgEnc[0], &Mb[0], &dim[0]);
	
		Circular_Shift_Columns_asm(&imgEnc[0], &Mb[0], &kc[0]);
		
		
		Rows_XOR_asm(&imgEnc[0], &dim[0], &kr[0]);
		Columns_XOR_asm(&imgEnc[0], &dim[0], &kc[0]);
		
	}
	printf ("\nEncryption done!");
}

void Generate_Idec(void)
{
	unsigned char ITERdec = 0;
	unsigned char Ma[M], Mb[N];
	int dim1[2] = {M, N};
	int dim2[2] = {M, N};
	unsigned int i, j;
	Save_addr1(&imgDec[0], &dim[0]);
	Save_addr2(&Ma[0], &Mb[0]);
	
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
		
	
		Columns_XOR_asm(&imgDec[0], &dim[0], &kc[0]);
		Rows_XOR_asm(&imgDec[0], &dim[0], &kr[0]);

		
		Sum_Columns_asm(&imgDec[0], &Mb[0], &dim1[0]);
		
		Not_vector(Mb, N);
		
		Circular_Shift_Columns_asm(&imgDec[0], &Mb[0], &kc[0]);
		
		Sum_Rows_asm(&imgDec[0], &Ma[0], &dim2[0]);
		
		Not_vector(Ma, M);

		Circular_Shift_Rows_asm(&imgDec[0], &Ma[0], &kr[0]);
		
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
