#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main(void)
{
	float B;
	float E0;
	float E1;
	float E3;
	float E9;
	float F1;
	float F2;
	float F3;
	float F6;
	float F9;
	float O;
	float O1;
	float O2;
	float O3;
	float O4;
	float P;
	float T2;
	float U1;
	float U2;
	float W;
	float X;
	float Y;
	float Z;

	F1 = -1.0;
	F2 = 0.5;
	O = 0.0;
	O1 = 1.0;
	O2 = 2.0;
	O3 = 3.0;
	O4 = 4.0;
	T2 = 32.0;

// 1160 PRINT "Searching for radix  B  and precision  P ; ";

	printf("Searching for radix B and precision P ; ");

// 1170 W=O1

	W = O1;

// 1180 W=W+W : Y=W+O1 : Z=Y-W : Y=Z-O1 : IF (F1+ABS(Y)<O) THEN 1180

	do {
		W = W + W;
		Y = W + O1;
		Z = Y - W;
		Y = Z - O1;
	} while (F1 + fabsf(Y) < O);

// 1200 P=O :  Y=O1

	P = O;
	Y = O1;

// 1210 B=W+Y : Y=Y+Y : B=B-W : IF (B=O) THEN 1210

	do {
		B = W + Y;
		Y = Y + Y;
		B = B - W;
	} while (B == O);

// 1220 IF (B<O2) THEN B=O1

	if (B < O2)
		B = O1;

// 1230 PRINT " Radix  B = "; B : IF (B=O1) THEN 1270

	printf("Radix B = %g\n", B);
	if (B == O1)
		goto L1270;

// 1240 W=O1

	W = O1;

// 1250 P=P+O1 : W=W*B : Y=W+O1 : Z=Y-W : IF (Z=O1) THEN 1250

	do {
		P = P + O1;
		W = W * B;
		Y = W + O1;
		Z = Y - W;
	} while (Z == O1);

// 1270 U1=O1/W : U2=B*U1 : PRINT "Closest relative separation found is  U1 ="; U1

L1270:	U1 = O1 / W;
	U2 = B * U1;
	printf("Closest relative separation found is U1 = %g\n", U1);

// 1280 PRINT : PRINT "Recalculating radix and precision ";

	printf("Recalculating radix and precision ");

// 1290 E0=B : E1=U1 : E9=U2 : E3=P

	E0 = B;
	E1 = U1;
	E9 = U2;
	E3 = P;

// 1300 X=O4/O3 : F3=X-O1 : F6=F2-F3 : X=F6+F6 : X=ABS(X-F3) : IF (X<U2) THEN X=U2

	X = O4 / O3;
	F3 = X - O1;
	F6 = F2 - F3;
	X = F6 + F6;
	X = fabsf(X - F3);
	if (X < U2)
		X = U2;

// 1320 U2=X : Y=F2*U2+T2*U2*U2 : Y=O1+Y : X=Y-O1 : IF (U2>X AND X>O) THEN 1320

	do {
		U2 = X;
		Y = F2 * U2 + T2 * U2 * U2;
		Y = O1 + Y;
		X = Y - O1;
	} while (U2 > X && X > O);

// 1340 X=O2/O3 : F6=X-F2 : F3=F6+F6 : X=F3-F2 : X=ABS(X+F6) : IF (X<U1) THEN X=U1

	X = O2 / O3;
	F6 = X - F2;
	F3 = F6 + F6;
	X = F3 - F2;
	X = fabsf(X + F6);
	if (X < U1)
		X = U1;

// 1360 U1=X : Y=F2*U1+T2*U1*U1 : Y=F2-Y : X=F2+Y : Y=F2-X : X=F2+Y : IF (U1>X AND X>O) THEN 1360

	do {
		U1 = X;
		Y = F2 * U1 + T2 * U1 * U1;
		Y = F2 - Y;
		X = F2 + Y;
		Y = F2 - X;
		X = F2 + Y;
	} while (U1 > X && X > O);

// 1380 IF (U1=E1) THEN PRINT " confirms closest relative separation  U1 ."

	if (U1 == E1)
		printf("confirms closest relative separation U1.\n");

// 1390 IF (U1><E1) THEN PRINT " gets better closest relative separation  U1 = "; U1

	if (U1 != E1)
		printf("gets better closest relative separation U1 = %g\n", U1);

// 1400 W=O1/U1 : F9=(F2-U1)+F2

	W = O1 / U1;
	F9 = (F2 - U1) + F2;

// 1410 B=INT(.01 + U2/U1) : IF (B=E0) THEN PRINT "Radix  B  confirmed."

	B = floorf(0.01 + U2 / U1);
	if (B == E0)
		printf("Radix B confirmed.\n");
}
