#include<iostream>
#include<iomanip>
#include<conio.h>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>
#include<vector>
#include<windows.h>
#include<cstdlib>
#include<time.h>
#include<cctype>
using namespace std;

//**************************************************************************************************


//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************   WINDOWS.H

static int BACKGROUND=0, FOREGROUND=11;

void textbackground(int color)
{
  BACKGROUND = color;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
    FOREGROUND + (color << 4));
}

void textcolor(int color)
{
  FOREGROUND = color;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
    color + (BACKGROUND << 4));
}

void gotoxy(int x, int y)
{
  COORD g;
  g.X = x;
  g.Y = y;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), g);
}

void wherexy(int& x, int& y)
{
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE); 
    if (!GetConsoleScreenBufferInfo(hStd, &screenBufferInfo)) 
        printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError()); 
    x = screenBufferInfo.dwCursorPosition.X; 
    y = screenBufferInfo.dwCursorPosition.Y;
}
//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************    GLOBAL DATA
class Menu;
class Fiszka;
class Memobox;
class Compartment;

#define ENTER_KEY 13
#define ESCAPE_KEY 27

const string Project_disc_path = "C:\\Users\\E6410\\Desktop\\Projekt Fiszki\\";
const int Fiszka_width = 40, Fiszka_height = 13;
const int console_middle = 90;
const int Option_corner_x = console_middle - 20;
const int Option_corner_y = 5;
const int Fiszka_left_corner_x = 30, Fiszka_left_corner_y = 20;
enum { BLACK=0, D_BLUE=1, GREEN=2, D_TURQUOISE=3, D_RED=4, D_PINK=5, D_YELLOW=6, 
	   D_WHITE=7, GREY=8, BLUE=9, SELEDIN=10, TURQUOISE=11, RED=12, PINK=13, YELLOW=14, WHITE=15 };
const int MAX_OPT_LENGTH = 40;
bool transfer_forward = false;
const int how_many_new_cards = 8;

//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************    SELF-MADE MANIPULATORS

static int newline_x_pos=1, newline_y_pos=1;

ostream& newline(ostream &strum)
{
	strum<<flush;
	int x,y;
	wherexy(x,y);
	gotoxy(newline_x_pos,y+1);
	return strum;	
}

void newline_cursor_position(int x, int y = newline_y_pos )
{
	newline_x_pos = x;
	newline_y_pos = y;
}



//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************    OTHER FUNCTIONS


void C_colors( int text = FOREGROUND, int background = BACKGROUND )
{
	textcolor( text );
	textbackground( background );
	BACKGROUND = background;
	FOREGROUND = text;
}

	
bool stream_state( iostream &S )
{
	if( S.fail() )
	{
		cout<<"Your stream failed...but now it is fixed";
	}
	S.setstate( ios::goodbit );
}

void tile( int left_corner_x, int left_corner_y, int width, int height, int text_color=FOREGROUND, int background_color=BACKGROUND )
{
	C_colors(text_color, background_color);
	for(int i=0; i<height; i++)
	{
		gotoxy( left_corner_x, left_corner_y +i);
		cout<<string( width, ' ' );
	}
}

void procrastination( int seconds )
{
	int a = time(0);
	while( time(0)-a<seconds );
}

void screen_erase()
{
	C_colors(WHITE, BLACK);
	system("cls");
}


void execute( Menu& M );
bool accept_window( Fiszka *card);
void check_if_correct( Fiszka *card, int Comp_num );
int minimum( int a, int b )
{
	return a<b?a:b;
}

//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************     MENU

class Menu
{
public:
	Menu(string My_Menu_Name="Menu_options.txt", int left_x = Option_corner_x, int width = MAX_OPT_LENGTH, int lcy = Option_corner_y);
	
	void display_menu();
	string get_contents(int opt_num);
	string move();
	
	~Menu(){ save_options(); }
	
protected:
	class Option
	{
	public:
		Option(string s="", int lcy=0, int lcx = Option_corner_x, int opt_w=MAX_OPT_LENGTH ) : contents(s), height( count_height() ),
									 left_corner_y(lcy), left_corner_x(lcx), option_width(opt_w) {}
	//	const static int left_corner_x = Option_corner_x;
		void write_me();
		friend istream& operator>>( istream& str, Option &opt )
		{
			getline( str, opt.contents );
		}
		friend ostream& operator<<( ostream& str, const Option &opt )
		{
			str << opt.contents << endl;
		}
		void change_left_corner_y(int y){ left_corner_y = y;  }
		
