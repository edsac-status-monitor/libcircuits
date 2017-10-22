#ifndef __CIRCUIT_H
#define __CIRCUIT_H

#include <stdio.h>

#include "vector.h"

#define CIRCUIT_OK 0
#define CIRCUIT_ERR 1

#define CIRCUIT_TYPE_WIRE "WIRE"

typedef struct {
    int start_x, start_y;
    int end_x, end_y;
} wire_t;

typedef struct {
    vector_t wires;
} circuit_t;

int circuit_parse_file(FILE *infile, circuit_t *cir);

void circuit_init(circuit_t *circuit);
void circuit_free(circuit_t *circuit);

#endif
