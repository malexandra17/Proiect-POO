﻿#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <string>
using namespace std;
class coloana
{private:
	char* nume_coloana;
	string tip;
	int dimensiune;
public:
	coloana()
	{
		 nume_coloana = nullptr;
		 tip="";
		 dimensiune=0;
    }
	coloana(const char* nume_coloana)
	{
		if (nume_coloana != nullptr)
		{
			this->nume_coloana = new char[strlen(nume_coloana) + 1];
			strcpy_s(this->nume_coloana, strlen(nume_coloana) + 1, nume_coloana);
		}

	}
	coloana(const char* nume_coloana, string tip, int dimensiune)
	{
		this->nume_coloana = new char[strlen(nume_coloana  ) + 1];
		strcpy_s(this->nume_coloana, strlen(nume_coloana) + 1, nume_coloana);
		this->dimensiune = dimensiune;
		this->tip = tip;
		
	}
	coloana(const coloana& c)
	{
		if (c.nume_coloana != nullptr)
		{
			this->nume_coloana = new char[strlen(c.nume_coloana) + 1];
			strcpy_s(this->nume_coloana, strlen(c.nume_coloana) + 1, c.nume_coloana);
		}
		else nume_coloana = nullptr;
		

		this->dimensiune = c.dimensiune;
		this->tip = c.tip;

	}
	~coloana()
	{
		if (nume_coloana != nullptr)
			delete[] nume_coloana;
	}
	coloana& operator=(const coloana& c)
	{
		if (nume_coloana != nullptr)
			delete[] nume_coloana;
		if (c.nume_coloana != nullptr)
		{
			this->nume_coloana = new char[strlen(c.nume_coloana) + 1];
			strcpy_s(this->nume_coloana, strlen(c.nume_coloana) + 1, c.nume_coloana);
		}
		else nume_coloana = nullptr;
		

		this->dimensiune = c.dimensiune;
		this->tip = c.tip;
		return *this;

	}
	string get_tip()
		{
		return tip;
		}
	string get_denumire_coloana()
	{
		string nume = nume_coloana;
		return nume;
	}
	int get_dimensiune()
	{
		return dimensiune;
	}
	void set_nume_coloana(const char* nume_coloana)
	{
		if (nume_coloana != nullptr)
		{
			this->nume_coloana = new char[strlen(nume_coloana) + 1];
			strcpy_s(this->nume_coloana, strlen(nume_coloana) + 1, nume_coloana);
		}
	}
	void set_tipul(string tip)
	{
		if (tip != "")
		{
			this->tip = tip;
		}
	}
	void set_dimensiunea(int dimensiune)
	{
		if (dimensiune > 0)
		{
			this->dimensiune = dimensiune;
		}
	}
	char operator[](int index)
	{
		if (index >= 0 && index < strlen(nume_coloana))
			return nume_coloana[index];
    }
	coloana operator+(int valoare)
	{
		if (valoare > 0)
		{
			coloana copie = *this;
			copie.dimensiune = copie.dimensiune + valoare;
			return copie;
		}
	}
	coloana operator++()
	{
		this->dimensiune++;
		return *this;
	}
	coloana operator++(int i)
	{
		coloana copie = *this;
		this->dimensiune++;
		return copie;
	}
	int operator()()
	{
		if (nume_coloana != nullptr)
			return strlen(nume_coloana);
	}
	bool operator!()
	{
		return dimensiune > 0;
	}
	bool operator<(int valoare)
	{
		if (dimensiune < valoare) return true;
		else return false;
	}
	bool operator==(coloana c)
	{
		int ok = 1;
		if (strcmp(nume_coloana, c.nume_coloana) != 0) ok = 0;
		if (tip != c.tip) ok = 0;
		if (dimensiune != c.dimensiune) ok = 0;
		if (ok == 1) return true;
		else return false;
	}
	friend ostream& operator<<(ostream&, coloana);
	friend istream& operator>>(istream&, coloana&);

};
ostream& operator<<(ostream&out, coloana c)
{
	out << c.nume_coloana << " ";
	out << c.dimensiune << " ";
	out << c.tip<<endl;
	return out;

}
istream& operator>>(istream&in , coloana&c)
{
	string buffer;
	in >> buffer;
	if (c.nume_coloana != nullptr)
		delete[] c.nume_coloana;
	c.nume_coloana = new char[buffer.length() + 1];
	strcpy_s(c.nume_coloana, buffer.length() + 1, buffer.c_str());
	in >> c.dimensiune;
	in >> c.tip;
	return in;
}

template<typename T>
class valori_coloana:public coloana
{private:
	int nr_valori=0;
	T valoare_default;
	T* valori=nullptr;

public:
	valori_coloana()
	{
		int nr_valori = 0;

		T* valori = nullptr;

	}
	valori_coloana(T valoare_default,const char* nume):coloana(nume)
	{
		this->valoare_default = valoare_default;
		this->valori=nullptr;
		nr_valori = 0;
	}
	void set_valoare(T valoare_default)
	{if(valoare_default>0||valoare_default!="")
		this->valoare_default = valoare_default;
	}
	void insert(T valoare)
	{
		T* copie = new T[nr_valori+1];
		for (int i = 0;i < nr_valori;i++)
			copie[i] = valori[i];
		
		copie[nr_valori] = valoare;
		nr_valori++;
		delete[] valori;
		valori = new T[nr_valori];
		for (int i = 0;i < nr_valori;i++)
			valori[i] = copie[i];
		delete[]copie;
	}
	int get_nr_valori()
	{
		return nr_valori;
	}