		int option_width;
		int count_height();
		string contents;
		int height;
		int left_corner_y;
		int left_corner_x;
	protected:
		
	private:
		
	};
	
	int left_corner_x, left_corner_y, option_width;
	int highlighted_option; // informs us, which option are we currently indicating at
	vector<Option> options; // here we hold options
	void display_option(int opt_num);
	void read_options();  // UWAGA, naroznik kazdej opcji musi byc tak dobrany, aby tekst nie byl wypisywany od poczatku okienka, tylko od drugiej lini
	void save_options();
	string menu_name;
	void delete_dispensable_options();
	
private:
	
};

void Menu::delete_dispensable_options()
{
	int S = options.size()-1;
	while( get_contents(S)=="" ) 
	{
		options.erase(options.begin()+S);
		S--;
	}	
}

string Menu::get_contents(int opt_num)
{
	return options[opt_num].contents;  // dlaczego tu musi byc opt_num+1   ??? nie mam zielonego pojecia dlaczego
}

string Menu::move()
{
	char c;
	while( ( c = getch() ) != ENTER_KEY  )
	{
		if( c == 'w' )
		{
			if( highlighted_option > 1 )
			{
				highlighted_option--;
			//	display_menu();
				display_option(highlighted_option);
				display_option(highlighted_option+1);
			}
		}
		else if( c == 's' )
		{
			if( highlighted_option < options.size()-1 ) 
			{
				highlighted_option++;
			//	display_menu();
				display_option(highlighted_option);
				display_option(highlighted_option-1);
			}
		}
		else if( c == ESCAPE_KEY )
		{
			return "END";
		}
	}
	
	return get_contents( highlighted_option );
}

void Menu::save_options()
{
	string file_name = Project_disc_path + menu_name;
	ofstream save_stream( file_name.c_str() );
	if( save_stream.fail() )
	{
		cout<<"Nie ma pliku o sciezce: "<<file_name<<newline<<"Proponuje poprawic program...";
		procrastination( 5 );
		return;
	}
	
	for(int i=1; i<options.size(); i++)
	{
		save_stream << options[i];
	}

}

int Menu::Option::count_height()
{
	int a = 0, b = 0, h=1;
	while( b+a < contents.length() )
	{
		if( contents[b+a]==' ' && a> MAX_OPT_LENGTH -12 )
		{
			b=b+a;
			a=1;
			h++;
		}
		a++;
	}	
	return h;
}

void Menu::Option::write_me()
{
	gotoxy( left_corner_x, left_corner_y );
	int a = 0, b = 0;
	while( b+a < contents.length() )
	{
		if( contents[b+a]==' ' && a> option_width - 10 )
		{
			cout<<newline;
			b=b+a;
			a=1;
		}
		
		cout<<contents[b+a];
		a++;
	}	
}

void Menu::display_option(int opt_num)
{

	if( highlighted_option!=opt_num )
	{
		if(opt_num == 0 ) options[0].contents.erase( options[0].contents.find(".txt") );
		C_colors( BLACK,D_YELLOW );
		tile( left_corner_x-1, options[opt_num].left_corner_y-1,option_width, options[opt_num].height+2 );
		options[opt_num].write_me();
		if( opt_num == 0 ) options[0].contents +=".txt";
	}
	else
	{
		C_colors( YELLOW, D_RED );	
		tile( left_corner_x-1, options[opt_num].left_corner_y-1,option_width, options[opt_num].height+2 );
		options[opt_num].write_me();
	}
}

Menu::Menu(string My_Menu_Name, int left_x, int width , int lcy) : menu_name(My_Menu_Name), 
				highlighted_option(1), left_corner_x(left_x), option_width(width), left_corner_y(lcy) // konstruktor
{
	options.push_back( Option( My_Menu_Name,left_corner_y,left_corner_x, option_width ) );	
	read_options();
	delete_dispensable_options();
	display_menu();
}

