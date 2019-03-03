//POP_2016_12_09_projekt_1_Fabich_Magdalena_EIT_2_165342 Dev C++ wersja 5.11 GCC

#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_M = 8;
const int GRACZ1 = -1;
const int GRACZ2 = 1;
const int MAX_N = 100;

void poczatek(char numer[MAX_N], int plansza[MAX_M][MAX_M]);
void pisz_menu(int plansza[MAX_M][MAX_M]);
void menu(char numer[MAX_N], int plansza[MAX_M][MAX_M]);
void tworz_tablice(int plansza[MAX_M][MAX_M]);
void tworz_krzyzyki(int plansza[MAX_M][MAX_M]);
void tworz_kolka(int plansza[MAX_M][MAX_M]);
void pisz_ramke(bool piszLitery);
void pisz_wiersz(int plansza[MAX_M][MAX_M], int i, bool piszLitery);
void pisz_tablice(int plansza[MAX_M][MAX_M]);
int ruch(int wybor1, int wybor2, int cel1, int cel2, int plansza[MAX_M][MAX_M], int gracz);
int konwersja(char tablica[MAX_N], bool kolumna);
void pytanie(int plansza[MAX_M][MAX_M], int gracz);
int sprawdzenie(int plansza[MAX_M][MAX_M], int wspx, int wspy, int gracz); 
int szukanie(int plansza[MAX_M][MAX_M], int gracz);
int zliczanie(int plansza[MAX_M][MAX_M], int gracz); 


int main()
{
	int plansza[MAX_M][MAX_M];
    
    pisz_menu(plansza);
    

	while (true) 
	{
	    bool brakruchow1 = false;
	    bool brakruchow2 = false;
	
		if (szukanie(plansza, GRACZ1) == 0)
			pytanie(plansza, GRACZ1);
		else 
		{
			cout<<endl<<"Gracz 1 nie ma mozliwych ruchow. "<<endl;
			brakruchow1 = true;
		}
		
		if (szukanie(plansza, GRACZ2) == 0)
			pytanie(plansza, GRACZ2);
		else 
		{
			cout<<endl<<"Gracz 2 nie ma mozliwych ruchow. "<<endl;
			brakruchow2 = true;
		}
		
		if (brakruchow1 && brakruchow2)
	    {
		int pionki1 = zliczanie(plansza, GRACZ1);

		int pionki2 = zliczanie(plansza, GRACZ2);

		if (pionki1>pionki2) 
		{
			cout << "Wygral GRACZ 1"<<endl<<endl;
			pisz_menu(plansza);
			brakruchow1=false;
			brakruchow2=false;
			continue;
			
		}
		else if (pionki1<pionki2) 
		{
		    cout << "Wygral GRACZ 2"<<endl<<endl;
		    pisz_menu(plansza);
		   	brakruchow1=false;
			brakruchow2=false;
			continue;
		}
		else
		{
			cout<<"REMIS"<<endl<<endl;
			pisz_menu(plansza);
			brakruchow1=false;
			brakruchow2=false;
			continue;
		}
		
		}
		
    }
}


