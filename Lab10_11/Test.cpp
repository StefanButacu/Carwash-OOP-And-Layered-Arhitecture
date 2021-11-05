#include "Test.h"
#include "Car.h"
#include "Repository.h"
#include "Service.h"
#include "Exception.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <exception>
#include <map>
using namespace std;

ofstream fout("out.txt");


void testDomain();
void testRepo();
void testService();
void testSortDublex();

void testWash();
void testUndo();
void testFileRepo();
void Test::testAll()
{
	testDomain();
	testRepo();
	testService();
	testSortDublex();
	testWash();
	
	testUndo();
	testFileRepo();
}
void testDomain() {
	Car c1 = Car(1, "a", "a", "a");
	assert(c1.getNrInmatr() == 1);
	assert(c1.getProd() == "a");
	assert(c1.getModel() == "a");
	assert(c1.getTip() == "a");
	Car c2 = Car(1, "b", "b", "b");
	assert(c1 == c2);
	c1.setTip("c");
	c1.setModel("c");
	c1.setProd("c");
	assert(c1.getProd() == "c");
	assert(c1.getModel() == "c");
	assert(c1.getTip() == "c");
	string s;
	fout << c1;
	fout.close();
	ifstream fin("out.txt");
	getline(fin, s);
	assert(s == "1 c c c");
	fin.close();
}
void testRepo() {
	Repository r;
	assert(r.size() == 0);
	Car c1 = Car(1, "a", "a", "a");
	r.append(Car(3, "c", "c", "c"));

	c1 = c1;
	r.append(c1);
	assert(r.size() == 2);
	r.remove(c1);
	assert(r.size() == 1);
	try {
		r.remove(c1);
		assert(false);
	}
	catch (const RepoException& err) {
		assert(err.getMessage() == "Masina nu exista!");
		assert(true);
	}
	r.append(c1);


	assert(r.size() == 2);
	Car c2 = Car(1, "b", "b", "b");
	r.update(c2);
	Car elem = r.search(Car(1, "", "", ""));
	try {
		Car c = r.search(Car(6, "", "", ""));
		assert(false);
	}
	catch (const RepoException& err) {
		assert(err.getMessage() == "Masina nu exista!");
		assert(true);
	}
	assert(elem.getNrInmatr() == 1);
	assert(elem.getProd() == "b");
	assert(elem.getModel() == "b");
	assert(elem.getTip() == "b");
	try {
		r.update(Car(5, "", "", ""));
		assert(false);
	}
	catch (const RepoException& err) {
		assert(err.getMessage() == "Masina nu exista!");
		assert(true);
	}

}
void testService() {
	Repository r;
	Service srv(r);
	vector <Car> AllCars = srv.getAll();
	assert(AllCars.size() == 0);
	srv.add(1, "a", "a", "a");
	srv.add(2, "b", "b", "a");
	AllCars = srv.getAll();
	assert(AllCars.size() == 2);
	try {
		srv.add(2, "b", "b", "a");  // duplicata
		assert(false);
	}
	catch (const RepoException& err) {
		assert(err.getMessage() == "Masina este deja introdusa!");
		assert(true);
	}

	try {
		srv.add(3, "", "", "");  // invalida 
		assert(false);
	}
	catch (const ValidationException& err) {
		assert(err.getMessage() == "Masina invalida!");
		assert(true);
	}
	srv.sterge(1);
	AllCars = srv.getAll();
	assert(AllCars.size() == 1);
	try {
		srv.sterge(1); // sterge inexistenta
		assert(false);
	}
	catch (const RepoException& err) {
		assert(err.getMessage() == "Masina nu exista!");
		assert(true);
	}

	srv.modifica(2, "b2", "b3", "b4");
	Car elem = srv.cauta(2);
	assert(elem.getNrInmatr() == 2);
	assert(elem.getProd() == "b2");
	assert(elem.getModel() == "b3");
	assert(elem.getTip() == "b4");
	try {
		srv.modifica(2, "", "", ""); // masina invalida
		assert(false);
	}
	catch (const ValidationException& err) {
		assert(err.getMessage() == "Masina invalida!");
		assert(true);
	}
	srv.sterge(2);
	assert(srv.getAll().size() == 0);
	srv.add(5, "aa", "bb", "cc");
	srv.add(4, "ab", "bc", "ca");
	srv.add(3, "aa", "aa", "ac");
	srv.add(1, "aa", "za", "cc");
	srv.add(2, "c", "aa", "cc");
	map < string, CarDTO > m = srv.nrTip();
	assert(m["cc"].count == 3);
	assert(m["ca"].count == 1);
	assert(m["ac"].count == 1);

	vector<Car> filtrate1 = srv.filtrare(1, "aa");
	assert(filtrate1.size() == 3);
	assert(filtrate1.at(0).getNrInmatr() == 5);
	//filtrate1.clear();    // /////////////////////////////////////////

	vector <Car> filtrate2 = srv.filtrare(2, "cc");
	assert(filtrate2.size() == 3);
	assert(filtrate2.at(0).getNrInmatr() == 5);
	assert(filtrate2.at(1).getNrInmatr() == 1);
	assert(filtrate2.at(2).getNrInmatr() == 2);
	//filtrate2.clear();
	srv.sorteaza(1); // nr Imatriculare
	vector <Car> sorted = srv.getAll();
	assert(sorted.at(0).getNrInmatr() == 1);
	assert(sorted.at(1).getNrInmatr() == 2);
	assert(sorted.at(2).getNrInmatr() == 3);
	assert(sorted.at(3).getNrInmatr() == 4);
	assert(sorted.at(4).getNrInmatr() == 5);
	srv.sorteaza(2); // tip
	sorted = srv.getAll();
	assert(sorted.at(0).getNrInmatr() == 3);
	assert(sorted.at(1).getNrInmatr() == 4);
	assert(sorted.at(2).getNrInmatr() == 1);
	assert(sorted.at(3).getNrInmatr() == 2);
	assert(sorted.at(4).getNrInmatr() == 5);
	srv.sorteaza(3); // prducator + model
	sorted = srv.getAll();
	assert(sorted.at(0).getNrInmatr() == 3);
	assert(sorted.at(1).getNrInmatr() == 5);
	assert(sorted.at(2).getNrInmatr() == 1);
	assert(sorted.at(3).getNrInmatr() == 4);
	assert(sorted.at(4).getNrInmatr() == 2);

}
void testSortDublex() {
	Repository r;
	Service srv(r);
	srv.add(5, "aa", "bb", "cc");
	srv.add(4, "aa", "bc", "ca");
	srv.add(3, "aa", "aa", "ac");
	srv.add(1, "bb", "aa", "cc");
	srv.add(2, "bb", "ba", "cc");
	srv.add(6, "zz", "ba", "cc");
	srv.sorteaza(3); // prducator + model
	vector <Car> sorted = srv.getAll();
	assert(sorted.at(0).getNrInmatr() == 3);
	assert(sorted.at(1).getNrInmatr() == 5);
	assert(sorted.at(2).getNrInmatr() == 4);
	assert(sorted.at(3).getNrInmatr() == 1);
	assert(sorted.at(4).getNrInmatr() == 2);
	assert(sorted.at(5).getNrInmatr() == 6);

}
void testWash() {
	Repository r;
	Service srv(r);
	srv.add(1, "a", "a", "a");
	srv.add(2, "a", "a", "a");
	srv.add(3, "a", "a", "a");
	srv.add(4, "a", "a", "a");
	srv.add(5, "a", "a", "a");
	assert(srv.getWashList().size() == 0);
	srv.addWash(1);
	srv.addWash(2);
	assert(srv.getWashList().size() == 2);
	srv.clearWashList();
	assert(srv.getWashList().size() == 0);
	srv.generate(3);
	assert(srv.getWashList().size() == 3);
	srv.clearWashList();
	srv.addWash(1);
	srv.exportCSV("wash.txt");
	ifstream fin("wash.txt");
	string s;
	getline(fin, s);
	assert(s == "1,a,a,a");
	fin.close();
}

