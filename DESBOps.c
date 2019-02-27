#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <math.h>


const int initialPermutation [64] = {
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

const int Sbox[8][4][16] = {
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

const int Schedule [16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

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

void printB(uint64_t number, int size){
    for (int i = size-1; i >= 0; i--) 
        if (number >> i & 0x1) 
            putchar('1');
        else 
            putchar('0');
    putchar('\n');
}

uint64_t toBin64(char s[]) {
    int size =strlen(s);
    for(int i=size; i<8; i++)
        s[i]=0;
    uint64_t bin64=0;
    for(int i=0;i<8;i++){ 
            bin64=bin64<<8;
            bin64+=s[i];
        }
    return bin64;
}

uint64_t initialPermute(uint64_t a){
    uint64_t ret=0;
    for(int i=0;i<64;i++){
        ret=ret<<1;
        if((a>>(64-initialPermutation[i])) & 1)
            ret++;
    }
    return ret;
}

uint64_t pCh1(uint64_t a){
    uint64_t ret=0;
    for(int i=0;i<56;i++){
        ret=ret<<1;
        if((a>>(64-PC1[i]) & 1))
            ret++;
    }
    return ret;
}

uint64_t pCh2(uint64_t a){
    uint64_t ret=0;
    for(int i=0;i<48;i++){
        ret=ret<<1;
        if((a>>(56-PC2[i]) & 1))
            ret++;
    }
    return ret;
}

void LShift(uint64_t * a, int shift){
    uint32_t halfLeft= *a >> 28;
    uint32_t halfRight= *a & 0xFFFFFFF;
    halfLeft= halfLeft<<shift | halfLeft >> (28-shift);
    halfLeft=halfLeft & 0xFFFFFFF;
    *a =halfLeft;
    *a=*a<<28;
    halfRight= halfRight<<shift | halfRight >> (28-shift);
    halfRight=halfRight & 0xFFFFFFF;
    *a+=halfRight;
}

uint64_t ExpantionP(uint64_t a){
    uint64_t ret=0;
    a=a<<1;
    a+=(a>>32)&1;
    a+=(a&2)<<32;
    for(int i=0; i<8;i++){
        ret=ret<<6;
        ret+=a>>28;
        a=a<<4;
        a=a&0x3FFFFFFFF;
    }
    return ret;
}

uint64_t permutation(uint64_t a){
    uint64_t ret=0;
    for(int i=0;i<32;i++){
        ret=ret<<1;
        if((a>>(32-PF[i]) & 1))
            ret++;
    }
    return ret;
}

uint64_t finalPermute(uint64_t a){
    uint64_t ret=0;
    for(int i=0;i<64;i++){
        ret=ret<<1;
        if((a>>(64-InverseIP[i]) & 1))
            ret++;
    }
    return ret;
}

int selectSBox(int bit6, int index){
    if(bit6>63)
        return 0;
    int firstandlast=0;
    firstandlast+= (bit6&32)>>4;
    firstandlast+=bit6&1;
    bit6=bit6>>1;
    int mid4=bit6&15;
    return Sbox[index][firstandlast][mid4];
}

uint64_t SBoxed (uint64_t bin48){
    uint64_t ret=0;
    int temp;
    for(int i=0; i<8; i++){
        ret=ret<<4;
        temp= (bin48>>(42-i*6)) & 0b111111;
        ret+=selectSBox(temp,i);
        }
    return ret;
}

void performRound(uint64_t * plainText, uint64_t key){
    uint64_t Key48=pCh2(key);//48 bit key after contraction
    uint64_t ptLeft= *plainText>>32; //first 32 bits of plain text 
    uint64_t ptRight= *plainText & 0xFFFFFFFF; //last 32 bits of plain text 
    uint64_t expanded=ExpantionP(ptRight);//48 bit expanded plain text
    uint64_t Xor=expanded^Key48;
    uint64_t Sb= SBoxed(Xor);//32 bits
    uint64_t SbPermuted= permutation(Sb);
    uint64_t Y= SbPermuted^ptLeft;

    ptRight=ptRight<<32;//swapping initial right 32 bits to left
    ptRight+=Y;//adding initial left 32 bits to the right
    *plainText= ptRight;
}

void swap32(uint64_t * ptBin){
    uint64_t temp= *ptBin>>32;
    *ptBin=*ptBin & 0xFFFFFFFF;
    *ptBin=*ptBin<<32;
    *ptBin+=temp;
}

uint64_t encryptBin(uint64_t bDATA, uint64_t key){
    uint64_t ptBin= initialPermute(bDATA);//64 bit initial permutation of plain text
    uint64_t passBin=pCh1(key);//56 bit key

    for(int i=0;i<16;i++){
			LShift(&passBin,Schedule[i]);
            performRound(&ptBin,passBin);
    }

    swap32(&ptBin);
    ptBin=finalPermute(ptBin);

    return ptBin;
}

uint64_t decryptBin(uint64_t bDATA, uint64_t key){
    uint64_t ptBin= initialPermute(bDATA);//initial permutation of plain text
    uint64_t passBin=pCh1(key);//56 bit key
    uint64_t keys[16];

    for(int i=0;i<16;i++){
			LShift(&passBin,Schedule[i]);
            keys[15-i]=passBin;
    }

    for(int i=0;i<16;i++)
            performRound(&ptBin,keys[i]);

    swap32(&ptBin);
    ptBin=finalPermute(ptBin);

    return ptBin;
}

int roundUP(float x){
    int ret= x;
    if((x-ret)>0)
        ret++;
    return ret;
}

uint64_t * ECBbin (uint64_t ptBin[], uint64_t key,int size, int mode){
    uint64_t * ret= (uint64_t *) malloc(size*sizeof(uint64_t));
    if(mode==0)
        for(int i=0; i<size; i++)
            ret[i]=encryptBin(ptBin[i],key);
    else if(mode==1)
        for(int i=0; i<size; i++)
            ret[i]=decryptBin(ptBin[i],key);
    else 
        return 0;
    return ret;
}

uint64_t * ACIIArray64(char plainText[]){
    int stringLen= strlen(plainText);
    int size= roundUP(stringLen/8.0);
    uint64_t * ptBins= (uint64_t *) malloc(size*sizeof(uint64_t));
    char temp[8];

    for(int i = 0; i < size; i++){
        for(int j = 0; j < 8; j++)
            temp[j]=plainText[j];
        ptBins[i]=toBin64(temp);
        plainText=plainText+8;
    }
    return ptBins;
}


uint64_t * ECBACII (char plainText[], char key[]){
    int size= roundUP(strlen(plainText)/8.0);
    uint64_t * ptBins=ACIIArray64(plainText);
    uint64_t * ret= ECBbin(ptBins,toBin64(key),size,0);
    free(ptBins);
    return ret;
}

int main(){
    char pt[]="testtexttesttexttesttexttesttexttesttexttes";
    char pass[]="passtext";

    uint64_t i= toBin64(pt);
    uint64_t k= toBin64(pass);
    uint64_t * result= ECBACII(pt,pass);


    //for(int i = 0; i < roundUP(strlen(pt)/8.0); i++)
    //    printf("%llx ",(unsigned long long)result[i]);
    
    
    clock_t t; 
    t = clock(); 
    int x;

    for (int j=0; j<10000; j++){
        result= ECBACII(pt,pass);
        free(result);
	}

    t = clock() - t; 
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("fun() took %f seconds to execute \n", time_taken);

    result= ECBbin(result,k,6,1);

  //  for(int i = 0; i < roundUP(strlen(pt)/8.0); i++)
    //    printf("%llx ",(unsigned long long)result[i]);

    free(result);

    //printf("\n\nPlaintext hex:            %llx\n",(unsigned long long)i);
    //printf("Ciphertext hex:           %llx\n",(unsigned long long)result);
   // printf("Decrypted ciphertext hex: %llx\n",(unsigned long long)decryptBin(result,k));

    return 0;
}