	valori_coloana(const  valori_coloana& c):coloana(c)
	{
		this->valoare_default = c.valoare_default;
		this->nr_valori = c.nr_valori;
		valori = new T[nr_valori];
		if (c.valori != nullptr)
		{
			
			for (int i = 0;i < c.nr_valori;i++)
			this->valori[i] = c.valori[i];
		}
		else this->valori = nullptr;
	}
	~valori_coloana()
	{
		if (valori!= nullptr)
			delete[] valori;
	}
	valori_coloana& operator=(const  valori_coloana& c)
	{coloana::operator=(c);
		if (valori!= nullptr&&nr_valori>0)
			delete[] valori;
		
		this->valoare_default = c.valoare_default;
		this->nr_valori = c.nr_valori;
		valori = new T[nr_valori];
		if (c.valori != nullptr)
		{
			for (int i = 0;i < c.nr_valori;i++)
				this->valori[i] = c.valori[i];
		}
		else this->valori = nullptr;
		return*this;

	}
	void set_valoare_default(T valoare_default)
	{
		this->valoare_default = valoare_default;
	}
	void sterge()
	{
		
		T* copie = new T[nr_valori];
		for (int i = 0;i < nr_valori;i++)
			copie[i] = valoare_default;
		delete[] valori;
		valori = nullptr;
		valori = new T[nr_valori];
		for (int i = 0;i < nr_valori;i++)
			valori[i] = copie[i];
		delete[]copie;
	}
	T& operator[](int index)
	{
		if (index >= 0 && index < nr_valori)
			return valori[index];
	}
	valori_coloana operator+(T valoare)
	{
		valori_coloana copie = *this;
		for (int i = 0;i < nr_valori;i++)
			copie[i] = copie[i] + valoare;
		return copie;
	}
	valori_coloana operator++()
	{
		this->nr_valori++;
		return *this;
	}
	valori_coloana operator++(int i)
	{
		valori_coloana copie = *this;
		this->nr_valori++;
		return copie;
	}
	int operator()()
	{
		if (valori != nullptr)
			return nr_valori;
	}
	bool operator!()
	{
		return nr_valori > 0;
	}
	bool operator<(int valoare)
	{
		return nr_valori < valoare;
	}
	bool operator==(valori_coloana c)
	{
		int ok = 1;
		if ((coloana)*this == (coloana)c) ok = 1;
		else ok = 0;
		if (nr_valori != c.nr_valori) ok = 0;
		if (valoare_default != c.valoare_default) ok = 0;
		for (int i = 0;i < nr_valori;i++)
			if (valori[i] != c.valori[i])ok = 0;
		if (ok == 1) return true;
		else return false;
	}
	T get_valoare_default()
	{
		return valoare_default;
	}
	T* get_valori()
	{
		if (valori != nullptr)
		{
			T* copie = new T[nr_valori];
			for (int i = 0;i < nr_valori;i++)
			{
				copie[i] = valori[i];
			}
			return copie;
		}
		else return nullptr;
	}
	void set_nr_valori(int nr_valori)
	{
		if (nr_valori > 0)
			this->nr_valori = nr_valori;
		else this->nr_valori = 0;
	}

