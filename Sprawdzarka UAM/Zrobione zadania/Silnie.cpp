#include<stdio.h>
#include<iostream>

using namespace std;

int silnia(int, int);
int main()
{
    int liczba_testow, sample1, sample2;
    cin>>liczba_testow;
    
    for(int i=0; i<liczba_testow; i++)
    {
            cin>>sample1;
            cin>>sample2;
            cout<<silnia(sample1,sample2);
    }
    
    
}
int silnia(int N, int K)
{
    int iloczyn=1;
    if(N>=K)
    {
    iloczyn=N*silnia(N-K,K);
    return iloczyn;
    }
    else return iloczyn;;
    
    
}
