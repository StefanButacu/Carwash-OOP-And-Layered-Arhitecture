#pragma once
#include "Car.h"
#include <vector>
class AbstractRepo
{

public:
	AbstractRepo() {};
	virtual void append(const Car& c) = 0;
	virtual Car remove(const Car& c) = 0;
	virtual void update(const Car& c) = 0;
	virtual Car search(const Car& c) = 0;
	virtual ~AbstractRepo() {};
	virtual int size() = 0;
	virtual vector <Car>& getElems() = 0;
	virtual Car getByPoz(int i) = 0;
};

