#include "graph.h"
#include "node.h"
#include "algorithm"
#include <iostream>

//Default Constructors
Graph::Graph(){
	this->node_id = 0;
	this->edge_id = 0;
}

Graph::Graph(const Graph& new_graph){
	this->node_id = new_graph.node_id;
	this->edge_id = new_graph.edge_id;
	this->id_to_node_map = new_graph.id_to_node_map;
	this->adjacency_list = new_graph.adjacency_list;
}

Graph::Graph(int node_ID){
	this->edge_id = 0;
	this->node_id = node_ID;
	for(int i = 0; i < node_ID; i++){
		int new_id = i+1;
		Node n(new_id);
		vector<Node> node_list;
		this->id_to_node_map[new_id] = n;
		this->adjacency_list.push_back(node_list);
	}
}

void Graph::add_edge(int x, int y){
	edge_id+=1;
	Node X(x);
	Node Y(y);
	this->adjacency_list.at(x-1).push_back(Y);
	this->adjacency_list.at(y-1).push_back(X);
}

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v){
	
	Graph G = Graph(num_nodes);
	int edID = u.size();
	for(int i=0; i<edID; i++){
		G.add_edge(u.at(i), v.at(i));
	}
	return G; // remove this line if you implement the function
}

int Graph::get_num_nodes() {
	return this->node_id;
}

int Graph::get_num_edges() {
	return this->edge_id;
}

bool Graph::is_adjacent(Node x, Node y){
	vector<Node> nlist = adjacency_list.at(x.id-1);
	for(int i = 0; i< nlist.size();i++){
		if(nlist.at(i).id == y.id){
			return true;
		}
	}
	return false;
}

std::vector<Node> Graph::get_neighbors(Node u) {
	return this->adjacency_list.at(u.id-1);
}

std::map<int, Node>Graph::get_id_to_node_map(){
	return this->id_to_node_map;
}

Graph::~Graph() {}

//bool vectors_have_same_nodes(vector<Node> nodes1, vector<Node> nodes2)
//{
//    sort(nodes1.begin(), nodes1.end(), [](const Node& u, const Node& v){return u.id < v.id;});
//    sort(nodes2.begin(), nodes2.end(), [](const Node& u, const Node& v){return u.id < v.id;});
//    return nodes1 == nodes2;
//}
//
//int main(){
//	Graph graph = make_graph(2, vector<int>{1}, vector<int>{2});
//    map<int, Node> id_to_node = graph.get_id_to_node_map();
//    int x = graph.get_num_nodes();
//	int y = graph.get_num_edges();//
//	std::cout<<"test nodes: "<<x<<"\n";
//	std::cout<<"test edges: "<<y<<"\n";
//	std::vector<Node> n1 = graph.get_neighbors(id_to_node[1]);
//	std::vector<Node> n2 = graph.get_neighbors(id_to_node[2]);
//	for(int i = 0; i<n1.size(); i++){
//		std::cout << n1.at(i).id << "\n";
//	}
//		std::cout << id_to_node[2].id << "\n";
//	
//	for(int j = 0; j<n1.size(); j++){
//		std::cout << n2.at(j).id << "\n";
//	}
//		std::cout << id_to_node[1].id << "\n";
//	std::cout << vectors_have_same_nodes(graph.get_neighbors(id_to_node[1]), vector<Node>{id_to_node[2]}) <<"\n";
//	
//	return 0;
//}
