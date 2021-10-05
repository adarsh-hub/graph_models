//Barabasi-Albert Random Graph Implementation
#include "project3.h"
#include "graph.h"
#include <set>
#include <iostream>
#include <chrono>
#include <vector>

using namespace std;

//******************** RANDOM GENERATION FUNCTIONS *************************//
int get_randint1(mt19937 mt, int x, int y)
{
    return uniform_int_distribution<int>(x, y)(mt);
}

mt19937 get_seed1()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}
//*************************************************************************//

Graph create_BA_graph(int nodes, int degree){
	
	Graph barabasi_albert = make_graph(nodes, vector<int>{}, vector<int>{});
	int size = 2*nodes*degree;
	int L[size];
	set<tuple<int,int>> edges;
	
	for(int i = 0; i < nodes; i++){
		for(int j = 0; j< degree; j++){
			mt19937 seed = get_seed1();
			L[2*(i * degree + j)] = i;
			int p = get_randint1(seed,0,2*(i*degree+j));
			L[2*(i * degree + j)+1] = L[p];
		}
	}
	
	for(int x =0; x<nodes*degree; x++){
		int nid1 = L[2 * x] + 1;
		int nid2 = L[2 * x + 1] + 1;
		tuple<int,int> edge = make_tuple(nid1,nid2);
		tuple<int,int> edge2 = make_tuple(nid2,nid1);
		if(nid1!=nid2 && edges.find(edge) == edges.end()){
			barabasi_albert.add_edge(nid1,nid2);
			edges.insert(edge);
			edges.insert(edge2);
		}
	}
	
	return barabasi_albert;
}
