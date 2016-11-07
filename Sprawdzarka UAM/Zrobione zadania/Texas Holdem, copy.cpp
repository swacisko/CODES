#include<iostream>
using namespace std;

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
	char Colour;
	int Value; // i will count from 2 to 14
	Card( char aColour=0, char aValue=0 ) // nie potrzebuje konstruktora
	{
	//	Color = aColor;
	//	Value = convertValue( aValue );
	}
	
	int convertValue( char v )
	{
		if( v >= 50 && v <= 57 ) return (int)v - 48;
		else if( v == '0' ) return 10;
		else if( v == 'J' ) return 11;
		else if( v == 'Q' ) return 12;
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

class Hand
{
public:
	Card hand[2];
	void readHand()
	{
		hand[0].readCard();
		hand[1].readCard();
	}
};

class Table
{
public:
	Card table[5];
	void readTable()
	{
		for(int i=0; i<5; i++)
		{
			table[i].readCard();
		}
	}
};


class AllCards
{
public:
	Hand hand;
	Table table;
	Card *cards[7];
	int Statistics[15];
	
	AllCards() // konstruktor
	{}
	
	void readAllCards()
	{
		hand.readHand();
		table.readTable();
		
		cards[0] = &hand.hand[0];
		cards[1] = &hand.hand[1];
		for(int i=2; i<7; i++)
		{
			cards[i] = &table.table[i-2];
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
		for(int i=0; i<7; i++)
		{
			Statistics[ cards[i]->Value ]++;
			if( cards[i]->Value == 14 ) Statistics[1]++;
		}
	}
	
	void writeAllCards()
	{
		for(int i=0; i<7; i++)
		{
			cout << cards[i]->Colour << cards[i]->Value << " ";
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
	}
	
	bool existHighCard();
	bool existPair();
	bool existStrongPair();
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
	return ( S[14] || S[13] );	
}

bool AllCards::existPair()
{
	int *S = Statistics;
	for(int i=14; i>1; i--)
	{
		if( S[i] == 2 ) return true;
	}
	return false;
}

bool AllCards::existStrongPair()
{
	int *S = Statistics;
	for(int i=14; i>12; i--)
	{
		if( S[i] == 2 ) return true;		
	}
	return false;	
}

bool AllCards::existTwoPairs()
{
	bool first,second;
	first = second = false;
	for(int i=14; i>1; i--)
	{
		if( first && Statistics[i]==2 )
		{
			second = true;
			break;
		}
		if( Statistics[i] == 2 ) first = true;		
	}
	
	return ( first && second );
}

bool AllCards::existThree()
{
	int *S = Statistics;
	for(int i=14; i>1; i--)
	{
		if( S[i] == 3 ) return true;
	}
	return false;
}

bool AllCards::existStrit()
{
	int *S = Statistics;
	for(int i=1; i<11; i++)
	{
		if( S[i] && S[i+1] && S[i+2] && S[i+3] && S[i+4]  ) return true;		
	}
	return false;
}

bool AllCards::existColour()
{
	int S,H,D,C;
	S=H=D=C=0;
	for(int i=0; i<7; i++)
	{
		if( cards[i]->Colour == 'S' ) S++;
		else if( cards[i]->Colour == 'H' ) H++;
		else if( cards[i]->Colour == 'D' ) D++;
		else if( cards[i]->Colour == 'C' ) C++;
	}
	
	return ( S >= 5 || H >= 5 || D >= 5 || C >= 5 );
}

bool AllCards::existFull()
{
	int *S = Statistics;
	bool first, second;
	bool pair;
	first = second = pair = false;
	for(int i=14; i>1; i--)
	{
		if( first && S[i] == 3 )
		{
			second = true;
		}
		if( S[i] == 3 ) first = true;
		if( S[i] == 2 ) pair = true;
	}
	
	if( first && second ) return true;
	return ( first && pair );
}

bool AllCards::existFour()
{
	int *S = Statistics;
	for(int i=14; i>1; i--)
	{
		if( S[i] == 4 ) return true;
	}
	return false;
}

bool AllCards::existPoker()
{
	return ( existStrit() && existColour() );	
}


Action getStrongestHand( AllCards &Set )
{
	if( Set.existPoker() ) return Poker;
	else if( Set.existFour() ) return Four;
	else if( Set.existFull() ) return Full;
	else if( Set.existColour() ) return Colour;
	else if( Set.existStrit() ) return Strit;
	else if( Set.existThree() ) return Three;
	else if( Set.existTwoPairs() ) return TwoPairs;
	else if( Set.existStrongPair() ) return StrongPair;
	else if( Set.existPair() ) return Pair;
	else if( Set.existHighCard() ) return HighCard;
	else return Nothing;
	
}

int getStake( AllCards &Set ) // mysle ze powinienem dac zdecydowanie wyzsze stawki, bo racze jw 100 testach nie dam rady wygrac 500 zetonow
{
	Action StrongestHand = getStrongestHand( Set );
	
	switch( StrongestHand )
	{
		case HighCard:
			{
			//	cout << "HighCard" << endl;
				return 2;
				break;
			}
		case Pair:
			{
			//	cout << "Pair" << endl;
				return 5;
				break;
			}
		case StrongPair:
			{
			//	cout << "StrongPair" << endl;
				return 8;
				break;
			}
		case TwoPairs:
			{
			//	cout << "TwoPairs" << endl;
				return 12;
				break;
			}
		case Three:
			{
			//	cout << "Three" << endl;
				return 20;
				break;
			}
		case Strit:
			{
			//	cout << "Strit" << endl;
				return 22;
				break;
			}
		case Colour:
			{
			//	cout << "Colour" << endl;
				return 22;
				break;
			}
		case Full:
			{
			//	cout << "Full" << endl;
				return 25;
				break;
			}
		case Four:
			{
			//	cout << "Four" << endl;
				return 25;
				break;
			}
		case Poker:
			{
			//	cout << "Poker" << endl;
				return 25;
				break;
			}
		case Nothing:
			{
			//	cout << "Nothing" << endl;
				return 0;
				break;
			}
		default:
			{
				
			}
	}
	
	
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
		Game.readAllCards();
	//	Game.writeAllCards();
	//	Game.writeStatistics();
	
	//	wyniki[ getStake( Game ) ]++;
		cout << getStake( Game ) << endl;		
	}	
	
/*	for(int i=0; i<26; i++)
	{
		cout << i << ": " << wyniki[i] << endl;
	}
*/
	
}




