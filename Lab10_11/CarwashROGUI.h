#pragma once
#include <qwidget.h>
#include "qpainter.h"
#include "Observer.h"
#include "Carwash.h"
#include "qdebug.h"
#define PhotosNr 5
class CarwashROGUI : // paints on window car icons as many as cars are in washList
    public QWidget, public Observer
{
private:
    Carwash& wash;
public:
    CarwashROGUI(Carwash& c) :wash{ c },  Observer() {
        wash.addObserver(this);
        update();
    };
    void paintEvent(QPaintEvent* ev)override;
    void update() override;
    ~CarwashROGUI() {
        wash.removeObserver(this);
    }
};

