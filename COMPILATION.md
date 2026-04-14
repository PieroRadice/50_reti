# Le Fasi della Compilazione in C

Questo documento spiega le fasi della compilazione di un programma C, usando il progetto **50_reti** come esempio pratico.

## Panoramica del Processo

La compilazione di un programma C passa attraverso **4 fasi principali**:

```
Codice Sorgente (.c, .h)
         ↓
    [1. PREPROCESSORE]
         ↓
Codice Preprocessato (.i)
         ↓
    [2. COMPILATORE]
         ↓
Assembly (.s)
         ↓
    [3. ASSEMBLATORE]
         ↓
Codice Oggetto (.o)
         ↓
    [4. LINKER]
         ↓
Eseguibile (.exe)
```

---

## Fase 1: Preprocessore

### Cosa Fa

Il preprocessore elabora tutte le **direttive** che iniziano con `#`:
- `#include`: Include il contenuto di altri file
- `#define`: Sostituisce macro e costanti
- `#ifndef`, `#ifdef`, `#endif`: Compilazione condizionale

### Esempio dal Progetto 50_reti

**File originale** `src/main.c`:
```c
#include <stdio.h>
#include "../include/persona.h"
#include "../include/ipv4.h"

int main()
{
    init_ip_istituto();
    printf("\n*** IP ISTITUTO: %s ***\n", ISTITUTO_NOME);
    // ...
}
```

**Dopo il preprocessore**:
```c
// Contenuto di stdio.h (migliaia di righe)
// ...

// Contenuto di config.h
#define MAX_STRG 255
#define ISTITUTO_NOME "Istituto Leonardo Da Vinci Parma"
// ...

// Contenuto di persona.h
typedef struct { /* ... */ } Persona;
// ...

// Contenuto di ipv4.h
typedef unsigned char IpV4[4];
extern IpV4_address ip_istituto;
// ...

int main()
{
    init_ip_istituto();
    printf("\n*** IP ISTITUTO: %s ***\n", "Istituto Leonardo Da Vinci Parma");
    // ...
}
```

### Operazioni Chiave

1. **Inclusione dei file header**: `#include "../include/ipv4.h"` → tutto il contenuto di `ipv4.h` viene copiato
2. **Sostituzione delle macro**: `ISTITUTO_NOME` → `"Istituto Leonardo Da Vinci Parma"`
3. **Sostituzione delle costanti**: `MAX_STRG` → `255`
4. **Guard di inclusione**: `#ifndef CONFIG_H` previene inclusioni multiple

### Comando per Vedere l'Output

```bash
gcc -E -I include src/main.c -o main.i
```

- `-E`: Ferma dopo il preprocessore
- `-I include`: Specifica dove cercare i file header
- `-o main.i`: Salva l'output in `main.i`

### Esempio Pratico: config.h

**Prima del preprocessore**:
```c
#define CLASSE_A_MAX 127

if (primo_ottetto <= CLASSE_A_MAX)
    return 'A';
```

**Dopo il preprocessore**:
```c
if (primo_ottetto <= 127)
    return 'A';
```

---

## Fase 2: Compilatore

### Cosa Fa

Il compilatore traduce il codice C preprocessato in **linguaggio assembly** specifico per l'architettura del processore (x86, ARM, ecc.).

### Processo

1. **Analisi lessicale**: Identifica token (parole chiave, identificatori, operatori)
2. **Analisi sintattica**: Verifica la correttezza grammaticale
3. **Analisi semantica**: Controlla i tipi, le dichiarazioni, ecc.
4. **Ottimizzazione**: Migliora il codice per velocità/dimensione
5. **Generazione assembly**: Produce codice assembly

### Esempio dal Progetto 50_reti

**Codice C** da `src/ipv4.c`:
```c
void assegna_ip(IpV4_address *ip_address, unsigned char a, unsigned char b, unsigned char c, unsigned char d)
{
    ip_address->ip[0] = a;
    ip_address->ip[1] = b;
    ip_address->ip[2] = c;
    ip_address->ip[3] = d;
}
```

**Assembly generato** (x86-64, semplificato):
```asm
assegna_ip:
    movb    %sil, (%rdi)        # ip_address->ip[0] = a
    movb    %dl, 1(%rdi)        # ip_address->ip[1] = b
    movb    %cl, 2(%rdi)        # ip_address->ip[2] = c
    movb    %r8b, 3(%rdi)       # ip_address->ip[3] = d
    ret
```

### Controlli del Compilatore

Il compilatore verifica:
- **Tipi**: `assegna_ip(&ip_address, 192, 168, 1, 1)` → parametri corretti?
- **Dichiarazioni**: `ip_istituto` è dichiarato con `extern` in `ipv4.h`?
- **Sintassi**: Parentesi bilanciate, punto e virgola, ecc.

### Comando per Vedere l'Assembly

```bash
gcc -S -I include src/ipv4.c -o ipv4.s
```

- `-S`: Ferma dopo la compilazione (genera assembly)
- `-o ipv4.s`: Salva l'assembly in `ipv4.s`

