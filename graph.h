#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include "node.h"
using namespace std;

class Graph 
{
	public:
		// DO NOT MODIFY MEMBERS BELOW THIS LINE
        int get_num_nodes(); 						// get number of nodes
        int get_num_edges(); 						// get number of edges
        std::vector<Node> get_neighbors(Node u); 	// return neighbors of u 
        std::map<int, Node> get_id_to_node_map(); 	// allows lookup of nodes from ids
		// DO NOT MODIFY MEMBERS ABOVE THIS LINE
		
		// declare any constructors, members, and member functions you may want to use
		int node_id;
		int edge_id;
		vector<vector<Node>> adjacency_list;
        map<int, Node> id_to_node_map;
		Graph();
		Graph(int node_ID);
		Graph(const Graph&);
		Graph(vector<vector<Node>> nodelist);
		//Graph(const& Graph);
		//bool is_adjacent(Node& x, Node& y);
		//bool is_adjacent(const Node x, const Node y);
		bool is_adjacent(Node x, Node y);
		void add_edge(int x, int y);
		~Graph();
		// implement any newly declared member functions in graph.cpp
};

#endif
