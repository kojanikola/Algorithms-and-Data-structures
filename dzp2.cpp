#include <iostream>
#include <string>
using namespace std;

class Cvor {
	void kopiraj(const Cvor& c) {
		key = c.key;
		son = brother = father = nullptr;
	}
	void premesti(Cvor& c) {
		son = father = brother = nullptr;
		key = c.key;
	}
public:
	int key;
	int brdece;
	int lvl;
	int stepen;
	Cvor* son, *father, *brother;
	~Cvor() {
		father = son = brother = nullptr;
	}
	//Cvor()  = default;
	Cvor(int kk, int llvl) :key(kk), lvl(llvl) { son = father = brother = nullptr; } // ima pokazivaca pa da obezbedimo
	Cvor(const Cvor& c) { kopiraj(c); }
	Cvor(Cvor&& c) { premesti(c); }
	Cvor& operator=(const Cvor& cc) { if (this != &cc) { kopiraj(cc); } }
	Cvor& operator = (Cvor&& cc) { if (this != &cc) premesti(cc); }
	friend ostream& operator<<(ostream& it, const Cvor& c) {   //laksi ispis, ne mora rucno
		it << ' ' << c.key << ' ';
		return it;
	}
	//int getkey()const { return key; }		// ako su elementi privatni
};
using namespace std;
class Red {
	int duz;	//br el u redu trenutno
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

