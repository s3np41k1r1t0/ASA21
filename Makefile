cc     = g++
dflags = -O3 -Wall -std=c++11 -g -lm
flags  = -O3 -Wall -std=c++11 -lm

params = 4 1

randomDAG: src/randomDAG.cpp
	$(cc) $(flags) -o bin/randomDAG src/randomDAG.cpp
	./bin/randomDAG $(params) > bin/problem

build: randomDAG src/file.cpp
	cat bin/problem
	$(cc) $(flags) -o bin/file src/file.cpp

run: build
	./bin/file < bin/problem

debug: src/file.cpp
	$(cc) $(debug_flags) -o bin/debug src/file.cpp

clean:
	rm -f bin/*
