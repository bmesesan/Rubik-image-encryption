#define rows R6
#define columns R7
#define pos R2

.section program
.global _Circular_Shift_Rows_asm;

_Circular_Shift_Rows_asm:
R0 = I1;
P4 = R0;
rows = [P4++];
columns = [P4];//save the rows and columns

R0 = I2;
P4 = R0;//Ma addr

R0 = M0;
P5 = R0;//key addr

R2 = 0;

start1:
R0 = B[P4++];//dir, current Ma
R1 = B[P5++];//current key
P3 = R0;

comp1:
CC = R7 <= R1;
IF CC jump et1;
jump et2;
et1:
R1 = R1 - R7;
jump comp1;//se face operatia de k[i] % N
et2:

CC = R1 == 0;
IF CC jump stop2;
LC1 = R1;

LSETUP (start2, stop2) LC1;

start2:
R0 = P3;
CC = R0 == 0;
IF CC jump rotate_r;

R0 = I0;//set input before call
//CALL _Rotate_Row_L_asm;


//START ROTATE L
P0 = R0;//input

R3 = columns;
R3 *= pos;
R4 = P0;
R4 = R4 + R3;
P0 = R4;//go to the specified row

R4 = B[P0];//save the first element
R5 = 1;
R3 = columns - R5;//N - 1

LC0 = R3;//Number of iterations

LSETUP (start3, stop3) LC0;

start3:

R3 = P0;
R3 = R3 + R5;
P1 = R3;
R3 = B[P1];

stop3: B[P0++] = R3;

B[P0] = R4;
//STOP ROTATE L


jump stop2;

rotate_r:
R0 = I0;
//call _Rotate_Row_R_asm;


//START ROTATE R
P0 = R0;//input

R3 = columns;
R3 *= pos;
R4 = P0;
R4 = R4 + R3;
P0 = R4;//go to the specified row

R5 = 1;
R3 = columns - R5;
R4 = R4 + R3;//go to the last element of the row and save it
P1 = R4;
R4 = B[P1];//save the last element from the row

LC0 = R3;//Number of iterations

LSETUP (start4, stop4) LC0;

start4:

R3 = P1;
P2 = R3;
R3 = R3 - R5;
P1 = R3;
R3 = B[P1];

stop4: B[P2] = R3;

B[P1] = R4;
//STOP ROTATE R


stop2:

R5 = 1;
R2 = R2 + R5;
CC = R2 < R6;
IF CC jump start1;
stop1:nop;



RTS;
_Circular_Shift_Rows_asm.end: