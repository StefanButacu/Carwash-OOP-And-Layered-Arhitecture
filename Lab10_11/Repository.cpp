#include "Repository.h"
#include <stdexcept>
#include "Exception.h"
#include <fstream>
#include <iostream>
using std::vector;
using std::ostream;
using std::ifstream;

int Repository::size()
{
	return this->v.size();
}

void Repository::append(const Car& c) {
	std::vector<Car>::iterator it = find_if(v.begin(), v.end(), [c](Car x) {return x == c; });
	if (it != v.end())
		throw RepoException("Masina este deja introdusa!");
	else
		this->v.push_back(c);
}

Car Repository::remove(const Car& c)
{
	int index = -1;
	for (size_t i = 0; i < v.size(); i++) {
		if (v.at(i) == c) {
			index = i;
			break;
		}
	}
	if (index == -1)
		throw RepoException("Masina nu exista!");
	Car aux = v.at(index);
	v.erase(v.begin() + index);
	return aux;
}

void Repository::update(const Car& c)
{
	bool find = false;
	for (Car& x : v) {
		if (x == c) {
			x = c;
			find = true;
		}
	}
	if (find == false)
		throw RepoException("Masina nu exista!");

}

Car Repository::search(const Car& c)
{

	std::vector<Car>::iterator it = find_if(v.begin(), v.end(), [c](Car x) {return x == c; });
	if (it != v.end())
		return *it;
	throw RepoException("Masina nu exista!");

}

vector<Car>& Repository::getElems()
{
	return this->v;
}

void Repository::clearElems()
{
	v.clear();
}

Car Repository::getByPoz(int i)
{
	return v.at(i);
}





FileRepo::FileRepo(const string& fileN) : Repository(), fileName{ fileN } {
	loadFromFile();
};
FileRepo::~FileRepo()
{
	//std::ofstream ofs(fileName);
//	ofs.open(fileName, ios::out | ios::trunc); // golesc fisierul la iesirea din aplicatie 
	//ofs.close();
}

void FileRepo::append(const Car& c)
{
	//	loadFromFile();
	Repository::append(c);
	writeToFile();
}

Car FileRepo::remove(const Car& c) {

	//	loadFromFile();
	Car c1 = Repository::remove(c);
	writeToFile();
	return c1;
}

void FileRepo::update(const Car& c) {
	//	loadFromFile();
	Repository::update(c);
	writeToFile();

}
Car FileRepo::getByPoz(int i) {
	//	loadFromFile();
	return Repository::getByPoz(i);
}

void FileRepo::clearElems() {
	Repository::clearElems();
	writeToFile();
}

Car FileRepo::search(const Car& c) {
	//	loadFromFile();
	return Repository::search(c);
}

int FileRepo::size() {
	//loadFromFile();
	return Repository::size();
}

vector <Car>& FileRepo::getElems() {
	//	loadFromFile();
	return Repository::getElems();
}


void FileRepo::loadFromFile() {
	ifstream in(fileName);
	if (!in.is_open())
		throw RepoException("Eroare la deschidearea fisisierului!");
	while (!in.eof())
	{
		int nr;
		string prod, model, tip;
		in >> nr;
		if (in.eof()) break;
		in >> prod;
		if (in.eof()) break;

		in >> model;
		if (in.eof()) break;

		in >> tip;
		Car c(nr, prod, model, tip);
		Repository::append(c);
	}
	in.close();
}
void FileRepo::writeToFile() {
	//	loadFromFile(); // ma asigur ca tot ce am este incarcat in memorie
	ofstream out(fileName);
	/*if (!out.is_open())
		throw RepoException("Eroare la deschiderea fisierului!");
	*/
	for (const Car& c : getElems()) {
		out << c.getNrInmatr() << endl;
		out << c.getProd() << endl;
		out << c.getModel() << endl;
		out << c.getTip() << endl;
	}
	out.close();
}