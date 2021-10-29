/*#pragma once
#include <iostream>
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
	Cvor(int kk,int llvl) :key(kk),lvl(llvl) { son = father = brother = nullptr;  }
	Cvor(const Cvor& c) { kopiraj(c); }
	Cvor(Cvor&& c) { premesti(c); }
	Cvor& operator=(const Cvor& cc) { if (this != &cc) { kopiraj(cc); } }
	Cvor& operator = (Cvor&& cc) { if (this != &cc) premesti(cc); }
	friend ostream& operator<<(ostream& it, const Cvor& c) {
		it << ' ' << c.key << ' ';
		return it;
	}
	int getkey()const { return key; }
};*/
