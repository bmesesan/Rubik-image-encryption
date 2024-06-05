.section program

.global _Save_addresses;

_Save_addresses:
P3 = R0;//INPUT
P4 = R1;//DIMENSION
P5 = R2;//KEYS

R6 = B[P4++];
R6 = B[P4];


RTS;
_Save_addresses.end: