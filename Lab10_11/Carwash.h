#pragma once
#include "Observer.h"

#include "Car.h"
#include <vector>
#include "AbstractRepo.h"
using std::vector;

class Carwash: public Subject
{
private:
	AbstractRepo& repo;
	vector < Car> v;
public:

	Carwash(AbstractRepo& repo) : Subject(), repo{ repo } {
	};
	void append(const Car& c);
	vector <Car> getElems();
	void clearElems();
	void generate(int count);
	void exportCSV(const string& fileN);
};

