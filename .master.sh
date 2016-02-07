#!/bin/zsh
# questo script è per eseguire il merge fra un mio branch privato e master

echo "Attenzione! Non ci devono essere file modificati. Seguira un git commit automatico. Continuare? [yn]"
read c

if [[ "$c" -eq "y" ]]
then
	# elimina il file .gitmodules
	rm .gitmodules

	# elimina le librerie gestite da submodules
	rm -r src/lib/lib-technicolor-password-tester

	git commit -am "Eliminato .gitmodules e lib"
	
	# aggiunge le librerie come subtree
	git subtree add --prefix=src/lib/lib-technicolor-password-tester https://github.com/matteoalessiocarrara/lib-technicolor-password-tester v1.3.1 --squash

else
	echo "Annullato"
fi



