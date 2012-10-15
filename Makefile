all:client.bin server.bin

client.bin:
	@echo "Compilation de client.bin"
	cd src/client && qmake && make
	

server.bin:
	@echo "Not yet implemented"

clean:
	@echo "Nettoyage du repertoire client"
	@cd src/client && make clean
