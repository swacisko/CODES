//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
//#include<conio.h>

using namespace std;

#define REP( x,y ) for( int x=0; x<(y); x++ )
#define FORD( x,y,z ) for( int x=y; x>=(z); x-- )
#define FOR(x,b,e) for( int x = b; x <= (e); ++x )
#define SIZE(v) (int)v.size()
#define ALL(c) c.begin(),c.end()
#define VAR(v,n) __typeof(n) v=(n)
#define FOREACH(i,c) for( VAR(i,c.begin());i!=c.end();++i )
#define PB push_back
#define MP make_pair
#define ST first
#define ND second
#define WRITE( V ){ FOREACH(it,V) cout << *it << ", "; cout << endl; }
#define WRITE_ALL(V) {  REP( i,SIZE(V) ){ cout  << i << " ---- ";  FOREACH(it,V[i]) cout << *it << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
//int N,M,K,a,b,c,y,t,w,l_zest;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef vector< VD > VVD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef long long LL;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;
typedef vector< VPII > VVPII;


int Z;
VI pauza; // pazua[i] to numer tury, w ktorej pauzuje i-ty zespol
VI revpauza; // revpauza[i] to numer zepsolu, ktory zauzuje w i-tej turze
VB was;

VVPII ans;

void parzyste(){
	
	
	int ile = 0;
	int minpauza = INF;
	REP(i,Z){
		if( pauza[i] < Z && pauza[i] >= 0 ) ile++;
		if( pauza[i] >= 0 ) minpauza= min( pauza[i], minpauza );
	}
	
	if( ile == 0 || (ile == 1 && minpauza >= Z-1) ){ // no wlasnie, jak to zrobic, gdy sa same zera??
		VPII M;
		int p,q;
				
		p = Z-2;
		q = 1;
		while(p>q){
			M.PB( MP(p,q) );
			p--;
			q++;			
		}
		
		cout << Z-1 << endl;
		REP(i,Z-1){
			cout << Z/2 << " " << Z << "-" << i+1  << " " ;
			REP(k,Z/2 - 1){
				int x = i + M[k].ST;
				x %= (Z-1);
				x++;
				
				int y = i + M[k].ND;
				y %= (Z-1);
				y++;
				
				cout << x << "-" << y << " ";
			}
			cout << endl;
		}
		
		return;
	}
	
	
	REP(i,Z){
		if( pauza[i] > Z ) pauza[i] = -1;
	}
	
//	cout << "ile = " << ile << endl;
		
	if( ile <= Z/2 ){
		REP(i,Z) if( pauza[i] == Z ){ pauza[i] = -1; revpauza[Z] = -1; }
		
		
		VPII M1, M2;
		int p = Z-1;
		int q = 1;
		REP(i,(Z/2)-1){
			M1.PB( MP( p,q ) );
			p--;
			q++;			
		}
		
		p = Z-1;
		q = 0;
		REP(i,Z/2){
			M2.PB( MP(p,q) );
			p--;
			q++;			
		}
		
		
		VI perm(Z);
		p = 0;
		REP(i,Z){
			if( pauza[i] != -1 ) perm[i] = p++;
		}
		REP(i,Z){
			if( pauza[i] == -1 ) perm[i] = p++;
		}
		
	//	cout << "perm" << endl;
	//	REP( i, SIZE(perm) ) cout << perm[i] + 1 << " ";
	//	cout << endl;
		
		
		VI revperm(Z);
		REP(i,Z) revperm[ perm[i] ] = i;
		
		
		int rest = 0;
		int x,y;
		int a = -1;
		cout << Z << endl;
		REP( i,Z ){
			a = -1;
			if( revpauza[i] != -1 ){
				a = revpauza[i];
				was[a] = true;				
			}
			else{				
				REP( k,Z ) if( !was[k] && pauza[k] == -1 ){
					a = k;
					was[a] = true;
					break;
				}					
			}
			
		//	cout << "a = " << a+1 << endl;
			if( pauza[a] == -1 && rest < Z/2 ){
				was[a] = true;
				cout << Z/2 << " ";
				REP( k,Z/2 ){
					//x = -1 + rest + M2[k].ST;
				//	cout << "perm[" << rest + 1 <<"] = " << perm[rest]+1 << "   M2[" << k << "] = " << M2[k].ST+1 << "," << M2[k].ND+1 << endl;
					x = revperm[ (rest + M2[k].ST) % Z ];
					x %= Z;
					x++;
					
					//y = -1 + rest + M2[k].ND;
					y = revperm[ (rest + M2[k].ND) % Z ];
					y %= Z;
					y++;
					cout << x << "-" << y << " ";
				}
				cout << endl;			
				
				rest++;
			}
			else{
				cout << (Z/2)-1 << " ";
				REP( k, SIZE(M1) ){
					//x = a + M1[k].ST;
					x = revperm[ (perm[a] + M1[k].ST) % Z ];
					x %= Z;
					x++;
					
					//y = a + M1[k].ND;
					y = revperm[ (perm[a] + M1[k].ND) % Z ] ;
					y %= Z;
					y++;
					
					cout << x << "-" << y << " ";
				}				
				cout << endl;
				
			}
			
		}
				
	}
	else{
		VPII M3;
		
		int p = (Z/2) - 1;
		int q = p+1;		
		REP( i,Z/4 ){
			M3.PB( MP(p,q) );
			p--;
			q++;
		}
		
		q++;
		while( q<Z ){
			M3.PB( MP(p,q) );
			p--;
			q++;	
		}
		
	//	cout << "M3: SIZE = " << SIZE(M3) << endl;
	
		
		int a = -1;
		int rest = 1;
		int x,y;
		
		cout << Z+1 << endl;
		REP( i,Z+1 ){
			a = -1;
			if( revpauza[i] != -1 ){
				a = revpauza[i];
				was[a] = true;
			//	cout << "\t\tznalazlem a = " << a << endl;			
			}
			else{				
				REP( k,Z ) if( !was[k] && pauza[k] == -1 ){
					a = k;
					was[a] = true;
					break;
				}					
			}
			
			if( a == -1 || ( pauza[a] == -1 && rest == 1 ) ){
				if( a != -1 ) was[a] = false;
				rest++;
				cout << Z/2 << " ";
				REP(k,Z/2){
					cout << k+1 << "-" << k+1 + Z/2 << " ";					
				}
				cout << endl;
			}
			else{
		//		cout << "here" << endl;
				cout << SIZE(M3) << " ";
				REP( k, SIZE(M3) ){
					x = a + M3[k].ST;
					x %= Z;
					x++;
					
					y = a + M3[k].ND;
					y %= Z;
					y++;
					
					cout << x << "-" << y << " ";
				}
				cout << endl;				
			}			
		}		
	}
	
	
	
	
	
	
}