void poczatek(char numer[MAX_N], int plansza[MAX_M][MAX_M])
{
	cout<<endl<<"ZASADY"<<endl;
	cout<<"Gre rozpoczyna GRACZ1 (biale pionki 'ooo'). GRACZ2 (czarne pionki '###'). Gracze wykonuja ruchy na zmiane."<<endl;
	cout<<"Piony poruszaja sie o jedno pole w dowolona strone (rowniez ukosnie) a sasiednie, wolne pole."<<endl;
	cout<<"Bicie pionow przeciwnika nastepuje po odejsciu piona bijacego od piona bitego,"<<endl;
	cout<<"z planszy zdejmowany jest pion znajdujacy sie w linii ruchu piona bijacego."<<endl;
	cout<<"W jednym ruchu mozna zbic tylko jeden pion."<<endl;
	cout<<"Nie wolno wykonywac ruchow, w ktorych nie odbywa sie bicie."<<endl;
	cout<<"Jesli gracz nie moze wykonac ruchu - kolejka przechodzi na przeciwnika."<<endl;
	cout<<"Wygrywa gracz, ktory zbije wszytskie piony przecinika"<<endl;
	cout<<"lub w przypadku braku mozliwosci wykonania ruchu obu graczy - ten ktoremu pozostalo wiecej pionkow na planszy."<<endl<<endl;
	cout<<"Wpisywanie pola:"<<endl;
	cout<<"Numer wiersza [ENTER] litera kolumny [ENTER]"<<endl<<endl;
		
	pisz_menu(plansza);
}
 
 
void tworz_tablice(int plansza[MAX_M][MAX_M])
{
	for (int i = 0; i<MAX_M; i++)
	{
		for (int j = 0; j<MAX_M; j++)
		{
			plansza[i][j] = 0;
		}
	}
}


void tworz_krzyzyki(int plansza[MAX_M][MAX_M])
{
	for (int i = 2; i<MAX_M - 2; i++)
	{
		for (int j = 2; j<MAX_M - 2; j++)
		{
			plansza[i][j] = 1;
		}
	}
}


void tworz_kolka(int plansza[MAX_M][MAX_M])
{
	for (int i = 2; i<MAX_M - 2; i++)
	{
		for (int j = 2; j<MAX_M - 2; j++)
		{
			if ((i + j) % 2 == 0)
			{
				plansza[i][j] = -1;
			}
		}
	}
}


void pisz_ramke(bool piszLitery = false)
{
	cout << "   +-----+-----+-----+-----+-----+-----+-----+-----+";
	cout << endl;
	
	if (piszLitery) 
	{
		cout << " ";
		for (int i = 65; i<73; i++)
		{
			cout << setw(6) << (char)i;
		}
		cout << "   ";
	}
}


void pisz_wiersz(int plansza[MAX_M][MAX_M], int i, bool piszLitery = false)
{
	if (piszLitery)
	{
		cout << " " << i + 1 << " ";
	}
	else
	{
		cout << "   ";
    } 
	
	for (int j = 0; j<MAX_M; j++)
	{
		switch (plansza[i][j])
		{
		case  0: cout << "|     ";
			     break;
		case -1: cout << "| ooo ";
			     break;
		case  1: cout << "| ### ";
		       	 break;
		}
	}

	cout << "|";
}


void pisz_tablice(int plansza[MAX_M][MAX_M])
{
	for (int i = 0; i<MAX_M; i++)
	{
		pisz_ramke();
		pisz_wiersz(plansza, i);
		cout << endl;
		pisz_wiersz(plansza, i, true);
		cout << endl;
	}
	pisz_ramke(true);

}


int ruch(int wybor1, int wybor2, int cel1, int cel2, int plansza[MAX_M][MAX_M], int gracz)
{
	int wektorX = cel1 - wybor1;
	int wektorY = cel2 - wybor2;
	int przecX = wybor1 - wektorX;
	int przecY = wybor2 - wektorY;
	
	if(wybor1>=0 && wybor1<8 && wybor2>=0 && wybor2<8 && cel1>=0 && cel1<8 && cel2>=0 && cel2<8)
	{
		if (plansza[wybor1][wybor2] == gracz)
		{
			if (plansza[cel1][cel2] == 0)
			{	
				if (wektorX == 1 || wektorX == -1 || wektorY == 1 || wektorY == -1) 
				{
				  if(plansza[przecX][przecY]!=gracz)//na ukos jak jest kilka tych samych
				  {
					while (przecX >= 0 && przecX<8 && przecY >= 0 && przecY<8) 
					{
						if (plansza[przecX][przecY] == gracz*(-1)) 
						{
							plansza[przecX][przecY] = 0;
							plansza[wybor1][wybor2] = 0;
							plansza[cel1][cel2] = gracz;
							system("cls");
							pisz_tablice(plansza);
							return 0;
						}
						else
						{
							przecX = przecX - wektorX;
							przecY = przecY - wektorY;
						}
					}
					 system("cls");
					 cout<<"Nie mozesz wykonac tego ruchu."<<endl;
		      	  }
		     	 
		      	else
		      	{
		      		system("cls");
		      		cout<<"Nie mozesz wykonac tego ruchu."<<endl;
			  	}
	
				}
				
				else
				{
					system("cls");
					cout<<"Mozesz poruszac sie tylko o jedno pole."<<endl;
				}
	
			}
	
			else 
			{
				system("cls");
				cout<<"Nie mozesz postawic pionka na tym polu"<<endl;
			}
		}
		else 
		{
			system("cls");
			cout<<"Nie mozesz poruszac tym pionkiem"<<endl;
		}
    }
    
		pisz_tablice(plansza);
		return 1;  
}


