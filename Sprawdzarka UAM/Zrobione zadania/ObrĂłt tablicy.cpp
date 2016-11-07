#include<iostream>
#include<stdio.h>
using namespace std;

int main()
{
    int N,M;
    scanf("%d %d",&N,&M);
    
    int tablica[N][M];
    int tab2[M][N];
     
    for(int i=0; i<N; i++)
    {
            for(int k=0; k<M; k++)
            {
                    cin>>tablica[i][k];
                    tab2[M-k-1][N-i-1]=tablica[i][k];
            }      
                
    }
       
    for(int i=M-1; i>=0; i--)
    {
            cout<<"\n";
            
            for(int k=0; k<N; k++)
            {
                    cout<<tab2[i][k]<<" ";
                    
            }            
    }
    
    
}
