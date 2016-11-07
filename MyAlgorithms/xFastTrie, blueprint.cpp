//#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<map>
//#include<complex>
//#include<stack>
//#include<list>
#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<ctime>
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


template<class _Key, class _Value>
class HTNode{
	public:
	HTNode( _Key k, _Value v ) : key(k), value(v) {
	}
	
	_Key key;
	_Value value;	
};


template<class _Key, class _Value>
ostream & operator<<( ostream& str, HTNode<_Key,_Value> & node ){
	str << "key = " << (int) node.key << "         value = " << (int)node.value;; 
	return str;	
}


template<class _Key, class _Value>
class HashTable{
	typedef HTNode<_Key, _Value> NKV;
	typedef vector< NKV* > VN;
	typedef vector< VN > VVN;
	#define HASHCODE(key,num) (int)key%functions[num]
	
public:
	
	HashTable( int maxSize = 1000000, int tableQuantity = 3 ): Q(maxSize), hQuant(tableQuantity), size(0) {
		if( tableQuantity == 2 ) FACTOR = 4;
		else if(tableQuantity == 3 ) FACTOR = 2;
		else FACTOR = 1.5;
		
		createTables();
		cout << "Stworzylem tablice hashujaca" << endl;
		ENDL(1);
		
	}
	
	// checks whether a given number is prime...
	bool isPrime( int p ){
		if( p%2 == 0 ) return false;
		for( int i = 3; i*i <= p; i+=2 ){
			if( p%i == 0 ) return false;
		}
		return true;
	} 

	// returns lowest prime number greater or equal to bound / bound must be greater than 2
	int getLowerPrime( int bound ){
		int p = (bound%2 == 0) ? bound-1 : bound;
		while( !isPrime(p) ) p--;
		return p;
	}
	
	void createTables(){
		tables = VVN(hQuant, VN( FACTOR*Q ) );
		REP(i,SIZE(tables)) REP(k,SIZE(tables[i])) tables[i][k] = 0;
		functions = VI(hQuant);
		int p = FACTOR*Q+1;
		REP(i,hQuant){
			p = getLowerPrime(p);
			functions[i] = p;
			p--;
		}		
	}
	
	// return hashedCode of element with key key produced by hNum function
	// CAUSION - requires parsing from key to int    (int)key
	int getHashCode( _Key key, int hNum ){
		return ((int)key) % functions[ hNum ];		
	}
	
	
	// pushes further from table number hNum an element pointed by node or alocates this element if there is free space
	// returns true if i can allocate the element or false if there is a cycle...
	bool relocate( int hNum, NKV* node, int counter ){
		if( counter > 300 ){ cout << "PETLA w relocate!! " << endl; return false; }
		int h = 0;
		if( tables[hNum][ h = HASHCODE(node->key, hNum ) ] == 0 ){ // tutaj moze byc rownie dobrze getHashCode, ale zrobilem makro, szybciej
			//cout << "relocate, h = " << h << endl;
			tables[hNum][h] = node;
			size++;
		}
		else if( tables[hNum][h]->key != node->key ){ // if there is a different value, i have to relocate it...
			swap( node, tables[hNum][h] );
			if( relocate( (hNum+1)%hQuant, node, counter+1 ) == false ) return false;
		}		
		
		return true;
	}
	
	bool insert( NKV* node ){
		if( find(node->key) != 0 ) return false;
		return relocate( 0, node, 0 );
	}
	
	bool insert( _Key key, _Value value ){
		return insert( new NKV(key,value) );
	}
	
	// return pointer to element with key key or NULL if there is no such element
	NKV* find( _Key key ){
		int h = 0;
		REP( i, hQuant ){
			h = HASHCODE( key,i ); // tutaj moze byc rownie dobrze getHashCode, ale zrobilem makro, szybciej
			if( tables[i][h] != 0 && tables[i][h]->key == key ){
				return tables[i][h];				
			}
		}
		return 0;
	}
	
