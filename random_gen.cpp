#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>

using namespace std;


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

//int main()
//{
//	
//	uniform_int_distribution<int> distribution = get_generator(1,10);
//
//	// number of experiments
//	const int num_of_exp = 100;
//
//	int n = num_of_exp;
//	vector<int> result;
//	int total;
//	for (int i = 0; i < num_of_exp; ++i) {
//
//		// using operator() function
//		// to give random values
//		int number = get_randint(get_seed(), 1, 10);
//		cout << number << " , ";
//		total += number;
//		result.push_back(number);
//	}
//	
//	cout << endl;
//	
//	cout << "mean: " << total/num_of_exp ;
//
//	return 0;
//}
