#include<iostream>
#include<string>
using namespace std;

int N;
string znaki;
int tab[501][501];

inline int max( int a, int b ){
	return a > b ? a : b;
}

void solve( int pocz, int kon, char c ){
	if( pocz == kon ){
		tab[pocz][kon+1] = ( znaki[pocz]==c ? 1 : 0 );
		return;
	}
	
	int M = 0;
	
	for( int k=pocz; i<=kon; i++ ){
		if( znaki[i] == c ){
			
			if( i == pocz ){
				M = max( M, tab[i+1][kon] + 1 );
			}
			else if( i == kon ){
				M = max( M, tab[pocz][i-1] + 1 );
			}
			else{
				M = max( M, tab[pocz][i-1] + tab[i+1][kon] + 1 );
			}
		}
	}
	
	M = max( M, tab[pocz][kon] );
	
	tab[pocz][kon+1] = M;
	
}

int main(){
	int l_zest;
	char c;
	
	cin >> l_zest;
	while(l_zest--){		
		cin >> znaki;
	//	for(int i=0; i<znaki.size(); i++) cout << i;
	//	cout << endl << endl;
		
		
		N = znaki.size();
		for( int i=0; i<N; i++ ){
			for(int k=0; k<N; k++){
				tab[i][k] = 0;
			}
		} 
		
		for( int i=1; i<N; i++ ){
			c = znaki[i];
			for(int k=0; k<i; k++){
				solve( k,i-1,c );
			//	cout << "k=" << k << "  i=" << i << "tab[k][i]=" << tab[k][i] << endl;
			}
		}
		
		cout << N - 2*tab[0][N-1] << endl;
		
	}
	
	
	
	
}