	// erases all elements with key matching to parameter key
	bool erase( _Key key ){
		int h = 0;
		bool found = false;
		REP( i, hQuant ){
			h = HASHCODE( key,i ); // tutaj moze byc rownie dobrze getHashCode, ale zrobilem makro, szybciej
			if( tables[i][h] != 0 && tables[i][h]->key == key ){
				delete tables[i][h];
				tables[i][h] = 0;
			//	cout << "\t\t  key " << key << " erased succesfully" << endl;
				size--;
				found = true;			
			}
		}
		return found;	
	}
	
	
	void writeTables(){
		REP(i,hQuant){
			cout << "Table nr " << i << endl;
			REP(k,SIZE(tables[i])){
				if( tables[i][k] == 0 ) cout << "k = " << k << "    --> NULL" << endl;
				else cout << "k = " << k << "   -->  " << (*tables[i][k]) << endl;
			}
			cout << endl << endl;;
		}		
	}
	
	void writeFunctions(){
		REP(i,hQuant){
			cout << "Function nr " << i << " to liczba " << functions[i] << endl;			
		}		
	}

	int Q; // it is the number of queries - if we want to insert at most Q elements from certain range
	
	int hQuant; // this number denotes the numbver of hash tables i use in hashing...
	VI functions; // functions is the vector of primes for which we take modulo operations... these are hashing functions...
	VVN tables; // these are my hash tables...
	double FACTOR;
	
	int size; // this is the number of elements stored in hash tables...
	
};




//*****************************************************   TUTAJ SIE ZACZYNA IMPLEMENTACJA MOJEGO WLASNEGO xFastTrie

typedef int _T;
const int USIZE = 31; // number of bits in stored numbers, 32 for int and 64 for long long

struct xFastNode{
	
	xFastNode(  ){
		
	}
	
	xFastNode *par, *left, *right, *pred, *succ; // wskazniki na lewego i prawego syna oraz nastepnika i poprzednika w drzewie xFast	
	_T value; //value is the real value of the number stored int this node
	
	// the node is a leaf iff it has no sons
	bool isLeaf(){
		return left == 0 && right == 0;
	}
	
};

struct xFast{
	
	typedef xFastNode XFN;
	
	HashTable<_T,XFN* > hash;
	
	// N is here the maximum number of elements i will store in the tree, necessary only for the hashtable to be built reasonably
	xFast( int N ){
		hash = HashTable< _T,XFN* >(N*log(N)); // NlgN is the number of elements that will be stored in hashtable
	}
	
	// inserts element to the xFastTrie
	void insert( _T val ){
		
	}
	
	//deletes element from xFastTrie
	void Delete( _T val ){
		
	}
	
	// return a pointer to the node in the tree with the longest common prefix with val
	// int firstDifferentBit return the first bit on which fragment of val cannot be extended to longer prefix
	//
	// e.g. in trie there are nodes 10-1001-01-1-100  and val = 1010010010    then k = 2, because its second bit (counted from back) cannot be
	// added to form the longer prefix (lcp = 1010010)
	XFN* getLongestPrefix( _T val, int & firstDifferentBit ){
		int p=0, q=USIZE, k; // I need to select quickly in O(1) first k digits of number val
		do{
			k = (p+q)/2;
			if( hash.find( val >> k ) != 0 ){ // if in the tree there is already value val>>k, i decrease k 
				k = q-1;
			}
			else{
				k = p+1;
			}
			
			
		}while( p < q );
		
		return 0; // temporary to compile
	}
	
	// return pointer to the successor of element with key val
	XFN* Successor( _T val ){
		int firstDifferentBit;
		XFN* lcp = getLongestPrefix(val,firstDifferentBit);
		
		return 0;
	}
	
	// return the pointer to the predecessor of element with key val
	XFN* Predecessor( _T val ){
		return Successor(val)->left;		
	}
	
	
	
};



int main(){
	ios_base::sync_with_stdio(0);
	srand( unsigned(time(0)));
	cout << fixed;
	cout.precision(10);
	
	
	
	
	


	return 0;
}




