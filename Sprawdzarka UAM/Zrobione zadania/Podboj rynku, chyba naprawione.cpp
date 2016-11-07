#include<iostream>
#include<vector>
using namespace std;

bool directedGraphCycleExistence( vector< vector<int> > &V, bool *wasVisited, bool *isOnPath, int vertex )
{
//	cout << "I am in vertex " << vertex << endl;
	for(int i=0; i < V[vertex].size(); i++)
	{
		if( isOnPath[ V[vertex][i] ] ) return true;
		else if( wasVisited[ V[vertex][i] ] );
		else
		{
			wasVisited[ V[vertex][i] ] = true;
			isOnPath[ V[vertex][i] ] = true;
			
			if( directedGraphCycleExistence( V, wasVisited, isOnPath, V[vertex][i] ) ) return true;
			
			isOnPath[ V[vertex][i] ] = false;
		}
	}
	
	return false;
}

int maximumWorkersNumberBFS( vector< vector<int> > &V, vector< vector<int> > &Predecessors, int start  )
{
	vector<int> currentWorkersNumbers;
	vector<int> recentWorkersNumbers;
	bool *wasVisited = new bool[ V.size()+1 ];
	for(int i=0; i<V.size()+1; i++) wasVisited[i] = false;
	
	int max = 0;
	
	int *numberOfPredecessors = new int[V.size()];
	for( int i = 1; i<V.size(); i++ ) numberOfPredecessors[i] = Predecessors[i].size();
	
	for(int i=0; i<V[start].size(); i++) // i add vertices from the start vertex to currentWorkersNumbers
	{
		currentWorkersNumbers.push_back( V[start][i] );
	}
	
	do
	{
		swap( currentWorkersNumbers, recentWorkersNumbers ); // here current workers become recent workers
		currentWorkersNumbers.clear(); // we do not need 'more than recent' workers, but we need spcae for current workers
		
		if( recentWorkersNumbers.size() > max ) max = recentWorkersNumbers.size(); // here we save the answer for the whole problem-maximum number of workers needed
//		cout << "recentWorkers: "; for(int i=0; i<recentWorkersNumbers.size(); i++) cout << recentWorkersNumbers[i] << " ";
//		cout << "\tmaximum = " << max << endl;
		
		for(int i=0; i < recentWorkersNumbers.size(); i++ ) // we have two for-loops in a while-loop, but complexity is still linear
		{
			for( int k=0; k < V[ recentWorkersNumbers[i] ].size(); k++ )
			{
				if( ( ! wasVisited[ V[ recentWorkersNumbers[i] ][k] ] ) && numberOfPredecessors[ V[ recentWorkersNumbers[i] ][k] ] == 1 ) // if we werent at the vertex, we add it to queue-currentWorkersNumbers
				{
					wasVisited[ V[ recentWorkersNumbers[i] ][k] ] = true;
					currentWorkersNumbers.push_back( V[ recentWorkersNumbers[i] ][k] );
				}
				else numberOfPredecessors[ V[ recentWorkersNumbers[i] ][k] ]--;
			}
		}
		
		
	}while( currentWorkersNumbers.size() ); // until array size is greater tahn zero, we will iterate BFS
//	cout << endl;
	return max;
}


int main()
{
	ios_base::sync_with_stdio(0);
	int l_zest,x,y,r;
	int N,M;
	bool *wasVisited, *isOnPath;
	
	cin >> l_zest;
	
	while(l_zest--)
	{
		cin >> N >> M;
		
		wasVisited = new bool[N+1];
		isOnPath = new bool[N+1];
		for(int i=0; i<N+1; i++)
		{
			wasVisited[i] = false;
			isOnPath[i] = false;
		}
		
		vector<int> noPredecessorVertices;
		vector< vector<int> > Neighbours(N+1); // Neighbours[i] - list of neighbours of a vertex i
		vector< vector<int> > Predecessors(N+1); // Predecessors[i] - list of vertices, which are connected with vertex i with direct edge
		// task i can be done if and only if task Predecessors[i] is done
		
		for(int i=0; i<M; i++)
		{
			cin >> x >> y;
			
			Neighbours[y].push_back(x);
			Predecessors[x].push_back(y);
		}
		
		Neighbours.push_back( vector<int>() ); // from now on Neighbours[N] will denote the vertex we create and join with every vertex that has no predecessor
		for(int i=1; i<=N; i++) // here we join the graph, so that we can later call BFS( every vertex with no predecessor will have the same one- vertex N );
		{
			if( Predecessors[i].size() == 0 )
			{
				Neighbours[N+1].push_back(i);
				Predecessors[i].push_back( N+1 );
			}
		}
		
		if( Neighbours[N+1].size() == 0 ) // if there are no vertices with degree zero, we have no solution
		{
			cout << "Brak rozwiazania"<< endl;
			continue;
		}
		
		if( directedGraphCycleExistence( Neighbours, wasVisited, isOnPath,N+1 ) ) // if there is a cycle, we have no solution, else there is one
		{
			cout << "Brak rozwiazania" << endl;
			continue;
		}
		
		bool everyVisited = true;
		for(int i=1; i<=N; i++) // it can happen as in test nr 5,6,7,8 of my tests
		{
	//		cout << "Vertex " << i << " wasVisited["<<i<<"] = " << wasVisited[i] << endl;
			if( wasVisited[i] == false )
			{
				everyVisited = false;
				break;
			}
		}
		
		if( !everyVisited )
		{
		//	cout << "Brak rozwiazania, because not every was Visited" << endl;
		cout << "Brak rozwiazania" << endl;
			continue;
		}
		
	//	cout << "It passed DFS, but failed BFS";
		
		int maxWorkersNumber = maximumWorkersNumberBFS( Neighbours,Predecessors, N+1 );
		
		if( maxWorkersNumber == 0 ) cout << "Brak rozwiazania" << endl;
		else  cout << maxWorkersNumber << endl;		
		
		
		delete[]wasVisited;
		delete[]isOnPath;
	}
	
	
	
}
