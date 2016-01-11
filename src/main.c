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

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# include "header.h"
# include "filter.c"
# include "debug.h"

/* Controlla se alla fine della stringa c'è \n */
# define line_is_truncated(str, len) (str[(len) - 1] != '\n')

/* Controlla se è stato scelto un limite per le password da controllare
 * Se var è maggiore di 0, allora si, altrimenti no
 */
# define is_set_pass_limit(var) (var > 0)

long max_pass = -1;

void help()
{
	/* FIXME Stringhe troppo lunghe, è brutto */

	printf(SW_DESC "\n\n");
	printf("Uso: tpt [quante_password_stampare]\n\n");
	printf("Report bugs to: <" BUG_EMAIL ">\n");
	printf(SW_NAME " home page: <" HOME_PAGE_URL ">\n");

	exit(0);
}

static inline bool is_valid_line(char * line)
{
	static bool ignore_until_newline = false;

	printd("letto \"%s\"\n", line);

	/* strlen considera anche \n, mentre PASS_LEN no */
	if (strlen(line) == (PASS_LEN + 1))
	{
		/* La riga è della lunghezza giusta */

		if (line_is_truncated(line, PASS_LEN + 1))
		{
			/* La riga non finisce con \n */
			printd("letta linea troncata\n");

			/* Significa che la password inserita è troppo lunga
			 * Questa riga contiene una password non valida, quindi ignoriamo
			 * tutto fino al newline
			 */
			 ignore_until_newline = true;
			 return false;
		}
		else
		{
			/* La riga finisce con \n */
			printd("ultimo carattere \\n\n");

			/* Se è la parte finale di una riga non valida, la ignoriamo */
			if (ignore_until_newline)
			{
				printd("ignorata, era la fine di una riga non valida\n");
				ignore_until_newline = false;
				return false;
			}
			else
			{
				/* Altrimenti, è una line valida */
				printd("è una linea valida\n");
				return true;
			}
		}
	}
	else
	{
		/* Qui sarebbe stata ignorata comunque, perché è troppo corta, ma va
		 * modificata la variabile */
		if (ignore_until_newline)
		{
			printd("trovata fine di una riga troncata (non valida)\n");
			ignore_until_newline = false;
		}

		printd("linea non valida, troppo corta\n");
		return false;
	}
}

/* Stampa la linea se è una password valida
 * Restituisce true se è una password valida, false altrimenti
 */
static inline bool print_valid_pass(char * line)
{
	if (is_valid_line(line))
	{
		/* ATTENZIONE; gli va passata solo quando si sa che è una linea valida */
		if (is_valid_pass(line))
		{
			printd("è una password valida\n");
			printf("%s", line);
			return true;
		}
		else
			printd("non è una password valida\n");
			return false;
	}
	else
		return false;
}

int main(int argc, char ** argv)
{
	/* Dovrebbe contenere: password + '\n' + '\0' */
	char line[PASS_LEN + 1 + 1];
	long npass = 0;

	if (argc > 1)
	{
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
			help();
		else
			max_pass = atol(argv[1]);
			printd("max_pass = atol(argv[1]) = %ld\n", atol(argv[1]));
	}

	printd("is_set_pass_limit(max_pass) = %d\n", is_set_pass_limit(max_pass));

	if (is_set_pass_limit(max_pass))
	{
		while ((npass < max_pass) && (fgets(line, PASS_LEN + 2, stdin) != NULL))
			if(print_valid_pass(line))
				npass++;

		printd("EOF o limite di password raggiunto\n");
	}
	else
	{
		while (fgets(line, PASS_LEN + 2, stdin) != NULL)
			print_valid_pass(line);

		printd("EOF\n");
	}

	return 0;
}