void nieparzyste(){
	VPII M;
	int p = Z-1;
	int q = 1;
	REP(i,Z/2){		
		M.PB( MP( p,q ) );
		p--;
		q++;		
	}
	
	int a = -1;
	
	REP(i,Z){
		if( pauza[i] >= Z ) pauza[i] = -1;
	}
	
	cout << Z << endl;
	REP(i,Z){
		a = -1;
		if( revpauza[i] != -1 ){
			a = revpauza[i];
			was[a] = true;		
		}
		else{
			REP( k,Z ) if( !was[k] && pauza[k] == -1 ){
				a = k;
				was[a] = true;
				break;
			}
		}
		
	//	cout << "a = " << a << endl;
		int x,y;
		cout << Z/2 << " ";
		REP(k,SIZE(M)){
			x = a+M[k].ST;
			x %= Z;
			x++;
			y = a+M[k].ND;
			y %= Z;
			y++;			
			
			cout << x << "-" << y << " ";
		}
		cout << endl;		
	}
	
	
}




int main(){
	ios_base::sync_with_stdio(0);
//	cout << fixed;
//	cout.precision(2);

    cin >> Z;
    pauza = VI(Z);
    revpauza = VI(Z+1);
    was = VB(Z,false);
    ans = VVPII(Z+1);
    
    REP(i,Z){    	
    	cin >> pauza[i]; 
		pauza[i]--;  	
	}
	
	//cout << Z << endl;
	//REP(i,Z) cout << pauza[i]+1 << endl;
	
	fill( ALL(revpauza),-1 );
	REP(i,Z) if( pauza[i] <= Z && pauza[i] >= 0 ) revpauza[ pauza[i] ] = i;
	
	//cout << "pauza" << endl;
//	WRITE(pauza);
//	cout << "revpauza" << endl;
//	WRITE(revpauza);
	
    
    if( Z % 2 == 0 ) parzyste();
    else nieparzyste();


	return 0;
}












