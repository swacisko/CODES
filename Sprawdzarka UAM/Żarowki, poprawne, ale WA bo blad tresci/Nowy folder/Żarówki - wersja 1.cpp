#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

int N,M;
typedef vector<vector<int> > VVI;
typedef vector<int> VI;
const int infinity = ( 31 << 26 );


int min( int a, int b ){
	return a<b?a:b;
}
int max( int a, int b ){
	return a>b?a:b;
}

class Node{
public:
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
bool ifWas[10000];

int getOnStatus( int parent, int myNumber ){
	int m = 0;
	for( int i=0; i<V[myNumber].size(); i++ ){
		if( V[myNumber][i] != parent ){
			m += min( nodes[ V[myNumber][i] ].lighted, nodes[ V[myNumber][i] ].off );			// UWAGA, TUTAJ ROZNE WERSJE !!!
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
			if( ifOneIsOn == false && nodes[ V[myNumber][i] ].min == nodes[ V[myNumber][i] ].on ) ifOneIsOn = true;
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
	Node &n = nodes[myNumber]; // nie pamietam czy tak to dziala
	n.hasLeafSon = false;
	
	if( V[myNumber].size() == 0 || ( V[myNumber].size() == 1 && parent != myNumber  )   ){ // jesli jest lisciem
		n.on = 1;
		n.lighted = 1;
		n.off = 0;
		n.diff = 0;
		n.min = 1;
		n.isLeaf = true;
	}
	else{
		
		for( int i=0; i<V[myNumber].size(); i++ ){
			if( ifWas[ V[myNumber][i] ] == false ){
				DFS( myNumber, V[myNumber][i] );
				if( nodes[ V[myNumber][i] ].isLeaf == true ) n.hasLeafSon = true;
			}			
		}
		
		int on = getOnStatus( parent, myNumber );
		int lighted = getLightedStatus( parent, myNumber );
		int off = getOffStatus( parent, myNumber );
		
		if( n.hasLeafSon ){
			n.isLeaf = false;
			off = infinity;
		} 
		n.on = on;
		n.lighted = lighted;
		n.off = off;		
		n.diff = on-lighted>0 ? on-lighted : 0; 
		n.min = min( on, lighted );
				
	}
	
//	cout << "Oto ja!\n\tMy number is " << myNumber << endl << "\t" << nodes[myNumber] << endl;
}

void zerujWszystkieTablice(){
	V.clear();
	nodes.clear();
		
	for( int i=0; i<N; i++ ) ifWas[i] = false;		
	for( int i=0; i<N; i++ ) V.push_back( VI() );
	for( int i=0; i<N; i++ ) nodes.push_back( Node() );
}

int main(){
	
	ios_base::sync_with_stdio(0);
	int a, b;
	int result;
	
	int l_zest;
	cin >> l_zest;
	
	while( l_zest-- ){
		
		cin >> N;
		if( N > 0 ) {
			cin >> M;
		}
		
		zerujWszystkieTablice();
		
		for( int i=0; i<M; i++ ){
			cin >> a >> b;
			
			V[ a-1 ].push_back( b-1 );
			V[ b-1 ].push_back( a-1 );		
		}
		
		result = 0;
		for( int i=0; i<N; i++ ){
			if( ifWas[i] == false ){				
				DFS( i, i  ); // dla poczatkowego wierzcholka moze byc parent = myNumber - wtedy nie bedzie nieporozumien
				result += nodes[i].min;
			}		
		}
	/*	
		int *zaczynajacOd = new int[N];
		int res2 = 0;
		for( int k=0; k<N; k++ ){
			for( int i=0; i<N; i++ ) ifWas[i] = false;
			DFS( k,k );			
			zaczynajacOd[k] = nodes[k].min;	
		}
		
		for( int i=0; i<N; i++ ){
			cout << "Zaczynjac od " << i << ": \t" << zaczynajacOd[i] << endl;
		}*/
		
		cout << result << endl;
		
		
	}
	
	
	
	
	
}
