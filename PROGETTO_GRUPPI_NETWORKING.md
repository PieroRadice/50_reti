# Progetto Modulare di Networking - Classe 3 ITIS

## Obiettivo del Progetto
Sviluppare una libreria modulare in C per la gestione e l'analisi di reti informatiche, dove ogni gruppo lavora su un modulo specifico seguendo standard comuni di programmazione.

---

## Struttura del Progetto

### Coordinatori (1 coppia - 2 studenti)
**Modulo**: `network_core.c` / `network_core.h`

**Responsabilità**:
- Definire le strutture dati comuni utilizzate da tutti i gruppi
- Creare il file `config.h` con costanti globali del progetto
- Sviluppare il `main.c` che integra tutti i moduli
- Verificare la compatibilità tra i moduli dei vari gruppi
- Gestire la compilazione finale del progetto
- Coordinare le riunioni di integrazione
- Risolvere conflitti tra moduli

**Contenuto del modulo**:
- Strutture base: `NetworkPacket`, `NetworkInterface`, `ConnectionInfo`
- Funzioni di utilità comuni: conversioni, validazioni base
- Gestione errori centralizzata

---

## Gruppi di Lavoro (6 gruppi)

### Gruppo 1: Gestione Indirizzi MAC
**Modulo**: `mac_address.c` / `mac_address.h`

**Argomento**: Indirizzi MAC (Media Access Control)

**Funzionalità da implementare**:
- Struttura per rappresentare un indirizzo MAC (6 byte)
- Parsing di MAC address da stringa (formato `AA:BB:CC:DD:EE:FF`)
- Validazione formato MAC address
- Conversione MAC in stringa
- Identificazione vendor da OUI (primi 3 byte)
- Generazione MAC address casuali
- Confronto tra MAC address
- Verifica MAC broadcast/multicast/unicast

**Esempio di utilizzo**:
```c
MacAddress mac;
assegna_mac_da_stringa(&mac, "00:1A:2B:3C:4D:5E");
stampa_mac(&mac);
char vendor[50];
identifica_vendor(&mac, vendor);
```

---

### Gruppo 2: Protocollo ARP
**Modulo**: `arp.c` / `arp.h`

**Argomento**: Address Resolution Protocol

**Funzionalità da implementare**:
- Struttura per entry ARP cache (IP + MAC + timestamp)
- Simulazione ARP cache (array di entry)
- Aggiunta entry alla cache
- Ricerca MAC da IP
- Ricerca IP da MAC
- Rimozione entry scadute (timeout)
- Stampa tabella ARP
- Simulazione richiesta/risposta ARP
- Gestione ARP gratuito

**Esempio di utilizzo**:
```c
ArpCache cache;
inizializza_arp_cache(&cache);
aggiungi_arp_entry(&cache, "192.168.1.10", "AA:BB:CC:DD:EE:FF");
MacAddress *mac = cerca_mac_da_ip(&cache, "192.168.1.10");
```

---

### Gruppo 3: Protocollo ICMP
**Modulo**: `icmp.c` / `icmp.h`

**Argomento**: Internet Control Message Protocol (ping, traceroute)

**Funzionalità da implementare**:
- Struttura messaggio ICMP (tipo, codice, checksum, dati)
- Tipi di messaggi ICMP (Echo Request/Reply, Destination Unreachable, ecc.)
- Simulazione ping (invio Echo Request, ricezione Echo Reply)
- Calcolo RTT (Round Trip Time) simulato
- Simulazione traceroute (hop-by-hop)
- Gestione messaggi di errore ICMP
- Statistiche ping (pacchetti inviati/ricevuti/persi)
- Calcolo checksum ICMP

**Esempio di utilizzo**:
```c
IcmpPacket packet;
crea_echo_request(&packet, 1, 1);
simula_ping("8.8.8.8", 4, &statistiche);
stampa_statistiche_ping(&statistiche);
```

---

### Gruppo 4: DNS
**Modulo**: `dns.c` / `dns.h`

**Argomento**: Domain Name System

**Funzionalità da implementare**:
- Struttura record DNS (nome, tipo, valore, TTL)
- Simulazione cache DNS locale
- Risoluzione nome → IP (lookup simulato)
- Risoluzione inversa IP → nome
- Tipi di record (A, AAAA, MX, CNAME, NS, PTR)
- Validazione nome dominio
- Gestione TTL e scadenza cache
- Simulazione query DNS ricorsiva/iterativa

