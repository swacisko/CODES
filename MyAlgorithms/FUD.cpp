//#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>

using namespace std;

#define REP( x,y ) for( int x=0; x<y; x++ )
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
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest,d;
const long double EPS = 1e-11;
typedef vector<double> VD;
typedef pair<double,int> PDI;
typedef pair<double, double> PDD;
typedef vector<bool> VB;
typedef vector<int> VI;
typedef vector< VI > VVI;
typedef pair<int,int> PII;
typedef long long LL;
typedef pair<LL,LL> PLL;
typedef vector<LL> VLL;
typedef vector<VLL> VVLL;
typedef vector<PII> VPII;

// this structure will represent the nodes of my FUDTree
struct Node{ // the nodes key is of type _T
	Node( int value ) : val(value), rank(1) { 
		reset();
	}
	Node *par, *left, *right, *son; // necessary pointers, son is a pointer
	int val; // number stored in the node
	int rank; // number of elements in the tree to which belongs (*this) - must be checked as find(*this)->rank
	
	void reset(){ // resets everything except value, this will be useful in delete operation
			rank = 1;
			par = son = 0;
			left = right = this;
	}
	bool isRoot(){
		return par == 0;
	}
	bool isLeaf(){
		return son == 0;
	}	
	void writeNode(){
		cout << "val = " << val << "\tpar = " << ( par == 0 ? -1 : par->val ) << "\tright = " << right->val
			<< "\tleft = " << left->val << "\tson = " << ( son == 0 ? -1 : son->val ) << endl;
	}
};


// my Find-Union-Delete structure
// stores elements indexed form 0 to N-1
struct FUD{
	FUD( int aN ) : N(aN) {
		nodes = vector< Node* >(N);
		REP(i,N) nodes[i] = new Node(i);
		
		
	}
	
	vector<Node*> nodes; // table of pointers to nodes
	int N; // number of elements
	
	/*// detaches from parent and attaches to grandparent
	void detachToGrandparent( Node* p ){
		if( p == 0 || p->isRoot() || p->par->isRoot() ) return; // if my parent is a root, then i cannot do anything		
		Node* par = p->par;
		
		p->right->left = p->left; // i change the layer of p
		p->left->right = p->right;
		
		par->right->left = p; // i change the layer of par
		p->right = par->right;
		par->right = p;
		p->left = par;
		
		p->par = par->par;
		p->par->son = p;	// this isnt necessary, but with this son pointer points always to the rightest of its sons
	}
	
	// splits path - attaches p to its grandparent, if it exists and doeas the same for all vertices on the way to the root
	void splitPath( Node* p ){
		if( p == 0 || p->isRoot() ) return;
		while( !p->par->isRoot() ){
			Node* par = p->par;
			detachToGrandparent(p);
			splitPath(par);
		}
	}*/
	
	// detaches from parent and attaches to the root of the tree, both p and root must be given as a parameter
	void detachToRoot( Node* p, Node* root ){
		if( p == 0 || p->isRoot() || p->par->isRoot() ) return;
		
		Node* par = p->par;
		
		p->right->left = p->left; // i change the layer of p
		p->left->right = p->right;
		if( p->par->son == p ){
			if( p->left == p ) p->par->son = 0;
			else p->par->son = p->left;
		}
		
		if( root->isLeaf() ){
			return;
		}
		
		par = root->son;
		par->right->left = p; // i change the layer of par
		p->right = par->right;
		par->right = p;
		p->left = par;
		
		p->par = root;
		root->son = p; // this isnt necessary, it is only to reduce possible time for delete operation...
		//	but with this code  son pointer points always to the rightest of its sons
	}
	
	// return the pointer to the root of the tree
	// during the find operation i do path splitting - i detach all elements on the path to root
	Node* Find( Node* p ){
		if( p->isRoot() ) return p;
		Node* rt = Find( p->par );
		detachToRoot(p,rt);
		return rt;
	}
	
	// return the number of set, to which p belongs
	int Find( int p ){
		return Find( nodes[p] )->val;
	}
	
	//return the leaf which is a son of node p, or return p if p is a leaf;
	Node* getLeaf( Node* p ){
		while( !p->isLeaf() ) p = p->son;
		return p;		
	}
	
	
	// deletes number p from its set // pessimistic time O(lgN)
	void Delete( int p ){		
		Node* leaf = getLeaf( nodes[p] );
		
		Find(leaf)->rank--;
		
		leaf->right->left = leaf->left; // i change the layer of the leaf
		leaf->left->right = leaf->right;
		
		swap( leaf->val, nodes[p]->val );
		swap( nodes[ leaf->val ], nodes[ nodes[p]->val ] );
		
		if( leaf->par != 0 && leaf->par->son == leaf ){
			if( leaf->left == leaf ) leaf->par->son = 0;
			else leaf->par->son = leaf->left;
		}
		leaf->reset();
	}
	
