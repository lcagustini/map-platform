linux: create_bin
	make -f Makefile.linux

check:
	cppcheck --enable=all --force src/

create_bin:
	mkdir -p bin

clean:
	rm -rf bin
