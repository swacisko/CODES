#include<iostream>
#include<vector>
#include<map>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
#define PB push_back
#define MP make_pair

int N,M,a,b,p,K;
typedef vector<int> VI;
map<int,bool> mapa;



int main(){
	
//	VI rows; // ile juz jest w danym rzedzie
	VI cols;
	bool czy_dalej;
	
	int l_zest;
	cin >> l_zest;
	
	while(l_zest--){
		
		cin >> N >> K >> p;
		
//		rows.clear();
		cols.clear();
		REP(i,N)cols.PB(0);
//		REP(i,K)rows.PB(0);
		
		czy_dalej = true;
		
		REP(i,p){
			cin >> a;
			
			if( czy_dalej == true ){
//				rows[ cols[a-1] ]++;
				cols[a-1]++;
				
				if( mapa.find( a-1 ) != mapa.end() ) mapa.insert( MP( a-1, false ) );
				
			//	REP(k,N) cout << cols[k] << " ";
			//	cout << endl;
			//	REP(k,K) cout << rows[k] << " ";
			//	cout << endl << endl;
				
				if( mapa.size() == N ){
					mapa.clear();
					REP(i,N) cols[i]--;
					
					REP( i,N ){
						if( cols[i] > 0 ) mapa.insert( MP( i,false ) );
					}
				}
				
				if( cols[a-1] > N ){
					czy_dalej = false;
				}
				
				
				
				
			}
		}
		
		if( czy_dalej == true ) cout << "TAK" << endl;
		else cout << "NIE" << endl;
		
	}
		
	return 0;	
}



