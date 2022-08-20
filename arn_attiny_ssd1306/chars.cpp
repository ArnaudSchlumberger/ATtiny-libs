#include "chars.h"
#include <avr/pgmspace.h>

const uint8_t char_A[5] PROGMEM = {
    4,
    0b1111110,
    0b0010001,
    0b0010001,
    0b1111110

};
const uint8_t char_B[5] PROGMEM = {
    4,
    0b1111111,
    0b1001001,
    0b1001001,
    0b0110110

};
const uint8_t char_C[5] PROGMEM = {
    4,
    0b0111110,
    0b1000001,
    0b1000001,
    0b0100010

};
const uint8_t char_D[5] PROGMEM = {
    4,
    0b1111111,
    0b1000001,
    0b1000001,
    0b0111110
};
const uint8_t char_E[5] PROGMEM = {
    4,
    0b1111111,
    0b1001001,
    0b1001001,
    0b1000001
};
const uint8_t char_F[5] PROGMEM = {
    4,
    0b1111111,
    0b0001001,
    0b0001001,
    0b0000001
};

const uint8_t char_G[5] PROGMEM = {
    4,
    0b0111110,
    0b1000001,
    0b1010001,
    0b0110010
};

const uint8_t char_H[5] PROGMEM = {
    4,
    0b1111111,
    0b0001000,
    0b0001000,
    0b1111111
};

const uint8_t char_I[5] PROGMEM = {
    3,
    0b1000001,
    0b1111111,
    0b1000001
    
};

const uint8_t char_J[5] PROGMEM = {
    4,
    0b0100000,
    0b1000000,
    0b1000000,
    0b0111111
};

const uint8_t char_K[5] PROGMEM = {
    4,
    0b1111111,
    0b0001000,
    0b0010100,
    0b1100011
};

const uint8_t char_L[5] PROGMEM = {
    4,
    0b1111111,
    0b1000000,
    0b1000000,
    0b1000000
};

const uint8_t char_M[6] PROGMEM = {
    5,
    0b1111111,
    0b0000010,
    0b0000100,
    0b0000010,
    0b1111111
};

const uint8_t char_N[5] PROGMEM = {
    4,
    0b1111111,
    0b0000010,
    0b0000100,
    0b1111111
};

const uint8_t char_O[5] PROGMEM = {
    4,
    0b0111110,
    0b1000001,
    0b1000001,
    0b0111110
};

const uint8_t char_P[5] PROGMEM = {
    4,
    0b1111111,
    0b0001001,
    0b0001001,
    0b0000110
};

const uint8_t char_Q[5] PROGMEM = {
    4,
    0b0111110,
    0b1000001,
    0b0100001,
    0b1011110
};

const uint8_t char_R[5] PROGMEM = {
    4,
    0b1111111,
    0b0001001,
    0b0001001,
    0b1110110
};

const uint8_t char_S[5] PROGMEM = {
    4,
    0b0100110,
    0b1001001,
    0b1001001,
    0b0110010
};

const uint8_t char_T[6] PROGMEM = {
    5,
    0b0000001,
    0b0000001,
    0b1111111,
    0b0000001,
    0b0000001
};

const uint8_t char_U[5] PROGMEM = {
    4,
    0b0111111,
    0b1000000,
    0b1000000,
    0b0111111
};

const uint8_t char_V[6] PROGMEM = {
    5,
    0b0011111,
    0b0100000,
    0b1000000,
    0b0100000,
    0b0011111
};

const uint8_t char_W[6] PROGMEM = {
    5,
    0b0111111,
    0b1000000,
    0b0110000,
    0b1000000,
    0b0111111
};

const uint8_t char_X[5] PROGMEM = {
    4,
    0b1110111,
    0b0001000,
    0b0001000,
    0b1110111
};

const uint8_t char_Y[5] PROGMEM = {
    4,
    0b0100111,
    0b1001000,
    0b1001000,
    0b0111111
};

const uint8_t char_Z[5] PROGMEM = {
    4,
    0b1110001,
    0b1001001,
    0b1001001,
    0b1000111
};

const uint8_t  char_space[4] PROGMEM = {
    3,
    0b00000000,
    0b00000000,
    0b00000000
};

