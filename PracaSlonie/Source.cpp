#include <vector>


const short N = 4;
short perm[N] = { 3, 2, 1, 4 };

std::vector<std::vector<short>> createCycles(short* perm) {
	std::vector<std::vector<short>> cycles;
	bool odw[N] = { false };
	short c = 0, x;

	for(int i = 0; i < N; ++i)
		if (!odw[i]) {
			++c;
			x = i;
		}

	return cycles;
}


int main(int argc, char* argv[]) {



	return 0;
}