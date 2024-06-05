.section program;

.global _Rows_XOR_asm;

_Rows_XOR_asm:
R0 = I1;
P4 = R0;
R6 = [P4++];
R7 = [P4];//save the rows and columns

R0 = M0;
P5 = R0;//key addr

R0 = I0;
P0 = R0;//input addr

R2 = 0;//counter 1
LC0 = R6;

LSETUP (start1, stop1) LC0;

start1:
R3 = 0;//counter 2

LC1 = R7;
LSETUP (start2, stop2) LC1;

start2:

R0 = M0;
P5 = R0;//key addr

R5 = 1;
R0 = R2 & R5;
CC = R0 == 1;
IF CC jump xor1;

R5 = 1;
R5 = R7 - R5;
R5 = R5 - R3;
R0 = B[P0];
R4 = P5;
R4 = R4 + R5;
P1 = R4;
R4 = B[P1];
R0 = R0 ^ R4;
B[P0++] = R0;

jump et1;

xor1:
R0 = B[P0];
R4 = P5;
R4 = R4 + R3;
P1 = R4;
R4 = B[P1];
R0 = R0 ^ R4;
B[P0++] = R0;

et1:
R5 = 1;
stop2: R3 = R3 + R5;


R5 = 1;
stop1:R2 = R2 + R5;


RTS;
_Rows_XOR_asm.end: