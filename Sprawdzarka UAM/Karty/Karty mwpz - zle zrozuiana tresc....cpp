#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

#define PB push_back

int col_nr;

enum Action 
{
	HighCard = 0,
	Pair,
	StrongPair,
	TwoPairs,
	Three,
	Strit,
	Colour,
	Full,
	Four,
	Poker,
	Nothing
};

class Card
{
public:
	int number;
	int column_number;
	char Colour;
	int Value; // i will count from 2 to 14
	Card( char aColour=0, char aValue=0, int  anumber = 0 ) // nie potrzebuje konstruktora
	{
		number = anumber;
	//	Color = aColor;
	//	Value = convertValue( aValue );
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
	
	bool operator>( Card &other )
	{
		return ( Value > other.Value );
	}
	
	void readCard()
	{
		char aValue;
		cin >> Colour >> aValue;
		Value = convertValue( aValue );
	}
	
};

vector<Card> card_column;

class Table
{
public:
	Card table[25];
	void readTable()
	{
		for(int i=0; i<25; i++)
		{
			table[i].readCard();
			table[i].number = i;
		}
	}
};


class AllCards
{
public:
	Table table;
	vector<Card> cards;
	int Statistics[25];
	
	AllCards() // konstruktor
	{ cards.clear(); }
	
	void readAllCards()
	{
		table.readTable();
		
		for(int i=0; i<25; i++)
		{
			cards.PB( table.table[i] );
		}
		createStatistics();
	}
	
	void clearStatistics()
	{
		for(int i=0; i<15; i++) Statistics[i] = 0;
	}
	
	void createStatistics()
	{
		clearStatistics();
		for(int i=0; i<cards.size(); i++)
		{
			Statistics[ cards[i].Value ]++;
			if( cards[i].Value == 14 ) Statistics[1]++;
		}
	}
	
/*	void writeAllCards()
	{
		for(int i=0; i<cards.size(); i++)
		{
			cout << cards[i].Colour << cards[i].Value << " ";
		}
		cout << endl;
	}
	
	void writeStatistics()
	{
		cout << "Statistics:"<<endl;
		for(int i=0; i<15; i++)
		{
			cout << i << ": " << Statistics[i] << endl;
		}
	}*/
	
