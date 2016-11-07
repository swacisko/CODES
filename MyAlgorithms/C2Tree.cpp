//#include<stdio.h>
#include<iostream>
#include<vector>
//#include<string>
//#include<map>
//#include<complex>
//#include<stack>
//#include<list>
//#include<bitset>
//#include<set>
//#include<iterator>
#include<cmath>
//#include<queue>
//#include<time.h>
//#include<string.h>
//#include<fstream>
//#include<sstream>
#include<algorithm>
#include<iomanip>

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
#define WRITE_ALL(V,s,t) { cout << s << endl;  REP( i,SIZE(V) ){ cout  << i+1 << " ---- ";  FOREACH(it,V[i]) cout << *it+t << ", "; cout << endl;     } }
#define WRP(p) p.ST << " " << p.ND
#define CLEAR( dst,quant ) memset( dst,0, (quant)*sizeof( __typeof(*dst) ) );
#define WAR if( show_help )
#define ENDL(x) REP(crow,(x)) cout << endl;

const bool show_help = 1;
const int INF = 1000000001;
int N,M,K,a,b,c,y,t,w,l_zest;
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



//*******************************************************************************************************   C2Tree

//*******************************************************************************************************   C2Tree

//*******************************************************************************************************   C2Tree
// drzewko dwuwymiarowe - wszystkie wezly drzewa C2Tree sa drzewkami przedziałowymi jednowymiarowymi
// drzewko wspiera operacje
// ADD - dodaje do kazdego kwadraciku w prostokacie [a,b]x[c,d] pewna wartosc
// FINDSUM - zwraca sume elementow na danym prostokacie
// ISCOVERED - sprawdza, czy wszystkie elementy na danym prostokacie sa juz pokryte
// wszystko dziala na wskaznikach, aby moc stworzyc takie drzewo dla dowolnie duzej mapy - na statycznej tablicy potrzebowalibysmy bowie O(N^2) pamieci

typedef int _T;
typedef pair<_T,_T> PTT;
#define NRPK ( ( node->p + node->k ) >> 1 )

struct C1Tree{
	
	struct Node{
		Node( _T pp, _T kk ) :p(pp), k(kk), cov(0),sum(0), covered(false) {
			left = right= 0;
		}
				
		Node *left, *right;
		_T p,k; // p and k are the beginning and end of the represented interval
		int cov; // cov is the number of intervals added to the tree, which cover this node
		int sum; // sum is the sum o values sum of its sons. Total sum on the given subtree is then sum + (k-p+1)*cov
		bool covered; // covered is true if both its sons are covered...
		//_T _min; // min is the minimum value of element in the interval represented by its subtrees. So min in node is equal min + cov
	};
	
	
	C1Tree( _T NN ) : N(NN){
		_T s = 1;
		while( s <= N ) s <<= 1;
		root = new Node( 0, s-1 );
		
	}
	
	_T N; // this should be the maximum number i want to store in the tree - if i can add every int, then N = 1<<32;
	_T PP,KK,ILE; // theese are auxiliary integers to add intervals
	Node* root;
	
	
	// function creates sons of given node, if necessary
	void createSons( Node* node ){
		if( node->left == 0 ){
			node->left = new Node( node->p, NRPK );
		}
		if( node->right == 0 ){
			node->right = new Node( NRPK + 1, node->k );
		}
	}
	
	void helpADD( Node* node ){
		
		if( KK < node->p || PP > node->k ) return; // if [PP,KK] is disjoint with node
		if( PP <= node->p && KK >= node->k ){ // if whole node is covered by the interval [PP,KK]
			node->cov += ILE;
			return;
		}
		
		createSons(node);
		
		helpADD( node->left );
		helpADD( node->right );
		
		node->sum = node->left->sum + ( ( node->left->k - node->left->p + 1 ) * ( node->left->cov ) ); // SUM UPDATE for left son
		node->sum += node->right->sum + ( ( node->right->k - node->right->p + 1 ) * ( node->right->cov ) ); // SUM UPDATE for right son
		
		node->covered = ( node->right->covered || node->right->cov > 0 ) && ( node->left->covered || node->left->cov > 0 );
	}
	
