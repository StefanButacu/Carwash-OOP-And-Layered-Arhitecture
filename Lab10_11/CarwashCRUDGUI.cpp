#include "CarwashCRUDGUI.h"
void CarwashCRUDGUI::initGUIComp() {
	lst = new QListWidget;
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);
	ly->addWidget(lst);
	QVBoxLayout* lyBtns = new QVBoxLayout;
	btnClear = new QPushButton("Clear Wash-List");
	btnGen = new QPushButton("Generate");
	nrGen = new QSpinBox;
	nrGen->setMinimum(0);
	lyBtns->addWidget(btnClear);
	lyBtns->addWidget(btnGen);
	lyBtns->addWidget(nrGen);
	ly->addLayout(lyBtns);
}
void CarwashCRUDGUI::connectSignals() {
	QObject::connect(btnClear, &QPushButton::clicked, this, &CarwashCRUDGUI::clearElems);
	QObject::connect(btnGen, &QPushButton::clicked, this, &CarwashCRUDGUI::generate);
}
void CarwashCRUDGUI::reloadList(vector <Car> v) {
	lst->clear();
	for (const auto& x : v) {
		QString s = QString::number(x.getNrInmatr()) + ' ' + QString::fromStdString(x.getProd()) + ' ' + QString::fromStdString(x.getModel()) + ' ' + QString::fromStdString(x.getTip());
		QListWidgetItem* it = new QListWidgetItem(s);
		lst->addItem(it);
	}
}
void CarwashCRUDGUI::clearElems() {
	carw.clearElems();
}
void CarwashCRUDGUI::generate() {
	carw.generate(nrGen->value());
}
void CarwashCRUDGUI::update() {
	reloadList(carw.getElems());
};