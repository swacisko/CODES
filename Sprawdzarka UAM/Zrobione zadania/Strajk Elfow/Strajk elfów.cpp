#include<iostream>
#include<vector>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
#define PB push_back


int N,M,a,b,p,K;
typedef vector<int> VI;




int main(){
	
	VI rows; // ile juz jest w danym rzedzie
	VI cols;
	bool czy_dalej;
	
	int l_zest;
	cin >> l_zest;
	
	while(l_zest--){
		
		cin >> N >> K >> p;
		
		rows.clear();
		cols.clear();
		REP(i,N)cols.PB(0);
		REP(i,K)rows.PB(0);
		
		czy_dalej = true;
		
		REP(i,p){
			cin >> a;
			
			if( czy_dalej == true ){
				rows[ cols[a-1] ]++;
				cols[a-1]++;
				
			//	REP(k,N) cout << cols[k] << " ";
			//	cout << endl;
			//	REP(k,K) cout << rows[k] << " ";
			//	cout << endl << endl;
				
				if( rows[0] == N ){
					rows.erase( rows.begin() );
					rows.PB(0);
					
					REP(k,N) cols[k]--;
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



