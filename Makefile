build:
	gcc -Wall main.c liste.h cozistive.h arbori.h -o lanParty 

clean: 
	rm -f lanParty
