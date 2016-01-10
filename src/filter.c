/*
 * Copyright 2016 Matteo Alessio Carrara <sw.matteoac@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

# include <stdbool.h>

# include "header.h"
# include "debug.h"

/* Controlla se il carattere è A, B, C, D, E o F */
# define is_af(ch) (((ch) >= 'A') && ((ch) <= 'F'))

<<<<<<< HEAD
=======
/* Controlla se il carattere è un numero in ASCII */
# define is_09(ch) (((ch) >= '0') && ((ch) <= '9'))

/* Converte un carattere ASCII esadecimale in un numero (-1 in caso di errore) */
# define dec(hex) (is_09(hex)? hex - '0' : is_af(hex)? hex - 'A' + 10 : -1)

>>>>>>> stable
/* Funzioni prese da https://github.com/emanueleforestieri/technicolor_bruteforce
 * Grazie a Emanuele Forestieri <forestieriemanuele@gmail.com>
 */

/* There can be no more than two consecutive identical characters
 * Restituisce true se la password è corretta, false altrimenti
 */
static inline bool test0(char * pass)
{

	/* (PASS_LEN - 2): il codice sotto da sempre per scontato che dopo il
	 * carattere attuale (i) ce ne siano altri due (i + 1, i + 2), quindi scorriamo
	 * la stringa dall'inizio alla fine - 2, in questo modo i + 2 sarà l'ultimo
	 * carattere della stringa (e non oltre la fine della stringa!!)
	 */

	for (short i = 0; i < (PASS_LEN - 2); i++)
	{
		if (pass[i] == pass[i + 1])
		{
			if (pass[i + 1] == pass[i + 2])
				return false;
			else
				/* per evitare che l'if esterno ricontrolli inutilmente i due
				 * caratteri già controllati da questo if */
				i++;
		}
	}

	return true;
}


/* There can be no more than 5 characters A-F and 9 numbers
 * Restituisce true se la password è corretta, false altrimenti
 */
static inline bool test1(char * pass)
{
	short af = 0, numbers = 0;

	for (short i = 0; i < PASS_LEN; i++)
		is_af(pass[i])? af++ : numbers++;

	return ((af > 5) || (numbers > 9))? false : true;
}


/* There can be no more than three identical characters
 * Restituisce true se la password è corretta, false altrimenti
 */
static inline bool test2(char * pass)
{
<<<<<<< HEAD
	char test_ch;
	short times;

	/* TODO Migliorare algoritmo
	 * Ogni carattere può essere tradotto in dec 0 - 15
	 * Si può tenere un array di 16 elementi dove ogni variabile rappresenta
	 * un carattere
	 */

	for (short i = 0; i < PASS_LEN; i++)
	{
		test_ch = pass[i];
		times = 0;

		/* Conta quante volte test_ch è nella stringa */
		for (short i = 0; i < PASS_LEN; i++)
			if (pass[i] == test_ch)
				if (++times > 3)
					return false;
	}
=======
	/* Ogni elemento di questo array rappresenta un carattere del charset
	 * L'indice si ottiene semplicemente traducendo il carattere da esadecimale
	 * a decimale
	 * Per es, l'indice per "F" sarà 15, mentre per "A" 10
	 */
	short times[16];

	/* Azzeriamo ogni elemento dell'array times*/
	for (short i = 0; i < 16; i ++)
		times[i] = 0;

	/* Contiamo quante volte ogni carattere è nella password */
	for (short i = 0; i < PASS_LEN; i++)
		{
			times[dec(pass[i])] += 1;

			if (times[dec(pass[i])] > 3)
				return false;
		}
>>>>>>> stable

	return true;
}


extern inline bool is_valid_pass(char * pass)
{

	/* Test ordinati per velocità (i nomi sono a caso, non indicano la velocità)
	 * Meglio fare prima i test più veloci per vedere se non è valida, così non
	 * si perde tempo inutilmente
	 */

<<<<<<< HEAD
=======
	/* FIXME Prima di fare i test dobbiamo assicurarci che sia composta da caratteri
	 * validi, perché le altre funzioni danno per scontato che lo sia e se così
	 * non fosse potrebbero crearsi problemi
	 */
>>>>>>> stable
	if (test0(pass) == false)
		return false;
	else if (test1(pass) == false)
		return false;
	else if (test2(pass) == false)
		return false;
	else
		/* Tutti i test superati, password valida :) */
		return true;
}
