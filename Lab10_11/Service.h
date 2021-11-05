#pragma once
#include "Repository.h"
#include "Car.h"
#include "UndoAction.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include "Carwash.h"
typedef bool (*cmpFunction)(const Car& c1, const Car& c2);
using std::unique_ptr;



class Service
{
private:
	AbstractRepo& repo;

	// Repository washRepo;
	Carwash wash;

	Validator validator;
	vector <string> fileNames;
	//vector <unique_ptr < UndoAction > > undoList;
	vector <UndoAction*> undoList;

public:
	/*Constructor service obligatoriu contine un obiect Repository*/
	Service(AbstractRepo& r) : repo{ r }, wash(r) {};
	Service() = delete;
	~Service() {
		for (const auto& x : fileNames)
		{
			std::ofstream ofs(x);
			ofs.open(x, ios::out | ios::trunc);
			ofs.close();
		}
		for (auto act : undoList)
			delete act;
	};

	/* Returneaza un vector cu toate obiectele Car salvate*/
	vector <Car> getAll();
	/* Construieste si valideaza un obiect Car si il adauga in lista
	Arunca exceptii daca: -nr <= 0 sau unul dintre stringuri este vid
					daca: - exista o masina cu acelasi nr de inmatriculare salvata
	*/
	void add(const int nr, string prod, string model, string tip);
	/*Elimina un obiect masina din lista, obiectul trebuie sa aiba acelasi nr de inmatriculare
	Arunca exceptii daca nu exista o masina cu acest nr de inmatriculare*/
	void sterge(const int nr);
	/*Modifica campurile producator,model si tip al unei masini ce are acelasi nr de inmatriculare
	ca parametrul const in nr
	Arunca exceptie daca un string este vid sau nu exista o masina adaugata cu acelasi nr de inmatricular*/
	void modifica(const int nr, string prod, string model, string tip);
	/*Cauta un obiect masina ce are acelasi nr de inmatriculare
	Arunca exceptie daca nu exista */
	Car cauta(const int nr);
	/*Sorteaza lista de masini in functe de parametrul cmd
	cmd = 1 -> sorteaza dupa nrInmatriculare
	cmd = 2 -> sorteaza dupa tip
	cmd = 3 -> sorteaza dupa producator, iar in caz de egalitate dupa model*/
	void sorteaza(int cmd);
	/*Sorteaza prin metoda bubble sort un vector de obiecte Car in functie de functia de comparare*/
//	void bubbleSort(LSI<Car>& v, cmpFunction cF);


	/*Filtreaza obiectele care in functie de un camp, iar valoarea campului sa fie egala cu stringul nume
	daca Cmd =1 -> filtreaza dupa producator
	daca cmd =2 -> filtreaza dupa tip */
	vector <Car>  filtrare(int cmd, const string& name);

	/*Adauga o masina in lista pentru spalatorie
	Arunca exceptie de tipul RepoException daca nu exista o masina cu nr de inamtriculare*/
	void addWash(int nr);
	/*Returneaza o copie a listei cu masinile aflate in lista pentru spalatorie*/
	vector <Car> getWashList();
	/*Adauga in mod aleatoriu nr masini */
	void generate(int nr);
	/*Elimina toate masinile din lista pentru spalatorie*/
	void clearWashList();
	/*Exporta intr un fisier cu numele stringului s masinile selectate de utilizator in meniul de spalare*/
	void exportCSV(const string& s);

	/**/
	std::map < string, CarDTO> nrTip() {
		std::map < string, CarDTO> myMap;
		for (const Car& x : getAll()) {
			CarDTO c1(x.getTip(), 0);
			auto it = myMap.find(x.getTip());
			if (it == myMap.end()) {
				c1.count = 1;
				myMap.insert(make_pair(x.getTip(), c1));
			}
			else
				myMap[x.getTip()].incr();
		}
		return myMap;
	}

	/* Realizeaza operatia de undo asupra listei de masini */
	void undo();

	Carwash& getCarwash() {
		return wash;
	}
};