	void set_valori(T* valori, int nr_valori)
	{
		if (valori != nullptr && nr_valori > 0)
		{
			this->nr_valori = nr_valori;
			if (this->valori != nullptr)
				delete[] this->valori;
			this->valori = new T[nr_valori];
			for (int i = 0;i < nr_valori;i++)
				this->valori[i] = valori[i];
		}
		else
		{
			this->valori = nullptr;
			nr_valori = 0;
		}
	}
	friend ostream& operator<<(ostream&, valori_coloana);
	friend istream& operator>>(istream&, valori_coloana&);
};
ostream& operator<<(ostream& out, valori_coloana<int> c)
{
	out << (coloana)c << endl;
	out << c.valoare_default << endl;
	out << c.nr_valori << endl;
	if (c.nr_valori > 0 && c.valori != nullptr)
		for (int i = 0;i < c.nr_valori;i++)
			out << c.valori[i] << " ";
	return out;
}
istream& operator>>(istream& in , valori_coloana<int>&c)
{
	in >> (coloana&)c;
	in >> c.valoare_default;
	in >> c.nr_valori;
	if (c.valori != nullptr)
		delete[]c.valori;
	c.valori = new int[c.nr_valori];
	for (int i = 0;i < c.nr_valori;i++)
		in >> c.valori[i];
	return in;
}
ostream& operator<<(ostream& out, valori_coloana<string> c)
{
	out << (coloana)c << endl;
	out << c.valoare_default << endl;
	out << c.nr_valori << endl;
	if (c.nr_valori > 0 && c.valori != nullptr)
		for (int i = 0;i < c.nr_valori;i++)
			out << c.valori[i] << " ";
	return out;

}
istream& operator>>(istream& in, valori_coloana<string>& c)
{
	in >> (coloana&)c;
	in >> c.valoare_default;
	in >> c.nr_valori;
	if (c.valori != nullptr)
		delete[]c.valori;
	c.valori = new string[c.nr_valori];
	for (int i = 0;i < c.nr_valori;i++)
		in >> c.valori[i];
	return in;
}
ostream& operator<<(ostream& out, valori_coloana<float> c)
{
	out << (coloana)c << endl;
	out << c.valoare_default << endl;
	out << c.nr_valori << endl;
	if (c.nr_valori > 0 && c.valori != nullptr)
		for (int i = 0;i < c.nr_valori;i++)
			out << c.valori[i] << " ";
	return out;
}
istream& operator>>(istream& in, valori_coloana<float>& c)
{
	in >> (coloana&)c;
	in >> c.valoare_default;
	in >> c.nr_valori;
	if (c.valori != nullptr)
		delete[]c.valori;
	c.valori = new float[c.nr_valori];
	for (int i = 0;i < c.nr_valori;i++)
		in >> c.valori[i];
	return in;

}
class tabela
{private:
	string nume_tabela;
	coloana* c;
	valori_coloana<int>* valori_int;
	valori_coloana<string>* valori_string;
	valori_coloana<float>* valori_float;
	int nr_coloane;
	int nr_valori_int;
	int nr_valori_string;
	int nr_valori_float;
	
public:
	tabela()
	{
		nume_tabela = "";
		c = nullptr;
		nr_coloane = 0;
	 valori_int=nullptr;
	 valori_string = nullptr;;
	 valori_float=nullptr;
		 nr_valori_int=0;
		 nr_valori_string=0;
		 nr_valori_float=0;

	}
	tabela(string nume_tabela,int nr_coloane,coloana* c, valori_coloana<int>* valori_int, valori_coloana<string>* valori_string, valori_coloana<float>* valori_float,int nr_valori_int,int nr_valori_string,int nr_valori_float)
	{
		this->nume_tabela = nume_tabela;
		this->nr_coloane = nr_coloane;
		this->c = new coloana[nr_coloane];
		for (int i = 0;i < nr_coloane;i++)
			this->c[i] = c[i];
		if (valori_int != nullptr && nr_valori_int > 0)
		{
			this->nr_valori_int = nr_valori_int;
			for (int i = 0;i < nr_valori_int;i++)
				this->valori_int[i] = valori_int[i];
		}
		else {
			this->valori_int= nullptr;
			this->nr_valori_int = 0;
			
		}
		if (valori_string != nullptr && nr_valori_string > 0)
		{
			this->nr_valori_string = nr_valori_string;
			for (int i = 0;i < nr_valori_string;i++)
				this->valori_string[i] = valori_string[i];
		}
		else {
			this->valori_string = nullptr;
			this->nr_valori_string = 0;

		}
		if (valori_float != nullptr && nr_valori_float > 0)
		{
			this->nr_valori_float = nr_valori_float;
			for (int i = 0;i < nr_valori_float;i++)
				this->valori_float[i] = valori_float[i];
		}
		else {
			this->valori_float = nullptr;
			this->nr_valori_float = 0;

		}
	}
	tabela(string nume_tabel)
	{
		this->nume_tabela = nume_tabel;
		c = nullptr;
		nr_coloane = 0;
		valori_int = nullptr;
		valori_string = nullptr;
		valori_float = nullptr;
		nr_valori_int = 0;
		nr_valori_string = 0;
		nr_valori_float = 0;
	}
	int get_nr_coloane()
	{
		return nr_coloane;
	}
	 string get_nume_tabela()
	{
		return  nume_tabela;
	}
	tabela (const tabela& t)
	{
		nume_tabela = t.nume_tabela;
		nr_coloane = t.nr_coloane;
		c = new coloana[nr_coloane];
		for (int i = 0;i < nr_coloane;i++)
			c[i] = t.c[i];
		if (t.valori_int != nullptr && t.nr_valori_int > 0)
		{
			valori_int = new valori_coloana<int>[t.nr_valori_int];
			this->nr_valori_int = t.nr_valori_int;
			for (int i = 0;i < t.nr_valori_int;i++)
				this->valori_int[i] = t.valori_int[i];
		}
		else {
			this->valori_int = nullptr;
			this->nr_valori_int = 0;

		}
		if (t.valori_string != nullptr && t.nr_valori_string > 0)
		{
			valori_string = new valori_coloana<string>[t.nr_valori_string];
			this->nr_valori_string = t.nr_valori_string;
			for (int i = 0;i < t.nr_valori_string;i++)
				this->valori_string[i] = t.valori_string[i];
		}
		else {
			this->valori_string = nullptr;
			this->nr_valori_string = 0;

		}
		if (t.valori_float != nullptr && t.nr_valori_float > 0)
		{
			valori_float = new valori_coloana<float>[t.nr_valori_float];
			this->nr_valori_float = t.nr_valori_float;
			for (int i = 0;i < t.nr_valori_float;i++)
				this->valori_float[i] = t.valori_float[i];
		}
		else {
			this->valori_float = nullptr;
			this->nr_valori_float = 0;

		}
	}
	~tabela()
	{
		if(c!=nullptr)
			    delete[] c;
		

	}
	tabela& operator=(const tabela& t)
	{
		if (c != nullptr)
		
			delete[] c;
	
		
		
		nume_tabela = t.nume_tabela;
		nr_coloane = t.nr_coloane;
		c = new coloana[nr_coloane];
		for (int i = 0;i < nr_coloane;i++)
			c[i] = t.c[i];
		if (t.valori_int != nullptr && t.nr_valori_int > 0)
		{
			this->nr_valori_int = t.nr_valori_int;
			valori_int = new valori_coloana<int>[t.nr_valori_int];
			for (int i = 0;i < t.nr_valori_int;i++)
				this->valori_int[i] = t.valori_int[i];
		}
		else {
			this->valori_int = nullptr;
			this->nr_valori_int = 0;

		}
		if (t.valori_string != nullptr && t.nr_valori_string > 0)
		{
			valori_string = new valori_coloana<string>[t.nr_valori_string];
			this->nr_valori_string = t.nr_valori_string;
			for (int i = 0;i < t.nr_valori_string;i++)
				this->valori_string[i] = t.valori_string[i];
		}
		else {
			this->valori_string = nullptr;
			this->nr_valori_string = 0;

		}
		if (t.valori_float != nullptr && t.nr_valori_float > 0)
		{
			valori_float = new valori_coloana<float>[t.nr_valori_float];
			this->nr_valori_float = t.nr_valori_float;
			for (int i = 0;i < t.nr_valori_float;i++)
				this->valori_float[i] = t.valori_float[i];
		}
		else {
			this->valori_float = nullptr;
			this->nr_valori_float = 0;

		}
		return *this;
	}
	void adauga_coloana(coloana col_nou)
	{
		coloana* copie = new coloana[nr_coloane + 1];
		for (int i = 0;i < nr_coloane;i++)
			copie[i] = c[i];
		copie[nr_coloane] = col_nou;
		delete[] c;
		c = nullptr;
		nr_coloane++;
		c = new coloana[nr_coloane];
		for (int i = 0;i < nr_coloane;i++)
			c[i] = copie[i];
		delete[] copie;
	}
	
