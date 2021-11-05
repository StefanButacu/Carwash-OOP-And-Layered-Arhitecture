#pragma once
#include "Car.h"
#include "AbstractRepo.h"
#include <vector>
#include <gsl/gsl_ieee_utils.h>

class Repository : public AbstractRepo
{
private:
	std::vector < Car > v;

public:
	Repository() {};
	~Repository() {};
	virtual int size();
	/* Adauga un obiect masina
	Arunca exceptie de tipul RepoException daca masina este deja introdusa */
	virtual void append(const Car& c);
	/* Sterge un obiect masina si retureneaza obiectul sters
	Arunca exceptie de tipul RepoException daca masina NU este  introdusa */
	virtual Car remove(const Car& c);

	/*Modifica campurile Producator, Model, Tip al unui obiect masina salvat ce are acelasi nrInmatriculare
	ca obiectul Car c primit ca parametru
	Arunca exceptie de tipul RepoException daca masina NU este  introdusa
	*/
	virtual  void update(const Car& c);
	/*Returneaza un obiect masina care se afla in lista si are acelasi nr Inmatriculare ca obiectul Car c primit ca parametru
	Arunca exceptie daca nu exista*/
	virtual Car search(const Car& c);
	/*Returneaza lista cu toate obiectele masina*/
	//std::vector <Car>& getElems();
	virtual vector<Car>& getElems();

	/*Elimina toate elementele din repo*/
	virtual void clearElems();

	/*Returneaza elementul de pe o pozitie*/
	virtual Car getByPoz(int i);
};

class FileRepo :public Repository {
private:
	string fileName;
	void writeToFile();
	void loadFromFile();
public:
	FileRepo(const string& fileN);
	~FileRepo();
	void append(const Car& c) override;
	Car getByPoz(int i)override;
	Car remove(const Car& c) override;
	Car search(const Car& c) override;
	int size() override;
	void update(const Car& c)override;
	void clearElems()override;
	vector <Car>& getElems() override;

};