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
};

VVI V;
vector<Node> nodes;
bool ifWas[10000];

int getOnStatus( int parent, int myNumber ){
	int m = 0;
	for( int i=0; i<V[myNumber].size(); i++ ){
		if( V[myNumber][i] != parent ){
			m += min( nodes[ V[myNumber][i] ].min, nodes[ V[myNumber][i] ].off );			
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
	
	if( V[myNumber].size() == 0 || ( V[myNumber].size() == 1 && parent != myNumber  )   ){ // jesli jest lisciem
		n.on = 1;
		n.lighted = 1;
		n.off = 0;
		n.diff = 0;
		n.min = 1;
	}
	else{
		
		for( int i=0; i<V[myNumber].size(); i++ ){
			if( ifWas[ V[myNumber][i] ] == false ){
				DFS( myNumber, V[myNumber][i] );
			}			
		}
		
		int on = getOnStatus( parent, myNumber );
		int lighted = getLightedStatus( parent, myNumber );
		int off = getOffStatus( parent, myNumber );
				
		n.on = on;
		n.lighted = lighted;
		n.off = off;		
		n.diff = on-lighted>0 ? on-lighted : infinity; // jesli on < lighted, to roznica i tak nie bedzie nam potrzebna
		n.min = min( on, lighted );
				
	}
	
//	cout << "number: " << myNumber << "  on = " << n.on << "  lighted = " << n.lighted << "  off = " << n.off << "  diff = " << n.diff
//		<< "  min = " << n.min << endl;
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
	
	int l_zest;
	cin >> l_zest;
	
	while( l_zest-- ){
		
		cin >> N >> M;
		
		zerujWszystkieTablice();
		
		for( int i=0; i<M; i++ ){
			cin >> a >> b;
			
			V[ a-1 ].push_back( b-1 );
			V[ b-1 ].push_back( a-1 );		
		}
		
		int result = 0;
		for( int i=0; i<N; i++ ){
			if( ifWas[i] == false ){				
				DFS( i, i  ); // dla poczatkowego wierzcholka moze byc parent = myNumber - wtedy nie bedzie nieporozumien
				result += nodes[i].min;
			}		
		}
		
		cout << result << endl;
		
		
	}
	
	
	
	
	
}