	string get_denumiri_coloane(int i)
	{
		return c[i].get_denumire_coloana();
	}
	void adauga_coloana_int(valori_coloana <int>val_col)
	{
		
		
			valori_coloana<int>* copie = new valori_coloana<int>[nr_valori_int + 1];
			for (int i = 0;i < nr_valori_int;i++)
				copie[i] = valori_int[i];
			copie[nr_valori_int] = val_col;
			delete[] valori_int;
			valori_int = nullptr;
			nr_valori_int++;
			valori_int = new valori_coloana<int>[nr_valori_int];
			for (int i = 0;i < nr_valori_int;i++)
				valori_int[i] = copie[i];
			delete[] copie;
		
		
		
	}
	void adauga_coloana_float(valori_coloana <float>val_col)
	{
		valori_coloana<float>* copie = new valori_coloana<float>[nr_valori_float + 1];
		for (int i = 0;i < nr_valori_float;i++)
			copie[i] = valori_float[i];
		copie[nr_valori_float] = val_col;
		delete[] valori_float;
		valori_float = nullptr;
		nr_valori_float++;
		valori_float = new valori_coloana<float>[nr_valori_float];
		for (int i = 0;i < nr_valori_float;i++)
			valori_float[i] = copie[i];
		delete[] copie;

	}
	void adauga_coloana_string(valori_coloana <string>val_col)
	{
		
		
			valori_coloana<string>* copie = new valori_coloana<string>[nr_valori_string + 1];
			for (int i = 0;i < nr_valori_string;i++)
				copie[i] = valori_string[i];
			copie[nr_valori_string] = val_col;
			delete[] valori_string;
			valori_string = nullptr;
			nr_valori_string++;
			valori_string = new valori_coloana<string>[nr_valori_string];
			for (int i = 0;i < nr_valori_string;i++)
				valori_string[i] = copie[i];
			delete[] copie;
		

	}
	void sterge_coloana_int(string nume_coloana)
	{
	
		valori_coloana<int>* copie = new valori_coloana<int>[nr_valori_int];
		
		for (int i = 0;i < nr_valori_int;i++)
		{
			if (nume_coloana == valori_int[i].get_denumire_coloana())
				valori_int[i].sterge();
copie[i] = valori_int[i];
		}
		delete[] valori_int;
		valori_int = nullptr;
		
		valori_int = new valori_coloana<int>[nr_valori_int];
		for (int i = 0;i < nr_valori_int;i++)
			valori_int[i] = copie[i];
		delete[] copie;
	}
	void sterge_coloana_float(string nume_coloana)
	{
		valori_coloana<float>* copie = new valori_coloana<float>[nr_valori_float];
		for (int i = 0;i < nr_valori_float;i++)
		{
			if (nume_coloana == valori_float[i].get_denumire_coloana())
				valori_float[i].sterge();
				copie[i] = valori_float[i];
		}
		delete[] valori_float;
		valori_float = nullptr;
		
		valori_float = new valori_coloana<float>[nr_valori_float];
		for (int i = 0;i < nr_valori_float;i++)
			valori_float[i] = copie[i];
		delete[] copie;
	}
	void sterge_coloana_string(string nume_coloana)
	{
		valori_coloana<string>* copie = new valori_coloana<string>[nr_valori_string];
		for (int i = 0;i < nr_valori_string;i++)
		{
			if (nume_coloana == valori_string[i].get_denumire_coloana())
				valori_string[i].sterge();
				copie[i] = valori_string[i];
		}
		delete[] valori_string;
		valori_string = nullptr;
		
		valori_string = new valori_coloana<string>[nr_valori_string];
		for (int i = 0;i < nr_valori_string;i++)
			valori_string[i] = copie[i];
		delete[] copie;

	}
	int get_valoare_int(int k, int i)
	{
		return valori_int[k][i];
	}
	string get_valoare_string(int k, int i)
	{
		return valori_string[k][i];
	}
	/*string get_valoare_float(int k, int i)
	{
		return valori_float[k][i];
	}*/

