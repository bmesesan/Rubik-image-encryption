#define rows R6
#define columns R7
#define pos R2
#define iter R3
#define aux R4

.section program
.global _Circular_Shift_Columns_asm;
.extern _Rotate_Column_U_asm;
.extern _Rotate_Column_D_asm;

_Circular_Shift_Columns_asm:
R0 = I1;
P4 = R0;
rows = [P4++];
columns = [P4];//save the rows and columns

R0 = I3;
P4 = R0;//Mb addr

R0 = M1;
P5 = R0;//key addr

R2 = 0;

start1:
R0 = B[P4++];//dir, current Ma
R1 = B[P5++];//current key
P3 = R0;

comp1:
CC = R6 <= R1;
IF CC jump et1;
jump et2;
et1:
R1 = R1 - R6;
jump comp1;//se face operatia de k[i] % N
et2:

CC = R1 == 0;
IF CC jump stop2;
LC1 = R1;

LSETUP (start2, stop2) LC1;

start2:
R0 = P3;
CC = R0 == 0;
IF CC jump rotate_u;

R0 = I0;//set input before call

//START ROTATE D
P0 = R0;
P1 = R1;


R5 = 1;
aux = rows - R5;
aux *= columns;

aux = aux + pos;//we need to go to the last column

R3 = P0;
R3 = R3 + aux;
P0 = R3;//go to the address of the last element 
aux = B[P0];//save the last element

iter = rows - R5;
LC0 = iter;

LSETUP (start3, stop3) LC0;

start3:
R3 = P0;
R3 = R3 - columns;
P1 = R3;

R5 = B[P1];
B[P0] = R5;

stop3:P0 = R3;

B[P0] = aux;
//STOP ROTATE D


jump stop2;

rotate_u:
R0 = I0;

//START ROTATE U
P0 = R0;
P1 = R1;

R3 = P0;
R3 = R3 + pos;
P0 = R3;//go to the specified column

aux = B[P0];//save the first element

R5 = 1;
iter = rows - R5;
LC0 = iter;

LSETUP (start4, stop4) LC0;

start4:
R3 = P0;
R3 = R3 + columns;
P1 = R3;

R5 = B[P1];
B[P0] = R5;

stop4:P0 = R3;

B[P0] = aux;
//STOP ROTATE U


stop2:

R5 = 1;
R2 = R2 + R5;
CC = R2 < R6;
IF CC jump start1;
stop1:nop;

RTS;
_Circular_Shift_Columns_asm.end: