

#define rows R0
#define columns R1
#define pos R2
#define iter R3
#define aux R4

.section program;
.global _Rotate_Column_D_asm;

_Rotate_Column_D_asm:
P0 = R0;
P1 = R1;
R0 = [P1++];//number of rows
R1 = [P1];//number of columns

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

LSETUP (start1, stop1) LC0;

start1:
R3 = P0;
R3 = R3 - columns;
P1 = R3;

R5 = B[P1];
B[P0] = R5;

stop1:P0 = R3;

B[P0] = aux;

RTS;
_Rotate_Column_D_asm.end: