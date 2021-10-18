MAK= make --no-print-directory

readme:
	@less README.txt

zip:
	@zip -r resp.zip P1/suma-dec.c || \
		echo "No se encontro P1/suma-dec.c con la pregunta 1"
	@zip -r resp.zip P2/sumar-str.c || \
		echo "No se encontro P2/sumar-str.c con la pregunta 2"
	@zip -r resp.zip P3/prev.c || \
		echo "No se encontro P3/prev.c con la pregunta 3"
	@zip -r resp.zip P4/leeritemes.c || \
		echo "No se encontro P4/leeritemes.c con la pregunta 4"

clean:
	rm -f resp.zip
	@cd P1 ; make clean
	@cd P2 ; make clean
	@cd P3 ; make clean
	@cd P4 ; make clean
