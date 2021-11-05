#include "CarUi.h"
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qlist.h>
#include <qlistwidget.h>
#include <qstring.h>
#include "Exception.h"
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <qboxlayout.h>
#include "CarwashCRUDGUI.h"
void CarUi::initGUICmps()
{
	
	this->setStyleSheet("background-color:rgba(211, 246, 253, 0.93)");

	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	QVBoxLayout* lyCars = new QVBoxLayout;
	QLabel* myCars = new QLabel("All Cars");
	myCars->setAlignment(Qt::AlignCenter);
	lyCars->addWidget(myCars);

	tblViewCars = new QTableView;
	lyCars->addWidget(tblViewCars);

	//

	// Washing Layout
	QVBoxLayout* lyWash = new QVBoxLayout;
	QLabel* washLabel = new QLabel("Wash-List");
	washLabel->setAlignment(Qt::AlignCenter);

	lyWash->addWidget(washLabel);
	tblViewWash = new QTableView;
	 lyWash->addWidget(tblViewWash);


	//wash btns in new window


	QHBoxLayout* lyBtnsWash = new QHBoxLayout;
	btnWashCRUDGUI = new QPushButton("WashCRUD");
	lyBtnsWash->addWidget(btnWashCRUDGUI);
	btnWashROGUI = new QPushButton("WashReadOnly");
	lyBtnsWash->addWidget(btnWashROGUI);
	lyWash->addLayout(lyBtnsWash);

	// add wash Car
	nrWash = new QSpinBox;
	nrWash->setRange(-1000, 1000);
	btnWash = new QPushButton("Wash me");
	QHBoxLayout* lyAddWash = new QHBoxLayout;
	lyAddWash->addWidget(btnWash);
	lyAddWash->addWidget(nrWash);
// export 	
	QHBoxLayout* lyExport = new QHBoxLayout;
	txtExportFile = new QLineEdit;
	btnExport = new QPushButton("Export");
	lyExport->addWidget(btnExport);
	lyExport->addWidget(txtExportFile);
// generate 
	QHBoxLayout* lyGenWash = new QHBoxLayout;
	btnGen = new QPushButton("Generate");
	nrGen = new QSpinBox;
	lyGenWash->addWidget(btnGen);
	lyGenWash->addWidget(nrGen);
// remove 
	

	btnRemoveAll = new QPushButton("Clear Wash-List");
	lyWash->addLayout(lyAddWash);
	lyWash->addLayout(lyExport);
	lyWash->addLayout(lyGenWash);
	lyWash->addWidget(btnRemoveAll);
	//
	ly->addLayout(lyCars);
	btnArrow = new QPushButton(">");
	ly->addWidget(btnArrow);
	ly->addLayout(lyWash);
	
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	// sortari
	QHBoxLayout* sortLy = new QHBoxLayout;
	btnSortByNr = new QPushButton("Sort by nr");
	btnSortByProdModel = new QPushButton("Sort by Prod+Model");
	btnSortByTip = new QPushButton("Sort by type");	
	sortLy->addWidget(btnSortByNr);
	sortLy->addWidget(btnSortByTip);
	sortLy->addWidget(btnSortByProdModel);
	lyCars->addLayout(sortLy);

	txtFilter = new QLineEdit;
	lyCars->addWidget(txtFilter);
	QHBoxLayout* filterLy = new QHBoxLayout;
	btnFilterByProd = new QPushButton("Filter by Prod");
	btnFilterByTip = new QPushButton("Filter by tip");
	filterLy->addWidget(btnFilterByProd);
	filterLy->addWidget(btnFilterByTip);
	lyCars->addLayout(filterLy);
	///
	QWidget* widDetalii = new QWidget;
	QFormLayout* formDetalii = new QFormLayout;
	widDetalii->setLayout(formDetalii);
	// form fields
	this->txtNr = new QSpinBox;
	txtNr->setRange(-1000,1000);
	formDetalii->addRow(new QLabel("Numar inmatriculare"), txtNr);
	
	this->txtProd = new QLineEdit;

	//txtProd->setStyleSheet("background: transparent;  border: 50px ; background-color: green;");


	formDetalii->addRow(new QLabel("Producator"), txtProd);
	
	

	this->txtModel = new QLineEdit;
	formDetalii->addRow(new QLabel("Model"), txtModel);
	this->txtTip = new QLineEdit;
	formDetalii->addRow(new QLabel("Tip"), txtTip);
	

	btnAdd = new QPushButton("Add car");
	/// <summary>
	/// Culoare btn add
	//btnAdd->setStyleSheet("background-color:red");
	
	/// </summary>
	
	formDetalii->addWidget(btnAdd);
	btnRmv = new QPushButton("Remove car");
	formDetalii->addWidget(btnRmv);
	btnUpdate = new QPushButton("Update car");
	formDetalii->addWidget(btnUpdate);
	btnUndo = new QPushButton("Undo");	
	formDetalii->addWidget(btnUndo);
	lyCars->addWidget(widDetalii);

	
	
	//lyCars->addWidget(tblView);
	
}