	string get_tipul_coloana(int k)
	{
		return c[k].get_tip();

	}
	coloana& operator[](int index)
	{
		if (index >= 0 && index < nr_coloane)
			return c[index];
	}
	tabela operator+(int val)
	{
		if (val > 0)
		{
			tabela copie = *this;
			for (int i = 0;i < nr_valori_int;i++)
				valori_int[i] = valori_int[i] + val;
		}
	}
	tabela operator++()
	{
		nr_coloane++;
		return *this;
	}
	tabela operator++(int i)
	{
		tabela copie = *this;
		nr_coloane++;
		return copie;

	}
	int operator()()
	{
		return nr_coloane;
	}
	bool operator!()
	{
		return nr_coloane > 0;
	}
	bool operator<(int val)
	{
		if (nr_valori_int < val) return true;
		else return false;
	}
	bool operator==(tabela t)
	{
		int ok = 1;
		int nr = 0;
		if (nume_tabela != t.nume_tabela)ok = 0;
		if (nr_coloane != t.nr_coloane)ok = 0;
		if (nr_valori_int != t.nr_valori_int) ok = 0;
		if (nr_valori_string != t.nr_valori_string) ok = 0;
		if (nr_valori_float != t.nr_valori_float) ok = 0;
		for(int i=0;i<nr_coloane;i++)
			if(c[i]==t.c[i]) 
			{
				nr++;
			}
			else 
			{
				ok = 0;break;
			}
		nr = 0;
		for (int i = 0;i < nr_valori_int;i++)
			if (valori_int[i] == t.valori_int[i])
			{
				nr++;
			}
			else
			{
				ok = 0;break;
			}
		for (int i = 0;i < nr_valori_string;i++)
			if (valori_string[i] == t.valori_string[i])
			{
				nr++;
			}
			else
			{
				ok = 0;break;
			}
		for (int i = 0;i < nr_valori_float;i++)
			if (valori_float[i] == t.valori_float[i])
			{
				nr++;
			}
			else
			{
				ok = 0;break;
			}
		return ok;

	}
	void adauga_valoare_la_coloana_int(int k,int val)
	{
		
		valori_coloana<int>* copie = new valori_coloana<int>[nr_valori_int];
		for (int i = 0;i < nr_valori_int;i++)
		{
			if (i == k) valori_int[k].insert(val);
				copie[i] = valori_int[i];
		}
		
		delete[] valori_int;
		valori_int = nullptr;
		valori_int = new valori_coloana<int>[nr_valori_int];
		for (int i = 0;i < nr_valori_int;i++)
			valori_int[i] = copie[i];
		delete[] copie;
	}
		void adauga_valoare_la_coloana_string(int k,string val)
		{
			valori_string[k].insert(val);
			valori_coloana<float>* copie = new valori_coloana<float>[nr_valori_float];
			for (int i = 0;i < nr_valori_float;i++)
				copie[i] = valori_float[i];
			
			delete[] valori_float;
			valori_float = nullptr;
			
			valori_float = new valori_coloana<float>[nr_valori_float];
			for (int i = 0;i < nr_valori_float;i++)
				valori_float[i] = copie[i];
			delete[] copie;
		}
		void adauga_valoare_la_coloana_float(int k,float val)

		{
			valori_float[k].insert(val);
			valori_coloana<string>* copie = new valori_coloana<string>[nr_valori_string];
			for (int i = 0;i < nr_valori_string;i++)
				copie[i] = valori_string[i];
		
			delete[] valori_string;
			valori_string = nullptr;
		
			valori_string = new valori_coloana<string>[nr_valori_string];
			for (int i = 0;i < nr_valori_string;i++)
				valori_string[i] = copie[i];
			delete[] copie;
		}
		int get_nr_coloane_int()
		{
			return nr_valori_int;
		}
			int get_nr_coloane_float()
			{
				return nr_valori_float;
			}
			int get_nr_coloane_string()
			{
				return nr_valori_string;
			}
			string get_denumire_col_val_int(int k)
			{
				return valori_int[k].get_denumire_coloana();
			}
			string get_denumire_col_val_string(int k)
			{
				return valori_string[k].get_denumire_coloana();
			}
			string get_denumire_col_val_float(int k)
			{
				return valori_float[k].get_denumire_coloana();
			}
			coloana* get_coloane()
			{
				coloana* copie = new coloana[nr_coloane];
				for (int i = 0;i < nr_coloane;i++)
					copie[i] = c[i];
				return copie;

	        }
			valori_coloana<int>* get_valori_coloana_int()
			{
				valori_coloana<int>* copie = new valori_coloana<int>[nr_valori_int];
				for (int i = 0;i < nr_valori_int;i++)
					copie[i] = valori_int[i];
				return copie;
            }
			valori_coloana<string>* get_valori_coloana_string()
			{
				valori_coloana<string>* copie = new valori_coloana<string>[nr_valori_string];
				for (int i = 0;i < nr_valori_string;i++)
					copie[i] = valori_string[i];
				return copie;
			}
			valori_coloana<float>* get_valori_coloana_float()
			{
				valori_coloana<float>* copie = new valori_coloana<float>[nr_valori_float];
				for (int i = 0;i < nr_valori_float;i++)
					copie[i] = valori_float[i];
				return copie;
			}
			void set_nume_tabela(string nume)
			{
				if (nume != "")
					nume_tabela = nume;
			}
			void set_nr_coloane(int nr)
			{
				if (nr > 0)
					nr_coloane = nr;
				else nr_coloane = 0;
			}
			void set_nr_coloane_int(int nr)
			{
				if (nr > 0)
					nr_valori_int = nr;
				else nr_valori_int = 0;
			}
			void set_nr_coloane_string(int nr)
			{
				if (nr > 0)
					nr_valori_string = nr;
				else nr_valori_string = 0;
			}
			void set_nr_coloane_float(int nr)
			{
				if (nr > 0)
					nr_valori_float = nr;
				else nr_valori_float = 0;
			}
			void set_coloane(coloana* c1, int nr_c1)
			{
				if (c1!=nullptr&&nr_c1>0)
				{
					if (c != nullptr)
						delete[] c;
					nr_coloane = nr_c1;
					c = new coloana[nr_c1];
					for (int i = 0;i < nr_c1;i++)
						c[i] = c1[i];
				}
				else
				{
					c = nullptr;
					nr_coloane = 0;
				}
			}
			void set_coloane_int(valori_coloana<int>* c, int nr_c)
			{


				if (c != nullptr && nr_c > 0)
				{
					if (valori_int != nullptr)
						delete[] valori_int;
					nr_valori_int = nr_c;
					valori_int = new valori_coloana<int>[nr_c];
					for (int i = 0;i < nr_c;i++)
						valori_int[i] = c[i];

				}
				else
				{
					valori_int = nullptr;
					nr_valori_int = 0;
				}
			}
			void set_coloane_string(valori_coloana<string>* c, int nr_c)
			{


				if (c != nullptr && nr_c > 0)
				{
					if (valori_string != nullptr)
						delete[] valori_string;
					nr_valori_string = nr_c;
					valori_string = new valori_coloana<string>[nr_c];
					for (int i = 0;i < nr_c;i++)
						valori_string[i] = c[i];

				}
				else
				{
					valori_string = nullptr;
					nr_valori_string = 0;
				}
			}
			void set_coloane_float(valori_coloana<float>* c, int nr_c)
			{


				if (c != nullptr && nr_c > 0)
				{
					if (valori_float != nullptr)
						delete[] valori_float;
					nr_valori_float = nr_c;
					valori_float = new valori_coloana<float>[nr_c];
					for (int i = 0;i < nr_c;i++)
						valori_float[i] = c[i];

				}
				else
				{
					valori_float = nullptr;
					nr_valori_float = 0;
				}
			}
			friend ostream& operator<<(ostream&, tabela );
			friend istream& operator>>(istream&, tabela& );

};
ostream& operator<<(ostream& out, tabela t)
{
	out << t.nume_tabela << endl;
	out << t.nr_coloane << endl;
	out << t.nr_valori_int << endl;
	out << t.nr_valori_float << endl;
	out << t.nr_valori_string << endl;
	if (t.c != nullptr)
		for (int i = 0;i < t.nr_coloane;i++)
			out << t.c[i]<<" ";
	out << endl;
	if (t.valori_int != nullptr)
		for (int i = 0;i < t.nr_valori_int;i++)
			out << t.valori_int[i] << " ";
	out << endl;
	if (t.valori_string != nullptr)
		for (int i = 0;i < t.nr_valori_string;i++)
			out << t.valori_string[i] << " ";
	out << endl;
	if (t.valori_float != nullptr)
		for (int i = 0;i < t.nr_valori_float;i++)
			out << t.valori_float[i] << " ";
	return out;


 }
