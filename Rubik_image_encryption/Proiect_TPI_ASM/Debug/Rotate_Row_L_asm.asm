
#define rows R0
#define columns R1
#define pos R2

.section program;

.global _Rotate_Row_L_asm;

_Rotate_Row_L_asm:
P0 = R0;//input
rows = R6;
columns = R7;

R3 = columns;
R3 *= pos;
R4 = P0;
R4 = R4 + R3;
P0 = R4;//go to the specified row

R4 = B[P0];//save the first element
R5 = 1;
R3 = columns - R5;//N - 1

LC0 = R3;//Number of iterations

LSETUP (start1, stop1) LC0;

start1:

R3 = P0;
R3 = R3 + R5;
P1 = R3;
R3 = B[P1];

stop1: B[P0++] = R3;

B[P0] = R4;

RTS;
_Rotate_Row_L_asm.end:
