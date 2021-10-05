#include "project3.h"
#include "graph.h"
#include "barabasi_albert_graph.cpp"
#include "erdos_renyi_graph.cpp"
#include "graph_algorithms.cpp"

using namespace std;

int main(){
	
	Graph ER2 = create_ER_graph(10);
	cout << "Diamater: " << get_diameter(ER2) << endl;
	cout << "Clustering Coefficient: " << get_clustering_coefficient(ER2) << endl;
	
	
	Graph ER3 = create_ER_graph(50);
	cout << "Diamater: " << get_diameter(ER3) << endl;
	cout << "Clustering Coefficient: " << get_clustering_coefficient(ER3) << endl;
	
	
	Graph ER4 = create_ER_graph(100);
	cout << "Diamater: " << get_diameter(ER4) << endl;
	cout << "Clustering Coefficient: " << get_clustering_coefficient(ER4) << endl;
	
	
	Graph BA = create_BA_graph(1000,10);
	cout << "Diamater: " << get_diameter(BA) << endl;
	cout << "Clustering Coefficient: " << get_clustering_coefficient(BA) << endl;
	
	return 0;
	
}
