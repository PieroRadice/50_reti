#ifndef PERSONA_H
#define PERSONA_H

#include "config.h"

/**
 * @brief Struttura per rappresentare un indirizzo fisico
 * 
 * Contiene le informazioni relative a un indirizzo postale
 */
typedef struct
{
    char via[MAX_STRG];                        /**< Nome della via */
    unsigned char cap[MAX_CAP_LEN];            /**< Codice di Avviamento Postale */
    unsigned char numero_civico[MAX_CIVICO_LEN]; /**< Numero civico */
} Indirizzo;

/**
 * @brief Struttura per rappresentare una persona
 * 
 * Contiene i dati anagrafici di una persona
 */
typedef struct
{
    char nome[MAX_STRG];      /**< Nome della persona */
    char cognome[MAX_STRG];   /**< Cognome della persona */
    Indirizzo indirizzo;      /**< Indirizzo di residenza */
} Persona;

/**
 * @brief Assegna il nome a una persona
 * 
 * @param persona Puntatore alla struttura Persona da modificare
 * @param nome Stringa contenente il nome da assegnare
 */
void assegna_nome(Persona *persona, char nome[]);

/**
 * @brief Assegna il cognome a una persona
 * 
 * @param persona Puntatore alla struttura Persona da modificare
 * @param cognome Stringa contenente il cognome da assegnare
 */
void assegna_cognome(Persona *persona, char cognome[]);

Persona *creaPersona(char nome[], char cognome[]);
void distruggiPersona(Persona *persona);

#endif
