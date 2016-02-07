#!/bin/zsh
# questo script è per eseguire il merge fra un mio branch privato e master

echo "Attenzione! Non ci devono essere file modificati. Seguira un git commit automatico. Continuare? [yn]"
read c

if [[ "$c" -eq "y" ]]
then
	# elimina il file .gitmodules
	rm .gitmodules

	# elimina le librerie gestite da submodules
	rm -r src/lib/readability

	git commit -am "Eliminato .gitmodules e lib"
	
	# aggiunge le librerie come subtree
	git subtree add --prefix=src/lib/readability https://github.com/matteoalessiocarrara/readability v1.0.0 --squash

else
	echo "Annullato"
fi