	bool existHighCard();
	bool existPair();
	bool existTwoPairs();
	bool existThree();
	bool existStrit();
	bool existColour();
	bool existFull();
	bool existFour();
	bool existPoker();
	
};

bool AllCards::existHighCard()
{
	int *S = Statistics;
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existHighCard, col_nr = " << col_nr << endl;
	
	for( int i=0; i<5; i++ ){
		cards[0].column_number = col_nr;
		card_column.PB( cards[0] );
		cards.erase( cards.begin()+0 );
	}
	
	col_nr++;
	if( cards.size() > 0 ) return true;
	else return false;
		
}

bool AllCards::existPair()
{
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existPair, col_nr = " << col_nr << endl;
	
	int *S = Statistics;
	for(int i=14; i>1; i--)
	{
		if( S[i] >= 2 ){
			for( int k=0; k<cards.size(); k++ ){				
				if( cards[k].Value == i ){
					S[ cards[k].Value ]--;
					cards[k].column_number = col_nr; 
					card_column.PB( cards[k] );
					cards.erase( cards.begin() + k );
					k--;
				}
			}
			
			for( int k=0; card_column.size()%5 > 0; k++ ){
				S[ cards[k].Value ]--;
				cards[k].column_number = col_nr; 
				card_column.PB( cards[k] );
				cards.erase( cards.begin() + k );
				k--;
			}			
			
			col_nr++;
			return true;
		} 
	}
	return false;
}


bool AllCards::existTwoPairs()
{
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existTwoPairs, col_nr = " << col_nr << endl;
	
	bool first,second;
	first = second = false;
	int *S = Statistics;
	for(int i=14; i>1; i--)
	{
		for( int j=i-1; j>1; j-- ){
			
			if( Statistics[i] >= 2 && Statistics[j] >= 2 ){
				
				for( int k=0; k<cards.size(); k++ ){
					if( cards[k].Value == i || cards[k].Value == j ){
						S[ cards[k].Value ]--;
						cards[k].column_number = col_nr; 
						card_column.PB( cards[k] );
						cards.erase( cards.begin() + k );
						k--;						
					}
				}
				
				for( int k=0; card_column.size()%5 > 0; k++ ){
					S[ cards[k].Value ]--;
					cards[k].column_number = col_nr; 
					card_column.PB( cards[k] );
					cards.erase( cards.begin() + k );
					k--;
				}			
				
				col_nr++;
				return true;
			}
			
			
		}		
	}
	
	return ( first && second );
}

bool AllCards::existThree()
{
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existThree, col_nr = " << col_nr << endl;
	
	int *S = Statistics;
	for(int i=14; i>1; i--)
	{
		if( S[i] >= 3 ){
			for( int k=0; k<cards.size(); k++ ){
				if( cards[k].Value == i ){
					S[ cards[k].Value ]--;
					cards[k].column_number = col_nr; 
					card_column.PB( cards[k] );
					cards.erase( cards.begin() + k );
					k--;
				}
			}
				
			for( int k=0; card_column.size()%5 > 0; k++ ){
				S[ cards[k].Value ]--;
				cards[k].column_number = col_nr; 
				card_column.PB( cards[k] );
				cards.erase( cards.begin() + k );
				k--;
			}			
			
			col_nr++;
			return true;
		
		}
	}
	return false;
}

bool AllCards::existStrit()
{
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existStrit, col_nr = " << col_nr << endl;
	
	int *S = Statistics;
	for(int i=1; i<15; i++)
	{
		if( S[i] && S[i+1] && S[i+2] && S[i+3] && S[i+4]  ){
			
			for( int k=0; k<cards.size(); k++ ){
				if( cards[k].Value == i || cards[k].Value == i+1 || cards[k].Value == i+2 || cards[k].Value == i+3 || cards[k].Value == i+4  ){
					S[ cards[k].Value ]--;
					cards[k].column_number = col_nr; 
					card_column.PB( cards[k] );
					cards.erase( cards.begin() + k );
					k--;
					
				}
			}
				
			for( int k=0; card_column.size()%5 > 0; k++ ){
				S[ cards[k].Value ]--;
				cards[k].column_number = col_nr; 
				card_column.PB( cards[k] );
				cards.erase( cards.begin() + k );
				k--;
			}			
			
			col_nr++;
			return true;
			
		}		
	}
	return false;
}

bool AllCards::existColour()
{
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existColour, col_nr = " << col_nr << endl;
	
	int S,H,D,C;
	S=H=D=C=0;
	char col = 'Q';
	
	for(int i=0; i<cards.size(); i++)
	{
		if( cards[i].Colour == 'P' ) S++;
		else if( cards[i].Colour == 'K' ) H++;
		else if( cards[i].Colour == 'R' ) D++;
		else if( cards[i].Colour == 'T' ) C++;
	}
	
	if( S >= 5 ) col = 'P';
	else if( H >= 5 ) col = 'K';
	else if( D >= 5 ) col = 'R';
	else if( C >= 5 ) col = 'T';
	
	int ile_dodal = 0;
	for( int k=0; k<cards.size(); k++ ){
		if( cards[k].Colour == col ){			
			if( ile_dodal == 5 ) break; // zeby przez przypadek nie dodac 6 kart...
			
			ile_dodal++;
			Statistics[ cards[k].Value ]--;
			cards[k].column_number = col_nr; 
			card_column.PB( cards[k] );
			cards.erase( cards.begin() + k );
			k--;
			
		}
	}
				
	for( int k=0; card_column.size()%5 > 0; k++ ){
		Statistics[ cards[k].Value ]--;
		cards[k].column_number = col_nr; 
		card_column.PB( cards[k] );
		cards.erase( cards.begin() + k );
		k--;
	}			
	
	if( col != 'Q' ) col_nr++;
	
	return ( S >= 5 || H >= 5 || D >= 5 || C >= 5 );
}

bool AllCards::existFull()
{
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existFull, col_nr = " << col_nr << endl;
	
	int *S = Statistics;
	int ilei = 0;
	int ilej = 0;
	
	for(int i=14; i>1; i--)
	{
		for( int j=i-1; j>1; j-- ){
			
			if( S[i] >=3 && S[j] >= 2 ){
				
				for( int k=0; k<cards.size(); k++ ){
					if( cards[k].Value == i || cards[k].Value == j ){
						if( cards[k].Value == i && ilei == 3 ) continue;
						if( cards[k].Value == j &&  ilej == 2 ) continue;
						if( cards[k].Value == i ) ilei++;
						if( cards[k].Value == j ) ilej++;
						
						S[ cards[k].Value ]--;
						cards[k].column_number = col_nr; 
						card_column.PB( cards[k] );
						cards.erase( cards.begin() + k );
						k--;
						
					}
				}
					
				for( int k=0; card_column.size()%5 > 0; k++ ){
					S[ cards[k].Value ]--;
					cards[k].column_number = col_nr; 
					card_column.PB( cards[k] );
					cards.erase( cards.begin() + k );
					k--;
				}			
				
				col_nr++;
				return true;
				
				
			}
			else if( S[i] >=2 && S[j] >= 3 ){
				for( int k=0; k<cards.size(); k++ ){
					if( cards[k].Value == i || cards[k].Value == j ){
						if( cards[k].Value == i && ilei == 2 ) continue;
						if( cards[k].Value == j &&  ilej == 3 ) continue;
						if( cards[k].Value == i ) ilei++;
						if( cards[k].Value == j ) ilej++;
						
						S[ cards[k].Value ]--;
						cards[k].column_number = col_nr; 
						card_column.PB( cards[k] );
						cards.erase( cards.begin() + k );
						k--;
						
					}
				}
					
				for( int k=0; card_column.size()%5 > 0; k++ ){
					S[ cards[k].Value ]--;
					cards[k].column_number = col_nr; 
					card_column.PB( cards[k] );
					cards.erase( cards.begin() + k );
					k--;
				}			
				
				col_nr++;
				return true;
				
				
			}
			
			
			
		}
	}
	
	return false;
}

bool AllCards::existFour()
{
	if( cards.size() == 0 ) return false;
//	cout << "Jestem w existFour, col_nr = " << col_nr << endl;
	
	int *S = Statistics;
	for(int i=14; i>1; i--)
	{
		if( S[i] == 4 ){
			
			for( int k=0; k<cards.size(); k++ ){
				if( cards[k].Value == i  ){
					S[ cards[k].Value ]--;
					cards[k].column_number = col_nr; 
					card_column.PB( cards[k] );
					cards.erase( cards.begin() + k );
					k--;
					
				}
			}
				
			for( int k=0; card_column.size()%5 > 0; k++ ){
				S[ cards[k].Value ]--;
				cards[k].column_number = col_nr; 
				card_column.PB( cards[k] );
				cards.erase( cards.begin() + k );
				k--;
			}			
			
			col_nr++;
			return true;			
			
		}
	}
	return false;
}

bool AllCards::existPoker()
{
	int *S = Statistics;
	char col = 'Q';
	
	
	for( int i=2; i<11; i++ ){
		if( S[i] && S[i+1] && S[i+2] && S[i+3] && S[i+4] ){
			
			
			
			
			
			
		}		
		
	}
	
	
	
	return false;	
}



bool myfun( Card c1, Card c2 ){
	return ( c1.number < c2.number );
}

int main()
{
	ios_base::sync_with_stdio(0);
	int Partie;
	AllCards Game;
	
//	int wyniki[26];
//	for(int i=0; i<26; i++) wyniki[i] = 0;
	
	cin >> Partie;
	while( Partie-- )
	{
		card_column.clear();
		Game.readAllCards();
		col_nr = 1;
	//	Game.writeAllCards();
//		Game.writeStatistics();
		
	//	while( Game.existPoker() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
			
	//	}
		while( Game.existFour() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 1 " << endl;
		
		while( Game.existFull() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 2 " << endl;
		
		while( Game.existColour() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 3 " << endl;
		
		while( Game.existStrit() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 4 " << endl;
		
		while( Game.existThree() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 5 " << endl;
		
		while( Game.existTwoPairs() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 6 " << endl;
		
		while( Game.existPair() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 7 " << endl;
		
		while( Game.existHighCard() ){
	//		for( int i=0; i<card_column.size(); i++ ){
	//			cout << card_column[i].Colour << card_column[i].Value << " ";
	//		}
	//		cout << endl;
		}
	//	cout << "Jestem juz gdzies dalej... 8 " << endl;
		
	//	cout << "Rozmiar card_column to " << card_column.size() << endl;
		sort( card_column.begin(), card_column.end(), myfun  );
		
		
	//	cout << "Jestem po sorcie " << endl;
		for( int i=0; i<card_column.size(); i++ ){
			cout << card_column[i].column_number << " ";
		}
		cout << endl;
	
	//	wyniki[ getStake( Game ) ]++;
		
				
	}	
	
/*	for(int i=0; i<26; i++)
	{
		cout << i << ": " << wyniki[i] << endl;
	}
*/
	
}