---

## Fase 3: Assemblatore

### Cosa Fa

L'assemblatore converte il codice assembly in **codice oggetto** (binario), ma non ancora eseguibile.

### Caratteristiche del Codice Oggetto

- **Formato binario**: Non leggibile dall'uomo
- **Simboli non risolti**: Riferimenti a funzioni/variabili esterne
- **Rilocabile**: Può essere combinato con altri file oggetto

### Esempio dal Progetto 50_reti

**File oggetto generati**:
- `main.o`: Contiene la funzione `main()`, ma ha riferimenti non risolti a:
  - `init_ip_istituto()` (definita in `ipv4.o`)
  - `printf()` (nella libreria standard C)
  - `ip_istituto` (definita in `ipv4.o`)
  
- `ipv4.o`: Contiene:
  - Definizione di `init_ip_istituto()`
  - Definizione di `ip_istituto`
  - Definizione di tutte le funzioni IPv4
  - Riferimenti non risolti a `printf()`, `strcpy()`, ecc.

- `persona.o`: Contiene:
  - Definizione di `assegna_nome()`
  - Definizione di `assegna_cognome()`
  - Riferimenti non risolti a `strcpy()`

### Tabella dei Simboli

Ogni file `.o` contiene una **tabella dei simboli**:

**main.o**:
```
SIMBOLI DEFINITI:
  - main (funzione)

SIMBOLI NON RISOLTI (extern):
  - init_ip_istituto
  - ip_istituto
  - printf
  - stampa_info_rete
  - assegna_ip
  - assegna_mask
  - assegna_dominio
```

**ipv4.o**:
```
SIMBOLI DEFINITI:
  - ip_istituto (variabile globale)
  - init_ip_istituto (funzione)
  - assegna_ip (funzione)
  - assegna_mask (funzione)
  - stampa_info_rete (funzione)
  - calcola_rete (funzione)
  - calcola_broadcast (funzione)
  - determina_classe (funzione)
  - is_ip_privato (funzione)
  - ... (altre funzioni)

SIMBOLI NON RISOLTI:
  - printf
  - strcpy
```

### Comando per Generare File Oggetto

```bash
gcc -c -I include src/main.c -o main.o
gcc -c -I include src/ipv4.c -o ipv4.o
gcc -c -I include src/persona.c -o persona.o
```

- `-c`: Compila senza linkare (genera `.o`)

### Visualizzare i Simboli

```bash
nm main.o
```

Output esempio:
```
U init_ip_istituto        # U = Undefined (non risolto)
U ip_istituto
0000000000000000 T main   # T = Text section (codice)
U printf
U stampa_info_rete
```

---

## Fase 4: Linker (Collegamento)

### Cosa Fa

Il linker **collega** tutti i file oggetto e le librerie per creare l'eseguibile finale:

1. **Risolve i simboli**: Collega le chiamate a funzioni con le loro definizioni
2. **Combina le sezioni**: Unisce codice, dati, ecc. da tutti i file `.o`
3. **Assegna indirizzi**: Determina dove in memoria andrà ogni funzione/variabile
4. **Aggiunge librerie**: Include codice dalla libreria standard C

### Processo di Linking per 50_reti

```
main.o + ipv4.o + persona.o + libc.a → 50_reti.exe
```

**Risoluzione dei simboli**:

1. `main.o` chiama `init_ip_istituto()` → trovata in `ipv4.o` ✓
2. `main.o` usa `ip_istituto` → trovata in `ipv4.o` ✓
3. `main.o` chiama `printf()` → trovata in `libc.a` (libreria C standard) ✓
4. `ipv4.o` chiama `strcpy()` → trovata in `libc.a` ✓
5. `persona.o` chiama `strcpy()` → trovata in `libc.a` ✓

### Esempio Pratico: Variabile Globale

**In ipv4.h** (dichiarazione):
```c
extern IpV4_address ip_istituto;  // "Questa variabile esiste da qualche parte"
```

**In ipv4.c** (definizione):
```c
IpV4_address ip_istituto;  // Allocazione effettiva della memoria
```

**In main.c** (utilizzo):
```c
#include "ipv4.h"
int main() {
    init_ip_istituto();
    stampa_info_rete(&ip_istituto);  // Usa la variabile globale
}
```

**Cosa fa il linker**:
1. Vede che `main.o` usa `ip_istituto` (simbolo esterno)
2. Cerca in tutti i file `.o` chi definisce `ip_istituto`
3. Trova la definizione in `ipv4.o`
4. Collega il riferimento in `main.o` alla definizione in `ipv4.o`
5. Assegna un indirizzo di memoria fisso a `ip_istituto`

### Errori Comuni di Linking

**Simbolo non definito**:
```
undefined reference to `init_ip_istituto'
```
→ Hai dimenticato di linkare `ipv4.o`

**Definizione multipla**:
```
multiple definition of `ip_istituto'
```
→ Hai definito `ip_istituto` in più di un file `.c` (invece di usare `extern`)

### Comando Completo di Linking

