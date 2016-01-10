OPTIMIZE = -O3 -fomit-frame-pointer -flto
TMP_BIN = ../bin/
LFLAGS = -lm
CC = c99

generic:
	$(CC) main.c -o $(TMP_BIN)tpt-generic $(LFLAGS) $(OPTIMIZE) -pipe

native:
	$(CC) main.c -o $(TMP_BIN)tpt-native $(LFLAGS) $(OPTIMIZE) -pipe -march=native

debug:
	$(CC) main.c -o $(TMP_BIN)tpt-debug $(LFLAGS) -Og -g -Wall -Wextra -DDEBUG -pipe

clean:
	rm -f $(TMP_BIN)*

# Questo lo uso per creare gli eseguibili quando pubblico una nuova versione
# Probabilmente crea eseguibili per linux solo quando si compila da linux

new: linux-64 linux-32

linux-64:
	$(CC) main.c -o $(TMP_BIN)tpt-linux-64 $(LFLAGS) $(OPTIMIZE) -pipe

linux-32:
	$(CC) main.c -o $(TMP_BIN)tpt-linux-32 $(LFLAGS) $(OPTIMIZE) -pipe -m32
