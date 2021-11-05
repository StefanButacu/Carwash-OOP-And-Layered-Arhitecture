#pragma once
#include <vector>
#include <algorithm>

class Observer
{
public:
	virtual void update() = 0;
	Observer() {};
	virtual ~Observer() {};
};

class Subject {
public:
	std::vector< Observer*> observers;
	

	Subject() {};
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}
	void removeObserver(Observer* obs) {
		observers.erase(std::remove(begin(observers), end(observers), obs), observers.end());
	}

	void notifyObserver() {
		for (auto obs : observers)
			obs->update();
	};
};


