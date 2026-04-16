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

Persona *creaPersona(char nome[], char cognome[])
{
    Persona *persona = (Persona *)malloc(sizeof(Persona));
    assegna_nome(persona, nome);
    assegna_cognome(persona, cognome);
    return persona;
}

void distruggiPersona(Persona *persona)
{
    free(persona);
}
