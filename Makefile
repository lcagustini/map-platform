check:
	cppcheck --enable=all --force src/

linux:
	make -f Makefile.linux

psp:
	make -f Makefile.psp
	rm src/*.o
	mv EBOOT.PBP bin
	mv PARAM.SFO bin
