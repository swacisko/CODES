#include<iostream>
using namespace std;


int main()
{
	int W,K;
	
	cin>>W>>K;
	
	int tab[W][K];
	
	for(int i=0; i<W; i++)
	{
		for(int k=0; k<K; k++)
		{
			cin>>tab[i][k];		
		}	
		
	}
	
	for(int i=0; i<K; i++)
	{
		for(int k=0; k<W; k++)
		{
			cout<<tab[k][K-i-1];
			
		}
		cout<<endl;
	}
	
	
	
}