istream& operator>>(istream& in, tabela& t)
{
	in >> t.nume_tabela;
	in >> t.nr_coloane;
	in >> t.nr_valori_int;
	in >> t.nr_valori_string;
	in >> t.nr_valori_float;
	if (t.c != nullptr)
		delete[] t.c;
	if (t.valori_int != nullptr)
		delete[] t.valori_int;
	if (t.valori_string != nullptr)
		delete[] t.valori_string;
	if (t.valori_float != nullptr)
		delete[] t.valori_float;
	t.c = new coloana[t.nr_coloane];
	t.valori_int = new valori_coloana<int>[t.nr_valori_int];
	t.valori_float = new valori_coloana<float>[t.nr_valori_float];
	t.valori_string = new valori_coloana<string>[t.nr_valori_string];
	for (int i = 0;i < t.nr_coloane;i++)
		in >> t.c[i];
	for (int i = 0;i < t.nr_valori_int;i++)
		in >> t.valori_int[i];
	for (int i = 0;i < t.nr_valori_float;i++)
		in >> t.valori_float[i];
	for (int i = 0;i < t.nr_valori_string;i++)
		in >> t.valori_string[i];
	return in;


}
class baza_de_date
{
private:
	int nr_tabele;
	tabela* t;
public:
	baza_de_date()
	{
		nr_tabele = 0;
		t = nullptr;
	}
	baza_de_date(const baza_de_date& b)
	{
		this->nr_tabele = b.nr_tabele;;
		this->t = new tabela[nr_tabele];
		for (int i = 0;i < nr_tabele;i++)
			this->t[i] = b.t[i];
	}
	~baza_de_date()
	{
		if (t != nullptr)
			delete[] t;

	}
	baza_de_date& operator=(const baza_de_date& b)
	{
		if (t != nullptr)
			delete[] t;
		this->nr_tabele = b.nr_tabele;;
		this->t = new tabela[nr_tabele];
		for (int i = 0;i < nr_tabele;i++)
			this->t[i] = b.t[i];
		return *this;
	}

	void adauga_tabela( tabela tab_nou)
	{
		if (t != nullptr)
		{
			tabela* copie_t = new tabela[nr_tabele + 1];
			for (int i = 0;i < nr_tabele;i++)
				copie_t[i] = t[i];

			copie_t[nr_tabele] = tab_nou;

			delete[] t;
			t = nullptr;
			nr_tabele++;
			t = new tabela[nr_tabele];
			
			for (int i = 0;i < nr_tabele;i++)
				t[i] = copie_t[i];
			delete[] copie_t;
		}
		else {
			t = new tabela[1];
			t[0] = tab_nou;
			nr_tabele++;
		}


	}
	void stergere_tabela(string nume_tabela)
	{
		tabela* copie = new tabela[nr_tabele-1];
		for (int i = 0;i < nr_tabele;i++)
			if(t[i].get_nume_tabela()!=nume_tabela) copie[i] = t[i];
		
		nr_tabele--;
		delete[] t;
		t = new tabela[nr_tabele];
		for (int i = 0;i < nr_tabele;i++)
			t[i] = copie[i];
		delete[] copie;

	}
	int get_nr_tabele()
	{
		return nr_tabele;
	}
	tabela* get_tabele()
	{
		tabela* copie = new tabela[nr_tabele];
		for (int i = 0;i < nr_tabele;i++)
			copie[i] = t[i];
		return copie;
	}
	void set_nr_tabele(int nr)
	{
		if (nr > 0)
			nr_tabele = nr;
		else nr_tabele = 0;
	}
	void set_tabele(tabela* t1,int nr)
	{
		if (nr > 0 && t1 != nullptr)
		{
			if (t != nullptr)
				delete[] t;
			nr_tabele = nr;
			t = new tabela[nr];
			for (int i = 0;i < nr;i++)
				t[i] = t1[i];
	    }
		else
		{
			t = nullptr;
			nr_tabele = 0;

		}
	}
	string get_nume_tabela_i(int i)
	{
		return t[i].get_nume_tabela();
	}
	int get_nr_coloane_tabela_i(int i)
	{
		return t[i].get_nr_coloane();
	}
  string get_denumire_coloane_tabela_i(int i, int k)
	{
		return t[i].get_denumiri_coloane(k);
	}
 