```bash
gcc -o 50_reti main.o ipv4.o persona.o
```

O tutto in un comando:
```bash
gcc -Wall -I include -o 50_reti src/main.c src/persona.c src/ipv4.c
```

Questo comando esegue tutte e 4 le fasi automaticamente!

---

## Riepilogo: Compilazione Completa del Progetto 50_reti

### Passo per Passo

```bash
# 1. PREPROCESSORE (per ogni file .c)
gcc -E -I include src/main.c -o main.i
gcc -E -I include src/ipv4.c -o ipv4.i
gcc -E -I include src/persona.c -o persona.i

# 2. COMPILATORE (da .i a .s)
gcc -S main.i -o main.s
gcc -S ipv4.i -o ipv4.s
gcc -S persona.i -o persona.s

# 3. ASSEMBLATORE (da .s a .o)
gcc -c main.s -o main.o
gcc -c ipv4.s -o ipv4.o
gcc -c persona.s -o persona.o

# 4. LINKER (da .o a .exe)
gcc -o 50_reti.exe main.o ipv4.o persona.o
```

### Comando Semplificato (Tutto Insieme)

```bash
gcc -Wall -I include -o 50_reti src/main.c src/persona.c src/ipv4.c
```

GCC esegue automaticamente tutte le 4 fasi e cancella i file intermedi.

---

## Visualizzare le Fasi con Flag Verbose

```bash
gcc -Wall -I include -v -o 50_reti src/main.c src/persona.c src/ipv4.c
```

Il flag `-v` mostra tutti i comandi interni eseguiti da GCC.

---

## Diagramma Completo per 50_reti

```
src/main.c ──┐
             ├─→ [PREPROCESSORE] ─→ main.i ─→ [COMPILATORE] ─→ main.s ─→ [ASSEMBLATORE] ─→ main.o ──┐
include/*.h ─┘                                                                                          │
                                                                                                        │
src/ipv4.c ──┐                                                                                          │
             ├─→ [PREPROCESSORE] ─→ ipv4.i ─→ [COMPILATORE] ─→ ipv4.s ─→ [ASSEMBLATORE] ─→ ipv4.o ────┼─→ [LINKER] ─→ 50_reti.exe
include/*.h ─┘                                                                                          │
                                                                                                        │
src/persona.c ┐                                                                                         │
              ├→ [PREPROCESSORE] ─→ persona.i ─→ [COMPILATORE] ─→ persona.s ─→ [ASSEMBLATORE] ─→ persona.o ┘
include/*.h ──┘                                                                                         │
                                                                                                        │
libc.a (libreria C standard) ──────────────────────────────────────────────────────────────────────────┘
```

---

## Concetti Chiave

### 1. Compilazione Separata

Ogni file `.c` viene compilato **indipendentemente**:
- `main.c` → `main.o`
- `ipv4.c` → `ipv4.o`
- `persona.c` → `persona.o`

**Vantaggio**: Se modifichi solo `main.c`, devi ricompilare solo `main.o`, non tutto il progetto!

### 2. File Header (.h)

I file `.h` **non vengono compilati direttamente**. Vengono:
- Inclusi nei file `.c` tramite `#include`
- Processati dal preprocessore
- Il loro contenuto viene copiato nei file `.c`

### 3. extern vs Definizione

**Dichiarazione** (`extern` in `.h`):
```c
extern IpV4_address ip_istituto;  // "Promessa" che esiste
```

**Definizione** (in `.c`):
```c
IpV4_address ip_istituto;  // Creazione effettiva
```

Il linker collega le dichiarazioni `extern` alla definizione unica.

### 4. Guard di Inclusione

```c
#ifndef CONFIG_H
#define CONFIG_H
// ... contenuto ...
#endif
```

Previene l'inclusione multipla dello stesso header, che causerebbe errori di ridefinizione.

---

## Esercizio Pratico

Prova a eseguire ogni fase manualmente:

```bash
# Fase 1: Preprocessore
gcc -E -I include src/main.c > main_preprocessed.txt
# Apri main_preprocessed.txt e cerca ISTITUTO_NOME

# Fase 2: Compilatore
gcc -S -I include src/ipv4.c
# Apri ipv4.s e cerca la funzione assegna_ip

# Fase 3: Assemblatore
gcc -c -I include src/ipv4.c
nm ipv4.o  # Visualizza i simboli

# Fase 4: Linker
gcc -o 50_reti src/main.c src/persona.c src/ipv4.c -I include
./50_reti.exe  # Esegui!
```

---

## Conclusione

La compilazione è un processo in **4 fasi** che trasforma il codice sorgente leggibile dall'uomo in un eseguibile binario:

1. **Preprocessore**: Espande macro e include file
2. **Compilatore**: Traduce C in assembly
3. **Assemblatore**: Converte assembly in codice oggetto
4. **Linker**: Collega tutto insieme creando l'eseguibile

Comprendere queste fasi aiuta a:
- Capire gli errori di compilazione
- Ottimizzare i tempi di build
- Organizzare meglio i progetti
- Debuggare problemi di linking
