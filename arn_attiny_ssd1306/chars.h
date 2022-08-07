#ifndef CHARS_H
#define CHARS_H
#include <Arduino.h>
#include <avr/pgmspace.h>
extern const uint8_t  char_A[5] PROGMEM;
extern const uint8_t  char_B[5] PROGMEM;
extern const uint8_t  char_C[5] PROGMEM;
extern const uint8_t  char_D[5] PROGMEM;
extern const uint8_t  char_E[5] PROGMEM;
extern const uint8_t  char_F[5] PROGMEM;
extern const uint8_t  char_G[5] PROGMEM;
extern const uint8_t  char_H[5] PROGMEM;
extern const uint8_t  char_I[5] PROGMEM;
extern const uint8_t  char_J[5] PROGMEM;
extern const uint8_t  char_K[5] PROGMEM;
extern const uint8_t  char_L[5] PROGMEM;
extern const uint8_t  char_M[6] PROGMEM;
extern const uint8_t  char_N[5] PROGMEM;
extern const uint8_t  char_O[5] PROGMEM;
extern const uint8_t  char_P[5] PROGMEM;
extern const uint8_t  char_Q[5] PROGMEM;
extern const uint8_t  char_R[5] PROGMEM;
extern const uint8_t  char_S[5] PROGMEM;
extern const uint8_t  char_T[6] PROGMEM;
extern const uint8_t  char_U[5] PROGMEM;
extern const uint8_t  char_V[6] PROGMEM;
extern const uint8_t  char_W[6] PROGMEM;
extern const uint8_t  char_X[5] PROGMEM;
extern const uint8_t  char_Y[5] PROGMEM;
extern const uint8_t  char_Z[5] PROGMEM;

extern const uint8_t  char_1[4] PROGMEM;
extern const uint8_t  char_2[5] PROGMEM;
extern const uint8_t  char_3[5] PROGMEM;
extern const uint8_t  char_4[5] PROGMEM;
extern const uint8_t  char_5[5] PROGMEM;
extern const uint8_t  char_6[5] PROGMEM;
extern const uint8_t  char_7[5] PROGMEM;
extern const uint8_t  char_8[5] PROGMEM;
extern const uint8_t  char_9[5] PROGMEM;
extern const uint8_t  char_0[5] PROGMEM;


extern const uint8_t  char_space[4] PROGMEM;
extern const uint8_t  char_dot[2] PROGMEM;
extern const uint8_t  char_2dot[2] PROGMEM;

extern const uint8_t  char_deg[4] PROGMEM;

const uint8_t *letter2char(const char letter);
#endif