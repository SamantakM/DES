#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int initialPermutation [64] = 
{
    58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

const int PC1[56] = {
   57, 49, 41, 33, 25, 17,  9,
    1, 58, 50, 42, 34, 26, 18,
   10,  2, 59, 51, 43, 35, 27,
   19, 11,  3, 60, 52, 44, 36,
   63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
   14,  6, 61, 53, 45, 37, 29,
   21, 13,  5, 28, 20, 12,  4
};

const int PC2[48] = {
   14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
   23, 19, 12,  4, 26,  8,
   16,  7, 27, 20, 13,  2,
   41, 52, 31, 37, 47, 55,
   30, 40, 51, 45, 33, 48,
   44, 49, 39, 56, 34, 53,
   46, 42, 50, 36, 29, 32
};

const int Sbox[8][4][16] = 
{
   {
        {14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
        { 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
        { 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
        {15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
   },
 
   {
        {15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
        { 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
        { 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
        {13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
   },
 
   {
        {10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
        {13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
        {13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
        { 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
   },
 
   {
        { 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
        {13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
        {10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
        { 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
   },
 
   {
        { 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
        {14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
        { 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
        {11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
   },
 
   {
        {12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
        {10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
        { 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
        { 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
   },
 
   {
        { 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
        {13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
        { 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
        { 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
   },
 
   {
        {13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
        { 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
        { 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
        { 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
   },
};

const int PF[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
};

const int Schedule [16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

const int InverseIP[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

const char HexMap[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

int * toBin64(char* s) {
    if(strlen(s)>8)
        return 0;
    int i,k,temp,bc=0;
    int size=strlen(s);
    int* bin=(int*) malloc(64 * sizeof(int));
    for(i=0;i<8;i++)
        for (k = 7; k >= 0; k--) { 
            temp = (int)s[i] >> k; 
            if (temp & 1) 
                bin[bc]=1;
            else
                bin[bc]=0;
            bc++;
        }
    return bin;
}

int * initialPermute(int * a){
    int* bin=(int*) malloc(64 * sizeof(int));
    int i;
    for(i=0;i<64;i++)
        bin[i]=a[initialPermutation [i]-1];
    return bin;
}

int * pCh1(int* c){
    int* bin=(int*) malloc(56 * sizeof(int));
    int i;
    for(i=0;i<56;i++)
        bin[i]=c[PC1[i]-1];
    return bin;
}

void LShift(int * a, int round){
    int i, shift=Schedule [round-1];
    while(shift){
        shift--;
        for(i=0; i<27;i++)
            swap(&a[i],&a[i+1]);
        for(i=28; i<55;i++)
            swap(&a[i],&a[i+1]);
    }
}

int * pCh2(int* c){
    int* bin=(int*) malloc(56 * sizeof(int));
    int i;
    for(i=0;i<48;i++)
        bin[i]=c[PC2[i]-1];
    return bin;
}

int * ExpantionP(int *a){
    int* bin=(int*) malloc(48 * sizeof(int));
    bin[0]=a[31];
    bin[47]=a[0];
    int i,j=0;
    for(i=1;i<47;i++){
        if(i%6!=0)
            bin[i]=a[j];
        else {
            j-=2;
            bin[i]=a[j];
        }
        j++;
    }
    return bin;
}

int ** split(int * a, int size, int sections ){
    int** bin=(int**) malloc(sections * sizeof(int *));
    int i,j=0;
    for (i=0; i<sections; i++) 
         bin[i] = (int *)malloc(size * sizeof(int)); 

    for(i=0;i<sections;i++)
        for(j=0;j<size;j++)
            bin[i][j]=a[i*size+j];
    return bin;
}

int selectSBox(int * bin6, int index){
    int firstandlast=0;
    firstandlast+=bin6[0];
    firstandlast=firstandlast<<1;
    firstandlast+=bin6[5];
    int mid4=0,i;
    for(i=0;i<4;i++){
        mid4=mid4<<1;
        mid4+=bin6[i+1];
    }
    return Sbox[index][firstandlast][mid4];
}

int * SB(int* a){
    int* bin=(int*) malloc(32 * sizeof(int));
    int ** sixes=split(a,6,8);
    int i,j,k,SSelect,count=0;
    for(i=0;i<8;i++){
        SSelect=selectSBox(sixes[i],i);
        for(j=0;j<4;j++){   
            if(SSelect & 8)
                bin[count]=1;
            else
                bin[count]=0;
            SSelect=SSelect<<1;
            count++;
        }   
    }
    for(i=0;i<8;i++)
        free(sixes[i]);
    free(sixes);
    return bin;
}

int * permutation(int *a){
    int* temp=(int*) malloc(32 * sizeof(int));
    int i=0;
    for(i=0;i<32;i++)
        temp[i]=a[PF[i]-1];
    return temp;
}

int * XOR(int* a,int *b, int size){
    int*  XORed=(int *)malloc(size* sizeof(int));
    int i=0;
    for(i=0;i<size;i++)
        XORed[i]=a[i]^b[i];
    return XORed;
}

int * join(int * a, int *b,int size){
    int * joined= (int*)malloc(2*size*sizeof(int));
    int i;
    for(i=0;i<size;i++)
        joined[i]=a[i];
    for(i=0;i<size;i++)
        joined[size+i]=b[i];
    return joined;    
}

void performRound(int * pt, int* key){
    int * Ki=pCh2(key);//48 bit key after contraction
    int** ptLR=split(pt,32,2);//split plain text left and right parts
    int* expanded=ExpantionP(ptLR[1]);//48 bit expanded plain text
    int i;
    int* X=XOR(Ki,expanded,48);
    int *Sboxed=SB(X);
    int *PSboxed=permutation(Sboxed);
    int * Y=XOR(PSboxed,ptLR[0],32);
    int * t=join(ptLR[1],Y,32);
    for(i=0;i<64;i++)
        pt[i]=t[i]; 
    free(X);
    free(expanded);
    for(i=0;i<2;i++)
        free(ptLR[i]);
    free(Sboxed);
    free(PSboxed);
    free(ptLR);
    free(Ki);
    free(Y);
    free(t);
}

int * finalPerm(int * a){
    int* bin=(int*) malloc(64 * sizeof(int));
    int i;
    for(i=0;i<64;i++)
        bin[i]=a[InverseIP[i]-1];
    return bin;
}

int * encryptBin(int * bDATA , int* key){
    int i,j,k;
    int* ptBin= initialPermute(bDATA);//initial permutation of plain text
    int* passBin=pCh1(key);//56 bit key

    for(i=1;i<=16;i++){
			LShift(passBin,i);
            performRound(ptBin,passBin);
    }

    int ** SPL=split(ptBin,32,2);
    int * ptBinJoined=join(SPL[1],SPL[0],32);
    int * FinalPerm=finalPerm(ptBinJoined);
    free(ptBinJoined);
    free(ptBin);
    free(passBin);
    for(i=0;i<2;i++)
        free(SPL[i]);
    free(SPL);
    return FinalPerm;
}

int ** keys16(int * key){
	int ** keys=(int **) malloc(16 * sizeof(int *));
	int i,j,k;	
	for(i=0; i<16;i++)
		keys[i]=(int *) malloc(56* sizeof(int));
	
	for(k=0; k<56;k++)
		keys[0][k]=key[k];
	LShift(keys[0],1);
	for(i=1; i<16;i++){
		for(k=0; k<56;k++)
			keys[i][k]=keys[i-1][k];
		LShift(keys[i],i+1);	
		}

	return keys;
}

int * decryptBin(int * bDATA , int* key){
	int* ptBin= initialPermute(bDATA);
	int i;
	int* passBin=pCh1(key);
	int ** keyss=keys16(passBin);
    for(i=15;i>=0;i--)
			performRound(ptBin,keyss[i]);

	int ** SPL=split(ptBin,32,2);
    int * ptBinJoined=join(SPL[1],SPL[0],32);
    int * FinalPerm=finalPerm(ptBinJoined);
    free(ptBinJoined);
    free(ptBin);
    free(passBin);
    for(i=0;i<2;i++)
        free(SPL[i]);
    free(SPL);
    for(i=0;i<16;i++)
        free(keyss[i]);
    free(keyss);
	return FinalPerm;
}

char * bintohex(int * bin){
    int i,j=0,temp=0;
    char* hex=(char*) malloc(64);
    for(i=0;i<64;i++){
        temp=temp<<1;
        temp+=bin[i];
        if((i+1)%4==0){
            hex[j]=HexMap[temp];
            j++;
            temp=0;
        }
    }
    hex[16]='\0';
    return hex;
}



int main(){
    char pt[]="testtext";
    char pass[]="passtext";
    int i,j;
    int * ptB=toBin64(pt);
    int * passB=toBin64(pass);
    int * result=encryptBin(ptB,passB);

    clock_t t; 
    t = clock(); 
    int x;

    for (int j=0; j<100000; j++){
        ptB= toBin64(pt);
        passB= toBin64(pass);
	    result= encryptBin(ptB,passB);
        free(ptB);
        free(passB);
        free(result);
	}

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("fun() took %f seconds to execute \n", time_taken);

    char * hex=bintohex(result);
    printf("%s\n",hex);
    free(result);
    free(hex);
    return 0;
}


