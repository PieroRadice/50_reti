# Progetto 50_reti - Gestione Indirizzi IPv4

Progetto didattico in C per la gestione e l'analisi di indirizzi IPv4.

## Struttura del Progetto

```
50_reti/
├── 50_reti.cbp          # File progetto Code::Blocks
├── README.md            # Questo file
├── include/             # File header (.h)
│   ├── config.h        # Costanti e configurazioni globali
│   ├── persona.h       # Interfaccia modulo persona
│   └── ipv4.h          # Interfaccia modulo IPv4
└── src/                # File sorgente (.c)
    ├── main.c          # Programma principale
    ├── persona.c       # Implementazione modulo persona
    └── ipv4.c          # Implementazione modulo IPv4
```

## Documentazione del Codice

Tutti i file header sono completamente documentati in **stile Doxygen** con:
- **Descrizione delle strutture**: Scopo e contenuto di ogni struct
- **Documentazione dei campi**: Ogni campo è commentato con `/**< descrizione */`
- **Documentazione delle funzioni**: Include `@brief`, `@param`, `@return`
- **Esempi e dettagli**: Informazioni su range validi, formati supportati, comportamento

### Vantaggi della Documentazione

✅ **Autocomplete intelligente**: Gli IDE mostrano la documentazione mentre scrivi  
✅ **Facile comprensione**: Capire cosa fa una funzione senza leggere l'implementazione  
✅ **Manutenibilità**: Modifiche future più semplici con documentazione chiara  
✅ **Generazione automatica**: Compatibile con Doxygen per generare HTML/PDF  

### Esempio di Utilizzo nell'IDE

Quando scrivi codice, l'IDE mostra automaticamente:
```c
// Scrivendo "assegna_ip(" l'IDE mostra:
/**
 * @brief Assegna un indirizzo IP specificando i 4 ottetti
 * @param ip_address Puntatore alla struttura IpV4_address da modificare
 * @param a Primo ottetto (0-255)
 * ...
 */
```

## Descrizione dei File

### File Header (include/)

#### `config.h`
Contiene **costanti e literals globali** del progetto - configurazioni condivise da tutti i moduli:

**Costanti per stringhe e array:**
- **`MAX_STRG`**: Dimensione massima stringhe (255)
- **`MAX_CAP_LEN`**: Lunghezza CAP (5)
- **`MAX_CIVICO_LEN`**: Lunghezza numero civico (9)

**Costanti IPv4:**
- **`IPV4_OCTETS`**: Numero di ottetti in un IP (4)
- **`IPV4_MIN_VALUE`**, **`IPV4_MAX_VALUE`**: Range valori (0-255)

**Costanti classi IP:**
- **`CLASSE_A_MAX`** (127), **`CLASSE_B_MAX`** (191), **`CLASSE_C_MAX`** (223), **`CLASSE_D_MAX`** (239)

**Costanti IP privati (RFC 1918):**
- **`IP_PRIVATO_10`**, **`IP_PRIVATO_172`**, **`IP_PRIVATO_192_FIRST`**, **`IP_PRIVATO_192_SECOND`**
- **`IP_PRIVATO_172_MIN`** (16), **`IP_PRIVATO_172_MAX`** (31)

**Literals stringa (informazioni istituto):**
- **`ISTITUTO_NOME`**: "Istituto Leonardo Da Vinci Parma"
- **`ISTITUTO_CITTA`**: "Parma"
- **`ISTITUTO_INDIRIZZO`**: "Viale Leonardo Da Vinci"
- **`ISTITUTO_CAP`**: "43100"

**Literals stringa (configurazioni di rete):**
- **`DOMINIO_DEFAULT`**: "example.com"
- **`DNS_GOOGLE_PRIMARY`**: "8.8.8.8"
- **`DNS_GOOGLE_SECONDARY`**: "8.8.4.4"

**Vantaggi**: 
- Valori "magici" sostituiti da costanti con nomi significativi
- Facile modificare configurazioni in un unico punto
- Codice più leggibile e manutenibile
- Informazioni dell'istituto centralizzate e riutilizzabili

#### `persona.h`
**Modulo completo per la gestione dei dati persona** - raggruppa tipi e funzioni correlate:

**Tipi definiti:**
- **`Indirizzo`**: struttura per indirizzi fisici (via, CAP, numero civico)
- **`Persona`**: struttura per dati anagrafici (nome, cognome, indirizzo)

**Funzioni:**
- `assegna_nome()`: Assegna il nome a una persona
- `assegna_cognome()`: Assegna il cognome a una persona

