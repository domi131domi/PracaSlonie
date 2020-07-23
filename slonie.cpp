#include <iostream>
#include <vector>
#include <algorithm>

const unsigned M_MAX = 6501;    //maximal weight

struct Cycle {
    unsigned long long sumC = 0;
    unsigned minC = M_MAX;
    unsigned size = 0;
};

//create all necessary data about cycles
std::vector<Cycle> createCycles(unsigned* perm, unsigned n, unsigned& min, unsigned* m) {
    std::vector<Cycle> cycles;
    bool* odw = new bool[n];
    for(unsigned i = 0; i < n; ++i)
        odw[i] = false;

    unsigned x, c = 0;
    Cycle cycle;

    for(unsigned i = 0; i < n; ++i)
        if(!odw[i]) {
            x = i;
            cycles.push_back(cycle);
            while(!odw[x]) {
                odw[x] = true;

                //actualize cycle data
                ++cycles[c].size;
                cycles[c].sumC += m[x];
                if(cycles[c].minC > m[x])
                    cycles[c].minC = m[x];
                if(min > m[x])
                    min = m[x];

                x = perm[x];
            }
            ++c;
        }
    return cycles;
}

//calculate result
long long calcResult(std::vector<Cycle>& cycles, unsigned min) {
    long long m1, m2, result = 0;

    for(Cycle cycle : cycles) {
        if(cycle.size >= 2) {
            m1 = cycle.sumC + (cycle.size - 2) * cycle.minC;
            m2 = cycle.sumC + cycle.minC + (cycle.size + 1) * min;
            result += std::min(m1,m2);
        }
    }

    return result;
}

int main(int argc, char* argv[]) {

    unsigned n;
    std::cin >> n;


    unsigned* m = new unsigned[n];
    unsigned* a = new unsigned[n];
    unsigned* perm = new unsigned[n];
    unsigned min = M_MAX;

    for(unsigned i = 0; i < n; ++i)
        std::cin >> m[i];
    for(unsigned i = 0; i < n; ++i)
        std::cin >> a[i];

    unsigned temp;
    for(unsigned i = 0; i < n; ++i) {
        std::cin >> temp;
        perm[temp-1] = a[i]-1;
    }

    delete[] a;



    std::vector<Cycle> cycles = createCycles(perm, n, min, m);
    std::cout << calcResult(cycles, min) << std::endl;

    delete[] perm;
    delete[] m;

    return 0;
}
