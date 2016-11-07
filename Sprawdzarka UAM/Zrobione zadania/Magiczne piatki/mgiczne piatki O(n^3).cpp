#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define PB push_back
#define ST first
#define ND second

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector< vector<int> > VVI;
typedef vector< PII > VPII;
typedef vector< VPII > VVPII;

VVI V;
VVPII vec;
int N,M;
int suma[200];
int tab1[200][200];
int tab2[200][200];

int fun( int A, int B, int C, int F ){	
	return suma[C] - tab2[C][B] + tab1[C][F] + tab1[C][A]*tab1[A][B] - tab2[C][F] + tab1[C][A] + tab1[C][B] - tab2[C][A] + tab1[C][F] + tab1[C][B]*tab1[B][A] - tab1[C][F]*( V[F].size()-1 ) 
			- tab1[C][A]*( V[A].size()-1 ) - tab1[C][B]*( V[B].size()-1 );
}

void wypiszGraf( VVI &K ){
	cout << endl;
	for( int i=0; i<K.size(); i++ ){
		for( int k=0; k<K[i].size(); k++ ){
			cout << K[i][k] << " - ";
		}
		cout << endl;
	}
}

void wypiszTab1(){
	cout << endl;
	for( int i=0; i<N; i++ ){
		for(int k=0; k<N; k++ )cout << tab1[i][k] << " ";
		cout << endl;
	}
}

void wypiszTab2(){
	cout << endl;
	for( int i=0; i<N; i++ ){
		for(int k=0; k<N; k++ )cout << tab2[i][k] << " ";
		cout << endl;
	}
}

void wypiszSumy(){
	cout << endl;
	for( int i=0; i<N; i++ ){
		cout << " i = " << i << "  " << suma[i] << endl;
	}
}

void wypiszDrogi(){
	cout << endl;
	for( int i=0; i<vec.size(); i++ ){
		for( int k=0; k<vec[i].size(); k++ ){
			cout << i << "  " << vec[i][k].ST << "  " << vec[i][k].ND << endl;
			
		}
	}
}

int main(){
	
	int l_zest;
	int a,b,x,y;
	int A,B,C,F;
	int K;
	
	cin >> l_zest;
	
	while(l_zest--){
		V.clear();
		vec.clear();
		
		cin >> N >> M;
		
		for( int i=0; i<N; i++ ) V.PB( VI(0) );
		for( int i=0; i<N; i++ ) suma[i] = 0;
		for( int i=0; i<N; i++ ) vec.PB( vector< PII >(0) );
		for( int i=0; i<N; i++ ) for( int k=0; k<N; k++ ) tab1[i][k] = 0;
		for( int i=0; i<N; i++ ) for(int k=0; k<N; k++) tab2[i][k] = 0;
		
		
		
		for( int i=0; i<M; i++ ){
			cin >> a >> b;
		//	cout << "a = " << a << "  b = " << b << " !!!" << endl;
			V[ a-1 ].PB( b-1 );
			V[ b-1 ].PB( a-1 );
			
		//	wypiszGraf( V );
		}
		
		
		for( int i=0; i<N; i++ ){
			for( int k=0; k<V[i].size(); k++ ){
				tab1[i][ V[i][k] ] = 1;
			}
		}
		
	//	wypiszTab1();
		
		int sum = 0;
		for( int i=0; i<N; i++ ){
			for( int k=0; k<N; k++ ){				
				if( i == k ) continue;
				
				sum = 0;
				for( int j=0; j<V[k].size(); j++ ){
					sum += tab1[i][ V[k][j] ];					
				}
				
				tab2[i][k] = sum;
			}		
		}
		
	//	wypiszTab2();
		
		for( int i=0; i<N; i++ ){
			for( int k=0; k<V[i].size(); k++ ){
				K = V[i][k];
				if( i == K ) continue;				
				
				for( int j=0; j<V[K].size(); j++ ){
					if( V[K][j] == i ) continue;
					
					x = K;
					y = V[K][j];
					
					vec[i].PB( make_pair( x,y ) );					
				}				
			}			
		}
		
	//	wypiszDrogi();
		
		sum = 0;
		for( int i=0; i<N; i++ ){
			sum = 0;
			for( int k=0; k<N; k++ ){
				sum += tab2[i][k];
			}			
			suma[i] = sum;			
		}
		
	//	wypiszSumy();
		
		int piatki = 0;
		int t = 0;
		
		for( int i=0; i<N; i++ ){
			for(int k=0; k<V[i].size(); k++ ){
				for( int j=0; j<vec[i].size(); j++ ){					
					A = i;
					C = V[i][k];
					F = vec[i][j].ST;
					B = vec[i][j].ND;
					
					if( F == A || B == C || F == C ) continue;
					
					t = fun( A,B,C,F );
					piatki += t > 0 ? t : 0;
				//	cout << "A = " << A << "  C = " << C << "  F = " << F << "  B = " << B << "  t = " << t << endl;
				}				
			}			
		}
		
	//	piatki *= 2;
		
		cout << piatki << endl;
		
	} // koniec whilea
	
	
}