**Vantaggi**: Chi include `persona.h` ha tutto ciò che serve per lavorare con le persone.

#### `ipv4.h`
**Modulo completo per la gestione degli indirizzi IPv4** - raggruppa tipi e funzioni correlate:

**Tipi definiti:**
- **`IpV4`**: typedef per array di 4 unsigned char (indirizzo IPv4)
- **`Mask`**: typedef per array di 4 unsigned char (maschera di rete)
- **`IpV4_address`**: struttura completa per indirizzo IP con maschera, dominio e proprietario

**Variabili globali:**
- **`ip_istituto`**: Istanza globale di `IpV4_address` per l'indirizzo IP dell'istituto
  - Allocata in RAM all'avvio del programma
  - Accessibile da qualsiasi file che include `ipv4.h`
  - Inizializzata tramite `init_ip_istituto()`

**Funzioni:**
- `init_ip_istituto()`: Inizializza la variabile globale `ip_istituto` con i dati dell'istituto
- `assegna_ip()`: Assegna un indirizzo IP
- `assegna_mask()`: Assegna una maschera di rete
- `assegna_dominio()`: Assegna un nome di dominio
- `assegna_ip_da_stringa()`: Parsing di IP da stringa
- `stampa_ip()`: Stampa l'indirizzo IP
- `stampa_mask()`: Stampa la maschera di rete
- `calcola_rete()`: Calcola l'indirizzo di rete (IP AND mask)
- `calcola_broadcast()`: Calcola l'indirizzo di broadcast
- `conta_bit_mask()`: Conta i bit a 1 nella maschera (notazione CIDR)
- `determina_classe()`: Determina la classe dell'IP (A, B, C, D, E)
- `is_ip_privato()`: Verifica se l'IP è privato (RFC 1918)
- `stampa_info_rete()`: Stampa tutte le informazioni sulla rete

**Vantaggi**: Chi include `ipv4.h` ha tutto ciò che serve per lavorare con gli indirizzi IP, inclusa una variabile globale pronta all'uso per l'istituto.

### File Sorgente (src/)

#### `main.c`
Programma principale che dimostra l'utilizzo dei moduli:

**Inizializzazione:**
- Chiama `init_ip_istituto()` per inizializzare la variabile globale
- Mostra le informazioni dell'IP dell'istituto usando `ISTITUTO_NOME` da `config.h`

**5 esempi pratici di configurazioni di rete:**
1. Rete classe C privata (192.168.1.130/25)
2. Rete classe B privata (172.16.50.100/20)
3. Rete classe A privata (10.20.30.40/8)
4. IP pubblico classe A (8.8.8.8/24 - Google DNS)
5. Subnet /30 point-to-point (192.168.100.5/30)

#### `persona.c`
Implementazione delle funzioni per la gestione dei dati persona.

#### `ipv4.c`
Implementazione completa delle funzioni per la gestione degli indirizzi IPv4.

## Concetti Chiave

### Classi di Indirizzi IP
- **Classe A**: 0-127 (primo ottetto) - Reti grandi
- **Classe B**: 128-191 - Reti medie
- **Classe C**: 192-223 - Reti piccole
- **Classe D**: 224-239 - Multicast
- **Classe E**: 240-255 - Riservata/Sperimentale

### Indirizzi IP Privati (RFC 1918)
- **10.0.0.0/8**: 10.0.0.0 - 10.255.255.255
- **172.16.0.0/12**: 172.16.0.0 - 172.31.255.255
- **192.168.0.0/16**: 192.168.0.0 - 192.168.255.255

### Calcoli di Rete
- **Indirizzo di rete**: IP AND maschera
- **Indirizzo di broadcast**: IP OR (NOT maschera)
- **Numero host validi**: (2^bit_host) - 2 (esclusi rete e broadcast)

## Compilazione

### Con Code::Blocks
1. Apri il file `50_reti.cbp`
2. Premi F9 per compilare ed eseguire

### Da Riga di Comando

**Compilazione:**
```bash
gcc -Wall -I include -o 50_reti src/main.c src/persona.c src/ipv4.c
```

**Esecuzione:**

Su Windows (PowerShell):
```powershell
.\50_reti.exe
```

Su Windows (CMD):
```cmd
50_reti.exe
```

Su Linux/Mac:
```bash
./50_reti
```

## Spiegazione File .cbp

Il file `50_reti.cbp` è il file di progetto di Code::Blocks in formato XML:

```xml
<Compiler>
    <Add option="-Wall" />        <!-- Abilita tutti i warning -->
    <Add directory="include" />   <!-- Percorso per i file header -->
</Compiler>
```

