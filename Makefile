check:
	cppcheck --enable=all --force src/

linux: create_bin
	make -f Makefile.linux

psp: create_bin
	make -f Makefile.psp
	rm src/*.o
	mv EBOOT.PBP bin
	mv PARAM.SFO bin

create_bin:
	mkdir -p bin

clean:
	rm -rf bin
