#ifndef PERSONA_H
#define PERSONA_H

#include "config.h"

typedef struct
{
    char via[MAX_STRG];
    unsigned char cap[MAX_CAP_LEN];
    unsigned char numero_civico[MAX_CIVICO_LEN];
} Indirizzo;

typedef struct
{
    char nome[MAX_STRG];
    char cognome[MAX_STRG];
    Indirizzo indirizzo;
} Persona;

void assegna_nome(Persona *persona, char nome[]);
void assegna_cognome(Persona *persona, char cognome[]);

#endif