**Esempio di utilizzo**:
```c
DnsCache cache;
inizializza_dns_cache(&cache);
aggiungi_record_dns(&cache, "www.google.com", A, "142.250.180.46", 300);
char ip[16];
risolvi_nome(&cache, "www.google.com", ip);
```

---

### Gruppo 5: Indirizzi IPv6
**Modulo**: `ipv6.c` / `ipv6.h`

**Argomento**: Gestione indirizzi IPv6

**Funzionalità da implementare**:
- Struttura per rappresentare un indirizzo IPv6 (16 byte)
- Parsing IPv6 da stringa (formato completo e compresso)
- Conversione IPv6 in stringa (con compressione zeri)
- Espansione indirizzo IPv6 compresso
- Validazione formato IPv6
- Identificazione tipo indirizzo (unicast, multicast, link-local, loopback)
- Estrazione prefisso di rete da IPv6/prefisso
- Confronto tra indirizzi IPv6
- Conversione IPv4-mapped IPv6

**Esempio di utilizzo**:
```c
Ipv6Address ipv6;
assegna_ipv6_da_stringa(&ipv6, "2001:0db8::1");
char str_espanso[40];
espandi_ipv6(&ipv6, str_espanso);
printf("IPv6 espanso: %s\n", str_espanso);
char tipo[20];
identifica_tipo_ipv6(&ipv6, tipo);
```

---

### Gruppo 6: Frame Ethernet
**Modulo**: `ethernet.c` / `ethernet.h`

**Argomento**: Frame Ethernet e livello Data Link

**Funzionalità da implementare**:
- Struttura frame Ethernet (MAC dest, MAC src, EtherType, payload, FCS)
- Creazione frame Ethernet
- Parsing frame da buffer
- Identificazione protocollo da EtherType (IPv4, IPv6, ARP)
- Calcolo e verifica FCS (Frame Check Sequence)
- Gestione VLAN tag (802.1Q)
- Dimensione minima/massima frame (64-1518 byte)
- Stampa frame in formato leggibile
- Simulazione invio/ricezione frame

**Esempio di utilizzo**:
```c
EthernetFrame frame;
crea_frame_ethernet(&frame, "AA:BB:CC:DD:EE:FF", "11:22:33:44:55:66", ETHERTYPE_IPV4);
aggiungi_payload(&frame, dati, lunghezza);
calcola_fcs(&frame);
stampa_frame(&frame);
char protocollo[20];
identifica_protocollo_ethernet(&frame, protocollo);
```

---

## Regole di Redazione File

### 1. Struttura File Header (.h)

```c
#ifndef NOME_MODULO_H
#define NOME_MODULO_H

#include "network_core.h"  // Include sempre il core
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Costanti del modulo
#define COSTANTE_1 valore
#define COSTANTE_2 valore

// Typedef e strutture
typedef struct {
    // campi
} NomeStruttura;

// Prototipi funzioni (con commenti Doxygen)

/**
 * @brief Breve descrizione funzione
 * 
 * Descrizione dettagliata del comportamento
 * 
 * @param param1 Descrizione parametro 1
 * @param param2 Descrizione parametro 2
 * @return Descrizione valore di ritorno
 */
tipo_ritorno nome_funzione(tipo param1, tipo param2);

#endif
```

### 2. Struttura File Implementazione (.c)

```c
#include "nome_modulo.h"

// Implementazione funzioni
tipo_ritorno nome_funzione(tipo param1, tipo param2)
{
    // Implementazione
}
```

### 3. Convenzioni di Naming

**Costanti**:
- Tutto maiuscolo con underscore: `MAX_BUFFER_SIZE`

**Strutture**:
- PascalCase: `MacAddress`, `DnsCache`, `RoutingTable`

**Funzioni**:
- snake_case con prefisso modulo: `mac_assegna_da_stringa()`, `dns_risolvi_nome()`
- Verbi all'infinito: `calcola_`, `verifica_`, `stampa_`, `inizializza_`

**Variabili**:
- snake_case: `ip_address`, `num_host`, `cache_size`

### 4. Documentazione Obbligatoria

**Ogni file .h deve contenere**:
- Intestazione con nome gruppo, componenti, data
- Commento Doxygen per ogni funzione pubblica
- Descrizione scopo del modulo

