/*#pragma once
#include <iostream>
#include "cvor.h"
using namespace std;
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
	Red() { prvi = poslednji = nullptr; duz = 0; }
	Red(const Red& r) { kopiraj(r); }
	Red(Red&& r) { premesti(r); }
	Red& operator += (Cvor& cc) {
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
	Cvor* operator--(int t) {
		
		Cvor *pom = prvi->c;
		prvi = prvi->sl;
		if (!prvi) prvi = nullptr;
		return pom;
	}
	Cvor* operator--() {
		if (prvi) {
			Cvor *cc = prvi->c;
			return cc;
		}
	}
	bool empty()const {
		if (prvi == nullptr) return true;
		else return false;
	}
	void ocisti()
	{
		prvi = poslednji = nullptr;
	}
	bool tuje(int p) 
	{
		Elem *pom = prvi;
		while (pom && pom->c->key != p) pom = pom->sl;
		if (pom) return true;
		else return false;
	}
	Red& dodajnapocetak(Cvor& c) {
		Elem *pom = new Elem(&c, prvi);
		prvi = pom;
		return *this;
	}
	friend ostream& operator<<(ostream& it, const Red& r) {
		Elem *pom = r.prvi;
		while (pom) {
			it << (pom->c)->getkey() << "  ";
			pom = pom->sl;
		}
		return it;
	}
};*/