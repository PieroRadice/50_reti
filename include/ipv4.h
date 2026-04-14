#ifndef IPV4_H
#define IPV4_H

#include "config.h"
#include "persona.h"

typedef unsigned char IpV4[4];
typedef unsigned char Mask[4];

typedef struct
{
    IpV4 ip;
    Mask mask;
    char dominio[MAX_STRG];
    Persona *proprietario;
} IpV4_address;

void assegna_dominio(IpV4_address *ip_address, char dominio[]);
void assegna_ip_da_stringa(IpV4_address *ip_address, char ip[]);
void assegna_ip(IpV4_address *ip_address, unsigned char a, unsigned char b, unsigned char c, unsigned char d);
void assegna_mask(IpV4_address *ip_address, unsigned char a, unsigned char b, unsigned char c, unsigned char d);
void stampa_mask(IpV4_address *ip_address);
void stampa_ip(IpV4_address *ip_address);
void calcola_rete(IpV4_address *ip_address, IpV4 rete);
void calcola_broadcast(IpV4_address *ip_address, IpV4 broadcast);
int conta_bit_mask(Mask mask);
char determina_classe(IpV4 ip);
int is_ip_privato(IpV4 ip);
void stampa_info_rete(IpV4_address *ip_address);

extern IpV4_address ip_istituto;

void init_ip_istituto(void);

#endif
