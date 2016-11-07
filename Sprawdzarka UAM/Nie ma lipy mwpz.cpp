#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<cmath>
#include<queue>
#include<string.h>
#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( long long x=0; x<(y); x++ )
#define FORD( x,y,z ) for( long long x=y; x>=(z); x-- )
#define FOR(x,b,e) for( long long x = b; x <= (e); ++x )
#define SIZE(v) (long long)v.size()
#define PB push_back
#define PH push_heap
#define POP pop_back
#define MP make_pair
#define ST first
#define ND second

long long N,M,K,a,b,c,y,t,p,w,l_zest;
const long long INF = 1000000001;
typedef vector<double> VD;
typedef pair<double,long long> PDI;
typedef pair<double, double> PDD;
typedef vector<long long> VI;
typedef vector< VI > VVI;
typedef pair<long long,long long> PII;
typedef vector<PII> VPII;
typedef map< PII, bool > MPIIB;
typedef long long LL;





int main(){
	ios_base::sync_with_stdio(0);
	
	long long T,E;
	PII *czas; // moc, kalorie
	vector< pair< long long, PII > > exerc; // czas, moc , kalorie
	
	cin >> T >> E;
	
	czas = new PII[T+1];
	REP( i,T+1 ) czas[i].ST = czas[i].ND = 0; // czy tu moze byc zero?
	
	exerc.clear();
	REP(i,E){
		cin >> t >> p >> c;
		exerc.PB( MP( t,MP(p,c) ) );
	}
	
	REP( i,E ){
		FORD(k,T,0){
			if( czas[k].ST != 0 ){	
				if( exerc[i].ST + k > T );			
				else if( czas[ k + exerc[i].ST ].ST < czas[k].ST + exerc[i].ND.ST ){
					czas[ k + exerc[i].ST ].ST = czas[k].ST + exerc[i].ND.ST;
					czas[ k + exerc[i].ST ].ND =  czas[k].ND + exerc[i].ND.ND;			
				}
				else if( czas[ k + exerc[i].ST ].ST == czas[k].ST + exerc[i].ND.ST ){
					czas[ k + exerc[i].ST ].ND = max( czas[k+exerc[i].ST].ND, czas[k].ND + exerc[i].ND.ND );
				}
			}			
		}
		
		if( exerc[i].ST > T );			
		else if( czas[ exerc[i].ST ].ST < exerc[i].ND.ST ){
			czas[ exerc[i].ST ].ST = exerc[i].ND.ST;
			czas[ exerc[i].ST ].ND =  exerc[i].ND.ND;			
		}
		else if( czas[ exerc[i].ST ].ST == exerc[i].ND.ST ){
			czas[ exerc[i].ST ].ND = max( czas[ exerc[i].ST ].ND, exerc[i].ND.ND );
		}		
	}
	
//	REP(i,T+1) cout << "czas["<<i<<"] = " << czas[i].ST << " <- moc , kalorie->" << czas[i].ND << endl; 
	
	long long maxi = -1;
	long long C = -1;
	REP(i,T+1){
		if( czas[i].ST > maxi ){
			maxi = czas[i].ST;
			C = czas[i].ND;			
		}
		else if( czas[i].ST == maxi ) C = max( C, czas[i].ND ); // tu wyznaczam potrzebne mi kalorie
	}
	
	long long F,D;
	long long f;
	
	cin >> F >> D;
	
	VPII dania;
	dania.clear();
	REP(i,D){
		cin >> c >> f;
		dania.PB( MP( c,f ) );
	}
	
//	cout << "Jestem po wczytaniu dan" << endl;
	long long** sposoby;
	sposoby = new long long*[5001];
	REP(i,5001) sposoby[i] = new long long[F+1];
	REP( i,5001 ){
		REP(k,F+1) sposoby[i][k] = 0;
	}
	
	long long ILE = 0;
	
//	cout << "Jestem przed ostatnia petla" << endl;
	
//	cout << "P = " << maxi << "   C = " << C << "   F = " << F  << "  ILE = " << ILE << endl;

	if( C == 0 ) ILE++;
	
	REP( t,dania.size() ){
		FORD( i,5000,0 ){
			FORD( k,F,0 ){	
				if( sposoby[i][k] != 0 ){		
				//	cout << "i = " << i << "  k = " << k << "  sposoby["<<i<<"]["<<k<<"] = " << sposoby[i][k] << "  dania[t] = " << dania[t].ST << " , " << dania[t].ND << endl;			
					if( i + dania[t].ST < C && k + dania[t].ND <= F ){
						sposoby[ i + dania[t].ST ][ k + dania[t].ND ] += sposoby[i][k];
					}
					else if( i + dania[t].ST >= C && k + dania[t].ND <= F ){
					//	cout << "\tZwiekszam ILE o sposoby["<<i<<"]["<<k<<"] = " << sposoby[i][k] << endl;
						sposoby[ i + dania[t].ST ][ k + dania[t].ND ] += sposoby[i][k];
						ILE += sposoby[i][k];
						ILE %= 15483359;
					}
				}
			}
		}
		if( dania[t].ST >= C && dania[t].ND <= F ){
			ILE++;
		//	cout << "\tZwiekszam ILE o 1" << endl;
			sposoby[ dania[t].ST ][ dania[t].ND ]++;
		}
		else if( dania[t].ST < C && dania[t].ND <= F ) sposoby[ dania[t].ST ][ dania[t].ND ]++;
	}
	
	cout << ILE%15483359 << endl;
	
/*	cout << endl;
	REP(i,C+13){
		REP( k,F+1 ){
			cout << "sposoby["<<i<<"]["<<k<<"] = " << sposoby[i][k] << endl;
		}
		cout << endl;
	}*/
	
	return 0;
}











