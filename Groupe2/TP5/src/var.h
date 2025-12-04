#ifndef VAR_H
#define VAR_H

#include "type.h"

typedef struct {
    char name[30];
    Type type;   // <-- juste "Type", pas "enum Type"
    char *data;
} Var;

#endif
