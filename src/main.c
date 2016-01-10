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
# include <string.h>
# include <stdbool.h>

# include "header.h"
# include "filter.c"
# include "debug.h"

/* TODO Aggiungere un limite per le password da analizzare */

/* Controlla se alla fine della stringa c'è \n */
# define line_is_truncated(str, len) (str[(len) - 1] == '\n'? false : true)

int main()
{
	/* Contiene: password + '\n' + '\0' */
    char line[PASS_LEN + 1 + 1];
	bool ignore_until_newline = false;

	/* Legge password da stdin fino a quando non riceve EOF */
    while (fgets(line, PASS_LEN + 2, stdin) != NULL)
    {
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
				}
				else
				{
					/* Altrimenti, è una line valida */

					printd("è una linea valida\n");

					if (is_valid_pass(line))
					{
						printd("è una password valida\n");
						printf("%s", line);
					}
					else
						printd("non è una password valida\n");
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
		}
	}

	printd("EOF\n");
    return 0;
}