	// I add ile to each element of the interval [p,k]
	void ADD( _T p, _T k, _T ile = 1 ){
		ILE = ile;
		PP = p;
		KK = k;
		helpADD(root);
	}
	
	// return the sum on inteval [PP,KK];
	_T helpFINDSUM( Node* node ){
		if( KK < node->p || PP > node->k ) return 0; // if [PP,KK] is disjoint with node
		if( PP <= node->p && KK >= node->k ) {// if whole node is covered by the interval [PP,KK]
				return node->sum + (  (node->k - node->p + 1)*(node->cov)  );
		}
		
		_T leftval = 0, rightval = 0;		// i will return sum on two subtrees
		if( node->left != 0 ) leftval = helpFINDSUM( node->left );		
		if( node->right != 0 ) rightval = helpFINDSUM( node->right );
		
		int overlap = min( KK, node->k ) - max( PP, node->p ) + 1;
		return leftval + rightval + overlap * ( node->cov );
	}
	
	// function returns sum on given interval
	_T FINDSUM( _T p, _T k ){
		PP = p, KK = k;
		return helpFINDSUM( root );
	}
	
	// this function unfortunately can add O(lgN) nodes to the tree :(
	bool helpISCOVERED( Node *node ){
		if( KK < node->p || PP > node->k || node->cov > 0 ) return true; // if [PP,KK] is disjoint with node
		//if( PP >= node->p && KK <= node->k && node->cov > 0 ) return true;
		if( PP <= node->p && KK >= node->k ) {// if whole node is covered by the interval [PP,KK]
				return node->covered || node->cov > 0;
		}
		
		createSons( node );
		
		return helpISCOVERED( node->left ) && helpISCOVERED(node->right);		
	}
	
	//function checks whether there are some intervals in the tree which cover the interval [p,k]
	bool ISCOVERED( _T p, _T k ){
		PP = p, KK = k;
		return helpISCOVERED(root);		
	}
	
	void writeTree( Node *node, int d = 0 ){
		REP(i,d) cout << "\t";
		cout << "[" << node->p << ", " << node->k << "]   cov = " << node->cov << "    sum = " << node->sum;
		if( node->left == 0 ) cout << "   no left son";
		if( node ->right == 0 ) cout << "   no right son";
		cout << endl;
		
		if( node->left != 0 ) writeTree(node->left,d+1);
		if( node->right != 0 ) writeTree(node->right,d+1);
	}
	
	
};


//******************************************************************C2Tree
//******************************************************************C2Tree
//******************************************************************C2Tree
//******************************************************************C2Tree



struct C2Tree{
	
	struct Node{
		Node( _T NN, _T pp, _T kk ) : p(pp), k(kk) {
				leftSon = new C1Tree( NN );
				rightSon = new C1Tree(NN);
				treeMe = new C1Tree(NN);
		}
		
		C1Tree *leftSon, *rightSon, *treeMe; // treeSons will be affected by every operation on a subinterval of [p,k], treeMe only by those operations
								// which cover interval [p,k]
		_T p,k;
		Node *left, *right;
	};
	
	C2Tree( _T x, _T y ) : N(x){
		s = 1;
		while( s <= N ) s <<= 1;
		root = new Node( s,0,s-1 );
		s = 1;
		while( s <= y ) s <<= 1;
		s--;
	}
	
