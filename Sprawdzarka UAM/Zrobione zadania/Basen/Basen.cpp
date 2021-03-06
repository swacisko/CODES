#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int,int> PII;
typedef pair<int, PII> PIPII;

int N,M;
int SUMA_WODY;
int krok_wody;
bool minMogeLac;
int minNeighbour;

const int infinity = ( 31 << 26 );

vector<PIPII> wysokosci;
int wys[100][100];
bool czyMogeLac[100][100];
bool ifWas[100][100];
bool globalIfWas[100][100];

void setMinNeighbour( PII p, int h ){
	if( p.first < N-1 ){
		if( wys[p.first+1][p.second] > h && minNeighbour >= wys[p.first+1][p.second]     ){
			if( minNeighbour > wys[p.first+1][p.second] )	minMogeLac = czyMogeLac[p.first+1][p.second];
			else if( minMogeLac == true ) minMogeLac = czyMogeLac[p.first+1][p.second];
			minNeighbour = wys[p.first+1][p.second];
		}
	}
	
	if( p.first > 0 ){
		if( wys[p.first-1][p.second] > h && minNeighbour >= wys[p.first-1][p.second] ){
			if( minNeighbour > wys[p.first-1][p.second] )	minMogeLac = czyMogeLac[p.first-1][p.second];
			else if( minMogeLac == true ) minMogeLac = czyMogeLac[p.first-1][p.second];
			minNeighbour = wys[p.first-1][p.second];
		}
	}
	
	if( p.second < M-1 ){
		if( wys[p.first][p.second+1] > h && minNeighbour >= wys[p.first][p.second+1]  ){
			if( minNeighbour > wys[p.first][p.second+1] )	minMogeLac = czyMogeLac[p.first][p.second+1];
			else if( minMogeLac == true ) minMogeLac = czyMogeLac[p.first][p.second+1];
			minNeighbour = wys[p.first][p.second+1];
		}
	}
	
	if( p.second > 0 ){
		if( wys[p.first][p.second-1] > h && minNeighbour >= wys[p.first][p.second-1] ){
		 	if( minNeighbour > wys[p.first][p.second-1] )	minMogeLac = czyMogeLac[p.first][p.second-1];
			else if( minMogeLac == true ) minMogeLac = czyMogeLac[p.first][p.second-1];
			minNeighbour = wys[p.first][p.second-1];	
		}
	}
}

void upDFS( PII p, int h){
	czyMogeLac[p.first][p.second] = false;
	
	if( p.first < N-1 ){
		if( wys[p.first+1][p.second] >= h && czyMogeLac[p.first+1][p.second] == true ){
			upDFS( make_pair( p.first+1, p.second ), wys[p.first+1][p.second]  );
		}
	}
	
	if( p.first > 0 ){
		if( wys[p.first-1][p.second] >= h && czyMogeLac[p.first-1][p.second] == true ){
			upDFS( make_pair( p.first-1, p.second ), wys[p.first-1][p.second]  );
		}
	}
	
	if( p.second < M-1 ){
		if( wys[p.first][p.second+1] >= h && czyMogeLac[p.first][p.second+1] == true ){
			upDFS( make_pair( p.first, p.second+1 ), wys[p.first][p.second+1]  );
		}
	}
	
	if( p.second > 0 ){
		if( wys[p.first][p.second-1] >= h && czyMogeLac[p.first][p.second-1] == true ){
			upDFS( make_pair( p.first, p.second-1 ), wys[p.first][p.second-1]  );
		}
	}	
}

void findMinDFS( PII p, int h ){
	setMinNeighbour( p, h );
	ifWas[p.first][p.second] = true;
	
	if( p.first < N-1 ){
		if( wys[p.first+1][p.second] == h && ifWas[p.first+1][p.second] == false ){
			findMinDFS( make_pair( p.first+1, p.second ), wys[p.first+1][p.second]  );
		}
	}
	
	if( p.first > 0 ){
		if( wys[p.first-1][p.second] == h && ifWas[p.first-1][p.second] == false ){
			findMinDFS( make_pair( p.first-1, p.second ), wys[p.first-1][p.second]  );
		}
	}
	
	if( p.second < M-1 ){
		if( wys[p.first][p.second+1] == h && ifWas[p.first][p.second+1] == false ){
			findMinDFS( make_pair( p.first, p.second+1 ), wys[p.first][p.second+1]  );
		}
	}
	
	if( p.second > 0 ){
		if( wys[p.first][p.second-1] == h && ifWas[p.first][p.second-1] == false ){
			findMinDFS( make_pair( p.first, p.second-1 ), wys[p.first][p.second-1]  );
		}
	}
}