void CarUi::connectSignalsSlots()
{
	QObject::connect(btnAdd, &QPushButton::clicked, this, &CarUi::addNewCar);
	QObject::connect(btnRmv, &QPushButton::clicked, this, &CarUi::removeCar);
	QObject::connect(btnUpdate, &QPushButton::clicked, this, &CarUi::updateCar);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &CarUi::undo);
	QObject::connect(btnSortByNr, &QPushButton::clicked, this, &CarUi::sort1);
	QObject::connect(btnSortByTip, &QPushButton::clicked, this, &CarUi::sort2);
	QObject::connect(btnSortByProdModel, &QPushButton::clicked, this, &CarUi::sort3);
	QObject::connect(btnWash, &QPushButton::clicked, this, &CarUi::addWashCar);
	QObject::connect(btnGen, &QPushButton::clicked, this, &CarUi::generateWashList);
	QObject::connect(btnRemoveAll, &QPushButton::clicked, this, &CarUi::clearWashList);
	QObject::connect(btnExport, &QPushButton::clicked, this, &CarUi::exportWashList);
	QObject::connect(btnFilterByProd, &QPushButton::clicked, this, &CarUi::filterByProd);
	QObject::connect(btnFilterByTip, &QPushButton::clicked, this, &CarUi::filterByTip);
	QObject::connect(btnArrow, &QPushButton::clicked, this, &CarUi::addWashArrow);
	/// 
//	QObject::connect(lst, &QListWidget::itemSelectionChanged, this, &CarUi::printSelectedItem);
	//
	QObject::connect(btnWashCRUDGUI, &QPushButton::clicked, this, &CarUi::washCRUDGUI);
	QObject::connect(btnWashROGUI, &QPushButton::clicked, this, &CarUi::washROGUI);

	carw.addObserver(this);
}

void CarUi::washCRUDGUI() {


	CarwashCRUDGUI* ui = new CarwashCRUDGUI(carw);
	ui->show();
}

void CarUi::washROGUI() {

	CarwashROGUI* ui = new CarwashROGUI(carw);

	ui->show();
}


void CarUi::addWashArrow() {
	try {
		int id = txtNr->value();
		srv.addWash(id);
		reloadTable(carw.getElems());
	}
	catch (const Exception& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));

	
	}
}
void CarUi::printSelectedItem() {
	
	//qDebug() << "Selectie \n" << lst->selectedItems() << "\n";
/*	for (const auto& x : lst->selectedItems()) {
		QString s = x->text();
		QStringList list = s.split(QLatin1Char(' '));
		txtNr->setValue(list[0].toInt());
		txtProd->setText(list[1]);
		txtModel->setText(list[2]);
		txtTip->setText(list[3]);


	}
	*/
}
void CarUi::clearWashList() {
	srv.clearWashList();
	reloadTable(carw.getElems());

}

void CarUi::exportWashList() {
	
	if (txtExportFile->text().isEmpty())
		QMessageBox::warning(this, "Warning", "File cant be empty!");
	else
		srv.exportCSV(txtExportFile->text().toStdString());
}

void CarUi::filterByProd()
{
	if (txtFilter->text().isEmpty())
		QMessageBox::warning(this, "Warning", "Field can't be empty!");
	else
	{
		string s = txtFilter->text().toStdString();
		showNewWindow(srv.filtrare(1, s));
	}
}

void CarUi::filterByTip()
{
	if (txtFilter->text().isEmpty())
		QMessageBox::warning(this, "Warning", "Field can't be empty!");
	else
	{
		string s = txtFilter->text().toStdString();
		showNewWindow(srv.filtrare(2, s));
	}
}

void CarUi::generateWashList() {
	srv.generate(nrGen->value());
	reloadTable(carw.getElems());

}
void CarUi::addWashCar() {
	try {
		int id = nrWash->value();
		srv.addWash(id);
		reloadTable(carw.getElems());
	}
	catch (const Exception& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));

	}
}


void CarUi::sort1() {
	srv.sorteaza(1);
	reloadList(srv.getAll());
}
void CarUi::sort2() {
	srv.sorteaza(2);
	reloadList(srv.getAll());
}
void CarUi::sort3() {
	srv.sorteaza(3);
	reloadList(srv.getAll());
}
void CarUi::undo(){
	try {
		srv.undo();
		reloadList(srv.getAll());
	}
	catch (const Exception& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	}

}
void CarUi::addNewCar() {
	try {
		srv.add(txtNr->value(), txtProd->text().toStdString(), txtModel->text().toStdString(), txtTip->text().toStdString());
		reloadList(srv.getAll());
	}
	catch (const Exception& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	}
	
}
void CarUi::removeCar() {
	try {
		srv.sterge(txtNr->value());
		reloadList(srv.getAll());
	}
	catch (const Exception& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	}
}
void CarUi::updateCar() {
	try {
		srv.modifica(txtNr->value(), txtProd->text().toStdString(), txtModel->text().toStdString(), txtTip->text().toStdString());
		reloadList(srv.getAll());
	}
	catch (const Exception& e) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(e.getMessage()));
	}
}
void CarUi::reloadList(std::vector<Car> cars)
{
	//modelLst = new MyTableModel(cars);
	modelLst->setCars(cars);
	//tblViewCars->setModel(modelLst);
}
void CarUi::reloadTable(std::vector <Car> cars){

	//modelWash = new MyTableModel(cars);
	modelWash->setCars(cars);
	//tblViewWash->setModel(modelWash);
}

void CarUi::showNewWindow(vector < Car > v) {
	QWidget* wdg = new QWidget;
	QVBoxLayout* lv = new QVBoxLayout;
	wdg->setLayout(lv);
	QListWidget* lst = new QListWidget;
	for (const Car& c : v) {
		string s{ "" };
		s += to_string(c.getNrInmatr()) + ' ' + c.getProd() + ' ' + c.getModel() + ' ' + c.getTip();
		QString b = QString::fromStdString(s);
		QListWidgetItem* item = new QListWidgetItem(b, lst);
	}
	lv->addWidget(lst);
	wdg->show();
}