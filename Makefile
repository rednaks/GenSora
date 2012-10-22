all:client.bin server.bin

client.bin:
	@echo "Compilation de client.bin"
	cd src/client && qmake && make
	

server.bin:
	@echo "Compilation de server.bin"
	cd src/server && qmake && make

clean:
	@echo "Nettoyage du repertoire client"
	@cd src/client && make clean
	@cd src/server && make clean

delete: clean
	@echo "Suppression des fichier"
	rm src/*/*.bin src/*/Makefile