void fillDFS( PII p, int h, int upTo ){
	ifWas[p.first][p.second] = true;
	globalIfWas[p.first][p.second] = true;
	krok_wody += upTo - h;
	wys[p.first][p.second] = upTo;
	
	if( p.first < N-1 ){
		if( wys[p.first+1][p.second] == h && ifWas[p.first+1][p.second] == false ){
			fillDFS( make_pair( p.first+1, p.second ), wys[p.first+1][p.second],upTo  );
		}
	}
	
	if( p.first > 0 ){
		if( wys[p.first-1][p.second] == h && ifWas[p.first-1][p.second] == false ){
			fillDFS( make_pair( p.first-1, p.second ), wys[p.first-1][p.second],upTo  );
		}
	}
	
	if( p.second < M-1 ){
		if( wys[p.first][p.second+1] == h && ifWas[p.first][p.second+1] == false ){
			fillDFS( make_pair( p.first, p.second+1 ), wys[p.first][p.second+1],upTo  );
		}
	}
	
	if( p.second > 0 ){
		if( wys[p.first][p.second-1] == h && ifWas[p.first][p.second-1] == false ){
			fillDFS( make_pair( p.first, p.second-1 ), wys[p.first][p.second-1],upTo  );
		}
	}
	
}

void execute( PII p ){
	//znajduje podgraf o minimalnej wysokosci
	minMogeLac = true;
	minNeighbour = infinity;
	for( int i=0; i<N; i++  ) for( int k=0; k<M; k++ ) ifWas[i][k] = false;
	findMinDFS( p, wys[p.first][p.second] );
	
	// teraz wypelniam dany podgraf
	krok_wody = 0;
	for( int i=0; i<N; i++  ) for( int k=0; k<M; k++ ) ifWas[i][k] = false;
	fillDFS( p, wys[p.first][p.second], minNeighbour );
	
	// jesli musze, to jade upDFSem
	if( minMogeLac == false ) upDFS( p, wys[p.first][p.second] );
	
	SUMA_WODY += krok_wody;	
//	cout << "Zaczynam w punkcie " << p.first << " " << p.second << endl << "\tkrok_wody = " << krok_wody << "  SUMA_WODY = " << SUMA_WODY << "  minNeighbour = " << minNeighbour << "  minMogeLac = " << minMogeLac << endl;
}

void wypiszBasen(){
	cout << endl;
	
	for( int i=0; i<N; i++ ){
		for( int k=0; k<M; k++ ){
			if( czyMogeLac[i][k] == false ) cout << "X ";
			else cout << wys[i][k] << " ";
		}
		cout << endl;
	}
	
	cout << endl;
}	


int main(){
	
	int h,a,b;
	
	int l_zest;
	cin >> l_zest;
	while( l_zest-- ){
		cin >> N >> M;
		wysokosci.clear();
		SUMA_WODY = 0;
		
		for( int i=0; i<N; i++ ){
			for( int k=0; k<M; k++ ){
				cin >> h;
				wys[i][k] = h;
				wysokosci.push_back( make_pair( h, make_pair( i,k ) ) );
				czyMogeLac[i][k] = true; // przypisuje od razu
				globalIfWas[i][k] = false;
			}
		}
		
		for( int i=0; i<N; i++ ){
			for( int k=0; k<M; k++ ){
				if( ( i == 0 || i == N-1 || k == 0 || k == M-1 ) && czyMogeLac[i][k] == true ){
					upDFS( make_pair( i,k ), wys[i][k] );
				}			
			}
		}
		
		// skonczylem rozchodzic sie po brzegach
		
		sort( wysokosci.begin(), wysokosci.end() );
		
		for( int i=0; i<wysokosci.size(); i++ ){  // UWAGA, TUTAJ TRZEBA TO ZMAPOWAC, MOZE SIE OKAZAC, ZE PO fillDFS NIE ZACZNIEMY OD NAJNIZSZEGO!!!
			a = wysokosci[i].second.first;
			b = wysokosci[i].second.second;
			h = wysokosci[i].first;
			
			
			if( czyMogeLac[a][b] == true && globalIfWas[a][b] == false ){
			//	wypiszBasen();
				execute( make_pair(a,b) );				
			}
		}
		
		cout << SUMA_WODY << endl;
		
	} // koniec whilea
	
}




