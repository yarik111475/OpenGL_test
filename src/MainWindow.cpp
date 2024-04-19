#include "MainWindow.h"
#include "SceneWidget.h"
#include "ControlWidget.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      sceneWidgetPtr_{new SceneWidget},
      controlWidgetPtr_{new ControlWidget}
{
    QObject::connect(controlWidgetPtr_,&ControlWidget::setRotationAxisSignal,
                     sceneWidgetPtr_,&SceneWidget::setRotationAxisSlot);
    QObject::connect(controlWidgetPtr_,&ControlWidget::setRotationEnabledSignal,
                     sceneWidgetPtr_,&SceneWidget::setRotationEnabledSlot);
    QObject::connect(controlWidgetPtr_,&ControlWidget::setLeftColorSignal,
                     sceneWidgetPtr_,&SceneWidget::setLeftColorSlot);
    auto hboxLayoutPtr {new QHBoxLayout};
    hboxLayoutPtr->addWidget(controlWidgetPtr_);
    hboxLayoutPtr->addWidget(sceneWidgetPtr_);

    auto centralWidgetPtr {new QWidget};
    centralWidgetPtr->setLayout(hboxLayoutPtr);
    setCentralWidget(centralWidgetPtr);
}
