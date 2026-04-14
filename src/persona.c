#include "../include/persona.h"
#include <string.h>

void assegna_nome(Persona *persona, char nome[])
{
    strcpy(persona->nome, nome);
}

void assegna_cognome(Persona *persona, char cognome[])
{
    strcpy(persona->cognome, cognome);
}