	_T N,s, PP,KK, ILE;
	PTT YY;
	Node *root;
	
	
	void createSons( Node *node ){
		if( node->left == 0 ){
			node->left = new Node( s, node->p, NRPK );
		}
		if( node->right == 0 ){
			node->right = new Node( s, NRPK + 1, node->k );
		}
	}
	
	
	// UWAGA NA RAZIE NIE DZIALA ALBO DZIALA TYLKO DLA POJEDYNCZYCH PUNKTOW!!   TRZEBA COS DODAZ Z    OVERLAP ABY DZIALALO
	void helpADD( Node *node ){
		if( KK < node->p || PP > node->k ) return; // if [PP,KK] is disjoint with node
		if( PP <= node->p && KK >= node->k ){ // if whole node is covered by the interval [PP,KK] the i affect treeMe
			node->treeMe->ADD( YY.ST, YY.ND, ILE );
			return;
		}
		
		node->leftSon->ADD( YY.ST, YY.ND, ILE ); // otherwise i affect treeSons
		node->rightSon->ADD( YY.ST, YY.ND, ILE ); // otherwise i affect treeSons
		
		createSons(node);
		
		helpADD( node->left );
		helpADD( node->right );
		
	}
	
	void ADD( PTT x, PTT y, _T ile = 1 ){
		PP = x.ST, KK = x.ND, ILE = ile;
		YY = y;
		helpADD( root );
	}
	
	
	// UWAGA NA RAZIE NIE DZIALA ALBO DZIALA TYLKO DLA POJEDYNCZYCH PUNKTOW!!   TRZEBA COS DODAZ Z    OVERLAP ABY DZIALALO
	_T helpFINDSUM( Node *node ){
	//	cout << "I am in helpFINDSUM X = " << node->p << "," << node->k << "]" << endl;
		
		if( KK < node->p || PP > node->k ) return 0; // if [PP,KK] is disjoint with node
		if( PP <= node->p && KK >= node->k ) {// if whole node is covered by the interval [PP,KK] i return the sum of what has happend to me ans my sons
		//		cout << "Y = [" << YY.ST << "," << YY.ND << "]    leftSon->FINDSUM = " << node->leftSon->FINDSUM(YY.ST,YY.ND)
		//				<< "   rightSon->FINDSUM = " << node->rightSon->FINDSUM(YY.ST,YY.ND)
		//				<< "    treeMe->FINDSUM = " << node->treeMe->FINDSUM(YY.ST, YY.ND) << endl;
				return (node->leftSon->FINDSUM(YY.ST,YY.ND) + node->rightSon->FINDSUM(YY.ST,YY.ND) ) /** ( ( node->k - node->p + 1 ) >> 1 )*/
					+ node->treeMe->FINDSUM(YY.ST,YY.ND) * ( node->k - node->p + 1 );
		}
		
		_T leftval = 0, rightval = 0;
		if( node->left != 0 ) leftval = helpFINDSUM( node->left );
		if( node->right != 0 ) rightval = helpFINDSUM( node->right );
		
		int overlap = min( KK, node->k ) - max( PP, node->p ) + 1;
		
		return overlap * node->treeMe->FINDSUM( YY.ST, YY.ND ) + leftval + rightval;
	}
	
	_T FINDSUM( PTT x, PTT y ){
		PP = x.ST, KK = x.ND;
		YY = y;
		return helpFINDSUM( root );
	}
	
	bool helpISCOVERED( Node *node ){
		if( KK < node->p || PP > node->k || node->treeMe->ISCOVERED(YY.ST,YY.ND) ) return true; // if [PP,KK] is disjoint with node
		if( PP <= node->p && KK >= node->k ) {// if whole node is covered by the interval [PP,KK] 
				return node->leftSon->ISCOVERED(YY.ST,YY.ND) && node->rightSon->ISCOVERED(YY.ST,YY.ND);
		}
		
		createSons(node);
		
		return helpISCOVERED(node->left) && helpISCOVERED( node->right );
	}
	
	bool ISCOVERED( PTT x, PTT y ){
		PP = x.ST, KK = x.ND, YY=y;
		return helpISCOVERED(root);		
	}
	
