#include <iostream>
#include <string>
using namespace std;

class Cvor {
public:
	bool pobeda = false;
	string pobednik;
	char potezi[5][5];
	int poslednji1 = 4, poslednji2 = 4, poslednji3 = 4, poslednji4 = 4, poslednji5 = 4;
	Cvor* sin, *brat, *otac;
	int prednost ;
	char m;
	Cvor(char b) {            // pravljenje korena primam char da bi se dole menjalo
		cout << "unesite kuglice za pocetnu i broj kolone '/' za kraj " << endl;
		char c ;
		cin >> c;
		while (c != '/') {
			int a;
			cout << "unesite kolonu " << endl;
			cin >> a;
			while (a > 5 || a < 0)
			{
				cout << "unesite ponovo u opsegu " << endl;
				cin >> a;
			}
				cout << "vrsta je " << poslednji(a)+1 << endl;   //vrsta u koju se dodaje ali posto sam ih stavio na 4 dodajem 1 da ne bi kretalo od 0
			int k = poslednji(a)--;
			int l = a - 1;
			potezi[k][l] = b;

			if (b == 'b') b = 'p';                       //okretanje sl igraca, moglo sa int i mod
			else b = 'b';
			cout << " sledeci na potezu je: " << b << endl;
			cin >> c;
		}
		if (b == 'b') m = 'p';
		else m = 'b';
		sin = brat = otac = nullptr;
	}
	/*Cvor(int q)
	{
		char matrica[5][5];
		cout << "Unesite matricu 0 za prazno " << endl;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				cin >> matrica[i][j];
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				if (matrica[i][j] != 0)
					potezi[i][j] == matrica[i][j];
	}*/
	Cvor(Cvor& Otac, int i)
	{
		if (Otac.m == 'b') m = 'p';
		else if (Otac.m == 'p') m = 'b';	//ko treba da igra
		//pravim sina"
		poslednji1 = Otac.poslednji1; poslednji2 = Otac.poslednji2; poslednji2 = Otac.poslednji2; //prepisi dokle je popunjeno
		poslednji3 = Otac.poslednji3; poslednji4 = Otac.poslednji4; poslednji5 = Otac.poslednji5;
		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				potezi[i][j] = Otac.potezi[i][j];
		char b;
		b = m;
		int a = i;

		int k = poslednji(a)--;			//promeni inf o poslednjem
		int l = a - 1;
		potezi[k][l] = b;
		sin = brat = nullptr;
		otac = &Otac;				// povezi sa ocem

	}
	void win(char m)
	{
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {    //prodji kroz sve nenulte i registruj pobedu
				if (potezi[i][j] != '\0')
				{
					if (i > 0 && i < 4 && j>0 && j < 4) {
						//gore dole
						if (potezi[i][j] == potezi[i - 1][j] && potezi[i][j] == potezi[i + 1][j])
						{
							pobeda = true;
							if (potezi[i][j] == 'b') pobednik = "beli ";
							else pobednik = "plavi";
						}
						//levo desno
						if (potezi[i][j] == potezi[i][j - 1] && potezi[i][j] == potezi[i][j + 1])
						{
							pobeda = true;
							if (potezi[i][j] == 'b') pobednik = "beli ";
							else pobednik = "plavi";
						}
						//gore-desno dole-levo
						if (potezi[i][j] == potezi[i - 1][j + 1] && potezi[i][j] == potezi[i + 1][j - 1])
						{
							pobeda = true;
							if (potezi[i][j] == 'b') pobednik = "beli ";
							else pobednik = "plavi";
						}
						//gore-levo dole-desno
						if (potezi[i][j] == potezi[i - 1][j - 1] && potezi[i][j] == potezi[i + 1][j + 1])
						{
							pobeda = true;
							if (potezi[i][j] == 'b') pobednik = "beli ";
							else pobednik = "plavi";
						}
					}
					//coskove ne proveravam
					if (!((i == 0 && j == 0) || (i == 0 && j == 4) || (i == 4 && j == 0) || (i == 4 && j == 4))) {
						if (i == 0 || i == 4) {
							//levo desno
							if (potezi[i][j] == potezi[i][j - 1] && potezi[i][j] == potezi[i][j + 1])
							{
								pobeda = true;
								if (potezi[i][j] == 'b') pobednik = "beli ";
								else pobednik = "plavi";
							}
						}
						if (j == 0 || j == 4) {
							//gore dole
							if (potezi[i][j] == potezi[i - 1][j] && potezi[i][j] == potezi[i + 1][j])
							{
								pobeda = true;
								if (potezi[i][j] == 'b') pobednik = "beli ";
								else pobednik = "plavi";
							}
						}
					}
				}
			}
		}

	}
	int& poslednji(int a) {				//bolje da je poslednji bio niz i onda se samo pristupalo poslednji[i] gde je i kolona
		switch (a) {
		case 1: {return poslednji1; }
		case 2: {return poslednji2; }
		case 3: {return poslednji3; }
		case 4: {return poslednji4; }
		case 5: {return poslednji5; }
		}
	}
	friend ostream& operator<<(ostream& it, const Cvor& c) {
		for (int i = 0; i <5; i++) {
			for (int j = 0; j < 5; j++)
				cout << c.potezi[i][j] << ' ';		//stampaj matricu
			cout << endl;
		}
		return it;
	}
};

