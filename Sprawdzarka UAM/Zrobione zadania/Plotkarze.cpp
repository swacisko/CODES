#include<iostream>
#include<string>
 
using namespace std;
 
class person
{
public:
    static int population;
        string name;
        int nr;
        person *left, *right;
        person(string str): nr(population+1), name(str), right(NULL), left(NULL) { population++; }
};
 
//*************** ******************** ******************** ***********************
 
class BST
{
public:
        person *root;
        
        inline void insert( person *poczatek, person *osoba );
        inline person* search( person *poczatek, string imie );
        
        BST( person *osoba ){ root = osoba;     }
        
};
 
inline void BST::insert( person *poczatek, person *osoba )
{
        if( osoba->name > poczatek->name )
        {
                if( poczatek->right != 0 ) insert( poczatek->right, osoba );
                else
                {
                        poczatek->right = osoba;
                }
        }
        else
        {
                if( poczatek->left != 0 ) insert( poczatek->left, osoba );
                else
                {
                        poczatek->left = osoba;
                }       
        }       
}
 
inline person* BST::search( person *poczatek, string imie )
{       
        if( poczatek->name == imie ) return poczatek;
        else if( imie < poczatek->name ) return search( poczatek->left, imie );
        else return search( poczatek->right, imie );    
}
 
// *************** ****************8 **************** ***************** *******************
class B_l
{
public:
bool a : 1, b:1,c:1,d:1,e:1,f:1,g:1,h:1;
    B_l(): a(0),b(0),c(0),d(0),e(0),f(0),g(0),h(0) {}
        
        inline void assign( int no );
        inline bool get( int no );
        
};
 
inline void B_l::assign( int no )
{               
        switch(no)      
        {
                        case 1: { a=true; break;}
                        case 2: { b=true; break;}
                        case 3: { c=true; break;}
                        case 4: { d=true; break;}
                        case 5: { e=true; break;}
                        case 6: { f=true; break;}
                        case 7: { g=true; break;}
                        case 8: { h=true; break;}
                        default: {}
        }       
}
        
inline bool B_l::get( int no )
{
        switch(no)
        {
                        case 1: { return a;}
                        case 2: { return b;}
                        case 3: { return c;}
                        case 4: { return d;}
                        case 5: { return e;}
                        case 6: { return f;}
                        case 7: { return g;}
                        case 8: { return h;}
                        default: {}     
        }       
}
 
// ********************* /*********************** ************************* *******************
 
int person::population;
 
int main()
{
	ios_base::sync_with_stdio(0);
        int N,M,f1,f2;
        bool kennt_euch;
        string name, name_1, name_2;
        B_l **tab;
        BST *tree;
        
        while( true )
        {
                person::population = 0;         
                kennt_euch = true;
                
                cin>>N>>M;      
                if( N==0 && M ==0 ) break;
                
                tab = new B_l*[N];
                for(int i=0; i<N; i++) tab[i] = new B_l[ N/8 + 1 ];
                
                cin>>name;
                tree = new BST( new person(name) );
                
                for(int i=2; i<=N; i++)
                {
                        cin>>name;
                        tree->insert( tree->root, new person(name) );
                }
                
                //cout<<tree->root->name<<endl<<tree->root->left->name<<endl<<tree->root->right->name<<endl;
                
                tab[0][0].assign(1);
                for(int i=2; i<=N; i++)
                {
					tab[ i-1 ][ (i-1)/8 ].assign( i%8>0?i%8:8 );					
				}
				
				
				
				
				
				/*cout<<"Wypisuje kto kogo zna:"<<endl;
				for(int i=0; i<N; i++)
                {
					for(int k=0; k<=(N-1)/8; k++)
					{
						for(int j=1; j<=  ( (k<(N-1)/8) ? 8 : (N-((N-1)/8)*8)  )       ; j++)
						{
							cout<<tab[i][k].get(j)<<" ";
						}
					}
					cout<<endl;
				}*/
				
				
				
				
				
				
                
                for(int i=1; i<=M; i++)
                {
					cin>>name_1>>name_2;
					f1 = (tree->search( tree->root, name_1 ))->nr;
					f2 = (tree->search( tree->root, name_2 ))->nr;
					
					//cout<<"f1 = "<<f1<<"   f2 = "<<f2<<endl;
					
					for(int i=0; i<=(N-1)/8; i++)
					{
						for(int k=1; k<=8; k++)
						{
							if( tab[ f2-1 ][ i ].get(k) == true )
							{
								tab[ f1-1 ][ i ].assign(k);
							}
						}
					}
					
				/*	cout<<"Wypisuje kto kogo zna:"<<endl;
				for(int i=0; i<N; i++)
                {
					for(int k=0; k<=(N-1)/8; k++)
					{
						for(int j=1; j<=  ( (k<(N-1)/8) ? 8 : (N-((N-1)/8)*8)  )       ; j++)
						{
							cout<<tab[i][k].get(j)<<" ";
						}
					}
					cout<<endl;
				}cout<<endl<<endl;*/
				
					for(int i=0; i<=(N-1)/8; i++)
					{
						for(int k=1; k<=8; k++)
						{
							if( tab[ f1-1 ][ i ].get(k) == true )
							{
								tab[ f2-1 ][ i ].assign(k);
							}
						}
					}
					
					/*cout<<"Wypisuje kto kogo zna:"<<endl;
				for(int i=0; i<N; i++)
                {
					for(int k=0; k<=(N-1)/8; k++)
					{
						for(int j=1; j<=  ( (k<(N-1)/8) ? 8 : (N-((N-1)/8)*8)  )       ; j++)
						{
							cout<<tab[i][k].get(j)<<" ";
						}
					}
					cout<<endl;
				}cout<<endl<<endl;*/
				
				}
				
				
				
				
				
				
				
			/*	cout<<"Wypisuje kto kogo zna:"<<endl;
				for(int i=0; i<N; i++)
                {
					for(int k=0; k<=(N-1)/8; k++)
					{
						for(int j=1; j<=  ( (k<(N-1)/8) ? 8 : (N-((N-1)/8)*8)  )       ; j++)
						{
							cout<<tab[i][k].get(j)<<" ";
						}
					}
					cout<<endl;
				}*/
				
                
                for(int i=0; i<N; i++)
                {
					for(int k=0; k<=(N-1)/8; k++)
					{
						for(int j=1; j<= ( (k<(N-1)/8) ? 8 : (N-((N-1)/8)*8)  )    ; j++)
						{
							if( tab[i][k].get(j)==false )
							{
								kennt_euch=false;
								goto Ende;
							}
						}
					}
				}
                
Ende:			if( kennt_euch ) cout<<"YES"<<endl;
				else cout<<"NO"<<endl;
                
               // for(int i=0; i<N; i++) delete[]tab[i];
                delete tab;
                delete tree;
        }       
        
        
        
        
}
