#include<iostream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
#define FORD( x,y ) for( int x=y; x>=0; --x )

#define PB push_back
#define PH push_heap
#define POPB pop_back
#define MP make_pair
#define POPH pop_heap
#define ST first
#define ND second

int N,M,a,b;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

vector< pair<double, int> > priorytety;  // ST- stosunek zajetych krawedzi do krawedzi zajetych prze jasia
										// czyli 1 + zajetePrzezMalgosie / ZajetePrzezJAsia
VVI V; // graf
int ile_zajetych[315];
int ile_zajetych_przez_jasia[315];
map< PII,int> mapa;
VI maxy;

bool zajeta[315][315];
VPII zagrania; // zagrania[i] - i-ta krawedz ktora malgosia chce zajac
VPII vec; // vec[i] = krawedz numer i


void clearAll(){
	priorytety.clear();
	REP(i,N) priorytety.PB( MP( 0,i ) );
	
	mapa.clear();
	
	REP(i,N) ile_zajetych[i] = 0;
	REP(i,N) ile_zajetych_przez_jasia[i] = 0;
	
	V.clear();
	REP( i,N ) V.PB( VI() );
	
	zagrania.clear();
	
	vec.clear();
	
	maxy.clear();
	
	REP(i,N){
		REP(k,N) zajeta[i][k] = false;		
	}
}

void wypiszKrawedzie(){
	cout << "Wypisuje krawedzie:" << endl;
	REP(i,vec.size()){
		cout << "Krawedz nr "<< i+1 << ":  " << vec[i].ST+1 << " " << vec[i].ND+1 << endl;
	}
}/*
void wypiszMape(){
	cout << endl << "Wypisuje mape:" << endl;
	for( map<PII,int>::iterator it = mapa.begin(); it!=mapa.end(); it++ ){
		cout << "Krawedz nr " << it->ND+1 << " " << it->ST.ST+1 << " " << it->ST.ND+1 << endl;
	}
	
}

void wypiszWierzcholek( int pos ){
	cout << endl;
	cout << "\tNumer: " << priorytety[pos].ND+1 << endl;
	cout << "\tStosunek malgosi do jasia: " << priorytety[pos].ST << endl;	
}
	
void wypiszPriorytety(){
	REP(i,N){
		cout << "Priorytet nr "<< i+1 << " ";
		wypiszWierzcholek( i );
	} 
}*/

int main(){
	
	ios_base::sync_with_stdio(0);
	
	int index=0, index2=0;
	int d=0;
	int t;
	double max = 0, max2 = 0;
	bool wypisal = false;
	
	int l_zest=0;
	cin >> l_zest;
	while( l_zest-- ){
		
		cin >> N >> M;		
		clearAll();
		
		REP( i,M ){
			cin >> a >> b;
			
			vec.PB( MP(a-1,b-1) );
			
			mapa.insert( MP( MP(a-1,b-1), i ) );
			mapa.insert( MP( MP(b-1,a-1), i ) );
			
			V[a-1].PB(b-1);
			V[b-1].PB(a-1);
		}
		
	//	wypiszKrawedzie();
	//	wypiszMape();
		
		
		REP( i,M ){
			cin >> a;
			zagrania.PB( MP( vec[a-1].ST, vec[a-1].ND ) );			
		}
		
		REP(i,M){
			if( zajeta[ zagrania[i].ST ][ zagrania[i].ND ] == true ) continue;
			
			zajeta[ zagrania[i].ST ][ zagrania[i].ND ] = true;
			zajeta[ zagrania[i].ND ][ zagrania[i].ST ] = true;
			
	//		cout << endl << "Malgosia zajmuje krawedz nr " << mapa.find( MP(zagrania[i].ST,zagrania[i].ND  ) )->ND+1 << endl;
			
			ile_zajetych[ zagrania[i].ST ]++;
			ile_zajetych[ zagrania[i].ND ]++;
			
	//		REP(j,N) cout << "ile_zajetych["<<j+1<<"] = "<< ile_zajetych[j] << "  ile_zajetych_przez_jasia["<<j+1<<"] = " << ile_zajetych_przez_jasia[j] << endl;
			
			REP( k,N ){ 
			
					priorytety[k].ST = ( double ) ( ile_zajetych[ k ] / (0.0001 + ile_zajetych[k] + ile_zajetych_przez_jasia[ k ] ) );

				
			}
			
			
	//		cout << endl << "Zagrania["<<i+1<<"].ST="<<zagrania[i].ST+1<< "  zagrania["<<i+1<<"].ND="<<zagrania[i].ND+1 << endl;
	//		wypiszPriorytety();
			
			max = 0;
			index = 0;
			
			REP( k,N ){
				if( priorytety[k].ST > max && ile_zajetych[k] != V[k].size() ){
					maxy.clear();
					maxy.PB( k );
					max = priorytety[k].ST;
					index = k;
				}
				else if( priorytety[k].ST == max && ile_zajetych[k] != V[k].size() ){
					maxy.PB( k );
				}
				
			} // po tej petli w tablicy maxy bede mial wszystkie wierzcholki o maxymalnym zagrozeniu
			
			
			
	//		cout << endl << "\tWierzcholek o najwiekszym zagrozeniu:";
	//		wypiszWierzcholek(index);
	
			index2 = index = 0;
			max = 0;
			t = 0;
			wypisal = false;
			
				REP(k,maxy.size()){
					REP( j, V[ maxy[k] ].size() ){
						if( priorytety[ V[ maxy[k] ][j] ].ST > max && zajeta[ maxy[k] ][ V[maxy[k]][j] ] == false ){
							max = priorytety[ V[ maxy[k] ][j] ].ST;
							index = maxy[k];
							t = j;
						}
					}
				}
				
				
				
		//		cout << endl << "index = " << index+1 << "  drugi wierzholek =  "<< V[index][t]+1 << endl;
				
				wypisal = false;
					if( zajeta[ index ][ V[index][t] ] == false ){
						zajeta[ index ][ V[index][t] ] = true;
						zajeta[ V[index][t] ][ index ] = true;
						
						ile_zajetych[ index ]++;
						ile_zajetych[ V[index][t] ]++;
						
						ile_zajetych_przez_jasia[ index ]++;
						ile_zajetych_przez_jasia[ V[index][t] ]++;
						
						d = ( mapa.find( MP( index, V[index][t] ) )->ND );
						cout << d+1 << " ";
						wypisal = true;
	//					cout << endl << "Zajmuje krawedz "<< d+1 << ":  "<< vec[d].ST+1 << " "<< vec[d].ND+1 << endl;
					//	break;
					}
				
				
				if( wypisal == false ){
					REP( k,M ){
					if( zajeta[ zagrania[k].ST ][ zagrania[k].ND ] == false ){
						zajeta[ zagrania[k].ST ][ zagrania[k].ND ] = true;
						zajeta[ zagrania[k].ND ][ zagrania[k].ST ] = true;
						
						ile_zajetych[ zagrania[k].ST ]++;
						ile_zajetych[ zagrania[k].ND ]++;
						
						ile_zajetych_przez_jasia[ zagrania[k].ST ]++;
						ile_zajetych_przez_jasia[ zagrania[k].ND ]++;
						
						cout << k+1 << " ";
	//					cout << endl << "Wszystkie krawedzie dla danego weirzcholka sa juz zajete"<< endl;
						break;
					}
					}
				}
			
			
		//	cout << endl << endl << endl;
		}
		
		cout << endl;
	}
	
	
	
}
