#ifndef VAR_H
#define VAR_H

#include "type.h"

typedef struct {
    char name[30];
    Type type;  
    char *data;
} Var;

#endif
