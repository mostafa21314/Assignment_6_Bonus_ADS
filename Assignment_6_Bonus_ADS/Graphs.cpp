// FILE: graphs.cpp
// Graph Library Implementation File for Asn 6

#include <fstream>		// For reading file from disk
#include <iostream>
#include <string>		// For file name
#include <iomanip>
#include "Edge.h"		// Deinition of an Edge
#include "Graphs.h"

using namespace std;

// Constructor
Graphs::Graphs()
{
	E = V = order = 0;
}

// Destructor
Graphs::~Graphs()
{

}


// Map vertex number (0,1,2,..) to (A,B,C,..)
char Graphs::Vname(const int s) const
{
	return char(s + 65);
}

// Get Graph from text File (file name is stored in string fname)
// Graph is stored in adjacency matrix
void Graphs::getGraph(string fname)
{
	// Local data ...
	weightType wi;
	ifstream source;

	source.open(fname);
	string temp;
	getline(source, temp);
//	cout << temp;
	source >> temp;
//	cout << endl << temp << endl;;
	source >> temp;
	int counter = 0;
	while (source >> temp)
	{
	//	cout << temp << endl;
		counter++;
		if(temp=="A")
		break;

		
	}
	V = counter;	// Read no. of verices (V)

		
	// Input weights from the file into a 2-D 
	// Adjacency Matrix of V rows and V columns
	for (int r = 0; r < V; r++)
	{
		if(r!=0)  // to handle the exception of the first line
		source >> temp;// to skip the characters

		for (int i = 0; i < V; i++)
		{
			source >> temp;
			//cout << temp << endl;
			AdjMatrix[r][i]=stoi(temp);
		}
		// get V weights for row [r] from file
		// put V weights in adjacency matrix at row [r]
	}
	this->getEdges();
	source.close();

}

// Display Adjacency Matrix
void Graphs::dispGraph() const
{
	int i, j;
	cout << "Adjacency Matrix\n";
	for (i = 0; i < V; i++)
	{
		for (j = 0; j < V; j++)
			cout << setw(3) << AdjMatrix[i][j] << " ";
		cout << endl;
	}
}

// Get Non-Zero edges from adjacency matrix
// and store them in array edges[]. 
void Graphs::getEdges()
{
	int r, c;
	int i = 0;
	weightType weight;

	// Only examine weights above the diagonal 
	for (r = 0; r <= V - 2; r++)
		for (c = r + 1; c <= V - 1; c++)
		{
			weight = AdjMatrix[r][c];
			if (weight > 0)
			{
				// save (r,c,weight) in edges[i]
				edges[i].u = r;
				edges[i].v = c;
				edges[i].w = weight;
				i++;
			}
		}

	E = i;		// Number of non-zero edges

}

// Get number of vertices (V)	
int Graphs::No_of_Verices() const
{
	return V;
}

// Get Number of Non-zero edges (E)
int Graphs::No_of_Edges() const
{
	return E;
}

// Output an edge (e): Vertex names and weight
void Graphs::printEdge(Edge e) const
{
	cout << Vname(e.u) << " " << Vname(e.v) << " " << e.w << endl;
}

// Display Graph Edges
void Graphs::dispEdges() const
{
	cout << "Graph Edges\n";
	for (int i = 0; i < E; i++)
		printEdge(edges[i]);
}

// Shortest paths from node s
// uses Dijkstra's Algorithm
void Graphs::shPath(int s)
{
	for (int i = 0; i < V; i++)
	{
		distance[i] = INT_MAX;
		processed[i] = false;
	}
	distance[s] = 0;
	via[s] = s;
	visitShortest(s);


	cout << "SHortest Path From Node " << Vname(s)<<endl;
	for (int i = 0; i < V; i++)
	{
		printPath(s, i);
	}
	// Implement the function here
}

// Print path (vertex names) from source (s) to destination (i)
void Graphs::printPath(int s, int i) const
{

	cout<< "shortest path from " << Vname(s) << " to " << Vname(i) << " is " << distance[i] << " via " << Vname(via[i]) << endl;
	// Implement the function here
}

// Node Visit Function
void Graphs::visitShortest(int k)
{

	int shortest=INT_MAX;
	int index = -1;
	for (int i = 0; i < E; i++)
	{
		if (edges[i].u == k)
		{

			if ((edges[i].w < shortest) && (!processed[edges[i].v]))
			{
				index = edges[i].v;
				shortest = edges[i].w;
			}
			
			int temp = edges[i].w + distance[k];
			if (temp < distance[edges[i].v])
			{
				distance[edges[i].v] = temp;
				via[edges[i].v] = k;
				processed[k];
				//cout << k << endl;
				//cout << index << endl;
			}
		}



		if (edges[i].v == k)
		{

			if ((edges[i].w < shortest) && (!processed[edges[i].u]))
			{
				index = edges[i].u;
				shortest = edges[i].w;
			}

			int temp = edges[i].w + distance[k];
			if (temp < distance[edges[i].u])
			{
				distance[edges[i].u] = temp;
				via[edges[i].u] = k;
				processed[k];
				//cout << k << endl;
				//cout << index << endl;
			}
		}
	}
	processed[k]=true;
	//cout << index << " " << shortest << endl;
	if (index > -1)
	{
		visitShortest(index);
	}


	// Implement the function here	
}

// Depth First Search Traversal
void Graphs::DFS()
{
	order = 0;
	for (int i = 0; i < V; i++)
	{
		processed[i] = 0;
	}
	for (int i = 0; i < V; i++)
	{
		if (!processed[i])
		{
			visit(i);
		}
	}

	cout << "DFS Traversal visited nodes in this order : " << endl;;
	for (int i = 0; i < V; i++)
	{
		cout << val[i] << setw(3);
	}
	cout << endl;
	// Implement the function here	
}

void Graphs::visit(int k)
{
	
		val[order++] = k;
		processed[k] = true;
		/*cout << endl;
		for (int i = 0; i < V; i++)
		{
			cout << Vname(i) << "  " << processed[i] <<"   ";
		}*/
		for (int i = 0; i < V; i++)
		{
		//	cout << AdjMatrix[k][i] << endl;
			if (AdjMatrix[k][i] > 0)
			{
				if (!processed[i])
				{
					visit(i);
				}
			}
		}
	



}