class Red {
	int duz;
	void kopiraj(const Red& r) {
		Elem*pom = r.prvi;
		while (pom) {
			if (prvi == nullptr) {
				prvi = new Elem(pom->c);
				poslednji = prvi;
			}
			else {
				poslednji->sl = new Elem(pom->c);
				poslednji = poslednji->sl;
			}
			duz++;
			pom = pom->sl;
		}
	}
	void premesti(Red& r) {
		prvi = r.prvi;
		poslednji = r.poslednji;
		duz = r.duz;
		r.prvi = r.poslednji = nullptr;
	}
public:
	struct Elem {
		Cvor *c;
		Elem *sl;
		Elem(Cvor* cc, Elem* sled = nullptr) {
			c = cc;
			sl = sled;
		}
	};
	Elem *prvi, *poslednji;
	Red() { prvi = poslednji = nullptr; duz = 0; }		//nepotrebno u ovom zad ali moze za neke druge da posluzi
	Red(const Red& r) { kopiraj(r); }
	Red(Red&& r) { premesti(r); }

	Red& operator += (Cvor& cc) {		//dodaj element u red
		if (prvi == nullptr) {
			prvi = new Elem(&cc);
			poslednji = prvi;
		}
		else {
			poslednji->sl = new Elem(&cc);
			poslednji = poslednji->sl;
		}
		duz++;
		return *this;
	}
	Cvor* operator--(int t) {		//skidanje elementa sa reda, cvor je poslat po referenci pa se pristupa direktno njemu
		Cvor *pom = prvi->c;
		prvi = prvi->sl;
		duz--;
		return pom;
	}
	Cvor* operator--() {	//prefiksni operator za skidanje el
		Cvor *cc;
		if (prvi)
			Cvor *cc = prvi->c;
		if (prvi == poslednji) prvi = poslednji = nullptr;
		return cc;

	}
	bool empty()const {				//provera da li ima el. u redu. Koristim za kraj ispisa
		if (prvi == nullptr|| prvi==poslednji->sl) return true;
		else return false;
	}
	friend ostream& operator<<(ostream& it, const Red& r) {
		Elem *pom = r.prvi;
		while (pom) {
			it << *pom->c;
			pom = pom->sl;
		}
		return it;
	}
};

