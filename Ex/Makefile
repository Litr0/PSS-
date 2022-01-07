MAK= make --no-print-directory

readme:
	@less README.txt

zip:
	@zip -r resp.zip P1/corregir.c || \
		echo "No se encontro P1/corregir.c con la pregunta 1"
	@zip -r resp.zip P2/dividir.c || \
		echo "No se encontro P2/dividir.c con la pregunta 2"
	@zip -r resp.zip P3/incognito.c || \
		echo "No se encontro P3/incognito.c con la pregunta 3"
	@zip -r resp.zip P4/volumen.c || \
		echo "No se encontro P4/volumen.c con la pregunta 4"
	@echo "Estas son las respuestas encontradas:"
	@unzip -l resp.zip
	@echo "\n *** Entregue por u-cursos el archivo resp.zip ***\n"
	@echo "Luego descargue de u-cursos el mismo archivo, descomprimalo"
	@echo "y revise que las respuestas son lo que Ud. escribio."
	@echo "Si no lo son, vuelva a entregar."
	@echo "Si Ud. no alcanza a subir sus respuestas antes del plazo,"
	@echo "envieme sus respuestas por correo, pero sera penalizado"
	@echo "si no hay una buena justificacion."

clean:
	rm -f resp.zip
	@cd P1 ; make clean
	@cd P2 ; make clean
	@cd P3 ; make clean
	@cd P4 ; make clean
