#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

class Cycle {
public:
	std::vector<unsigned> numbers;
	unsigned long long sumC;
	unsigned minC;

	Cycle() {};
	~Cycle() {};
private:

};

std::vector<Cycle*> createCycles(unsigned* perm, unsigned N) {
	std::vector<Cycle*> cycles;
	bool* odw = new bool[N];
	for (unsigned i = 0; i < N; ++i)
		odw[i] = false;

	int c = -1, x;

	for(unsigned i = 0; i < N; ++i)
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

void calcParameters(std::vector<Cycle*> &cycles, int &min, unsigned* m) {
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


	unsigned N;
	std::cin >> N;
	unsigned* perm = new unsigned[N];
	unsigned* m = new unsigned[N];
	unsigned* a = new unsigned[N];
	unsigned* b = new unsigned[N];

	for (unsigned i = 0; i < N; ++i)
		std::cin >> m[i];
	for (unsigned i = 0; i < N; ++i)
		std::cin >> a[i];
	for (unsigned i = 0; i < N; ++i)
		std::cin >> b[i];
	for (unsigned i = 0; i < N; ++i)
		perm[b[i]-1] = a[i]-1;

	int min;

	std::vector<Cycle*> cycles = createCycles(perm, N);
	calcParameters(cycles, min, m);
	long long result = calcResult(cycles, min);

	std::cout << result << std::endl;
	

	delete[] perm;
	delete[] a;
	delete[] b;
	delete[] m;

	return 0;
}