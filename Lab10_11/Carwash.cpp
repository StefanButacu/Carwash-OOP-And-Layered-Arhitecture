#include "Carwash.h"
#include "Exception.h"
#include <algorithm>
#include <random>
#include <fstream>
void Carwash::append(const Car& c)
{
	std::vector<Car>::iterator it = find_if(v.begin(), v.end(), [c](Car x) {return x == c; });
	if (it != v.end())
		throw Exception("Masina este deja introdusa!");
	else
	{
		this->v.push_back(c);
		notifyObserver();
	}
}

vector<Car> Carwash::getElems()
{
	return v;
}

void Carwash::clearElems()
{
	v.clear();
	notifyObserver();

}

void Carwash::generate(int nr)
{
	int i = 0;
	while (i < nr && repo.size() - v.size() > 0) {
		try {
			std::mt19937 mt{ std::random_device{}() };
			const std::uniform_int_distribution<> dist(0, repo.size() - 1);
			const int rndNr = dist(mt);
			Car c = repo.getByPoz(rndNr); // trebuie luat elementul de pe o pozitie 
			this->append(c);
			i++;
		}
		catch (Exception&) {};
	}
}

void Carwash::exportCSV(const string& fileN)
{
	ofstream fout(fileN);   //washRepo.getElems()
	for (const Car& c : v) {
		fout << c.getNrInmatr() << ',' << c.getProd() << ',' << c.getModel() << ',' << c.getTip() << endl;
	}
}

