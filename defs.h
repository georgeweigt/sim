#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define NSYM 100
#define STACKSIZE 100
#define TOKENBUFLEN 100

struct sym {
	char *name;
	int value;
	int where; // line number
};

extern void (*ftab[256])(void);
extern char *buf;
extern int buflen;
extern int token;
extern int tokenlen;
extern char tokenbuf[TOKENBUFLEN + 1];
extern char *scanptr;
extern char *tokenptr;
extern char *lineptr;
extern int addrmode;
extern int value;
extern int pass;
extern int where;
extern struct sym stab[26][NSYM];
extern int stack[STACKSIZE];
extern int stackindex;
extern int curloc;
extern int curlin;
extern int start;
extern uint8_t *mem;
extern uint8_t acc;
extern uint8_t x;
extern uint8_t y; 
extern uint8_t sp;
extern uint8_t nf;
extern uint8_t of;
extern uint8_t df;
extern uint8_t id; 
extern uint8_t zf; 
extern uint8_t cf;
extern uint16_t pc;
