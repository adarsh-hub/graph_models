//Erdos-Renyi Random Graph Implementation
#include "project3.h"
#include "graph.h"
#include <set>
#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std;

//******************** RANDOM GENERATION FUNCTIONS *************************//

int get_randint2(mt19937 mt, int x, int y)
{
    return uniform_int_distribution<int>(x, y)(mt);
}

int get_randint3(mt19937 mt, double p)
{
    return binomial_distribution<>(1, p)(mt);
}

double get_randfloat2(mt19937 mt, double x, double y)
{
    return uniform_real_distribution<double>(x, y)(mt);
}

mt19937 get_seed2()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}
//*************************************************************************//

Graph create_ER_graph(int n){
	
	Graph erdos_renyi = make_graph(n, vector<int>{}, vector<int>{});
	double p = (2 * (log(n)))/n;
	int v = 1;
	int w = -1;
	double r;
	
	while(v<n){
		mt19937 seed2 = get_seed2();
		r = get_randint2(seed2, 0, 1);
		int x = (floor((log(1-r)/log(1-p))));
		w = w + 1 + x;
		while(w>=v and v<n){
			w = w-v;
			v = v+1;
		}
		if(v<=n){
			if(v<=0){v=1;} // Remove these lines 
			if(w<=0){w=1;} // when writing the report
				erdos_renyi.add_edge(v,w);
		}
	}
	
	
	return erdos_renyi;
}