  string get_tipul_coloana_tabela(int i, int k)
  {
	  return t[i].get_tipul_coloana(k);
	  tabela* copie_t = new tabela[nr_tabele];
	  for (int i = 0;i < nr_tabele;i++)
		  copie_t[i] = t[i];

	  delete[] t;
	  t = nullptr;
	
	  t = new tabela[nr_tabele];

	  for (int i = 0;i < nr_tabele;i++)
		  t[i] = copie_t[i];
	  delete[] copie_t;
  }
  void adauga_val_int_tabela(int l, int k, int val)
  {
	  tabela copie = t[l];
	  copie.adauga_valoare_la_coloana_int(k, val);
	  t[l] = copie;


  }
  void adauga_val_string_tabela(int i, int k, string val)
  {
	  t[i].adauga_valoare_la_coloana_string(k, val);
	  
	  tabela* copie_t = new tabela[nr_tabele];
	  for (int i = 0;i < nr_tabele;i++)
		  copie_t[i] = t[i];

	  delete[] t;
	  t = nullptr;

	  t = new tabela[nr_tabele];

	  for (int i = 0;i < nr_tabele;i++)
		  t[i] = copie_t[i];
	  delete[] copie_t;
	  }
  void adauga_val_float_tabela(int i, int k, float val)
  {
	  t[i].adauga_valoare_la_coloana_float(k, val);

	  }
  int get_nr_coloane_int_tabela(int i)
  {
	  return t[i].get_nr_coloane_int();
  }
  int get_nr_colaone_float_tabela(int i)
  {
	  return t[i].get_nr_coloane_float();

	  }
  int get_nr_coloane_string_tabela(int i)
  {
	  return t[i].get_nr_coloane_string();
	  }
  tabela operator[](int index)
  {if(index>=0&&index<nr_tabele)
	  return t[index];
  }
  baza_de_date operator+(int val)
  {
	  baza_de_date copie = *this;
	  copie.nr_tabele = copie.nr_tabele + val;
	  return copie;
  }
  baza_de_date operator++()
  {
	  nr_tabele++;
	  return *this;
  }
  baza_de_date operator++(int i)
  {
	  baza_de_date copie = *this;
	  nr_tabele++;
	  return copie;
  }
  int operator()()
  {
	  return nr_tabele;
  }
  bool operator!()
  {
	  return nr_tabele > 0;
  }
  bool operator<(int val)
  {
	  if (nr_tabele < val) return true;
	  else return false;
  }
  bool operator==(baza_de_date bd)
  {
	  int ok = 1;
	  int nr = 0;
	  if (nr_tabele != bd.nr_tabele) ok = 0;
	  for (int i = 0;i < nr_tabele;i++)
		  if (t[i] == bd.t[i]) nr++;
		  else { ok = 0;break; }
	  return ok;
  }
  string get_denumire_coloana_k_i(int i,int  k)
  {
	  return t[i].get_denumiri_coloane(k);
  }
  void sterge_coloana_din_tabela_i(int i,int k, string nume)
  {
	
	  if (t[i].get_tipul_coloana(k) == "integer")  t[i].sterge_coloana_int(nume);
	  else if (t[i].get_tipul_coloana(k) == "text") t[i].sterge_coloana_string(nume);
	  else t[i].sterge_coloana_float(nume);
	
	  
  }
  friend ostream& operator<<(ostream& , baza_de_date );
  friend istream& operator>>(istream& , baza_de_date&);
};
ostream& operator<<(ostream& out, baza_de_date bd)
{
	out << bd.nr_tabele<<endl;
	if (bd.nr_tabele > 0 && bd.t != nullptr)
		for (int i = 0;i < bd.nr_tabele;i++)
			out << bd.t[i] << endl;
	return out;
}
istream& operator>>(istream& in, baza_de_date& bd)
{
	in >> bd.nr_tabele;
	if (bd.t != nullptr)
		delete[] bd.t;
	bd.t = new tabela[bd.nr_tabele];
	for (int i = 0;i < bd.nr_tabele;i++)
		in >> bd.t[i];
	return in;
}
class comanda
{
	baza_de_date bd;
	string c;
};


