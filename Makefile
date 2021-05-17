cc     = g++
dflags = -O3 -Wall -std=c++11 -pg -lm
flags  = -O3 -Wall -std=c++11 -lm

<<<<<<< HEAD
=======
params = 10000 1000 

generate: src/gen2procs.cpp
	$(cc) $(flags) -o bin/gen2procs src/gen2procs.cpp
	./bin/gen2procs $(params) > bin/problem

>>>>>>> 82ed1b6 (wrong attempt)
build: src/file.cpp
	$(cc) $(flags) -o bin/file src/file.cpp

debug: src/file.cpp
	$(cc) $(dflags) -o bin/debug src/file.cpp

<<<<<<< HEAD
test: build 	
	bash -c "time ./bin/file < .tests/sanity.in"
=======
test: build generate
	bash -c "time ./bin/file < bin/problem"
>>>>>>> 82ed1b6 (wrong attempt)

sanity_check: build
	./bin/file < .tests/sanity.in > .tests/test.out
	diff .tests/test.out .tests/sanity.out

clean:
	rm -f bin/* .tests/test.out
