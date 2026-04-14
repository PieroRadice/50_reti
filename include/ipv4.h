#ifndef IPV4_H
#define IPV4_H

#include "config.h"
#include "persona.h"

/**
 * @brief Tipo per rappresentare un indirizzo IPv4
 * 
 * Array di 4 byte (ottetti) che rappresentano un indirizzo IP
 */
typedef unsigned char IpV4[4];

/**
 * @brief Tipo per rappresentare una maschera di rete
 * 
 * Array di 4 byte che rappresentano una subnet mask
 */
typedef unsigned char Mask[4];

/**
 * @brief Struttura completa per un indirizzo IPv4 con metadati
 * 
 * Contiene l'indirizzo IP, la maschera di rete, il dominio associato
 * e un puntatore opzionale al proprietario
 */
typedef struct
{
    IpV4 ip;                    /**< Indirizzo IPv4 (4 ottetti) */
    Mask mask;                  /**< Maschera di rete (4 ottetti) */
    char dominio[MAX_STRG];     /**< Nome di dominio associato */
    Persona *proprietario;      /**< Puntatore al proprietario (opzionale) */
} IpV4_address;

/**
 * @brief Assegna un nome di dominio a un indirizzo IP
 * 
 * @param ip_address Puntatore alla struttura IpV4_address da modificare
 * @param dominio Stringa contenente il nome di dominio (es: "example.com")
 */
void assegna_dominio(IpV4_address *ip_address, char dominio[]);

/**
 * @brief Parsing di un indirizzo IP da stringa
 * 
 * Converte una stringa in formato "xxx.xxx.xxx.xxx" in un indirizzo IP.
 * Supporta vari separatori (. , / \ | spazio) e valida il formato.
 * 
 * @param ip_address Puntatore alla struttura IpV4_address da modificare
 * @param ip Stringa contenente l'IP (es: "192.168.1.1")
 */
void assegna_ip_da_stringa(IpV4_address *ip_address, char ip[]);

/**
 * @brief Assegna un indirizzo IP specificando i 4 ottetti
 * 
 * @param ip_address Puntatore alla struttura IpV4_address da modificare
 * @param a Primo ottetto (0-255)
 * @param b Secondo ottetto (0-255)
 * @param c Terzo ottetto (0-255)
 * @param d Quarto ottetto (0-255)
 */
void assegna_ip(IpV4_address *ip_address, unsigned char a, unsigned char b, unsigned char c, unsigned char d);

/**
 * @brief Assegna una maschera di rete specificando i 4 ottetti
 * 
 * @param ip_address Puntatore alla struttura IpV4_address da modificare
 * @param a Primo ottetto della maschera (0-255)
 * @param b Secondo ottetto della maschera (0-255)
 * @param c Terzo ottetto della maschera (0-255)
 * @param d Quarto ottetto della maschera (0-255)
 */
void assegna_mask(IpV4_address *ip_address, unsigned char a, unsigned char b, unsigned char c, unsigned char d);

/**
 * @brief Stampa la maschera di rete in formato decimale puntato
 * 
 * @param ip_address Puntatore alla struttura IpV4_address contenente la maschera
 */
void stampa_mask(IpV4_address *ip_address);

/**
 * @brief Stampa l'indirizzo IP in formato decimale puntato
 * 
 * @param ip_address Puntatore alla struttura IpV4_address contenente l'IP
 */
void stampa_ip(IpV4_address *ip_address);

/**
 * @brief Calcola l'indirizzo di rete (IP AND maschera)
 * 
 * @param ip_address Puntatore alla struttura IpV4_address con IP e maschera
 * @param rete Array di 4 byte dove salvare l'indirizzo di rete calcolato
 */
void calcola_rete(IpV4_address *ip_address, IpV4 rete);

/**
 * @brief Calcola l'indirizzo di broadcast (IP OR NOT maschera)
 * 
 * @param ip_address Puntatore alla struttura IpV4_address con IP e maschera
 * @param broadcast Array di 4 byte dove salvare l'indirizzo di broadcast calcolato
 */
void calcola_broadcast(IpV4_address *ip_address, IpV4 broadcast);

/**
 * @brief Conta i bit a 1 nella maschera di rete (notazione CIDR)
 * 
 * @param mask Maschera di rete da analizzare
 * @return Numero di bit a 1 (es: 255.255.255.0 ritorna 24)
 */
int conta_bit_mask(Mask mask);

/**
 * @brief Determina la classe dell'indirizzo IP (A, B, C, D, E)
 * 
 * Classifica l'IP in base al primo ottetto:
 * - Classe A: 0-127
 * - Classe B: 128-191
 * - Classe C: 192-223
 * - Classe D: 224-239 (multicast)
 * - Classe E: 240-255 (riservato)
 * 
 * @param ip Indirizzo IPv4 da classificare
 * @return Carattere rappresentante la classe ('A', 'B', 'C', 'D', 'E')
 */
char determina_classe(IpV4 ip);

/**
 * @brief Verifica se l'IP è privato secondo RFC 1918
 * 
 * Controlla se l'IP appartiene ai range privati:
 * - 10.0.0.0/8
 * - 172.16.0.0/12
 * - 192.168.0.0/16
 * 
 * @param ip Indirizzo IPv4 da verificare
 * @return 1 se privato, 0 se pubblico
 */
int is_ip_privato(IpV4 ip);

/**
 * @brief Stampa tutte le informazioni sulla rete
 * 
 * Visualizza in modo formattato: IP, maschera, CIDR, rete, broadcast,
 * classe, tipo (privato/pubblico) e numero di host validi
 * 
 * @param ip_address Puntatore alla struttura IpV4_address da visualizzare
 */
void stampa_info_rete(IpV4_address *ip_address);

/**
 * @brief Variabile globale per l'indirizzo IP dell'istituto
 * 
 * Istanza globale di IpV4_address allocata in RAM, accessibile da
 * qualsiasi file che include ipv4.h. Deve essere inizializzata
 * chiamando init_ip_istituto() prima dell'uso.
 */
extern IpV4_address ip_istituto;

/**
 * @brief Inizializza la variabile globale ip_istituto
 * 
 * Configura ip_istituto con i valori predefiniti dell'istituto:
 * - IP: 192.168.1.1
 * - Maschera: 255.255.255.0
 * - Dominio: "itis-davinci.pr.it"
 * - Proprietario: NULL
 * 
 * Deve essere chiamata nel main() prima di usare ip_istituto
 */
void init_ip_istituto(void);

#endif
