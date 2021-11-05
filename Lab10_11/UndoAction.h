#pragma once
#include "Car.h"
#include "Repository.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
private:
	Car cAdd;
	AbstractRepo& r;
public:
	UndoAdd(AbstractRepo& r, const Car& c) : r{ r }, cAdd{ c }{};

	void doUndo() override {
		r.remove(cAdd);
	};

};

class UndoRemove : public UndoAction {
private:
	Car cDel;
	AbstractRepo& r;
public:
	UndoRemove(AbstractRepo& r, const Car& c) :r{ r }, cDel{ c }{};
	void doUndo() override {
		r.append(cDel);
	}
};

class UndoUpdate : public UndoAction {
private:
	Car cBefore;
	AbstractRepo& r;
public:
	UndoUpdate(AbstractRepo& r, const Car& c) :r{ r }, cBefore{ c }{};
	void doUndo()override {
		r.update(cBefore);
	}
};
