#include "Service.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <random>
#include "Exception.h"

vector <Car> Service::getAll()
{
	return this->repo.getElems();
}

void Service::add(const int nr, string prod, string model, string tip)
{
	Car c(nr, prod, model, tip);
	if (this->validator.validate(c))
	{
		repo.append(c);
		undoList.push_back(new UndoAdd{ repo, c });
		//undoList.push_back(make_unique < UndoAdd>( repo,c ) );
	}
	else
		throw(ValidationException("Masina invalida!"));
}

void Service::sterge(const int nr) {
	Car c(nr);
	Car c2 = repo.remove(c);
	undoList.push_back(new UndoRemove{ repo,c2 });
	//	undoList.push_back(make_unique<UndoRemove>(repo, c));
}

void Service::modifica(const int nr, string prod, string model, string tip)
{
	Car c = repo.search(Car(nr));
	Car c2(nr, prod, model, tip);
	if (this->validator.validate(c2))
	{
		repo.update(c2);
		undoList.push_back(new UndoUpdate{ repo, c });
		//	undoList.push_back(make_unique<UndoUpdate>(repo, c));
	}
	else
		throw(ValidationException("Masina invalida!"));
}

Car Service::cauta(const int nr)
{
	return repo.search(Car(nr));

}

bool cmpByNr(const Car& c1, const  Car& c2) {
	if (c1.getNrInmatr() <= c2.getNrInmatr())
		return true;
	return false;
}

bool cmpByTip(const Car& c1, const Car& c2) {

	return c1.getTip() < c2.getTip();

}
bool  cmpByProdModel(const Car& c1, const Car& c2) {
	if (c1.getProd() < c2.getProd())
		return true;
	if (c1.getProd() == c2.getProd())
		if (c1.getModel() <= c2.getModel())
			return true;
		else
			return false;
	else
		return false;
}

void Service::sorteaza(int cmd) {
	if (cmd == 1) {
		sort(this->repo.getElems().begin(), this->repo.getElems().end(), cmpByNr);
	}
	else {
		if (cmd == 2)
		{
			sort(this->repo.getElems().begin(), this->repo.getElems().end(), cmpByTip);
		}
		else
		{
			sort(this->repo.getElems().begin(), this->repo.getElems().end(), cmpByProdModel);
		}
	}
}

vector <Car> Service::filtrare(int cmd, const string& name)
{
	vector <Car> v = repo.getElems();

	vector <Car> rez(v.size());

	auto it = std::copy_if(v.begin(), v.end(), rez.begin(), [cmd, name](const Car& x) {	if (cmd == 1)
		return (x.getProd() == name);
	else
		return x.getTip() == name;
		});
	rez.resize(std::distance(rez.begin(), it));
	return rez;
}

void Service::addWash(int nr)
{
	Car c = cauta(nr);
	wash.append(c);
}

vector<Car> Service::getWashList()
{
	return wash.getElems();

}

void Service::generate(int nr)
{
	wash.generate(nr);
}

void Service::clearWashList()
{
	wash.clearElems();
}

void Service::exportCSV(const string& s) {
	fileNames.push_back(s);
	wash.exportCSV(s);
}
void Service::undo()
{
	if (undoList.empty()) {
		throw UndoException("Nicio actiune anterioara!");
	}
	UndoAction* act = undoList.back(); /*undoList.back()->doUndo();*/
	act->doUndo();
	delete act;
	undoList.pop_back();
}
