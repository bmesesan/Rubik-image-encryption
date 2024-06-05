
#define rows R0
#define columns R1
#define pos R2
#define iter R3
#define aux R4

.section program;
.global _Rotate_Column_U_asm;

_Rotate_Column_U_asm:
P0 = R0;
P1 = R1;
R0 = [P1++];//number of rows
R1 = [P1];//number of columns

R3 = P0;
R3 = R3 + pos;
P0 = R3;//go to the specified column

aux = B[P0];//save the first element

R5 = 1;
iter = rows - R5;
LC0 = iter;

LSETUP (start1, stop1) LC0;

start1:
R3 = P0;
R3 = R3 + columns;
P1 = R3;

R5 = B[P1];
B[P0] = R5;

stop1:P0 = R3;

B[P0] = aux;

RTS;
_Rotate_Column_U_asm.end: