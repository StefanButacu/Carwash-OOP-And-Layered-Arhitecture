#pragma once
#include "Observer.h"
#include <qwidget.h>
#include <qlist.h>
#include <qlistview.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlistwidget.h>
#include "Car.h"
#include <qspinbox.h>
#include <qtablewidget.h>
#include "Service.h"
#include "CarwashROGUI.h"
#include "MyTableModel.h"
#define MAXW 1000
#define MAXH 600
class CarUi : public QWidget, public Observer
{
private:
	Service& srv;
	
	//
	QTableView* tblViewCars;
	//
	QTableView* tblViewWash;


	MyTableModel* modelLst;
	MyTableModel* modelWash;
	//


	QSpinBox* txtNr;
	QLineEdit* txtProd;
	QLineEdit* txtModel;
	QLineEdit* txtTip;
	//General Buttons
	QPushButton* btnAdd;
	QPushButton* btnRmv;
	QPushButton* btnUpdate;
	QPushButton* btnUndo;
	// WashButtons
	QPushButton* btnArrow;
	QPushButton* btnWash;
	QPushButton* btnGen;
	QSpinBox* nrWash;
	QSpinBox* nrGen;
	QPushButton* btnExport;
	QPushButton* btnRemoveAll;
	QLineEdit* txtExportFile;
	//
	QPushButton* btnSortByNr;
	QPushButton* btnSortByTip;
	QPushButton* btnSortByProdModel;
	//
	QLineEdit* txtFilter;
	QPushButton* btnFilterByProd;
	QPushButton* btnFilterByTip;
	//
	QPushButton* btnWashCRUDGUI;
	QPushButton* btnWashROGUI;
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(std::vector< Car> cars);
	void reloadTable(std::vector <Car> cars);

	Carwash& carw;

public:
	CarUi(Service& srv) : srv{ srv }, carw{ srv.getCarwash() } {
		this->resize(MAXW, MAXH);
		initGUICmps();
		modelLst = new MyTableModel{ srv.getAll() };

		modelWash = new MyTableModel{ carw.getElems() };

		tblViewCars->setModel(modelLst);
		tblViewWash->setModel(modelWash);
		connectSignalsSlots();
		reloadList(srv.getAll());
		reloadTable(srv.getWashList());


	};
	~CarUi() {
		carw.removeObserver(this);
	}
	void addNewCar();
	void removeCar();
	void updateCar();
	void undo();
	void sort1();
	void sort2();
	void sort3();
	void addWashCar();
	void generateWashList();
	void clearWashList(); 
	void exportWashList();
	void filterByProd();
	void filterByTip();
	void showNewWindow(vector < Car> c);
	void printSelectedItem();
	void addWashArrow();
	void washCRUDGUI();
	void washROGUI();
	void update() override {
		reloadTable(carw.getElems());

	}
};

