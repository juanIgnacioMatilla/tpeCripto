lado.bmp se usa como portador en todos los casos
Todos tienen oculta una imagen .png
ladoLSB1.bmp
	con m�todo LSB1 (sin encripci�n)
ladoLSB4.bmp
	con m�todo LSB4 (sin encripci�n)
ladoLSBI.bmp
	con LSBI (sin encripci�n)

ladoLSBIaes256ofb.bmp
	con m�todo LSBI, encriptado previamente con aes256, modo ofb, 
	password "margarita" (derivando key e iv con el algoritmo bytesToKey, usando sha256, sin salt, 1 iteracion)
	
	key=F1BE6354B41828A0B8AA1201094A15CC00ADD2A52D5BDE5B582A1576FDFDFBD4
	iv =66ED36D9005C1D4F5A1C4055E7B14283

ladoLSBIdescfbPBKDF2.bmp
	con m�todo LSBI, encriptado previamente con des ede3 (triple des de tres claves), modo cfb8, 
	password "margarita" (derivando key e iv con PBKDF2 sin salt sha256 y 10000 iteraciones)
	Es decir, queda:
	key=B61160623AD4D2A58E2674FD701D6761BF289DBF5C15F2CF
	iv =65334532CB844902
	
	