#include<iostream>
#include<string>
#include<vector>
using namespace std;

int N;
string znaki;
int tab[501][501];
vector< vector<int> > V(200);

inline int max( int a, int b ){
	return a > b ? a : b;
}

void solve( int pocz, int kon, char c ){
	if( pocz == kon ){
		tab[pocz][kon+1] = ( znaki[pocz]==c ? 1 : 0 );
		return;
	}
	
	int M = 0;
	
	for( int k=0; V[c][k] <= kon; k++ ){
		int i = V[c][k];
		
		if( i < pocz ) continue;
			
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
	
	M = max( M, tab[pocz][kon] );
	
	tab[pocz][kon+1] = M;
	
}

int main(){
	ios_base::sync_with_stdio(0);
	
	int l_zest;
	char c;
	
	cin >> l_zest;
	while(l_zest--){		
		cin >> znaki;
		
		int t = 1;
		char prev = znaki[0];
		while( t < znaki.size() ){
			if( znaki[t] == prev ){
				znaki.erase( znaki.begin()+t );
				t--;
				znaki.erase( znaki.begin()+t );
				if( t > 0 )prev = znaki[t-1];
				else prev = '0';
			}
			else{
				prev = znaki[t];
				t++;
			}
			
		//	cout << znaki << endl;
		}
		
	//	cout << endl;
		
		while( znaki[0] == znaki[ znaki.size()-1 ] && znaki.size()>2 ){
			znaki = znaki.substr( 1, znaki.size()-2 );
	//		cout << znaki << endl;
		}
		
		
		
		N = znaki.size();
	//	for(int i=0; i<znaki.size(); i++) cout << i;
	//	cout << endl << endl;
		for( int i=65; i<=90; i++ ) V[i].clear();
	
		for( int i=0; i<N; i++ ){
			V[ (int)znaki[i] ].push_back( i );
		}
		
		
		
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
