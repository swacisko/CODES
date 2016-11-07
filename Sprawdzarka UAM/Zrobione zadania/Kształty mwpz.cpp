#include<iostream>
#include<cmath>

using namespace std;

void quicksort(int* tab,double*ile, int p, int r);
int podzial(int*tab,double* ile, int p, int r);

inline double odl( int x1, int y1, int srx, int sry )
{
	return sqrt( (srx-x1 )*(srx-x1 ) + (sry-y1 )*(sry-y1 ) );	
}


int main()
{
	
	ios_base::sync_with_stdio(0);
	
	int k,N,wspx, wspy, ile_min, ile_max, t=1, l_zest;
	int tab[40001][2];
	double  min, max, srx, sry;
	int *ktore;
	char *litera;
	double *ile;
	
	
	cin>>k; l_zest=k;
	
	ile = new double[k+1];
	ktore = new int[k+1];
	litera = new char[k+1];
	
	for(int i=1; i<=k; i++) ktore[i]=i;
	
	while(l_zest--)
	{
		max=0; min=1000;
		srx=0;
		sry=0;
		ile_min = ile_max = 0;
		cin>>N;
		
		for(int i=1; i<=N; i++)
		{
			cin>>tab[i][0]>>tab[i][1];
			srx+=tab[i][0];
			sry+=tab[i][1];
		}
		
		srx/=N;
		sry/=N;
		
		for(int i=1; i<=N; i++)
		{
			if( odl(tab[i][0], tab[i][1], srx, sry) > max  )
			{
				 max = odl(tab[i][0], tab[i][1], srx, sry);
				 //ile_max++;
			}
			else if( odl(tab[i][0], tab[i][1], srx, sry) < min )
			{
				 min = odl(tab[i][0], tab[i][1], srx, sry);
				 //ile_min++;
			}
		}
		
	//	max/=ile_max;		
	//	min/=ile_min;
		
	//	cout<<"srx="<<srx<<" sry="<<sry<<" max="<<max<<" min="<<min<<" max/min="<<max/min<<endl;
		
	//	if( max/min >= 2.05  ) cout<<"T"<<endl;
	//	else if( max/min > 1.39 && max/min < 2.05  ) cout<<"K"<<endl;
	//	else cout<<"O"<<endl;
		
		ile[t++] = max/min;
		
	}
	
	quicksort(ktore,ile,1,k);
	
	for(int i=1; i<=k/3; i++)
	{
		litera[ktore[i]]='T';
	}
	for(int i=k/3+1; i<=k-k/3; i++)
	{
		litera[ktore[i]]='K';
	}
	for(int i=k-k/3+1; i<=k; i++)
	{
		litera[ktore[i]]='O';
	}
	
	for(int i=1; i<=k; i++) cout<<litera[i]<<endl;
}

int podzial(int*tab,double*ile, int p, int r)
{
	double x=ile[p];
	int i = r+1;
	int pamiec1;
	double pamiec2;
	
	for(int j=r; j>=p+1; j--)
	{
		if( ile[j] <= x ) // teraz sortuje sie od najwiekszej do najmniejszej. Aby zamienic kolejnosc wystarczy zmeinic na >=
		{
			i--;
			pamiec1=tab[j];
			tab[j] = tab[i];
			tab[i] = pamiec1;
			
			pamiec2=ile[j];
			ile[j]=ile[i];
			ile[i]=pamiec2;
		}
	}
	
	pamiec1=tab[i-1];
	tab[i-1] = tab[p];
	tab[p] = pamiec1;
	
	pamiec2=ile[i-1];
	ile[i-1]=ile[p];
	ile[p]=pamiec2;
	return i-1;
	
}
//****************************************************
void quicksort(int* tab,double*ile, int p, int r)
{
	int q;
	if(p < r)
	{
		q=podzial(tab,ile,p,r);
		quicksort(tab,ile,p,q-1);
		quicksort(tab,ile,q+1,r);
		
	}
	
}

//******************************************************
