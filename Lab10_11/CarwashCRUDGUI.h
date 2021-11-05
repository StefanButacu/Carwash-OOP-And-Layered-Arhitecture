#pragma once
#include "Observer.h"

#include <qwidget.h>
#include <qpushbutton.h>
#include "Carwash.h"
#include <qboxlayout.h>
#include <qlistwidget.h>
#include <qspinbox.h>
class CarwashCRUDGUI:public QWidget,public Observer
{
private:
	Carwash& carw;
	QPushButton* btnClear;
	QPushButton* btnGen;
	QSpinBox* nrGen;
	QListWidget* lst;

	void initGUIComp();
	void reloadList(vector <Car> v);
	void connectSignals();
	void clearElems();
	void generate();

public:			    
	CarwashCRUDGUI(Carwash& c) :carw{ c } {
		carw.addObserver(this);
		initGUIComp();
		connectSignals();
		update();
	};
	void update() override;
	~CarwashCRUDGUI() {
		 carw.removeObserver(this);
	}
};