void Menu::display_menu()
{
	screen_erase();
	for(int i=0; i<options.size(); i++)
	{
		display_option(i);
	}
}

void Menu::read_options()
{
	string file_name = Project_disc_path + menu_name;
	ifstream read_stream( file_name.c_str() );
	if( read_stream.fail() )
	{
		cout<<"Nie ma pliku o sciezce: "<<file_name<<newline<<"Proponuje poprawic program...";
		procrastination( 2 );
		return;
	}
	
	while( !read_stream.eof() )
	{
		Option t( "", left_corner_y, left_corner_x, option_width );
		read_stream>>t;
		t.change_left_corner_y( options[ options.size()-1 ].left_corner_y + options[ options.size()-1 ].height + 2 );
		options.push_back(t);
	}
	
}

//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************    FISZKI

class Fiszka
{
public:
	Fiszka(string fsw="", string ssw="", string fsp="", string ssp=""):first_side_word(fsw), second_side_word(ssw), 
																		first_side_phrase(fsp), second_side_phrase(ssp),
																		learntype(false) {}
	Fiszka( string fs, string ss ):first_side(fs), second_side(ss), learntype(true) {}
	
	void write_first_side_word(){ write_me(first_side_word); }
	void write_first_side_phrase(){ write_me(first_side_phrase); }
	void write_second_side_word(){ write_me(second_side_word); }
	void write_second_side_phrase() { write_me(second_side_phrase); }
	void write_first_side(){ write_me(first_side); }
	void write_second_side(){ write_me(second_side); }
	void write_front();
	bool if_blank(){ if( first_side_word=="" || second_side_word=="" ) return true; return false;	}
	
	bool get_learntype(){ return learntype; }
	
	friend ostream& operator<<( ostream &str, Fiszka &card );
	friend ofstream& operator<<( ofstream &str, Fiszka &card );
	friend ifstream& operator>>( ifstream& str, Fiszka &card );
protected:
	
private:	
	bool learntype; // denotes, whether we learn language or sth else; false means we learn language;
	void write_me(string s);
	string first_side_word, first_side_phrase;
	string second_side_word, second_side_phrase;
	string first_side, second_side; // w przypadku gdy to nie jest fiszka do jezykow
};

ifstream& operator>>( ifstream& str, Fiszka &card )
{
	char tab[100];
	str.getline( tab, 100  ); card.first_side_word = tab;
	str.getline( tab, 100 ); card.second_side_word = tab;
	str.getline( tab, 100 ); card.first_side_phrase = tab;
	str.getline( tab, 100 ); card.second_side_phrase = tab;
}

ofstream& operator<<( ofstream &str, Fiszka &card )
{	
	str<<card.first_side_word<<endl<<card.second_side_word
	<<endl<<card.first_side_phrase<<endl<<card.second_side_phrase<<endl;
}


void Fiszka::write_front()
{
	cout<<*this;
	tile( 2*console_middle-Fiszka_left_corner_x-Fiszka_width-1, Fiszka_left_corner_y-1,Fiszka_width, Fiszka_height );
}


void Fiszka::write_me(string s)
{
	int a = 0, b = 0;
	while( b+a < s.length() )
	{
		if( s[b+a]==' ' && a>Fiszka_width-12 )
		{
			cout<<newline;
			b=b+a;
			a=1;
		}
		
		cout<<s[b+a];
		a++;
	}	
}