int konwersja(char tablica[MAX_N], bool kolumna) 
{
	if (tablica[1] != '\0') return -9999;
	else 
	{
		if (kolumna) 
		{
			switch (tablica[0]) 
			{
			case '1':return 0;

			case '2':return 1;

			case '3':return 2;

			case '4':return 3;

			case '5':return 4;

			case '6':return 5;

			case '7':return 6;

			case '8':return 7;

			default: return -9999;
			}
		}
		else 
		{
			switch (tablica[0]) 
			{
			case 'A':
			case 'a':return 0;

			case 'B':
			case 'b':return 1;

			case 'C':
			case 'c':return 2;

			case 'D':
			case 'd':return 3;

			case 'E':
			case 'e':return 4;

			case 'F':
			case 'f':return 5;

			case 'G':
			case 'g':return 6;

			case 'H':
			case 'h':return 7;

			default: return -9999;
			}
		}

	}
}


void pytanie(int plansza[MAX_M][MAX_M], int gracz)
{
	char wybor1_tab[MAX_N];
	char wybor2_tab[MAX_N];
	char cel1_tab[MAX_N];
	char cel2_tab[MAX_N];
	int wybor1;
	int wybor2;
	int cel1;
	int cel2;
	bool dobryWynik = false;
	bool dobryWpis = false;
	const bool kolumna = true;
	
	do {

		if (gracz == 1)cout<<endl<<endl<<"Gracz2: Ktory pionek chcesz przesunac (podaj wspolrzedne):"<<endl;
		else cout<<endl<<endl<<"Gracz1: Ktory pionek chcesz przesunac (podaj wspolrzedne):"<<endl;
		do {
			cin>>wybor1_tab>>wybor2_tab;
			cout<<endl;
			cout<<"Na jakie pole(podaj wspolrzedne):"<<endl;
			cin >>cel1_tab>>cel2_tab;

			wybor1 = konwersja(wybor1_tab, kolumna);
			wybor2 = konwersja(wybor2_tab, !kolumna);
			cel1 = konwersja(cel1_tab, kolumna);
			cel2 = konwersja(cel2_tab, !kolumna);


			if (wybor1 != -9999 && wybor2 != -9999 && cel1 != -9999 && cel2 != -9999) 
			{
				dobryWpis = true;
			}
			else 
			{
				system ("cls");
				pisz_tablice(plansza);
				cout<<endl<<"Nie ma takiego pola, wpisz ponownie: "<<endl;
			}
		} while (!dobryWpis);
		
		if (gracz == 1) 
		{
         	if (ruch(wybor1, wybor2, cel1, cel2, plansza, GRACZ2) == 0)
				dobryWynik = true;
		}
		else 
		{
		    if (ruch(wybor1, wybor2, cel1, cel2, plansza, GRACZ1) == 0)
				dobryWynik = true;
        }

	} while (!dobryWynik);
}


