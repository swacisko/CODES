#include<iostream>
#include<vector>
using namespace std;

inline int max( int a, int b )
{
	return ( a>b?a:b );
}

void SCAL_1(int *tab1,int p, int q, int r);
void SORT_SCAL(int *tab1, int p, int r);

int main()
{
    int l_zest, *pizza,*W,N,eat2,eat1;
    int tab[3][101][100]; // tab[0][i][j] to suma danego ciagu, tab[t][j][k] to maxymalna ilosc jaka moze zjesc gracz t w ciagu dlugosci j zaczynajacym sie od k-tego kawalka
    
    cin>>l_zest;
    
    while(l_zest--)
    {
                cin>>N;   
                eat1 = eat2 = 0;
                
                pizza = new int[N];
                W = new int[N];
                
                for(int i=0; i<N; i++)
                {
                        cin >> pizza[i];  
                        W[i] = pizza[i];    
                }
                
                SORT_SCAL(W,0,N-1); // zaczynam robic pierwszy sposob
               
                for(int i=N-1; i>=0; i--)
                {
                     if( i%2==1 ) eat1+=W[i];    
                }
                
                for(int i=0; i<N; i++)
                {
					tab[1][1][i] = pizza[i];
					tab[0][1][i] = pizza[i];
					tab[2][1][i] = 0;
					
					tab[1][2][i] = max( pizza[i], pizza[ (i+1)%N ] );
					tab[0][2][i] = tab[0][1][i] + pizza[ (i+1)%N ];
					tab[2][2][i] = tab[0][2][i] - tab[1][2][i];
				}
                
                for(int i=3; i<=N; i++)
                {
					for(int k=0; k<N; k++)
					{
						tab[1][i][k] = max( pizza[k] + tab[2][i-1][ (k+1)%N ] , pizza[ (k+i-1)%N ] + tab[2][i-1][k]  );
						tab[0][i][k] = tab[0][i-1][k] + pizza[ (k+i-1)%N ];
						tab[2][i][k] = tab[0][i][k] - tab[1][i][k];						
					}
				}
				
				for(int i=0; i<N; i++)
				{
					if( tab[1][N][i] > eat2 ) eat2 = tab[1][N][i];
				}
                
                cout<<eat1<<" "<<eat2<<endl;
                
              delete[]W;
			  delete[]pizza;  
    }   
    
}




void SORT_SCAL(int* tab1, int p, int r)
{
	if(p<r)
	{
		int q=(p+r)/2;
		SORT_SCAL(tab1,p,q);
		SORT_SCAL(tab1,q+1,r);
		SCAL_1(tab1,p,q,r);		
	}	
}

void SCAL_1(int* tab1,int p, int q, int r)
{
	int i=p, l=p, j=q+1;
	int* tab2 = new int[r+1];
	
	while(i<=q && j<=r)
	{
		if(tab1[i]<=tab1[j])
		{
			tab2[l]=tab1[i];
			i++;
		}
		else
		{
			tab2[l]=tab1[j];
			j++;
		}
		l++;
	}
	
	while(i<=q)
	{
		tab2[l]=tab1[i];
		i++;
		l++;
	}
	while(j<=r)
	{
		tab2[l]=tab1[j];
		j++;
		l++;
	}
	for(i=p; i<=r; i++)
	{
		tab1[i]=tab2[i];
	}
	delete[]tab2;
	
}