	struct Elem {		//struktura u redu, red pravim kao listu, nepotreban pristup tacno odredjenom
		Cvor *c;
		Elem *sl;
		Elem(Cvor* cc, Elem* sled = nullptr) {
			c = cc;
			sl = sled;
		}
	};
	Elem *prvi, *poslednji;
	Red() { prvi = poslednji = nullptr; duz = 0; }
	Red(const Red& r) { kopiraj(r); }		//zbog pokazivaca
	Red(Red&& r) { premesti(r); }
	Red& operator += (Cvor& cc) {			//operator za dodavanje u red
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
	Cvor* operator--(int t) {	//operator za skidanje, skida se pokazivac sve je po referenci pa pokazuje na original

		Cvor *pom = prvi->c;
		prvi = prvi->sl;
		if (!prvi) prvi = nullptr;
		return pom;
	}
	Cvor* operator--() {		//prefiksni
		if (prvi) {
			Cvor *cc = prvi->c;
			return cc;
		}
	}
	bool empty()const {		// da li je red prazan
		if (prvi == nullptr) return true;
		else return false;
	}

	friend ostream& operator<<(ostream& it, const Red& r) {
		Elem *pom = r.prvi;
		while (pom) {
			it << (pom->c)->key << "  ";
			pom = pom->sl;
		}
		return it;
	}
};
Cvor* pravi()
{
	Red r;
	int m;
	cout << "Stepen cvora?" << endl;
	cin >> m;
	Cvor* koren = nullptr;
	cout << "formira se stablo? Unesite cvorove, '/' za prekid unosa" << endl;
	char c; cin >> c;
	while (c != '/')
	{
		int i;
		cout << "Unesite kljuc narednog cvora " << endl;
		cin >> i;
		if (koren == nullptr)
		{
			koren = new Cvor(i, 0);
			koren->stepen = m;
		}
		else if (koren->son == nullptr)
		{
			koren->son = new Cvor(i, 1);
			koren->son->father = koren;
			koren->brdece++;
		}
		else
		{
			Cvor *pom = koren;
			if (pom->brdece < m)
			{
				Cvor *pom2 = pom->son;
				while (pom2->brother != nullptr) pom2 = pom2->brother;
				pom2->brother = new Cvor(i, pom2->lvl);
				pom2->father = pom;
				pom->brdece++;
			}
			else
			{
				while (pom->brdece == m)
				{
					r += *pom->son;               //kako da sprecim dvojku da dodje vise puta na red
					if (pom->brother != nullptr) pom = pom->brother;
					else pom = r--;
				}
				if (pom->son == nullptr)
				{
					pom->son = new Cvor(i, pom->lvl + 1);
					pom->son->father = pom;
					pom->brdece++;
				}
				else
				{
					Cvor *pomocni = pom->son;
					while (pomocni->brother != nullptr)pomocni = pomocni->brother;
					pomocni->brother = new Cvor(i, pom->lvl + 1);
					pomocni->father = pom;
					pom->brdece++;
				}
			}
		}
		cout<< "Nastavi sa formiranjem stabla?'/' za prekid unosa" << endl;
		cin >> c;
	}
	return koren;
}
int nivo(Cvor* koren)
{
	Red r1;
	r1 += *koren;
	int level = 0;
	while (!r1.empty())
	{


		Cvor *pom = r1--;
		Cvor *pom2 = pom;

		cout << "obisao " << pom->key << endl;
		if (pom->lvl > level) level = pom->lvl;
		if (pom->son != nullptr) {
			cout << "dodao sam sina u red "<<*pom->son << endl;
			r1 += *pom->son;
			Cvor *pom2 = pom->son;
			while (pom2->brother)
			{
				r1 += *pom2->brother;
				cout << "dodao sam brata" << *pom2->brother << endl;
				pom2 = pom2->brother;
			}
		}
		cout << "red je " << r1 << endl;
	}
	cout << "nivo je " << level<<endl;                      //odredjen l
	return level;
}
void brisi(Cvor * koren)
{
	Red r1,r2;
	r1 += *koren;
	int level = 0;
	while (!r1.empty())
	{
		Cvor *pom = r1--;
		r2 += *pom;
		Cvor *pom2 = pom;

		cout << "obisao " << pom->key << endl;
		if (pom->lvl > level) level = pom->lvl;
		if (pom->son != nullptr) {
			r1 += *pom->son;
			Cvor *pom2 = pom->son;
			while (pom2->brother)
			{
				r1 += *pom2->brother;
				cout << "dodao sam " << *pom2->brother << endl;
				pom2 = pom2->brother;
			}
		}
		cout << "red je " << r1 << endl;
	}
	cout << "nivo je " << level<<endl;                      //odredjen l
	Red::Elem *pom = r2.prvi;
	while(pom)
	{
		Cvor *pom2 = pom->c;
		pom = pom->sl;
		pom2->brother = pom2->father = pom2->son = nullptr;
		delete pom2;
	}
}
Cvor* dodaj(Cvor* koren,int i)
{
	Red r;
	if (koren == nullptr)
	{
		koren = new Cvor(i, 0);
	}
	else if (koren->son == nullptr)
	{
		koren->son = new Cvor(i, 1);
		koren->son->father = koren;
		koren->brdece++;
	}
	else
	{
		Cvor *pom = koren;
		if (pom->brdece < koren->stepen)
		{
			Cvor *pom2 = pom->son;
			while (pom2->brother != nullptr) pom2 = pom2->brother;
			pom2->brother = new Cvor(i, pom2->lvl);
			pom2->father = pom;
			pom->brdece++;
		}
		else
		{
			while (pom->brdece == koren->stepen)
			{
				r += *pom->son;               //kako da sprecim dvojku da dodje vise puta na red
				if (pom->brother != nullptr) pom = pom->brother;
				else pom = r--;
			}
			if (pom->son == nullptr)
			{
				pom->son = new Cvor(i, pom->lvl + 1);
				pom->son->father = pom;
				pom->brdece++;
			}
			else
			{
				Cvor *pomocni = pom->son;
				while (pomocni->brother != nullptr)pomocni = pomocni->brother;
				pomocni->brother = new Cvor(i, pom->lvl + 1);
				pomocni->father = pom;
				pom->brdece++;
			}
		}
	}
	return koren;
}
int main() {
	Cvor *koren = nullptr;
	char c='a';
	while (c != '/')
	{
		cout << "Unesite case za meni: " << endl;
		cout << " 1 za pravljenje" << endl;
		cout << " 2 za level" << endl;
		cout << " 3 za brisanje" << endl;
		cout << " 4 za dodavanje" << endl;
		cout << " / za kraj" << endl;
		cin >> c;
		switch (c)
		{
			case '1': koren = pravi(); break;
			case '2':
			{
				if (!koren) { cout << "Unesite prvo za pravljenje stabla" << endl; break; }
				int lvl = nivo(koren); break;
			}
			case '3':
			{
				if(koren==nullptr) { cout << "Unesite prvo za pravljenje stabla" << endl; break; }
				brisi(koren);
				koren = nullptr;
				break;
			}
			case '4':
			{
				cout << "unesite kljuc koji zelite da dodate " << endl;
				int i;
				cin >> i;
				koren=dodaj(koren,i);
				break;
			}
		}
	}
	int i;
	cin >> i;
}

