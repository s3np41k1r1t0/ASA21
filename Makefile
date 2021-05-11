cc     = g++
dflags = -O3 -Wall -std=c++11 -pg -lm
flags  = -O3 -Wall -std=c++11 -lm

build: src/file.cpp
	$(cc) $(flags) -o bin/file src/file.cpp

debug: src/file.cpp
	$(cc) $(dflags) -o bin/debug src/file.cpp

test: build 	
	bash -c "time ./bin/file < .tests/sanity.in"

sanity_check: build
	./bin/file < .tests/sanity.in > .tests/test.out
	diff .tests/test.out .tests/sanity.out

clean:
	rm -f bin/* .tests/test.out
