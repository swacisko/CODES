#include<iostream>
//#include<cstdlib>
//#include<time.h>
using namespace std;

class B_l
{
public:
bool a : 1, b:1,c:1,d:1,e:1,f:1,g:1,h:1;
    B_l(): a(0),b(0),c(0),d(0),e(0),f(0),g(0),h(0) {}
	
	void assign( int no );
	bool get( int no );
	
};
void B_l::assign( int no )
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
	
bool B_l::get( int no )
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
int main()
{
	ios_base::sync_with_stdio(0);
	
//	B_l obiekt;
	//cout<<"sizeof(obiekt) = "<<sizeof(obiekt);
	
	int N,f1;	
	cin>>N;
	B_l *tab = new B_l[ N/8 + 1];
	
	for(int i=1; i<=N; i++)
	{
		cin>>f1;
		
		if( f1 <= N ) tab[ (f1-1)/8 ].assign( f1%8>0?f1%8:8 );
	}
	
/*	for(int i=0; i<=N/8; i++)
	{
		for(int k=1; k<=8; k++)
		{
			cout<< 8*i + k<<":  "<<tab[i].get(k)<<endl;
		}
	}*/
	
	for(int i=0; i<=N/8; i++)
	{
		for(int k=1; k<=8; k++)
		{
			if( tab[i].get(k)==false )
			{
				cout<< 8*i + k;
				goto Ende;
			}
		}
	}
	
Ende:;
	
}
