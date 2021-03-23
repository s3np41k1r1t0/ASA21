cc     = g++
dflags = -O3 -Wall -std=c++11 -g -lm
flags  = -O3 -Wall -std=c++11 -lm

params = 3 1

randomDAG: randomDAG.cpp
	$(cc) $(flags) -o randomDAG randomDAG.cpp
	./randomDAG $(params) > problem

build: randomDAG file.cpp
	cat problem
	$(cc) $(flags) file.cpp

run: build
	./a.out < problem

debug: file.cpp
	$(cc) $(debug_flags) -o debug file.cpp

clean:
	rm -f problem a.out debug
