cc     = g++
dflags = -O3 -Wall -std=c++11 -pg -lm
flags  = -O3 -Wall -std=c++11 -lm

params = 10000 1000 

generate: src/gen2procs.cpp
	$(cc) $(flags) -o bin/gen2procs src/gen2procs.cpp
	./bin/gen2procs $(params) > bin/problem

build: src/file.cpp
	$(cc) $(flags) -o bin/file src/file.cpp

debug: src/file.cpp
	$(cc) $(dflags) -o bin/debug src/file.cpp

test: build generate
	bash -c "time ./bin/file < bin/problem"

sanity_check: build
	./bin/file < .tests/sanity.in
	#./bin/file < .tests/sanity.in > .tests/test.out
	#diff .tests/test.out .tests/sanity.out

clean:
	rm -f bin/* .tests/test.out
