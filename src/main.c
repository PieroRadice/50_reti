#include <stdio.h>
#include "../include/persona.h"
#include "../include/ipv4.h"

int main()
{
    Persona persona;
    IpV4_address ip_address;

    init_ip_istituto();

    printf("\n*** IP ISTITUTO: %s ***\n", ISTITUTO_NOME);
    stampa_info_rete(&ip_istituto);

    assegna_nome(&persona, "Mario");
    assegna_cognome(&persona, "Rossi");
    assegna_dominio(&ip_address, "www.google.com");

    printf("\n*** ESEMPIO 1: Rete classe C privata ***\n");
    assegna_ip(&ip_address, 192, 168, 1, 130);
    assegna_mask(&ip_address, 255, 255, 255, 128);
    stampa_info_rete(&ip_address);

    printf("*** ESEMPIO 2: Rete classe B privata ***\n");
    assegna_ip(&ip_address, 172, 16, 50, 100);
    assegna_mask(&ip_address, 255, 255, 240, 0);
    stampa_info_rete(&ip_address);

    printf("*** ESEMPIO 3: Rete classe A privata ***\n");
    assegna_ip(&ip_address, 10, 20, 30, 40);
    assegna_mask(&ip_address, 255, 0, 0, 0);
    stampa_info_rete(&ip_address);

    printf("*** ESEMPIO 4: IP pubblico classe A (Google DNS) ***\n");
    assegna_ip(&ip_address, 8, 8, 8, 8);
    assegna_mask(&ip_address, 255, 255, 255, 0);
    stampa_info_rete(&ip_address);

    printf("*** ESEMPIO 5: Subnet /30 (point-to-point) ***\n");
    assegna_ip(&ip_address, 192, 168, 100, 5);
    assegna_mask(&ip_address, 255, 255, 255, 252);
    stampa_info_rete(&ip_address);

    printf("indirizzo di memoria di ip_address: %p\n", &ip_address);
    printf("indirizzo di memoria di ip_istituto: %p\n", &ip_istituto);
    printf("indirizzo di memoria di ISTITUTO_NOME: %p\n", (void*)ISTITUTO_NOME);
    printf("Posizione in memoria del proprietario: %p\n", (void*)ip_address.proprietario);
    printf("Posizione in memoria dell'indirizzo del proprietario: %p\n", &(ip_address.proprietario));



    return 0;
}