	// UWAGA - ta funkcja rysuje pelna mape rozmiaru N x N
	void writeTree(){
		REP(i,N+1){
			REP(k, root->treeMe->N ){
				cout << setw(3) << FINDSUM( MP(i,i), MP(k,k) ) << flush;
			}
			cout << endl;
		}
		
	}

};


//****************************************************************  TESTING !!

void testC1Tree(){
	
	cout << "Enter upper boundary for your elements:\t";
	int N;
	cin >> N;
	
	C1Tree tree(N);
	
	_T a,b,ile;
	
	while( true ){
		cout << "1. Add" << endl << "2. FINDSUM" << endl << "3.ISCOVERED" << endl << "4. Write tree" << endl;
		cin >> N;
		switch(N){
			case 1:{
				cout << "Enter interval [a,b] you want to add to the tree and its quantity:\t";
				cin >> a >> b >> ile;
				tree.ADD(a,b,ile);
				cout << ile << " intervals [" << a << "," << b << "] were added to the tree" << endl;
				break;
			}
			case 2:{
				cout << "Enter interval [a,b] for which you want to find sum:\t";
				cin >> a >> b;
				ile = tree.FINDSUM(a,b);
				cout << "Sum of elements on the interval [" << a << "," << b << "] equals   " << ile << endl;
				break;
			}
			case 3:{
				cout << "Enter interval [a,b] you want to check whether it is covered:\t";
				cin >> a >> b;
				bool bl = tree.ISCOVERED(a,b);
				cout << "Interval [" << a << "," << b << "] " << ( bl?" is covered" : " is NOT covered" ) << endl;
				
				break;
			}
			case 4:{
				tree.writeTree( tree.root );
				break;
			}		
			default:{
				
			}
		}		
	}	
}


void testC2Tree(){
	
	cout << "Enter the boundaries of your map" << endl;
	cout << "x <= ?\t";
	int X,Y,a,b,c,d;
	cin >> X;
	cout << "y <= ?\t";
	cin >> Y;
	
	
	C2Tree tree(X,Y);
	
	while(true){
		cout << "1. ADD" << endl << "2.FINDSUM" << endl << "3.ISCOVERED" << endl << "4.Write Tree" << endl;
		int opt,ile;
		cin >> opt;
		switch(opt){			
			case 1:{
				cout << "\t\tADD OPTION" << endl;
				cout << "Enter X = [a,b]\t";
				cin >> a >> b;
				cout << "Enter Y = [c,d]\t";
				cin >> c >> d;
				cout << "Enter quantity\t";
				cin >> ile;
				tree.ADD( MP(a,b), MP(c,d),ile );
				cout << "I added " << ile << " to every element of square [" << a << "," << b << "] x [" << c << "," << d << "]" << endl;
				break;
			}
			case 2:{
				cout << "FINDSUM OPTION" << endl;
				cout << "Enter X = [a,b]\t";
				cin >> a >> b;
				cout << "Enter Y = [c,d]\t";
				cin >> c >> d;
				
				cout << "Sum on square [" << a << "," << b << "] x [" << c << "," << d << "] equals  " << tree.FINDSUM(MP(a,b),MP(c,d)) << endl;
				
				break;
			}
			case 3:{
				cout << "ISCOVERED OPTION" << endl;
				cout << "Enter X = [a,b]\t";
				cin >> a >> b;
				cout << "Enter Y = [c,d]\t";
				cin >> c >> d;
				
				bool bl = tree.ISCOVERED( MP(a,b),MP(c,d) );
				
				cout << "Square [" << a << "," << b << "] x [" << c << "," << d << "] " << ( bl? ("is covered") : ("is NOT covered") ) << endl;
				
				break;
			}
			case 4:{
				tree.writeTree();
				
				break;
			}
			default:{
				
			}			
		}		
	}	
}



int main(){
	
	
	//testC1Tree();
	testC2Tree();
	
}



/*

7 7
1
0 3
4 7
-3
1
2 5
2 5
2
2
0 3
3 6






*/







