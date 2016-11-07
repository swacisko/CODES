#include<iostream>
#include<vector>
#include<string.h>
using namespace std;

void writeGraph( vector<vector<int> > &V )
{
	for(int i=0; i<V.size(); i++)
	{
		cout << "Wierzcholek nr " << i << ":  ";
		for(int k=0; k<V[i].size(); k++)
		{
			cout << V[i][k] << " ";
		}
		cout << endl;
	}
	
}

class Edge
{
public:
	int A;
	int B;
	int x;
	int y;
	int waga;
	Edge( int a=0, int b=0, int X=0, int Y=0 ) : A(a), B(b), x(X), y(Y)
	{}
	
	void przypiszWage()
	{
		waga = x<y?x:y;
	}
	
	bool operator>( Edge &krawedz )
	{
		if( waga >= krawedz.waga ) return true;
		return false;
	}
};


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


int writeBFS( vector< vector<int> > &V, vector< vector<int> > &Predecessors, int start  )
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
		cout << V[start][i] << " "; // tutaj wypisuje poczatkowe wierzcholki - te dla ktorych wczesiej Predecessors[i] = 0
	}
//	cout << "Wierzcholek start to: " << start << endl; // tu upewniam sie czy wierzcholek start to na pewno N+1
	
//	int licznik = 1; // to jest niepotrzebne do niczego, poza znalezieniem bledu
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
					cout << V[ recentWorkersNumbers[i] ][k] << " ";
					wasVisited[ V[ recentWorkersNumbers[i] ][k] ] = true;
					currentWorkersNumbers.push_back( V[ recentWorkersNumbers[i] ][k] );
				}
				else numberOfPredecessors[ V[ recentWorkersNumbers[i] ][k] ]--;
			}
		}
		
//		cout << "Licznik petli: " << licznik++ << endl;
	}while( currentWorkersNumbers.size() ); // until array size is greater tahn zero, we will iterate BFS
//	cout << endl;
	return max;
}



template<class typ>
void zamien( typ& a, typ& b )
{
    typ c = a;
        a = b;
        b = c;  
}
 
template< class typ >
long long podzial( typ &tab, long long p, long long r )
{
        long long i = p-1;
        for(long long j=p; j<r; j++)
        {
                if( ! ( tab[j] > tab[r] ) )
                {
                        i++;
                        zamien( tab[j], tab[i] );
                }
        }
        
        zamien( tab[i+1], tab[r] );
        return i+1;     
}
 
template< class typ >
void quicksort( typ &tab, long long p, long long r )
{
        if( p < r )
        {
                long long q = podzial( tab,p,r );
                quicksort( tab,p,q-1 );
                quicksort( tab,q+1,r );
        }       
}



int MINIMUM;



int main()
{
	ios_base::sync_with_stdio(0);
	int l_zest;
	int N,M;
	int A,B;
	int x,y;
	int petloweMinimum;
	
	bool *wasVisited;
	bool *isOnPath;
	
	cin >> l_zest;
	
	while( l_zest-- )
	{
		MINIMUM = 100000000; // MINIMUM oznacza najmniejszy wystarczajacy iloraz inteligencji		
		
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
		
		// some comments (and code) are from task Podboj Rynku
		
		Edge *powiazania = new Edge[M]; // tworze powiazania
		
		for( int i=0; i<M; i++ ) // read input data
		{
			cin >> powiazania[i].A >> powiazania[i].B >> powiazania[i].x >> powiazania[i].y;
			powiazania[i].przypiszWage();
		}
		
		quicksort( powiazania, 0,M-1 ); // wypadalo by zamienic na zamiane wskaznikow, to znacznie skroci czas kopiowania struktur		
		
		for(int i=0; i<M; i++)
		{
			memset( isOnPath,false, N+1 );
			memset( wasVisited, false, N+1 );
			
			if( powiazania[i].x >= powiazania[i].y )
			{
				Neighbours[ powiazania[i].A ].push_back( powiazania[i].B );
				Predecessors[ powiazania[i].B ].push_back( powiazania[i].A );
				
				if( directedGraphCycleExistence( Neighbours, wasVisited,isOnPath,powiazania[i].A ) ) // jesli dodana krawedz tworzy cykl
				{
					Neighbours[ powiazania[i].A ].pop_back();
					Predecessors[ powiazania[i].B ].pop_back();
					
					Neighbours[ powiazania[i].B ].push_back( powiazania[i].A );
					Predecessors[ powiazania[i].A ].push_back( powiazania[i].B );
					
					if( powiazania[i].y < MINIMUM ) MINIMUM = powiazania[i].y;  // sprawdzam, czy waga dodanej krawedzi nie jest najwieksza z calego grafu
			//		cout << "Przypisanie nr 1" << endl;
				}
				else
				{
					if( powiazania[i].x < MINIMUM ) MINIMUM = powiazania[i].x;  // sprawdzam, czy waga dodanej krawedzi nie jest najwieksza z calego grafu
			//		cout << "Przypisanie nr 2" << endl;
				}				
			}
			else
			{				
				Neighbours[ powiazania[i].B ].push_back( powiazania[i].A );
				Predecessors[ powiazania[i].A ].push_back( powiazania[i].B );
				
				if( directedGraphCycleExistence( Neighbours, wasVisited,isOnPath,powiazania[i].B ) ) // jesli dodana krawedz tworzy cykl
				{
					Neighbours[ powiazania[i].B ].pop_back();
					Predecessors[ powiazania[i].A ].pop_back();
					
					Neighbours[ powiazania[i].A ].push_back( powiazania[i].B );
					Predecessors[ powiazania[i].B ].push_back( powiazania[i].A );
					
					if( powiazania[i].x < MINIMUM ) MINIMUM = powiazania[i].x;  // sprawdzam, czy waga dodanej krawedzi nie jest najwieksza z calego grafu					
			//		cout << "Przypisanie nr 3" << endl;
				}
				else
				{
					if( powiazania[i].y < MINIMUM ) MINIMUM = powiazania[i].y;  // sprawdzam, czy waga dodanej krawedzi nie jest najwieksza z calego grafu
			//		cout << "Przypisanie nr 4" << endl;
				}				
			}			
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
	/*	
		cout << "Oto tablica powiazan:"<<endl;
		for(int i=0; i<M; i++)
		{
			cout << "Powiazanie(krawedz) nr " << i << ": " << powiazania[i].A << " " << powiazania[i].B << " " << powiazania[i].x 
				<< " " << powiazania[i].y << " " << powiazania[i].waga << endl;
		}
		
		cout << "Oto twoj graf Neighbours:"<<endl;
		writeGraph( Neighbours );
		cout << endl << "A to twoj graf Predecessors:"<<endl;
		writeGraph( Predecessors );
		cout << endl;
	*/	
		cout << MINIMUM << " ";
		writeBFS( Neighbours,Predecessors,N+1 );
		cout << endl;
		
		delete[]powiazania;
	}
	
	
	
	
	
	
	
	
	
	
	
	
}





