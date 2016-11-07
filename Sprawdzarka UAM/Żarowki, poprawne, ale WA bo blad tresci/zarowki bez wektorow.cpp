#include<stdio.h>

#define infinity 100000000
int N,M;

class Node{
public:
	Node(){
		on = 1;
		lighted = 1;
		off = 0;
		hasLeafSon = false;
	}
	
	int on;
	int lighted;
	int off;
	bool hasLeafSon;
};

int ile[10010];
int aktSize[10010];
int inp[10010][2];
int **tab;
bool ifWas[10010];

Node nodes[10010];

int minfun( int a, int b ){
	if( a <= b ) return a;
	else return b;
}

int minTrippleFun( int a, int b, int c ){
	return minfun( a, minfun( b,c ) );
}

int getOn( int index, int parent ){
	int m = 0;
	for( int i=0; i<aktSize[index]; i++ ){
		if( tab[index][i] != parent ){
			m += minTrippleFun( nodes[ tab[index][i] ].on, nodes[ tab[index][i] ].lighted, nodes[ tab[index][i] ].off );
		}
	}
	
	m++;	
	return m;
}

int getLighted( int index, int parent ){
	int m = 0;
	int diff = infinity;
	
	for( int i=0; i<aktSize[index]; i++ ){
		if( tab[ index ][i] != parent ){
			m += minfun( nodes[ tab[index][i] ].on, nodes[ tab[index][i] ].lighted );
			
			if( nodes[ tab[index][i] ].on <= nodes[ tab[index][i] ].lighted ) diff = 0;
			else if( nodes[ tab[index][i] ].on - nodes[ tab[index][i] ].lighted < diff ) diff = nodes[ tab[index][i] ].on - nodes[ tab[index][i] ].lighted;		
		}
	}
	
	if( diff >= 0 )m += diff;
	else while(true);
	return m;	
}

int getOff( int index, int parent ){
	int m = 0;
	for( int i=0; i<aktSize[index]; i++ ){
		if( tab[index][i] != parent ){
			m += nodes[ tab[index][i] ].lighted;
		}
	}
	
	return m;	
}

void DFS( int index, int parent ){
	bool hasLeafSon = false;
	ifWas[ index ] = true;
	
	
	
	if( aktSize[ index ] == 1 && index != parent ){
		nodes[index].on = 1;
		nodes[index].lighted = 1;
		nodes[index].off = 0; 
	}
	else{
		
		for( int i = 0; i<aktSize[index]; i++ ){
			if( tab[index][i] != parent && aktSize[ tab[index][i] ] == 1 ) hasLeafSon = true;
			
			if( tab[index][i] != parent ){
				DFS( tab[index][i], index );
			}
		}
		
		nodes[index].on = getOn( index, parent );
		nodes[index].lighted = getLighted( index, parent );
		nodes[index].off = getOff( index, parent );
		
		if( hasLeafSon == true ){
			nodes[index].off = infinity;
		}	
	}
	
//	printf( "Jestem w DFS, index = %d   parent = %d  \n\t on = %d, lighted = %d,  off = %d \n\n", index+1, parent+1, nodes[index].on, nodes[index].lighted, nodes[index].off );
	
}


int main(){
	int t,a,b;
	int result;
	
	int l_zest;
	scanf( "%d", &l_zest );
	while( l_zest-- ){
		scanf( "%d %d", &N, &M );
		
		for( int i=0; i<N; i++ ){
			aktSize[i] = 0;
			nodes[i] = Node();
			ifWas[i] = false;
		}
		for( int i=0; i<M; i++ ){
			ile[i] = 0;
		}
		
		for( int i = 0; i<M; i++ ){
			scanf( "%d %d", &a, &b );
			inp[i][0] = a-1;
			inp[i][1] = b-1;
			ile[a-1]++;
			ile[b-1]++;
		}
		
		tab = new int*[N];
		for( int i=0; i<N; i++ ){
			tab[i] = new int[ ile[i] ];
			for( int k=0 ;k<ile[i]; k++ ){
				tab[i][k] = 0;
			}
		}
		
		for( int i=0; i<M; i++ ){
			tab[ inp[i][0] ][ aktSize[ inp[i][0] ] ] = inp[i][1];
			aktSize[ inp[i][0] ]++;
			tab[ inp[i][1] ][ aktSize[ inp[i][1] ] ] = inp[i][0];
			aktSize[ inp[i][1] ]++;
		}
		
	/*	printf("\n");
		for( int i=0; i<N; i++ ){
			printf("%d --> ",i+1);
			for(int k=0; k<aktSize[i]; k++){
				printf( "%d ", tab[i][k]+1 );
			}
			printf("\n");
		}*/
		
		// tutaj mam juz skonczone wczytywanie
		
		result = 0;		
		
		for( int i=0; i<N; i++ ){			
			if( (ifWas[i] == false ) && aktSize[i] == 0 ){
				ifWas[i] = true;
				result++;
			}
			else if( ifWas[i] == false ){
				DFS( i,i );
				result += minfun( nodes[i].on, nodes[i].lighted );
			}			
		}
		
		printf( "%d \n",result );
		
		for( int i=0; i<N; i++ ) {
			delete[] tab[i];
			tab[i] = 0;
		}
		delete[] tab;
		tab = 0;
		
	} // koniec whilea
	
	
}











