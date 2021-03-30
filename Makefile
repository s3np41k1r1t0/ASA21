cc     = g++
dflags = -O3 -Wall -std=c++11 -g -lm
flags  = -O3 -Wall -std=c++11 -lm

params = 9 "0.6"

randomDAG: src/randomDAG.cpp
	$(cc) $(flags) -o bin/randomDAG src/randomDAG.cpp
	./bin/randomDAG $(params) > bin/problem


build: randomDAG src/macarrao.cpp
	#$(cc) $(flags) -o bin/file src/macarrao.cpp
	$(cc) $(flags) -o bin/file src/file.cpp

run: build
	bash -c "time ./bin/file < bin/problem"

debug: src/file.cpp
	$(cc) $(debug_flags) -o bin/debug src/file.cpp

sanity_check: run
	./bin/file < .tests/sanity.in

clean:
	rm -f bin/*
