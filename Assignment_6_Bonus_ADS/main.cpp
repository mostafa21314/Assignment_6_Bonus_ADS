// Mostafa Gaafar
// 900214463
#include<iostream>
#include"Graphs.h"
const string fileName1 = "/Users/mosta/Desktop/AUC/Applied Data Structures/Assignments Applied data structures/Assignment_6_Bonus_ADS/2211Asn6F23/CitiesG.txt";
const string fileName2 = "/Users/mosta/Desktop/AUC/Applied Data Structures/Assignments Applied data structures/Assignment_6_Bonus_ADS/2211Asn6F23/TestG.txt";

using namespace std;
int main()
{

	Graphs testing;
	testing.getGraph(fileName1);
	cout << "Number of Vertices : " <<testing.No_of_Verices()<<endl;
	cout << "Number of Edges : " << testing.No_of_Edges() << endl;
	testing.dispGraph();
	testing.dispEdges();
	testing.shPath(0);
	testing.DFS();

}