ostream& operator<<( ostream &str, Fiszka &card )
{
	if( card.get_learntype() == 0 )
	{
		tile( Fiszka_left_corner_x-1, Fiszka_left_corner_y-1,Fiszka_width, Fiszka_height, BLACK, D_WHITE );
		gotoxy( Fiszka_left_corner_x, Fiszka_left_corner_y );
		newline_cursor_position( Fiszka_left_corner_x, Fiszka_left_corner_y );		
		int x2,y2;
		card.write_first_side_word(); cout<<newline<<newline<<newline;
		wherexy(x2,y2);
		card.write_first_side_phrase(); // cout<<newline<<newline;
		
		tile( 2*console_middle-Fiszka_left_corner_x-Fiszka_width-1, Fiszka_left_corner_y-1,Fiszka_width, Fiszka_height, BLACK, D_WHITE );
		gotoxy( 2*console_middle-Fiszka_left_corner_x-Fiszka_width, Fiszka_left_corner_y  );
		newline_cursor_position( 2*console_middle-Fiszka_left_corner_x-Fiszka_width, Fiszka_left_corner_y );
		card.write_second_side_word();
		gotoxy( 2*console_middle-x2-Fiszka_width, y2  );
		card.write_second_side_phrase(); // cout<<newline<<newline;
	}
	else
	{
		tile( Fiszka_left_corner_x-1, Fiszka_left_corner_y-1,Fiszka_width, Fiszka_height, BLACK, D_WHITE );
		gotoxy( Fiszka_left_corner_x, Fiszka_left_corner_y );
		newline_cursor_position( Fiszka_left_corner_x, Fiszka_left_corner_y );
		card.write_first_side();
		
		tile( 2*console_middle-Fiszka_left_corner_x-Fiszka_width-1, Fiszka_left_corner_y-1,Fiszka_width, Fiszka_height, BLACK, D_WHITE );
		gotoxy( 2*console_middle-Fiszka_left_corner_x-Fiszka_width, Fiszka_left_corner_y  );
		card.write_second_side();
	}
	
	return str;
}

//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************    COMPARTMENTS
const int Comps_quantity = 6;
const int f1_c_size = 60;
const int Comp_size[6] = { 50,f1_c_size, 2 * f1_c_size, 5 * f1_c_size, 9 * f1_c_size, 16 * f1_c_size };


class Compartment
{
public:
	Compartment(int comp_num=-1, string lang="") : my_compartment_number(comp_num), language(lang) {}
	
	friend class Memobox;
protected:
	
private:

	string language;
	Fiszka* revise_cards();
	void read_cards( string fname );
	void save_cards(string fname);
	int my_compartment_number;  // holds compartments number
	vector< Fiszka > index_cards; // here are held index_cards
};



Fiszka* Compartment::revise_cards()
{
	if( my_compartment_number >=1 && index_cards.size() <= Comp_size[my_compartment_number] ) return 0;
	if( my_compartment_number == 0 && index_cards.size()==0 ) return 0;

	check_if_correct( &index_cards[ 0 ], my_compartment_number );
		
	if( accept_window( &index_cards[ 0 ] ) )
	{
		transfer_forward = true;
	}
	else transfer_forward = false;
	
	Fiszka *ret = new Fiszka( index_cards[ 0 ] );
	index_cards.erase( index_cards.begin() + 0 );
	return ret;
}


void Compartment::read_cards(string fname)
{
	ifstream input( fname.c_str() );
	if( !input )
	{
		cout<<endl<<"Can't open file with path:  "<<fname<<endl;
		procrastination(2);
		return;
	}
	
	while( !input.eof() )
	{
		Fiszka card;
		input>>card; gotoxy(50,50);
	//	cout<<"Wczytalem fiszke, oto ona:"; if( ! card.if_blank() ){ cout<<card<<flush; procrastination(5); }
		index_cards.push_back( card );
	}
	
	input.close();
	
	for(int i=index_cards.size()-1; i>=0; i--)
	{
		if( index_cards[i].if_blank() ) index_cards.erase( index_cards.begin() + i );
	}
	
/*	for(int i=0; i<index_cards.size(); i++)
	{
		cout<<"Oto wczytana fiszka:"<<index_cards[i]; procrastination(3);
	} */
}

void Compartment::save_cards(string fname)
{
	ofstream output;
	output.open( fname.c_str() );
	
	for(int i=0; i<index_cards.size(); i++)
	{
		output<<index_cards[i];
	}
	output.close();
}

//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************    MEMOBOX

class Memobox
{
public:
	Memobox(string lang);

	void start_learning();
	void add_card();
	void search_card();
	
	~Memobox() { save_cards(); save_latter_data(); }	
protected:
	int how_many_compartments; 
	int which_compartment_latterly; // latter_data
	
	string language;
	vector<Compartment> Comps;
	Compartment Waiting_Room;
	Compartment Learned_cards;
	
	void create_new_card();
	void read_cards();
	void save_cards();
	
	
private:
	void read_latter_data();
	void save_latter_data();
	
};