void testUndo() {
	Repository r;
	Service srv(r);
	try {
		srv.undo();
		assert(false);
	}
	catch (const UndoException& e) {
		assert(e.getMessage() == "Nicio actiune anterioara!");
	}
	srv.add(1, "1", "1", "1");             // 1, 2
	srv.add(2, "2", "2", "2");
	assert(srv.getAll().size() == 2);
	srv.undo();
	assert(srv.getAll().size() == 1);		// 1 
	srv.sterge(1);
	assert(srv.getAll().size() == 0);     // 0 
	srv.undo();						// 1 
	assert(srv.getAll().size() == 1);
	srv.add(2, "1", "1", "1");
	srv.modifica(2, "2", "2", "2");
	Car c = srv.cauta(2);
	assert(c.getModel() == "2");
	assert(c.getTip() == "2");
	srv.undo();
	c = srv.cauta(2);
	assert(c.getModel() == "1");
	assert(c.getTip() == "1");

}
void testFileRepo() {
	ofstream fout("testFile.txt");
	for (int i = 1; i <= 4; i++)
		fout << 1 << endl;
	FileRepo r("testFile.txt");
	Service srv(r);
	srv.add(2, "b", "b", "b");
	assert(srv.getAll().size() == 2);
	assert(r.size() == 2);
	srv.add(3, "b", "b", "b");
	srv.sterge(3);
	assert(srv.getAll().size() == 2);
	srv.modifica(2, "a", "a", "a");
	Car c = srv.cauta(2);
	assert(c.getModel() == "a");
	r.clearElems();
	assert(r.getElems().size() == 0);

	// fisierul nu exista
	try {
		FileRepo r2{ "a/a,txt" };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	srv.add(1, "a", "a", "a");
	Car b = r.getByPoz(0);
	assert(b.getNrInmatr() == 1);
}