void brisi(Cvor * koren)		//trazeno da se komunicira sa menijem koji salje pokazivac na koren
{
	Red r1, r2;
	r1 += *koren;
	while (!r1.empty())
	{
		Cvor *pom = r1--;
		r2 += *pom;
		if (pom->sin != nullptr) {
			r1 += *pom->sin;
			Cvor *pom2 = pom->sin;
			while (pom2->brat)
			{
				r1 += *pom2->brat;
				//cout << "dodao sam " << endl;
				pom2 = pom2->brat;
			}
		}
	}
	Red::Elem *pom = r2.prvi;
	while (pom)		//brisanje elemenata u redu, nisu pravljene kopije dakle brisu se originali
	{
		Cvor *pom2 = pom->c;
		pom = pom->sl;
		//pom2->brat = pom2->otac = pom2->sin = nullptr;
		delete pom2;
	}
}
int main() {
	int a=1;
	char m1; // ko je prvi na potezu
	Cvor* nod=nullptr; // pravi koren
	Red r;
	while (a != '0') {
		cout << "Unesite tacku iz menija koju hocete da odradite " << endl;
		cout << "1-pravi koren" << endl;
		cout << "2 stampaj stablo" << endl;
		cout << "3 brisi stablo " << endl;
		cin >> a;

		switch (a)
		{
		case 1:
			{
				if (nod != nullptr)
				{
					cout << "Obrisite prvo prethodno stablo " << endl;
					break;
				}
				int randbr;							//pravljenje random broja jer za 2 mogucnosti je dovoljno
				int min = 1, max = 100;				//paran-neparan
				int range = (max - min) + 1;
				randbr = min + int(range*rand() / (RAND_MAX + 1.0));
				if (randbr % 2 == 0) m1 = 'b';
				else m1 = 'p';
				cout << "prvi na potezu je "<< m1 << endl;
				nod = new Cvor(m1); break;
			}
		case 2:
			{
				if(nod==nullptr)		//provera da nije vec napravljeno stablo
				{
					cout << "unesite 1 za pravljenje" << endl;
					break;
				}
				r += *nod;
				nod->win(m1);		//da li je unos ok tj. da li posle unosa treba raditi ista
				if (nod->pobeda)
				{
					cout << "VEC SE DESILA POBEDA" << endl;
					cout << *nod << endl;
					break;
				}
				while (!r.empty()) {
					Cvor *pom = r--;
					Cvor *pom1 = pom;
					while (pom1->brat != nullptr)
					{
						r += *pom1->brat;
						pom1 = pom1->brat;
					}

					if (!pom->pobeda)
					{
						Cvor *pom1;
						cout << "OTAC JE " << endl;
						cout << *pom << endl;
						int deca = 0;
						for (int i = 1; i <= 5; i++)
						{
							if (pom->poslednji(i) >= 0) {
								pom1 = new Cvor(*pom, i);
								pom1->win(m1);
								if (pom1->pobeda && pom1->m==m1) (pom->prednost)++;
								if (pom1->pobeda && pom1->m != m1) (pom->prednost)--;
								if (pom->sin == nullptr) pom->sin = pom1;
								else
								{
									Cvor *pom2 = pom->sin;
									while (pom2->brat != nullptr) pom2 = pom2->brat;
									pom2->brat = pom1;
								}
								deca++;
							}
						}
						if (pom->prednost > 0) (pom->prednost) = 1;
						if (pom->prednost < 0) (pom->prednost) = -1;
						cout << "PREDNOST JE " << pom->prednost << endl;
						cout << endl;
						pom1 = pom->sin;
						while(deca)
						{
							cout << "IGRA "<< pom1->m<< " SIN JE " << endl;
							cout << *pom1 << endl;
							if (pom1->pobeda) {
								cout << "Ima pobede , pobedio je " << pom1->pobednik << endl;
							}
							else cout << "Nema pobede " << endl;
							pom1 = pom1->brat;
							deca--;
							cout << endl;
						}
						if(pom->sin!=nullptr) r+= *pom->sin;
					}
				}
				break;
			}
		case 3:
		{
			if (nod == nullptr)				//brisanje stabla pomocu reda
			{
				cout << "unesite 1 za pravljenje" << endl;
				break;
			}
			if (nod->sin == nullptr) { delete nod; nod = nullptr; break; }
			brisi(nod);
			nod = nullptr;
			}
		}
	}
	int i;
	cin >> i;
}
