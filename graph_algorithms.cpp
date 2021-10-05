#include "graph.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <queue>
#include <unordered_set>
#include <stack>

using namespace std;

//******************** RANDOM GENERATION FUNCTIONS *************************//
uniform_int_distribution<int> get_generator(int x, int y)
{
    return uniform_int_distribution<int>(x, y);
}

int get_randint(mt19937 mt, int x, int y)
{
    return uniform_int_distribution<int>(x, y)(mt);
}

mt19937 get_seed()
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    return mt19937(seed);
}
//************************  HELPER FUNCTIONS  ******************************//
int get_two_edge_paths(Graph g){
	int size = g.get_num_nodes();
	int degree, result = 0;
	for (int i = 1; i <= size; i++) {
        Node n(i);
        degree = g.get_neighbors(n).size();
        result += degree * (degree - 1) / 2;
    }
    
    return result;
}
/*
1. Initialize an output list, L, to be empty.
2. Compute a number, dv, for each vertex v in G, which is the number of
neighbors of v that are not already in L. Initially, dv is just the degrees of v.
3. Initialize an array D such that D[i] contains a list of the vertices v that are not
already in L for which dv = i.
4. Let Nv be a list of the neighbors of v that come before v in L. Initially, Nv is
empty for every vertex v.
5. Initialize k to 0.
6. Repeat n times:
– Let i be the smallest index such that D[i] is nonempty.
– Set k to max(k, i).
– Select a vertex v from D[i]. Add v to the beginning of L and remove it
from D[i]. Mark v as being in L (e.g., using a hash table, HL).
– For each neighbor w of v not already in L (you can check this using HL):
• Subtract one from dw
• Move w to the cell of D corresponding to the new value of dw , i.e., D[dw]
• Add w to Nv
*/
int count_triangles(Graph g){
	int triangles = 0;
	int degeneracy = 0;
	int num_nodes = g.get_num_nodes();
	
    int deg[num_nodes];
    vector<int> N[num_nodes];
    
	stack<int> L; //Initialize an output list, L, to be empty.
    map<int, unordered_set<int>> D;

	//Initialize an array D such that D[i] contains a list of the vertices v that are not already in L for which dv = i.		
    for (int i = 1; i <= num_nodes; ++i) {
        Node n(i);
        int degree = g.get_neighbors(n).size();
        D[degree].insert(i);
        deg[i - 1] = degree;
    }
    //Select a vertex v from D[i]. Add v to the beginning of L and remove it from D[i]. Mark v as being in L (e.g., using a hash table, HL).
    unordered_set<int> H;
    for(int ind = 0; ind< num_nodes; ind++){
    	int min = -1;
    	for(auto j = D.begin(); j!=D.end();j++){
    		if(!j->second.empty()){
    			min = j->first;
    			break;
			}
		}
		unordered_set<int> nlist = D[min];
		degeneracy = max(degeneracy, min);
		
		int nid = *nlist.begin();
		L.push(nid);
		H.insert(nid);
		
		D[min].erase(nid);
		vector<Node> nblist = g.get_neighbors(Node(nid));
		/*
		– For each neighbor w of v not already in L (you can check this using HL):
		• Subtract one from dw
		• Move w to the cell of D corresponding to the new value of dw , i.e., D[dw]
		• Add w to Nv
		*/
		for(int x=0; x<nblist.size(); x++){
			Node nxt = nblist[x];
			int nodeID = nxt.id;
			if(H.find(nodeID) == H.end()){
				int cur = deg[nodeID-1]--;
				D[cur].erase(nodeID);
				D[cur-1].insert(nodeID);
				N[nid -1].push_back(nodeID);
			}
		}
	}
	
	//Count the traingles
	while(!L.empty()){
		int top = L.top();
		vector<int> nodes = N[top-1];
		int num_nodes2 = nodes.size();
		for(int a = 0; a< num_nodes2-1; a++){
			for(int b = a+1; b<num_nodes2; b++){
				if(g.is_adjacent( Node(nodes[a]), Node(nodes[b]) ) ){
					triangles++;
				}
			}
		}
		L.pop();
	}
	
	return triangles; 
}

tuple<Node, int> breadth_first_search(Graph g, Node start){
	int size = g.get_num_nodes();
	queue<int> Q;
	bool *visited = new bool[size];
	int *distance = new int[size];
	Node furthest(start);
	int dist_max = 0;
	
	for(int ind = 0; ind < size; ind++){
		visited[ind] = false; 	//initialize the arrays
		distance[ind] = 0;
	}
	
	visited[start.id-1] = true;
	Q.push(start.id);
	
	while(!Q.empty()){
		Node temp(Q.front());
		Q.pop();
		vector<Node> nlist = g.get_neighbors(temp);
		for(Node n: nlist){
			if(!visited[n.id - 1]){
				Q.push(n.id);
				visited[n.id-1]=true;
				distance[n.id-1] = distance[temp.id-1]+1;
			}
		}
	}
	
	for(int i=0; i<size; i++){
		if(distance[i]>dist_max){
			dist_max = distance[i];
			furthest = Node(i+1);
		}
	}
	tuple<Node, int> result = make_tuple(furthest, dist_max);
	return result;
}
//*************************************************************************//

int get_diameter(Graph graph)
{
	int size = graph.get_num_nodes();
	int diameter = 0;
	
	if(size>1){
		int max = 0;
		mt19937 seed = get_seed();
        int ind_start = get_generator(1, size)(seed);
        Node start(ind_start);
        tuple<Node, int> furthest = make_tuple(start, max);
        
        do{
        	diameter = get<1>(furthest);
        	furthest = breadth_first_search(graph, get<0>(furthest));
		} while(get<1>(furthest)>diameter);
	}
	
	return diameter;
}

float get_clustering_coefficient(Graph graph) 
{
	int triangles = count_triangles(graph);
	int two_edgepaths = get_two_edge_paths(graph);
	
	float clustering_coefficient = 3.0 * triangles / two_edgepaths;
    return clustering_coefficient;
}

std::map<int, int> get_degree_distribution(Graph graph) 
{
	map<int, int> deg_dist;
    int size = graph.get_num_nodes();
	int degree = 0;
	
    for (int i = 1; i <= size; ++i) {
        Node n(i);
        degree = graph.get_neighbors(n).size();
        deg_dist[degree] = deg_dist[degree] + 1;
    }
    return deg_dist; 
}

//int main(){
//	Graph graph = make_graph(3, vector<int>{1, 2}, vector<int>{2, 3});
//	int d = get_diameter(graph);
//	return d;
//}
