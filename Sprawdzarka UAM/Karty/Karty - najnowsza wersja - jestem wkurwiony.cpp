#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define PB push_back
#define REP(x,y) for(int x=0; x < y; x++)


class Card
{
public:
	Card( const Card& other ){
		number = other.number;
		column_number = other.column_number;
		Colour = other.Colour;
		Value = other.Value;
	}
	int number;
	int column_number;
	char Colour;
	int Value; // i will count from 2 to 14
	Card( char aColour=0, char aValue=0, int anumber = 0 ) // nie potrzebuje konstruktora
	{

	}
	
	int convertValue( char v )
	{
		if( v >= 50 && v <= 57 ) return (int)v - 48;
		else if( v == '0' ) return 10;
		else if( v == 'J' ) return 11;
		else if( v == 'D' ) return 12;
		else if( v == 'K' ) return 13;
		else if( v == 'A' ) return 14;
	}
	
	bool operator<( Card &other )
	{
		return ( Value < other.Value );
	}
	
/*	bool operator==( const Card &other ){		
		return( number == other.number && column_number == other.column_number && Colour == other.Colour && Value == other.Value );
	}
	
	void operator=( const Card &other ){
		number = other.number;
		Value = other.Value;
		Colour = other.Colour;
		column_number = other.column_number;
	}*/
	
	void readCard()
	{
		char aValue;
		cin >> Colour >> aValue;
		Value = convertValue( aValue );
	}
	
	void writeCard(){
		cout << Colour << Value << " ";
	}
	
};

vector< vector<Card> > rows(5);
vector< vector<Card> > card_column(5);
vector<Card> maxis(5);


enum Action {
	HighCard = 0,
	Pair,
	TwoPairs,
	Three,
	Strit,
	Colour,	
	Full,	
	Four,
	Poker,
	KingPoker
} maxy, cur;

bool myf( Card c1, Card c2 ){
	return ( c1.Value < c2.Value );
}
bool myf2( Card c1, Card c2 ){
	return ( c1.Value > c2.Value );
}

vector<Card> current(5);

Action getMaxis(){
//	cout << "Jestem w getMaxis tralala" << endl;
	Card V[5];
	copy( current.begin(), current.end(), V );
//	cout << "Skopiowalem" << endl;
	
	sort( V, V+5, myf );
	int S[15];
	REP(i,15)S[i]=0;
	REP(i,5)S[V[i].Value]++;
	
	if( V[0].Value == 10 && V[1].Value == V[0].Value+1 && V[2].Value == V[1].Value+1 && V[3].Value == V[2].Value+1 && V[4].Value == V[3].Value + 1
		&& V[0].Colour == V[1].Colour && V[1].Colour == V[2].Colour && V[2].Colour == V[3].Colour && V[3].Colour == V[4].Colour ) return KingPoker;
	
	if( V[1].Value == V[0].Value+1 && V[2].Value == V[1].Value+1 && V[3].Value == V[2].Value+1 && V[4].Value == V[3].Value + 1
		&& V[0].Colour == V[1].Colour && V[1].Colour == V[2].Colour && V[2].Colour == V[3].Colour && V[3].Colour == V[4].Colour ) return Poker;
		
	REP( i,15 ) if( S[i] == 4 ) return Four;
	
	REP( i,15) REP( k,15 ) if( S[i] == 3 && S[k] == 2 ) return Full;
	
	if( V[0].Colour == V[1].Colour && V[1].Colour == V[2].Colour && V[2].Colour == V[3].Colour && V[3].Colour == V[4].Colour ) return Colour;
	
	if( V[1].Value == V[0].Value+1 && V[2].Value == V[1].Value+1 && V[3].Value == V[2].Value+1 && V[4].Value == V[3].Value + 1 ) return Strit;
	
	REP( i,15 ) if( S[i] == 3 ) return Three;
	
	REP( i,15 ) REP( k,15 ) if( S[i] == 2 && S[k] == 2 && i!=k ) return TwoPairs;
	
	REP( i,15 ) if( S[i] == 2 ) return Pair;
	
	return HighCard;
	
}

void getMax( int row ){
//	cout << "Jestem w getMax, row = " << row << endl;
	if( row == 5 ){
//		cout << "Current:  ";
//		REP( i,current.size() ) cout << current[i].Value << " ";
//		cout << endl;
		
		if( (cur = getMaxis() ) > maxy || /*( cur==maxy && rows[0].size()==1 )*/ maxy==HighCard ){
			maxy = cur;
			REP( i,5 ) maxis[i] = current[i];
			
		//	if( cur == Three ) REP( i,current.size() ) current[i].writeCard();
		}
		
		if( cur == Full ){
		//	REP( i,5 ) cout << current[i].writeCard();
		}
		
		return;
	}
	
//	cout << "Rows[row].size() = " << rows[row].size() << endl;
//	REP( i,current.size() ) cout << current[i].Colour << current[i].Value << " ";
	
	REP( i, rows[row].size() ){			
		current.PB( rows[row][i] );
		getMax( row+1 );
		current.pop_back();		
	}
	
	return;
}


bool myfun( Card c1, Card c2 ){
	return ( c1.number < c2.number );
}


int main(){
	int n;
	int change[6];
	
	int l_zest;
	cin >> l_zest;
	while(l_zest--){
		
		rows.clear();
		REP(i,5)rows.PB( vector<Card>() );
		REP(i,5) REP(k,5) rows[i].PB( Card() );
		card_column.clear();
		REP(i,5)card_column.PB( vector<Card>() );
		REP( i,5 ) REP(k,5) card_column[i].PB( Card() );
		
	    n = 1;
		REP( i,5 ){
			REP(k,5){
				rows[i][k].readCard();
				rows[i][k].number = n++;
			//	cout << rows[i][k].Colour << rows[i][k].Value << endl;
			}
		}
		
		REP(i,5) sort( rows[i].begin(), rows[i].end(), myf2 );
	//	cout << endl;
	/*	REP(i,rows.size()){
			REP(k,rows[i].size()){
				cout << rows[i][k].Colour << rows[i][k].Value << " ";
			}
			cout << endl;
		}*/
	/*	REP( k,rows.size() ){
			REP(t, rows[k].size() ){
				cout << rows[k][t].Colour << rows[k][t].Value << " ";
			}
			cout << endl;
		}*/
		
			
		
		REP( i,5 ){
			current.clear();
			maxis.clear();
			REP(t,5) maxis.PB( Card() );
			maxy = HighCard;
			getMax(0);
			
		//	cout << "Maxis:  "; REP(t,maxis.size()) cout << maxis[t].Colour << maxis[t].Value << " "; cout << endl;
			
			REP( k,5 ){
				card_column[k][i] = maxis[k];
				card_column[k][i].column_number = i+1;
			}
		
			
			REP( k,rows.size() ){
				REP( j,rows[k].size() ){
					REP(t,maxis.size()){
				//		cout << "rows[k][j].number = " << rows[k][j].number << "  <-->  " << maxis[t].number << " = maxis[t].number" << endl;
						if( rows[k][j].number == maxis[t].number ){
							rows[k].erase( rows[k].begin() + j );
							j+=100;
							break;
						}
					}
				}
			}
					
		
		
		}
		
		REP( i,5 ) sort( card_column[i].begin(), card_column[i].end(), myfun );
		REP( i,5 ) change[ card_column[0][i].column_number ] = i+1;
		
		REP( i,5 ){
			REP( k,5 ){
				cout << change[ card_column[i][k].column_number ] << " ";
			}
		}
		cout << endl;
	
	} // koniec whilea
	
	return 0;
}