int sprawdzenie(int plansza[MAX_M][MAX_M], int wspx, int wspy, int gracz) //dookola kazdego pola
{
	int wektorX = -1;
	int wektorY = -1;
	int przeszukiwanyX = wspx - wektorX;
	int przeszukiwanyY = wspy - wektorY;

	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8) 
	{
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1)) 
		{
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}

	}

	wektorY++;
	przeszukiwanyX = wspx - wektorX;
	przeszukiwanyY = wspy - wektorY;

	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8) 
	{
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1)) 
		{
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}
	}
	
	wektorY++;
	przeszukiwanyX = wspx - wektorX;
	przeszukiwanyY = wspy - wektorY;

	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8) 
	{
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1)) 
		{
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}
	}
	
	wektorX++;
	przeszukiwanyX = wspx - wektorX;
	przeszukiwanyY = wspy - wektorY;


	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8)
	 {
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1)) 
		{
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}
	}

	wektorX++;
	przeszukiwanyX = wspx - wektorX;
	przeszukiwanyY = wspy - wektorY;

	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8) 
	{
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1))
	    {
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}
	}
	
	wektorY--;
	przeszukiwanyX = wspx - wektorX;
	przeszukiwanyY = wspy - wektorY;

	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8) 
	{
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1)) 
		{
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}
	}
	
	wektorY--;
	przeszukiwanyX = wspx - wektorX;
	przeszukiwanyY = wspy - wektorY;

	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8) 
	{
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1)) 
		{
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}
	}
	
	wektorX--;
	przeszukiwanyX = wspx - wektorX;
	przeszukiwanyY = wspy - wektorY;

	while (przeszukiwanyX >= 0 && przeszukiwanyX<8 && przeszukiwanyY >= 0 && przeszukiwanyY<8) 
	{
		if (plansza[przeszukiwanyX][przeszukiwanyY] == gracz*(-1)) 
		{
			return 0;
		}
		else 
		{
			przeszukiwanyX = przeszukiwanyX + wektorX;
			przeszukiwanyY = przeszukiwanyY + wektorY;
		}
	}

	return 1;
}


int szukanie(int plansza[MAX_M][MAX_M], int gracz) 
{
	for (int i = 0; i<MAX_M; i++) 
	{
		for (int j = 0; j<MAX_M; j++) 
		{
			if (plansza[i][j] == gracz) 
			{
				if (sprawdzenie(plansza, i, j, gracz) == 0)
					return 0;

			}
		}

	}
	return 1;
}


int zliczanie(int plansza[MAX_M][MAX_M], int gracz) 
{
	int ilosc_pionkow = 0;

	for (int i = 0; i<MAX_M; i++)
	{
		for (int j = 0; j<MAX_M; j++)
		{
			if(plansza[i][j] == gracz)
				ilosc_pionkow++;

		}
	}

	return ilosc_pionkow;
}


void pisz_menu(int plansza[MAX_M][MAX_M])
{
	char numer[MAX_N];
	
	cout<<"***MENU***"<<endl;
	cout<<"1 - ZASADY GRY"<<endl;
	cout<<"2 - GRA"<<endl;
	cout<<"3 - KONIEC"<<endl;
	
	cin>>numer;
	
	menu(numer,plansza);
}


void menu(char numer[MAX_N], int plansza[MAX_M][MAX_M])
{
	if(numer[1]!='\0') 
	{
	   system("cls");	
	   cout<<"Nie ma takiej opcji. Wpisz ponownie."<<endl<<endl;
	   pisz_menu(plansza);
    }   
    
    else
	{
		
	switch(numer[0])
	{
		case '1': system("cls"); 
		          poczatek(numer,plansza);
		          break;
		        
		case '2': tworz_tablice(plansza);

	              tworz_krzyzyki(plansza);

	              tworz_kolka(plansza);
      
                  system("cls");
               	  pisz_tablice(plansza);   
				  break;
				
		case '3': exit(0);	
		
		default: system("cls");
		         cout<<"Nie ma takiej opcji. Wpisz ponownie."<<endl<<endl;
		         pisz_menu(plansza);
				 break;   	       
	}
	
    }
}