### Opzioni del Compilatore
- **`-Wall`**: Abilita tutti i warning del compilatore (buona pratica)
- **`-g`**: Aggiunge informazioni di debug (utile per il debugging)
- **`directory="include"`**: Indica al compilatore dove cercare i file `.h`

### Unità di Compilazione
Ogni file del progetto è elencato come `<Unit>`:
- I file `.h` sono inclusi per la navigazione nell'IDE
- I file `.c` hanno `<Option compilerVar="CC" />` per indicare che vanno compilati

## Principio di Design: Coesione dei Moduli

Questo progetto segue il principio di **alta coesione**: ogni modulo raggruppa **tipi di dati** e **funzioni correlate** nello stesso file header.

### Esempio: Modulo `persona.h`
```c
// Definizione del tipo
typedef struct {
    char nome[MAX_STRG];
    char cognome[MAX_STRG];
    Indirizzo indirizzo;
} Persona;

// Funzioni che operano su quel tipo
void assegna_nome(Persona *persona, char nome[]);
void assegna_cognome(Persona *persona, char cognome[]);
```

### Vantaggi di questa Organizzazione

1. **Coesione**: Tipi e funzioni correlate sono raggruppati insieme
2. **Riusabilità**: Basta includere un header per avere tutto il necessario
3. **Leggibilità**: Chiaro quali funzioni operano su quali tipi
4. **Manutenibilità**: Modifiche a un tipo e alle sue funzioni sono localizzate
5. **Indipendenza**: Ogni modulo è autonomo e può essere riutilizzato
6. **Evita dipendenze circolari**: `config.h` contiene solo costanti globali
7. **No "magic numbers"**: Valori hardcoded sostituiti da costanti con nomi significativi

### Confronto con Approccio Alternativo

❌ **Approccio meno coeso** (tutti i tipi in `types.h`):
- Tipi separati dalle funzioni che li usano
- Difficile capire quali funzioni operano su quali tipi
- Meno riutilizzabile (devi includere più file)

✅ **Approccio adottato** (tipi con le loro funzioni):
- Moduli autoconsistenti
- Include un header = hai tutto ciò che serve
- Facile riutilizzare in altri progetti

## Utilizzo della Variabile Globale `ip_istituto`

Il progetto fornisce una variabile globale `ip_istituto` pronta all'uso per rappresentare l'indirizzo IP dell'istituto.

### Dichiarazione e Definizione

**In `ipv4.h` (dichiarazione):**
```c
extern IpV4_address ip_istituto;
void init_ip_istituto(void);
```

**In `ipv4.c` (definizione):**
```c
IpV4_address ip_istituto;

void init_ip_istituto(void)
{
    assegna_ip(&ip_istituto, 192, 168, 1, 1);
    assegna_mask(&ip_istituto, 255, 255, 255, 0);
    assegna_dominio(&ip_istituto, "itis-davinci.pr.it");
    ip_istituto.proprietario = NULL;
}
```

### Esempio di Utilizzo

```c
#include "ipv4.h"

int main()
{
    // Inizializza la variabile globale
    init_ip_istituto();
    
    // Usa la costante da config.h per il titolo
    printf("\n*** IP ISTITUTO: %s ***\n", ISTITUTO_NOME);
    
    // Accedi direttamente alla variabile globale
    stampa_info_rete(&ip_istituto);
    
    // Puoi anche modificarla se necessario
    assegna_ip(&ip_istituto, 10, 0, 0, 1);
    
    return 0;
}
```

### Caratteristiche

- **Allocazione statica**: La variabile è allocata in RAM all'avvio del programma
- **Visibilità globale**: Accessibile da qualsiasi file che include `ipv4.h`
- **Inizializzazione controllata**: Chiama `init_ip_istituto()` nel `main()` prima dell'uso
- **Modificabile**: Non è `const`, quindi può essere modificata durante l'esecuzione
- **Integrazione con config.h**: Usa le costanti `ISTITUTO_*` per informazioni correlate

## Esercizi Proposti

1. Aggiungere una funzione per verificare se due IP sono nella stessa rete
2. Implementare il calcolo del primo e ultimo host valido
3. Aggiungere supporto per la notazione CIDR (es: "192.168.1.0/24")
4. Creare una funzione per il subnetting (dividere una rete in sottoreti)
5. Implementare la validazione completa degli indirizzi IP

## Note

- Il progetto usa lo standard C99
- Tutti i file header hanno **header guards** per prevenire inclusioni multiple
- Gli include relativi usano `"../include/file.h"` dai file in `src/`
- Gli include tra header nella stessa cartella usano `"file.h"`
