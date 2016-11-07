#include<iostream>
#include<vector>
using namespace std;

int hmax, total_height_index;

class bucket
{
public:
	int height, total_height,radius;
	bucket( int r, int h, int th=0 ) : height(h), radius(r), total_height(th) {}
	
};

void place( vector<bucket>&constr, int high_ind );

int main()
{
	int l_zest, h, r, N;
	vector<bucket> construction;
	
	cin>>l_zest;
	
	while(l_zest--)
	{
		total_height_index=0;
		hmax=0;
		
		cin>>N;		int T=N;
		
		while(N)
		{
			N--;
			cin>>r>>h;
			construction.push_back(  bucket(r,h)  );
			
			if( T - N == 1 )
			{
				 construction[0].total_height = construction[0].height;
				 hmax = construction[0].total_height;
			}
			else	place( construction, total_height_index );
			
			
		//	cout<<"Najwyzsze wiaderko to: "<<total_height_index<<"   total_height:  "<<hmax<<endl;
			
			
			/*if( hmax >= construction[0].height )
			{
				 construction.erase( construction.begin() + 0 );
				 total_height_index--;
			}*/
			
			
		}
		
		construction.clear();
		cout<<hmax<<endl;
		
	}
		
}

//*************************************************************************************************************

void place( vector<bucket>&constr, int high_ind )
{
	bool laid=false;
	int highest_index = high_ind;
	
//	cout<<"Wkladanym wiadrem jest:  "<< constr.size()-1 << "   na razie nie ma maxymalnej wysokosci, jego wysokosc wlasna jest rowna:   " << constr[ constr.size()-1 ].height
//		<<"   jego promien to:  "<<constr[constr.size()-1].radius<<endl;
	
while( !laid )
{
	int local_highest=0, loc_high_ind=0; // w danym kregu wiader , parametry najwyzszego
	
	for(int i=constr.size()-1; i>=highest_index; i--)
	{
		if( constr[i].total_height > local_highest )
		{
			local_highest = constr[i].total_height;
			loc_high_ind = i;
		}		
	}
	
//	cout<<"Tu jeszcze nie ma bledu adresowania tablicy"<<flush;
//	cout<<"Najwyzszym lokalnym wiadrem jest:  "<<loc_high_ind<<"   jego wysokosc to:  "<<constr[loc_high_ind].total_height<<"   jego promien to:  "<<constr[loc_high_ind].radius<<endl;
	
	
	if( constr[loc_high_ind].radius <= constr[constr.size()-1].radius ) // jesli promien jest nie wiekszy to stawiamy na
	{
		constr[constr.size()-1].total_height = constr[loc_high_ind].total_height + constr[constr.size()-1].height;
		if( constr[constr.size()-1].total_height > hmax )
		{
			hmax = constr[constr.size()-1].total_height;
			total_height_index = constr.size()-1;  // total_height_index to obiekt globalny- najwyzsze ze wszystkich wiader
		}
		
		laid = true;
	}
	else // w przeciwnym wypdaku szukamy w srodku danego najwiekszego wiadra kolejnego najwiekszego wiadra itd.
	{
		if( loc_high_ind == constr.size()-2 ) // jezeli najwyzszy jest ostatnim nie liczac wkladanego wiadrem to wkladamy wiaderko do srodka
		{
			constr[constr.size()-1].total_height = constr[loc_high_ind].total_height - constr[loc_high_ind].height + constr[constr.size()-1].height ;
			if( constr[constr.size()-1].total_height > hmax )
			{
				hmax = constr[constr.size()-1].total_height;
				total_height_index = constr.size()-1;  // total_height_index to obiekt globalny- najwyzsze ze wszystkich wiader
			}			
			laid = true;
		}
		else // jezeli nie da sie wlozyc, to zawezamy krag poszukiwan
		{
			highest_index = loc_high_ind + 1;
		}
		
	}
	
} /// end of while
	
	
	
}