int main() 
{

	baza_de_date bd;
	coloana c1("nume", "text", 20);
	coloana c2("varsta", "integer", 2);
	coloana c7("organizatie", "text", 20);
	tabela t("student");
	tabela t1("voluntar");
	t.adauga_coloana(c1);
	t.adauga_coloana(c2);
	t1.adauga_coloana(c1);
	t1.adauga_coloana(c2);
	t1.adauga_coloana(c7);
	valori_coloana<string> c3("Aninim","nume");
	valori_coloana<int> c4(18,"varsta");
	valori_coloana<string>c8("sisc", "organizatie");
	int nr_inserari = 0;
	c4.insert(5);
	c4.insert(6);
	c4.insert(7);
	c3.insert("Roxana");
	c3.insert("dan");
	c8.insert("sisc");
	c8.insert("boss");
	t.adauga_coloana_int(c4);
	t.adauga_coloana_string(c3);
	t1.adauga_coloana_int(c4);
	t1.adauga_coloana_string(c3);
	t1.adauga_coloana_string(c8);
	t.adauga_valoare_la_coloana_int(0, 8);
	t.adauga_valoare_la_coloana_int(0, 9);
	t.adauga_valoare_la_coloana_string(0, "gica");
	bd.adauga_tabela(t);
	bd.adauga_tabela(t1);
	bd.adauga_val_int_tabela(0,0,10);
	bd.adauga_val_int_tabela(0, 0, 2);
	bd.adauga_val_string_tabela(0, 0, "petru");
	
	char comanda[200], sep[] = " ,)(;=", *p, v[200][20];
	int k=0;
	cin.getline(comanda, 200);
	p = strtok(comanda, sep);
	
	while (p != NULL)
	{
		strcpy_s(v[k++], strlen(p) + 1, p);
		p = strtok(NULL, sep);
		
	}
	
	//DISPLAY TABLE table_name
	
	if (strcmp(v[0],"DISPLAY")==0)
	{
		string nume_tabela = v[2];
		
		for (int i = 0;i < bd.get_nr_tabele();i++)
			if (bd.get_nume_tabela_i(i) == nume_tabela)
				for (int k = 0;k < bd.get_nr_coloane_tabela_i(i);k++)
					cout << bd.get_denumire_coloane_tabela_i(i, k) << " ";

	}
	//DROP TABEL TABLE_NAME
	if (strcmp(v[0], "DROP")==0)
	{
		string nume_tabela=v[2];
		for (int i = 0;i < bd.get_nr_tabele();i++)
			if (bd.get_nume_tabela_i(i) == nume_tabela)
				bd.stergere_tabela(nume_tabela);
		cout << "tabela a fost stearsa";
		cout << bd.get_nr_tabele();
		
	}
	//create tabel
	if (strcmp(v[0], "CREATE") == 0)
	{
		tabela* t = new tabela(v[2]);
		for (int i = 3;i < k;i = i + 4)
		{
			coloana* col_nou = new coloana(v[i], v[i + 1], atoi(v[i + 2]));
			if (strcmp(v[i + 1], "text") == 0)
			{
				valori_coloana<string>* val_col = new valori_coloana<string>(v[i + 3],v[i]);
				
				t->adauga_coloana_string(*val_col);
				delete val_col;
			}
			if (strcmp(v[i + 1], "integer") == 0)
			{
				valori_coloana<int>* val_col = new valori_coloana<int>(atoi(v[i + 3]),v[i]);
				
				t->adauga_coloana_int(*val_col);
				delete val_col;
			}
			else
			{
				valori_coloana<float>* val_col = new valori_coloana<float>(atof(v[i + 3]),v[i]);
				
				t->adauga_coloana(*val_col);
				delete val_col;
			}
			t->adauga_coloana(*col_nou);
			delete col_nou;
			
		}
		bd.adauga_tabela(*t);
		
		delete t;
	}
	int nr_cuvinte = k;
	//insert INSERT INTO nume_tabela VALUES(...)
	if (strcmp(v[0], "INSERT") == 0)
	{
		int nr_coloane_int_adaugate = 0;
		int nr_coloane_float_adaugate = 0;
		int nr_coloane_string_adaugate = 0;
		int nr_val = 4;
	
	
		string nume_tabela = v[2];
		cout << nume_tabela;
		for (int i = 0;i < bd.get_nr_tabele();i++)
			if (bd.get_nume_tabela_i(i) == nume_tabela)
			{
				
				for (int k = 0;k < bd.get_nr_coloane_tabela_i(i);k++)
				{
					
					if (bd.get_tipul_coloana_tabela(i, k) == "integer")
					{
						bd.adauga_val_int_tabela(i, nr_coloane_int_adaugate, atoi(v[nr_val]));
						nr_coloane_int_adaugate++;
						
					nr_val++;
						

					}
					else if (bd.get_tipul_coloana_tabela(i, k) == "text")
					{
						bd.adauga_val_string_tabela(i, nr_coloane_string_adaugate, v[nr_val]);
						nr_coloane_string_adaugate++;
						
					nr_val++;
					}
					else
					{
						bd.adauga_val_float_tabela(i, nr_coloane_float_adaugate, atof(v[nr_val]));
						nr_coloane_float_adaugate++;
						nr_val++;
					}

				}
				
			}
		nr_inserari++;
	}

	//select
	nr_inserari = 2;
	if (strcmp(v[0], "SELECT") == 0)
	{
		if(strcmp(v[1],"ALL")==0)
			
		for (int i = 0;i < bd.get_nr_tabele();i++)
			if (bd.get_nume_tabela_i(i) == v[3])
			{
				int nr_int = 0;
				int nr_float = 0;
				int nr_string = 0;
			
				for (int k = 0;k < bd.get_nr_coloane_tabela_i(i);k++)
				{
					cout << bd[i][k].get_denumire_coloana() << " ";
				}
				cout << endl;
				for (int d = 0;d < nr_inserari;d++)
				{
					for (int k = 0;k < bd.get_nr_coloane_tabela_i(i);k++)

					{
						if (bd.get_tipul_coloana_tabela(i, k) == "integer")
						{
							cout << bd[i].get_valoare_int(k, d) << " ";
							

						}
						else if (bd.get_tipul_coloana_tabela(i, k) == "text")
						{
							cout << bd[i].get_valoare_string(k, d) << " ";
							
						}
						else {
							//cout << bd[i].get_valoare_float(k, d);
						}

					}
					cout << endl;
				}
			}
	}
	
//delete DELETE FROM nume_tabela WHERE nume_coloană = valoare
	if (strcmp(v[0], "DELETE") == 0)
	{
		int ok = 0;

			for (int i = 0;i < bd.get_nr_tabele();i++)
				if (bd.get_nume_tabela_i(i) == v[2])
				{
					
					for (int k = 0;k < bd.get_nr_coloane_tabela_i(i);k++)
					{
						
						if (bd.get_denumire_coloana_k_i(i, k) == v[5])
						{
							
							bd.sterge_coloana_din_tabela_i(i, k, v[5]);
						}
					}
				}
	}
	
	

}