const uint8_t  char_1[5] PROGMEM = {
    4,
    0b1000010,
    0b1111111,
    0b1000000,
    0b0000000
};

const uint8_t  char_2[5] PROGMEM = {
    4,
    0b1100010,
    0b1010001,
    0b1001001,
    0b1000110
};
const uint8_t  char_3[5] PROGMEM= {
    4,
    0b0100010,
    0b1001001,
    0b1001001,
    0b0110110
};
const uint8_t  char_4[5] PROGMEM = {
    4,
    0b0001100,
    0b0001010,
    0b0001001,
    0b1111111
};
const uint8_t  char_5[5] PROGMEM = {
    4,
    0b1000111,
    0b1000101,
    0b1000101,
    0b0111001,
};
const uint8_t  char_6[5] PROGMEM = {
    4,
    0b0111100,
    0b1001010,
    0b1001001,
    0b0110000
};
const uint8_t  char_7[5] PROGMEM = {
    4,
    0b0000001,
    0b1110001,
    0b0001001,
    0b0000111,
};
const uint8_t  char_8[5] PROGMEM = {
    4,
    0b0110110,
    0b1001001,
    0b1001001,
    0b0110110,
};
const uint8_t  char_9[5] PROGMEM = {
    4,
    0b0000110,
    0b1001001,
    0b0101001,
    0b0011110,
};
const uint8_t  char_0[5] PROGMEM = {
    4,
    0b0111110,
    0b1001001,
    0b1000101,
    0b0111110,
};
const uint8_t char_dot[2] PROGMEM = {
    1,
    0b1000000,
};

const uint8_t char_2dot[2] PROGMEM = {
    1,
    0b1001000,
};

extern const uint8_t  char_deg[4] PROGMEM = {
    3,
    0b0000010,
    0b0000101,
    0b0000010
};


const uint8_t *letter2char(const char letter){
    switch (letter)
    {
    case 'A':
        return char_A;
        break;
    case 'B':
        return char_B;
        break;
    case 'C':
        return char_C;
        break;
    case 'D':
        return char_D;
        break;
    case 'E':
        return char_E;
        break;
    case 'F':
        return char_F;
        break;
    case 'G':
        return char_G;
        break;
    case 'H':
        return char_H;
        break;
    case 'I':
        return char_I;
        break;
    case 'J':
        return char_J;
        break;
    case 'K':
        return char_K;
        break;
    case 'L':
        return char_L;
        break;
    case 'M':
        return char_M;
        break;
    case 'N':
        return char_N;
        break;
    case 'O':
        return char_O;
        break;
    case 'P':
        return char_P;
        break;
    case 'Q':
        return char_Q;
        break;
    case 'R':
        return char_R;
        break;
    case 'S':
        return char_S;
        break;
    case 'T':
        return char_T;
        break;
    case 'U':
        return char_U;
        break;
    case 'V':
        return char_V;
        break;
    case 'W':
        return char_W;
        break;
    case 'X':
        return char_X;
        break;
    case 'Y':
        return char_Y;
        break;
    case 'Z':
        return char_Z;
        break;
    case ' ':
        return char_space;
        break;
    case '.':
        return char_dot;
        break;
    case ':':
        return char_2dot;
        break;
    case '$':
        return char_deg;
        break;
    case '0':
        return char_0;
        break;
    case '1':
        return char_1;
        break;
    case '2':
        return char_2;
        break;
    case '3':
        return char_3;
        break;
    case '4':
        return char_4;
        break;
    case '5':
        return char_5;
        break;
    case '6':
        return char_6;
        break;
    case '7':
        return char_7;
        break;
    case '8':
        return char_8;
        break;
    case '9':
        return char_9;
        break;
    default:
        break;
    }
}

const uint8_t *int2char(const char value){
    switch (value)
    {
    case 0:
        return char_0;
        break;
    case 1:
        return char_1;
        break;
    case 2:
        return char_2;
        break;
    case 3:
        return char_3;
        break;
    case 4:
        return char_4;
        break;
    case 5:
        return char_5;
        break;
    case 6:
        return char_6;
        break;
    case 7:
        return char_7;
        break;
    case 8:
        return char_8;
        break;
    case 9:
        return char_9;
        break;
    default:
        return char_E;
        break;
    }
}