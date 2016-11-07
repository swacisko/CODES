#include<stdio.h>

int znajdz(float* tab, int p, int r, float liczba);

int main()
{
    int l_zest, N, liczba,t;
    
    float tab[10005]={0};    
    
    scanf("%d",&l_zest);
    
    while(l_zest--)
    {
        scanf("%f",&N);
        
        scanf("%f",&tab[1]);
        printf("1");
        
        for(int i=2; i<=N; i++)
        {
            scanf("%f",tab[i]);
            t=tab[i];
        	liczba=znajdz(tab,1,i,t);
               
            for(int k=i-1; k>=liczba; k--)
            {
				tab[k+1]=tab[k];

			}
			tab[liczba]=t;				
               
            printf(" %f",tab[liczba]);
        }                  
              
        printf("\n");
                
    }   //while


}
int znajdz(float* tab, int p, int r, float liczba) // znajduje najmniejszy index, dla ktorego tab[ten_index]<liczba;
{	
	if(p<r)
	{	
		int q=(p+r)/2;
		
		if(tab[q]<=liczba) return znajdz(tab,q+1,r,liczba);
		else return znajdz(tab,p,q-1,liczba);
	}	
	else return p;
	
}

 
