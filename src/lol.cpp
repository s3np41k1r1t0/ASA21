#include <iostream>
#include <list>

using namespace std;

int _V;
unsigned int _prob;

void printUsage() {
	cout << "Usage: randomDAG #V #p seed" << endl;
	cout << "\t#V: number of vertices" << endl;
	cout << "\t#p: prob \\in [0,100] to create edge (u,v)" << endl;
	cout << "\tseed: random seed number (optional)" << endl;
	exit(0);
}

void parseArgs(int argc, char **argv) {
	int seed = 0;

	if (argc < 3) printUsage();

	sscanf(argv[1], "%d", &_V);
	if (_V < 1) {
		cout << "ERROR: # vertices must be > 1" << endl;
		printUsage();
	}

	sscanf(argv[2], "%u", &_prob);
	if (_prob < 0 || _prob > 100) {
		cout << "ERROR: Prob to create edge (u,v) between [0,1]" << endl;
		printUsage();
	}

	if (argc > 3) {
		// Init rand seed
		sscanf(argv[3], "%d", &seed);
		srand(seed);
	} else {
		srand((unsigned int)time(NULL));
	}
}

int main(int argc, char *argv[]) {
	// parse arguments
	parseArgs(argc, argv);

	int horizontal;
  if(_V > 100)
		horizontal = _V/10 - 1;
  else
		horizontal = _V/3;

	// idk how many edges the graph will have
	cout << _V << " " << _V*_V;

  int j,k,batch,nodes = 0;
	while(nodes < _V){
			batch = 1 + (rand() % horizontal);
			
			if(batch > _V-nodes) batch = _V-nodes;

			for(j = 0; j < nodes; j++)
					for(k = 0; k < batch; k++)
							if((rand() % 100) < _prob)
									cout << j+1 << " " << nodes+k+1 << endl;
			

			nodes += batch;
	}

	return 0;
}
