.section program;

.global _Sum_Columns_asm;

_Sum_Columns_asm:

R0 = I0;//input
R1 = I3;//mb
R2 = I1;//dim


P0 = R0;
P1 = R1;
P2 = R2;

R0 = [P2++];//number of rows
R1 = [P2];//number of columns

R6 = R0;
R7 = R0;//saves the nr of rows and columns

LC0 = R0;//number of iterations-rows

LSETUP (start1, stop1) LC0;
start1:

P3 = P0;
P0 += 1;
R2 = 0;//sum = 0;
LC1 = R1;//number of iterations-columns

LSETUP (start2, stop2) LC1;
start2:

R3 = B[P3];
R2 = R2 + R3;
R3 = P3;
R3 = R3 + R1;

stop2:P3 = R3;
R3 = 1;
R2 = R2 & R3;

stop1:B[P1++] = R2;

RTS;
_Sum_Columns_asm.end: 