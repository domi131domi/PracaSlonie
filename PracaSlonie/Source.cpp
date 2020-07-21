#include <iostream>
#include "Cycle.h"

const unsigned N = 10;
unsigned perm[N] = { 8, 4, 7, 2, 0, 3, 6, 5, 9, 1 };

//unsigned perm[N] = { 4, 9, 3, 5, 1, 7, 6, 2, 0, 8 };
unsigned m[N] = { 3015,4728,4802,4361,135,4444,4313,1413,4581,546 };
//short perm[N] = { 1, 3, 0, 2 };

std::vector<Cycle*> createCycles(unsigned* perm) {
	std::vector<Cycle*> cycles;
	bool odw[N] = { false };
	int c = -1, x;

	for(int i = 0; i < N; ++i)
		if (!odw[i]) {
			++c;
			x = i;
			cycles.push_back(new Cycle);
			while (!odw[x]) {
				odw[x] = true;
				cycles[c]->numbers.push_back(x);
				x = perm[x];
			}
		}

	return cycles;
}

void calcParameters(std::vector<Cycle*> &cycles, int &min) {
	min = -1;
	for (unsigned i = 0; i < cycles.size(); ++i) {
		cycles[i]->sumC = 0;
		cycles[i]->minC = -1;
		for (unsigned e : cycles[i]->numbers) {
			cycles[i]->sumC += m[e];
			if (cycles[i]->minC < 0)
				cycles[i]->minC = m[e];
			else if (cycles[i]->minC > m[e])
				cycles[i]->minC = m[e];
		}
		if (min < 0)
			min = cycles[i]->minC;
		else if (min > (int) cycles[i]->minC)
			min = cycles[i]->minC;
	}
	
	return;
}

long long calcResult(std::vector<Cycle*> &cycles, int min) {
	long long m1,m2,result = 0;

	for (unsigned i = 0; i < cycles.size(); ++i) {
		if (cycles[i]->numbers.size() >= 2) {
			m1 = cycles[i]->sumC + (cycles[i]->numbers.size() - 2) * cycles[i]->minC;
			m2 = cycles[i]->sumC + cycles[i]->minC + (cycles[i]->numbers.size()+1) * min;
			if (m1 > m2)
				result += m2;
			else
				result += m1;
		}	
	}
	return result;
}


int main(int argc, char* argv[]) {

	int min;

	std::vector<Cycle*> cycles = createCycles(perm);
	calcParameters(cycles, min);
	

	for (Cycle* i : cycles) {
		for (unsigned e : i->numbers)
			std::cout << e + 1 << " ";
		std::cout << std::endl << "Suma " << i->sumC << std::endl;
		std::cout << "Dlugosc " << i->numbers.size() << std::endl;
		std::cout << "MinC " << i->minC << std::endl;
		std::cout << std::endl;
	}
		std::cout << "MIN " << min << std::endl;
		std::cout << "Result: " << calcResult(cycles, min) << std::endl;

	system("pause");
	return 0;
}