void Memobox::save_latter_data()
{
	string fname = Project_disc_path +language + "\\Latter_data.txt";
	ofstream strum( fname.c_str() );
	strum<<which_compartment_latterly;
	strum.close();
}

void Memobox::read_latter_data()
{
	string fname = Project_disc_path +language + "\\Latter_data.txt";
	ifstream strum( fname.c_str() );
	if( !strum )
	{
		cout<<endl<<"Cannot open file with path:"<<endl<<fname;
		procrastination(2);
	}
	strum>>which_compartment_latterly;
	strum.close();
}

void Memobox::start_learning()
{
	while( true )
	{
		Fiszka *card = Comps[which_compartment_latterly].revise_cards();
		if( card == 0)
		{
/*		//	if( Comps[which_compartment_latterly].index_cards.size() != Comp_size[which_compartment_latterly]  ) break;
			if( which_compartment_latterly == 5 && Comps[5].index_cards.size() == Comp_size[which_compartment_latterly] )
			{
				int Min = minimum( how_many_new_cards, Waiting_Room.index_cards.size() );
				for(int i=1; i<=Min; i++)
				{
					Comps[0].index_cards.push_back( Waiting_Room.index_cards[0] );
					Waiting_Room.index_cards.erase( Waiting_Room.index_cards.begin() + 0 );
				}
			}
*/		
			if( which_compartment_latterly > 0 && Comps[which_compartment_latterly].index_cards.size() < Comp_size[which_compartment_latterly] )
			{
				which_compartment_latterly = 0;
				if( which_compartment_latterly == 0 && Comps[0].index_cards.size() == 0 )
				{
					int Min = minimum( how_many_new_cards, Waiting_Room.index_cards.size() );
					for(int i=1; i<=Min; i++)
					{
						Comps[0].index_cards.push_back( Waiting_Room.index_cards[0] );
						Waiting_Room.index_cards.erase( Waiting_Room.index_cards.begin() + 0 );
					}
				}
				break;
			} 
			if( which_compartment_latterly == 0 && Comps[0].index_cards.size() == 0 )
			{
				int Min = minimum( how_many_new_cards, Waiting_Room.index_cards.size() );
				for(int i=1; i<=Min; i++)
				{
					Comps[0].index_cards.push_back( Waiting_Room.index_cards[0] );
					Waiting_Room.index_cards.erase( Waiting_Room.index_cards.begin() + 0 );
				}
			}
			which_compartment_latterly = (which_compartment_latterly+1)%6 ;			
			break;	
		}
		
		if( transfer_forward )
		{
			if( which_compartment_latterly == 5 )
			{
				Learned_cards.index_cards.push_back( *card );
			}
			else
			{
				Comps[which_compartment_latterly+1].index_cards.push_back( *card );
			}
		}
		else
		{
			if( which_compartment_latterly >=3 )
			{
				Comps[1].index_cards.push_back( *card );
			}
			else
			{
				Comps[0].index_cards.push_back( *card );
			}
		}
				
		delete card;
		save_cards();
		save_latter_data();
	}
}

void Memobox::search_card()
{
	
}

void Memobox::add_card()
{
	string fsw,ssw,fsp,ssp;
	screen_erase();
	tile( 10,10,150,30,BLACK,WHITE );
	gotoxy( 11,11 );
	newline_cursor_position( 11 );
	
	cout<<setw(50)<<left<<"Please enter your first-side_word:";
	getline( cin,fsw );  cout<<newline;
	cout<<setw(50)<<left<<"Please enter your second-side-word(meaning):";
	getline( cin, ssw );  cout<<newline;
	cout<<setw(50)<<left<<"Please enter your first-side-phrase:";
	getline( cin, fsp );  cout<<newline;
	cout<<setw(50)<<left<<"Please enter your second-side-phrase:";
	getline( cin, ssp );  cout<<newline;
	
	Fiszka temporary_card( fsw,ssw,fsp,ssp );
	
	cout<<temporary_card;
	
	if( accept_window( &temporary_card) )
	{
		Waiting_Room.index_cards.push_back( temporary_card );
	}
	
}

Memobox::Memobox(string lang) : language(lang), how_many_compartments(Comps_quantity)    // CONSTRUCTOR
{ 
	for(int i=0; i<how_many_compartments; i++)
	{  
		Comps.push_back( Compartment( i, language ) );
	}
	read_cards();
	read_latter_data();
}

