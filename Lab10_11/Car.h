#pragma once
#include <string>
using namespace std;
class Car {
private:
	int nrInmatr;
	string prod;
	string model;
	string tip;

	static int nrAp;
public:
	/*Defaul constructor, sets nrInmatr to 0, and empty strings*/
	Car();
	/* Construct a car from const int nrInmatr, const  string prod, const string model, const string tip */
	Car(const int nrInmatr, const  string prod, const string model, const string tip);
	/* Constructor pentru car doar cu const int nrImatr, celelalte campuri sunt vide*/
	Car(const int nrInmatr);
	/* Constructor pentru copiere*/
	Car(const Car& ot);
	// getters 
	/* Returneaza nrInmatriculare al unei masini*/
	const int getNrInmatr() const noexcept;
	/*Returneaza stringul producator al unei masini */
	string getProd() const;
	/*Returneaza strigul model al unei masin*/
	string getModel()const;
	/*Returneaza stringul tip al unei masini*/
	string getTip() const;
	// setters 
	/* Seteaza campul producator al unei masini cu valoarea parameturlui string s*/
	void setProd(string s);;
	/* Seteaza campul model al unei masini cu valoarea parameturlui string s*/
	void setModel(string s);
	/* Seteaza campul tip al unei masini cu valoarea parameturlui string s*/
	void setTip(string s);
	// operators
	/* Pentru testarea egalitaii se testeaza egalitatea nr de inmatriculare */
	bool operator== (const Car& c) const noexcept;
	/* Operatorul de atribuire seteaza toate campurile obiectului curent la valorile obiectului c*/
	Car& operator= (const Car& other);
	/* Pentru afisare */
	friend std::ostream& operator<<(std::ostream& out, const Car& c);
	~Car();
};

class Validator {
public:
	bool validate(const Car& c) {
		if (c.getNrInmatr() <= 0 || c.getProd() == "" || c.getModel() == "" || c.getTip() == "")
			return false;
		return true;
	};
};


class CarDTO {
public:
	string tip;
	int count;
	CarDTO(const string& t, int c) :tip{ t }, count{ c }{};
	CarDTO() :tip{ "" }, count{ 0 }{};
	void incr() noexcept {
		this->count++;
	};
	CarDTO& operator=(const CarDTO& other)
	{
		this->count = other.count;
		this->tip = other.tip;
		return *this;
	}


};