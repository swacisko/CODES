#include<iostream>
#include<vector>
using namespace std;

int N = 0,M = 0;
typedef vector<vector<int> > VVI;
typedef vector<int> VI;
const int infinity = 100000000;


int minimum( int a, int b ){
	return a<=b?a:b;
}

class Node{
public:
	Node() : hasLeafSon(false), isLeaf(false), on(1), lighted(1), off(0), diff(0), min(1) {}
	int on;
	int lighted;
	int off;
	int diff;	// abs z roznicy miedzy on i lighted
	int min;	// minimum z on i lighted
	bool isLeaf;
	bool hasLeafSon;
};

ostream& operator<<( ostream& str, Node &n ){
	str << "On=" << n.on << "  Lighted=" << n.lighted << "  off=" << n.off << "  diff=" << n.diff << "  min=" << n.min << "  isLeaf=" << n.isLeaf << "  hasLeafSon=" << n.hasLeafSon << endl;
}

VVI V;
vector<Node> nodes;
vector<bool> ifWas;

int getOnStatus( int parent, int myNumber ){
	int m = 0;
	for( int i=0; i<V[myNumber].size(); i++ ){
		if( V[myNumber][i] != parent ){
			m += minimum( nodes[ V[myNumber][i] ].min, nodes[ V[myNumber][i] ].off );			// UWAGA, TUTAJ ROZNE WERSJE !!!
		}
	}
	
	return m+1;
}

int getLightedStatus( int parent, int myNumber ){
	bool ifOneIsOn = false;
	int m = 0;
	int minDiff = infinity;
	
	for( int i=0; i<V[myNumber].size(); i++ ){
		if( V[myNumber][i] != parent ){
			m += nodes[ V[myNumber][i] ].min;
			if( nodes[ V[myNumber][i] ].diff < minDiff ) minDiff = nodes[ V[myNumber][i] ].diff;
			if( ifOneIsOn == false && nodes[ V[myNumber][i] ].diff == 0 ) ifOneIsOn = true;
		}
	}
	
	if( ifOneIsOn == false ) m += minDiff;
	
	return m;
}

int getOffStatus( int parent, int myNumber ){
	int m = 0;
	for( int i=0; i<V[myNumber].size(); i++ ){
		if( V[myNumber][i] != parent ){
			m += nodes[ V[myNumber][i] ].lighted;			
		}
	}
	
	return m;
}

void DFS( int parent, int myNumber ){
	ifWas[myNumber] = true;
	
	if( V[myNumber].size() == 0 || ( V[myNumber].size() == 1 && parent != myNumber  )   ){ // jesli jest lisciem
		nodes[myNumber].on = 1;
		nodes[myNumber].lighted = 1;
		nodes[myNumber].off = 0;
		nodes[myNumber].diff = 0;
		nodes[myNumber].min = 1;
		nodes[myNumber].isLeaf = true;
	}
	else{
		
		for( int i=0; i<V[myNumber].size(); i++ ){
			if( V[myNumber][i] != parent ){
				DFS( myNumber, V[myNumber][i] );
				if( nodes[ V[myNumber][i] ].isLeaf == true ) nodes[myNumber].hasLeafSon = true;
			}			
		}
		
		int on = getOnStatus( parent, myNumber );
		int lighted = getLightedStatus( parent, myNumber );
		int off = getOffStatus( parent, myNumber );
		
		if( nodes[myNumber].hasLeafSon == true ){
		//	nodes[myNumber].isLeaf = false; // to nie jest potrzebne, bo jesli jeslesmy w elsie to wiadomo, ze nie jest lisciem
			off = infinity;
		} 
		nodes[myNumber].on = on;
		nodes[myNumber].lighted = lighted;
		nodes[myNumber].off = off;		
		nodes[myNumber].diff = on-lighted>=0 ? on-lighted : 0; 
		nodes[myNumber].min = minimum( on, lighted );
				
	}
	
//	cout << "Oto ja!\n\tMy number is " << myNumber+1 << endl << "\t" << nodes[myNumber] << endl;
}

int maxDegree;
int maxDegIndex;

void getMaxDegree( int index, int parent ){
	if( V[index].size() > maxDegree ){
		maxDegree = V[index].size();
		maxDegIndex = index;
	}
	
	for( int i=0; i<V[index].size(); i++ ){
		if( V[index][i] != parent ){
			getMaxDegree( V[index][i], index );
		}
	}
	
}

int main(){
	
	ios_base::sync_with_stdio(0);
	int a = 0, b = 0;
	int result = 0;
	int t = 0;
	
	int l_zest = 0;
	cin >> l_zest;
	
	while( l_zest-- ){
		
		cin >> N >> M;
		
		if( N == 0 ) while(true);
		
		V.clear();
		nodes.clear();
		ifWas.clear();
		for( int i=0; i<N; i++ ) ifWas.push_back( false );		
		for( int i=0; i<N; i++ ) V.push_back( VI() );
		for( int i=0; i<N; i++ ) nodes.push_back( Node() );
		
		for( int i=0; i<M; i++ ){
			cin >> a >> b;
			
			V[ a-1 ].push_back( b-1 );
			V[ b-1 ].push_back( a-1 );		
		}
		
	/*	cout << "Oto graf:" << endl;
		for( int i=0; i<V.size(); i++ ){
			cout << "Wierzcholek nr " << i+1 << ":  ";
			for(int k=0; k<V[i].size(); k++){
				cout << V[i][k]+1 << " ";
			}
			cout << endl;
		}*/
		
		result = 0;
		for( int i=0; i<N; i++ ){
			if( ifWas[i] == false && V[i].size() == 0 ) result++;
			else if( ifWas[i] == false && V[i].size() == 1 ){
				maxDegree = 0;
				maxDegIndex = 0;
				getMaxDegree( i,i );
				t = maxDegIndex;		
				DFS( t,t  ); // dla poczatkowego wierzcholka moze byc parent = myNumber - wtedy nie bedzie nieporozumien
		//		cout << "maxDegIndex = " << t+1 << endl;
			//	cout << "Jestem w wierzcholku nr " << i+1 << endl;
				result += nodes[t].min;
			}
			
		//	cout << "i = " << i+1 << "  result = " << result << endl;	
		}
		
		cout << result << endl;
	}
	
	
	
	
	
}