void Memobox::read_cards()
{
	ostringstream strum;
	for(int i=0; i<Comps.size(); i++)
	{
		strum<<Project_disc_path<<language<<"\\"<<"Compartment"<<i<<".txt";
		Comps[i].read_cards( strum.str() );	
		strum.str("");	
	}
	
	strum<<Project_disc_path<<language<<"\\"<<"Waiting_Room.txt";
	Waiting_Room.read_cards( strum.str() );
	strum.str("");
	
//	cout<<"Oto oczekujaca pierwsza fiszka:"<<Waiting_Room.index_cards[0]; procrastination(5);   // TU JEST OK-WCZYTYWANIE JEST OK
	
	strum<<Project_disc_path<<language<<"\\"<<"Learned_cards.txt";
	Learned_cards.read_cards( strum.str() );
}

void Memobox::save_cards()
{
	ostringstream strum;
	string file_name = Project_disc_path + language + "\\" + "Compartment";
	for(int i=0; i<Comps.size(); i++)
	{
		strum<<file_name<<i<<".txt";
		Comps[i].save_cards( strum.str() );
		strum.str("");
	}
	strum<<Project_disc_path<<language<<"\\"<<"Waiting_Room.txt";
	Waiting_Room.save_cards( strum.str() );
	strum.str("");
	
	strum<<Project_disc_path<<language<<"\\"<<"Learned_cards.txt";
	Learned_cards.save_cards( strum.str() );	
}


//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************   LATTER DATA





//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************   MAIN



int main()
{
/*	Fiszka moja( "abecadlo tralala" , "Z a gh e    e", "PIECA                      i", "spadlo__________" );
	ofstream zapis( "C:\\Users\\E6410\\Desktop\\PLIK_ZAPIS.txt" );
	zapis<<moja;
	zapis.close();
	ifstream wczyt( "C:\\Users\\E6410\\Desktop\\PLIK_ZAPIS.txt" );
	wczyt>>moja;
	cout<<moja;
	
	procrastination(5);
*/	

	Menu my_little_menu;
	execute( my_little_menu );


}


//**********************************************************************************************************************************************************
//**********************************************************************************************************************************************************
//*******************************************************************************************************************    OTHER FUNCTIONS


void execute_memo( Memobox *my_memo , Menu &M)
{
	string z;
	while( ( z = M.move() ) != "END" )
	{
		if( z == "Start learning" )
		{
			my_memo->start_learning();
		}
		else if( z == "Add card" )
		{
			my_memo->add_card();
		}
		else if( z == "Search card" )
		{
			my_memo->search_card();
		}
		
		M.display_menu();
	}	
}

void execute(Menu& M)
{
	string z;
	while( ( z = M.move() ) != "END" )
	{		
		Memobox *my_memo = new Memobox( z );
		Menu My_memo_menu( "Memo_menu_options.txt" );
		execute_memo( my_memo, My_memo_menu );
		
		
		
		M.display_menu();		
		delete my_memo;
	}
};



bool accept_window( Fiszka *card )
{
	cout<<newline<<newline;
	int x,y; wherexy(x,y);
	Menu acc_win_menu( "Accept_window_menu.txt", x,20 );
	cout<<*card;
	string conf;
	while(true)
	{
		conf = acc_win_menu.move();
		cout<<*card;
		if( conf == "Accept" ) return true;
		if( conf == "Don't Accept" ) return false;
		if( conf == "END" ) return false;
	}
}

void check_if_correct(Fiszka *card, int Comp_num )
{
	Menu my_menu( "Check_if_correct_menu.txt", console_middle-12, 25,23 );
	card->write_front();
	tile( console_middle-13,2,25,3, SELEDIN,BLACK ); gotoxy( console_middle-11,3 ); cout<<"Compartment "<<Comp_num;
	string conf;
	while(true)
	{
		conf = my_menu.move();
		card->write_front();
		tile( console_middle-13,2,25,3,SELEDIN,BLACK ); gotoxy( console_middle-11,3 ); cout<<"Compartment "<<Comp_num;
		if( conf == "CHECK" ) return;	
		if( conf == "END" ) return;
	}
}


            
