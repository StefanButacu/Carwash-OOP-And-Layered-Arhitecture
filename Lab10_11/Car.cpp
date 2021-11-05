#include "Car.h"
#include <iostream>

int Car::nrAp = 0;

Car::Car() {
	this->nrInmatr = 0;
	this->prod = "";
	this->model = "";
	this->tip = "";

}
Car::Car(const int nrInmatr, const  string prod, const string model, const  string tip)
{
	this->nrInmatr = nrInmatr;
	this->prod = prod;
	this->model = model;
	this->tip = tip;

}
Car::Car(const int nr) {

	this->nrInmatr = nr;
	this->prod = "";
	this->model = "";
	this->tip = "";

}
Car::Car(const Car& ot)
{
	//	 cout << "Am copiat" << endl;
		// Car::nrAp++;
		 //cout << Car::nrAp << "----" << endl;
	this->nrInmatr = ot.nrInmatr;
	this->prod = ot.prod;
	this->model = ot.model;
	this->tip = ot.tip;

}

const int Car::getNrInmatr() const noexcept
{
	return this->nrInmatr;
}

string  Car::getProd() const
{
	return this->prod;
}

string Car::getModel()const
{
	return this->model;
}

string Car::getTip()const
{
	return this->tip;
}

void Car::setProd(string s)
{
	this->prod = s;
}

void Car::setModel(string s)
{
	this->model = s;
}

void Car::setTip(string s)
{
	this->tip = s;
}

bool Car::operator==(const Car& c) const noexcept
{
	return this->nrInmatr == c.nrInmatr;
}

Car& Car::operator=(const Car& other)
{
	this->nrInmatr = other.nrInmatr;
	this->model = other.model;
	this->prod = other.prod;
	this->tip = other.tip;
	return *this;
}


Car::~Car()
{
}

std::ostream& operator<<(std::ostream& out, const Car& c)
{

	out << c.nrInmatr << ' ' << c.prod << ' ' << c.model << ' ' << c.tip;
	return out;
}
