#include "../include/ipv4.h"
#include <stdio.h>
#include <string.h>

IpV4_address ip_istituto;

void init_ip_istituto(void)
{
    assegna_ip(&ip_istituto, 192, 168, 1, 1);
    assegna_mask(&ip_istituto, 255, 255, 255, 0);
    assegna_dominio(&ip_istituto, "itis-davinci.pr.it");
    ip_istituto.proprietario = NULL;
}

void assegna_dominio(IpV4_address *ip_address, char dominio[])
{
    strcpy(ip_address->dominio, dominio);
}

void assegna_ip_da_stringa(IpV4_address *ip_address, char ip[])
{
    while (*ip == ' ') {
        ip++;
    }
    if (strlen(ip) > 15 || strlen(ip) < 7) {
        return;
    }
    while (ip[strlen(ip) - 1] == ' ') {
        ip[strlen(ip) - 1] = '\0';
    }
    int separatori = 0;
    for (int i = 0; i < strlen(ip); i++) {
        if (ip[i] == '.' || ip[i] == ',' || ip[i] == '/' || ip[i] == '\\' || ip[i] == ' ' || ip[i] == '|') {
            separatori++;
        }
    }
    if (separatori != 3) {
        return;
    }

    
    sscanf(ip, "%hhu.%hhu.%hhu.%hhu", &ip_address->ip[0], &ip_address->ip[1], &ip_address->ip[2], &ip_address->ip[3]);
}

void assegna_ip(IpV4_address *ip_address,unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    ip_address->ip[0]=a;
    ip_address->ip[1]=b;
    ip_address->ip[2]=c;
    ip_address->ip[3]=d;
}

void assegna_mask(IpV4_address *ip_address, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    ip_address->mask[0]=a;
    ip_address->mask[1]=b;
    ip_address->mask[2]=c;
    ip_address->mask[3]=d;
}

void stampa_mask(IpV4_address *ip_address)
{
    printf("%d.%d.%d.%d\n", ip_address->mask[0], ip_address->mask[1], ip_address->mask[2], ip_address->mask[3]);
}

void stampa_ip(IpV4_address *ip_address)
{
    printf("%d.%d.%d.%d\n", ip_address->ip[0], ip_address->ip[1], ip_address->ip[2], ip_address->ip[3]);
}

void calcola_rete(IpV4_address *ip_address, IpV4 rete)
{
    for(int i = 0; i < 4; i++)
    {
        rete[i] = ip_address->ip[i] & ip_address->mask[i];
    }
}

void calcola_broadcast(IpV4_address *ip_address, IpV4 broadcast)
{
    for(int i = 0; i < 4; i++)
    {
        broadcast[i] = ip_address->ip[i] | (~ip_address->mask[i]);
    }
}

int conta_bit_mask(Mask mask)
{
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        unsigned char byte = mask[i];
        while(byte)
        {
            count += byte & 1;
            byte >>= 1;
        }
    }
    return count;
}

char determina_classe(IpV4 ip)
{
    unsigned char primo_ottetto = ip[0];
    
    if(primo_ottetto <= CLASSE_A_MAX)
    {
        return 'A';
    }
    else if(primo_ottetto <= CLASSE_B_MAX)
    {
        return 'B';
    }
    else if(primo_ottetto <= CLASSE_C_MAX)
    {
        return 'C';
    }
    else if(primo_ottetto <= CLASSE_D_MAX)
    {
        return 'D';
    }
    else
    {
        return 'E';
    }
}

int is_ip_privato(IpV4 ip)
{
    if(ip[0] == IP_PRIVATO_10)
    {
        return 1;
    }
    if(ip[0] == IP_PRIVATO_172 && ip[1] >= IP_PRIVATO_172_MIN && ip[1] <= IP_PRIVATO_172_MAX)
    {
        return 1;
    }
    if(ip[0] == IP_PRIVATO_192_FIRST && ip[1] == IP_PRIVATO_192_SECOND)
    {
        return 1;
    }
    return 0;
}

void stampa_info_rete(IpV4_address *ip_address)
{
    IpV4 rete, broadcast;
    
    calcola_rete(ip_address, rete);
    calcola_broadcast(ip_address, broadcast);
    
    char classe = determina_classe(ip_address->ip);
    int cidr = conta_bit_mask(ip_address->mask);
    int privato = is_ip_privato(ip_address->ip);
    
    printf("\n=== INFORMAZIONI RETE ===\n");
    printf("IP:           %d.%d.%d.%d\n", 
           ip_address->ip[0], ip_address->ip[1], 
           ip_address->ip[2], ip_address->ip[3]);
    printf("Maschera:     %d.%d.%d.%d\n", 
           ip_address->mask[0], ip_address->mask[1], 
           ip_address->mask[2], ip_address->mask[3]);
    printf("CIDR:         /%d\n", cidr);
    printf("Rete:         %d.%d.%d.%d\n", 
           rete[0], rete[1], rete[2], rete[3]);
    printf("Broadcast:    %d.%d.%d.%d\n", 
           broadcast[0], broadcast[1], broadcast[2], broadcast[3]);
    printf("Classe:       %c\n", classe);
    printf("Tipo:         %s\n", privato ? "Privato" : "Pubblico");
    
    unsigned long num_host = 1;
    for(int i = 0; i < 4; i++)
    {
        num_host *= (256 - ip_address->mask[i]);
    }
    num_host -= 2;
    
    printf("Host validi:  %lu\n", num_host);
    printf("========================\n\n");
}
