# Technicolor Password Tester #

Prende in input delle password e restituisce solo quelle valide per i router
technicolor

## Esempio ##

Genera delle password con [crunch](http://sourceforge.net/projects/crunch-wordlist/),
e le filtra con questo programma che ne stampa 4 valide

```
richard% ./crunch 10 10 0123456789ABCDEF -s 001011223A | ./tpt-linux-64 4
001011223A
001011223B
001011223C
001011223D
```

## Sintassi ##

```
tpt [quante_password_stampare]
```

## Funzionamento ##

Il programma legge da stdin delle stringhe, e le riscrive su stdout solo quando
sono password valide per i router technicolor. Il programma termina quando legge EOF,
o quando raggiunge il limite di password da stampare.

### Input ###

Le password hanno queste caratteristiche:

 * Lunghezza: 10 caratteri
 * Charset: `0123456789ABCDEF`

Il programma accetta in input stringhe di qualsiasi tipo, ma solo quelle con queste
caratteristiche potrebbero essere password valide.

Le stringhe possono essere inserite da tastiera o generate con altri programmi,
come [crunch](http://sourceforge.net/projects/crunch-wordlist/), per poi
essere passate a questo filtro. Sopra c'è un [esempio](#esempio).

La prima password valida è `001011223A`: se si usa un programma per generare
le password, è possibile usare questa come prima combinazione, perché tutte
le combinazioni precedenti non sono valide.

### Output ###

Vengono scritte su stdout solo le password valide, una per riga.
Se è stato definito DEBUG prima di compilare, su stderr vengono scritte informazioni
per il debug.

## Compilazione ##

Entrare in src, quindi:

* `make generic` per creare un eseguibile generico
* `make native` per creare un eseguibile ottimizzato per la propria cpu
* `make debug` per creare un eseguibile con informazioni per il debug

Gli eseguibili vengono salvati in $(TMP_BIN), che attualmente è la directory bin
nella root di questo repo.
Per cancellare tutti gli eseguibili, usare `make clean`.

## Altre informazioni ##

> This is the Unix philosophy: Write programs that do one thing and do it well.
Write programs to work together. Write programs to handle text streams, because
that is a universal interface.

Aggiornamenti: [GitHub](http://github.com/matteoalessiocarrara/technicolor-password-tester)  
Email: sw.matteoac@gmail.com  
