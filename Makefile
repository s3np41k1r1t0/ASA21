cc     = g++
dflags = -O3 -Wall -std=c++11 -g -lm
flags  = -O3 -Wall -std=c++11 -lm

params = 10 1

randomDAG: src/randomDAG.cpp
	$(cc) $(flags) -o bin/randomDAG src/randomDAG.cpp
	./bin/randomDAG $(params) > bin/problem

build: randomDAG src/file.cpp
	cat bin/problem
	$(cc) $(flags) -o bin/file src/file.cpp

run: build
	time ./bin/file < bin/problem

debug: src/file.cpp
	$(cc) $(debug_flags) -o bin/debug src/file.cpp

sanity_check: run
	./bin/file < .tests/sanity.in > bin/out
	diff bin/out .tests/sanity.out

clean:
	rm -f bin/*
