all:client.bin server.bin

client.bin:
	@echo "Compilation de client.bin"
	cd src/client && qmake && make
	

server.bin:
	@echo "Compilation de server.bin"
	cd src/server && qmake && make

clean:
	@echo "Nettoyage du repertoire client"
ifeq ($(wildcard src/client/Makefile),)
	@echo "Rien à nettoyer"
else
	@cd src/client && make clean
endif
	@echo "Nettoyage du serveur"
ifeq ($(wildcard src/server/Makefile),)
	@echo "Rien à nettoyer"
else
	@cd src/server && make clean
endif

delete: clean
	@echo "Suppression des fichier"
ifeq ($(wildcard src/*/*.bin),)
	@echo "Rien à supprimer"
else
	rm src/*/*.bin src/*/Makefile
endif