	void Union( int p, int q ){
		Node* rootP = Find( nodes[p] );
		Node* rootQ = Find( nodes[q] );
		
		if( rootP == rootQ ) return;
		
		if( rootP->rank > rootQ->rank ) swap( rootP, rootQ ); // i want to attach rootP to rootQ ans therefore rank(Q) must be geq to rank(P)
		rootQ->rank += rootP->rank; // i increase the rank of the greater tree
		
		if( rootQ->isLeaf() ) {rootQ->son = rootP; rootP->par = rootQ; return;} // if a want to union two one-point trees i have to check this
		Node* s = rootQ->son;
		s->right->left = rootP;
		rootP->right = s->right;
		s->right = rootP;
		rootP->left = s;
		
		rootP->par = rootQ;
		rootQ->son = rootP;
	}
	
	
	void writeTree(){
		REP(i,N){
			cout << "Element " << i << ":\t";
			nodes[i]->writeNode();
		}
	}
	
};




void testFUD(){
	
	cout << "How many elements do you want to store in Find-Union-Delete structure?\t";
	int N;
	cin >> N;
	FUD fud(N);
	
	while( true ){
		cout << "1. Find" << endl << "2.Union" << endl << "3.Delete" << endl << "4.Write Tree" << endl;
		int opt,a,b;
		cin >> opt;
		switch( opt ){
			case 1:{
				cout << endl << "Which element to find? Enter it:\t";
				cin >> a;
				b = fud.Find(a);
				cout << endl << "Element " << a << " nalezy do drzewa o numerze " << b << endl;
				break;
			}
			case 2:{
				cout << endl << "Which elements do you want to union? Enter them:\t";
				cin >> a >> b;
				fud.Union( a,b );
				cout << "Union of elements " << a << " and " << b << " made" << endl;
				break;
			}
			case 3:{
				cout << endl << "Wchich element to delete? Enter it:\t";
				cin >> a;
				fud.Delete(a);
				cout << "Element " << a << " deleted" << endl;
				break;
			}
			case 4:{
				fud.writeTree();
				break;
			}			
			default:{
				
			}
		}
		
	}
		
	
}


void testFUDtime(){
	
	const int N = 10000;
	const int OPERATIONS = 1000000;
	
	
	FUD fud(N);
	int t0 = clock();
	int a=1,b;
	REP(i,OPERATIONS){
		if( (d = rand()%3 )== 0 ){ // find
			//cout << "find " << (d = rand()%N) << endl;
			d = rand()%N;
			a = fud.Find( d );
		}
		else if( d == 1 ){ // union
			//cout << "union " << (a=rand()%N) << " " << (b = rand()%N) << endl;
			a = rand()%N, b = rand()%N;
			fud.Union( a,b );
		}
		else{ // delete
			//cout << "delete " << (d = rand()%N )<< endl;
			d = rand()%N;
			fud.Delete( d );
		}
		
	//	fud.writeTree();
	}
	
	int t1 = clock();
	double Tfud;
	cout << "Wykonanie " << OPERATIONS << " operacji na FUD o rozmiarze " << N << " zajelo " << (Tfud = (double) ( t1-t0 ) / CLOCKS_PER_SEC )
		<< " sekund" << endl;
		
		
	
	
	set<int> zb;
	
	REP(i,N>>1) zb.insert(i);
	t0 = clock();
	REP( i,OPERATIONS ){
		if( (d = rand()%3 )== 0 ){ // find
			b = rand()%N;
			a = zb.count( b );
		}
		else if( d == 1 ){
			b = rand()%N;
			zb.insert( b );
		}
		else{ // delete
			b = rand()%N;
			zb.erase( b );
		}		
	}	
	
	t1 = clock();
	double Tset;
	cout << "Wykonanie " << OPERATIONS << " operacji na set<int> zajelo " << (Tset = (double) ( t1-t0 ) / CLOCKS_PER_SEC )
		<< " sekund" << endl;
		
	cout << "Czyli FUD dziala " << Tset / Tfud << " razy szybciej niz set" << endl;
	
}




int main(){
	
	testFUDtime();
	testFUD();
	
	
	
	
	
	return 0;
}


/*
10
2
0 1
2
2 3
2
4 5
2
6 7
4
2
0 2
4
2
0 7
4
*/





