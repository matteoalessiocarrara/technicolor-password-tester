# Technicolor Password Tester #

Controlla se una stringa è una password valida per router technicolor. Libreria in c.

## Sinossi ##

```c
# include "src/filter.c"

extern inline bool is_valid_pass(char * pass);
```

## Descrizione ##

La funzione is_valid_pass() controlla se la stringa pass è una password valida
per i router technicolor.

La stringa pass *dovrebbe* essere lunga 10 caratteri, con charset 0-9 A-F. 
Questo è il formato delle password valide. Se così non fosse, semplicemente sarà
sicuramente non valida.


## Return ##

La funzione restituisce true o false (stdbool.h)


## Esempio ##

Ho scritto un interfaccia basata su questa libreria, è disponibile 
[qui](https://github.com/matteoalessiocarrara/technicolor-password-tester)


## Altre informazioni ##

> This is the Unix philosophy: Write programs that do one thing and do it well.
Write programs to work together. Write programs to handle text streams, because
that is a universal interface.

Aggiornamenti: [GitHub](http://github.com/matteoalessiocarrara/lib-technicolor-password-tester)  
Email: sw.matteoac@gmail.com  