**Esempio intestazione**:
```c
/**
 * @file mac_address.h
 * @brief Gestione indirizzi MAC
 * @author Gruppo 1: Mario Rossi, Luca Bianchi, Sara Verdi
 * @date 2024-05-06
 * 
 * Modulo per la gestione e manipolazione di indirizzi MAC (Media Access Control).
 * Fornisce funzioni per parsing, validazione, conversione e identificazione vendor.
 */
```

### 5. Gestione Errori

- Ogni funzione deve validare i parametri in input
- Usare valori di ritorno per segnalare successo/errore:
  - `0` = successo
  - `-1` = errore generico
  - Altri codici per errori specifici
- Funzioni che restituiscono puntatori: `NULL` in caso di errore

**Esempio**:
```c
int assegna_mac_da_stringa(MacAddress *mac, const char *str)
{
    if (mac == NULL || str == NULL) {
        return -1;  // Parametri non validi
    }
    
    if (strlen(str) != 17) {
        return -2;  // Formato non valido
    }
    
    // ... implementazione ...
    
    return 0;  // Successo
}
```

### 6. Stile di Codice

**Indentazione**: 4 spazi (NO tab)

**Parentesi graffe**:
```c
if (condizione)
{
    // codice
}
else
{
    // codice
}
```

**Lunghezza righe**: Massimo 100 caratteri

**Commenti**:
- `//` per commenti su singola riga
- `/* */` per commenti multi-riga
- Doxygen `/** */` per documentazione API

### 7. File da Consegnare

Ogni gruppo deve consegnare:
1. `nome_modulo.h` - File header
2. `nome_modulo.c` - Implementazione
3. `test_nome_modulo.c` - File di test con funzione main() che testa tutte le funzionalità
4. `README_nome_modulo.md` - Documentazione del modulo con esempi d'uso

### 8. Compilazione e Test

**Compilazione singolo modulo**:
```bash
gcc -c nome_modulo.c -o nome_modulo.o
```

**Compilazione test**:
```bash
gcc test_nome_modulo.c nome_modulo.c network_core.c -o test_modulo
./test_modulo
```

**Il test deve**:
- Testare tutte le funzioni del modulo
- Stampare risultati in modo chiaro
- Verificare casi limite ed errori
- Non richiedere input utente (dati hardcoded)

### 9. Dipendenze tra Moduli

**Permesse**:
- Tutti i moduli possono includere `network_core.h`
- Moduli possono includere altri moduli se necessario (es: ethernet può usare mac_address)

**Vietate**:
- Dipendenze circolari
- Inclusione di moduli non necessari

### 10. Controllo Qualità

**Ogni gruppo deve verificare**:
- ✅ Compilazione senza warning (`gcc -Wall -Wextra`)
- ✅ Nessun memory leak (se si usa malloc/free)
- ✅ Tutti i prototipi hanno implementazione
- ✅ Documentazione completa
- ✅ Test funzionanti
- ✅ Codice formattato correttamente
- ✅ Nomi conformi alle convenzioni

---

## Timeline del Progetto

**Settimana 1**: Analisi requisiti e progettazione strutture dati
**Settimana 2**: Implementazione funzioni base
**Settimana 3**: Implementazione funzioni avanzate e test
**Settimana 4**: Integrazione moduli e test completo
**Settimana 5**: Documentazione finale e presentazione

---

## Valutazione

**Criteri di valutazione**:
- Correttezza funzionale (40%)
- Qualità del codice e stile (20%)
- Documentazione (20%)
- Test e validazione (10%)
- Integrazione con altri moduli (10%)

**Bonus**:
- Funzionalità extra oltre ai requisiti minimi
- Gestione casi edge particolarmente complessi
- Interfaccia utente particolarmente chiara

---

## Risorse Consigliate

**Riferimenti teorici**:
- RFC 791 (IP), RFC 826 (ARP), RFC 792 (ICMP)
- Libro di testo di Sistemi e Reti
- Wireshark per analisi pacchetti reali

**Tool utili**:
- GCC per compilazione
- Valgrind per memory leak
- GDB per debugging
- Doxygen per generare documentazione HTML

---

## Note Finali

- **Comunicazione**: Usare un gruppo WhatsApp/Teams per coordinamento
- **Versioning**: Ogni gruppo può usare git per il proprio modulo
- **Domande**: Rivolgersi ai coordinatori per dubbi su interfacce comuni
- **Collaborazione**: Aiutarsi tra gruppi è incoraggiato, copiare è vietato

**Buon lavoro!** 🚀
