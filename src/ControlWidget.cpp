#include "ControlWidget.h"
#include <QtWidgets>

ControlWidget::ControlWidget(QWidget *parent)
    : QWidget(parent),
      xAxisRButtonPtr_{new QRadioButton{"Rotation on X"}},
      yAxisRButtonPtr_{new QRadioButton{"Rotation on Y"}},
      zAxisRButtonPtr_{new QRadioButton{"Rotation on Z"}}
{
    xAxisRButtonPtr_->setChecked(true);
    QButtonGroup* rotationButtonGroupPtr {new QButtonGroup};
    QObject::connect(rotationButtonGroupPtr,
                     QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                     this,&ControlWidget::rotationToggledSlot);
    rotationButtonGroupPtr->setExclusive(true);
    rotationButtonGroupPtr->addButton(xAxisRButtonPtr_,0);
    rotationButtonGroupPtr->addButton(yAxisRButtonPtr_,1);
    rotationButtonGroupPtr->addButton(zAxisRButtonPtr_,2);

    QGroupBox* rotatinGroupBoxPtr {new QGroupBox(QObject::tr("Rotation"))};
    QVBoxLayout* rbVBoxLayoutPtr {new QVBoxLayout};
    rbVBoxLayoutPtr->addWidget(xAxisRButtonPtr_);
    rbVBoxLayoutPtr->addWidget(yAxisRButtonPtr_);
    rbVBoxLayoutPtr->addWidget(zAxisRButtonPtr_);

    QPushButton* rotationStartBtnPtr {new QPushButton{"Start"}};
    QObject::connect(rotationStartBtnPtr,&QPushButton::clicked,
                     this,&ControlWidget::startButtonClickedSlot);
    QPushButton* rotatiobFinishBtnPtr {new QPushButton{"Finish"}};
    QObject::connect(rotatiobFinishBtnPtr,&QPushButton::clicked,
                     this,&ControlWidget::finishButtonClickedSlot);

    QVBoxLayout* btnsVBoxLayoutPtr {new QVBoxLayout};
    btnsVBoxLayoutPtr->addWidget(rotationStartBtnPtr);
    btnsVBoxLayoutPtr->addWidget(rotatiobFinishBtnPtr);

    QHBoxLayout* groupBoxHBoxLayoutPtr {new QHBoxLayout};
    groupBoxHBoxLayoutPtr->addLayout(rbVBoxLayoutPtr);
    groupBoxHBoxLayoutPtr->addLayout(btnsVBoxLayoutPtr);
    rotatinGroupBoxPtr->setLayout(groupBoxHBoxLayoutPtr);

    QRadioButton* leftRedRButtonPtr {new QRadioButton("Color on Red")};
    leftRedRButtonPtr->setChecked(true);
    QRadioButton* leftGreenRButtonPtr {new QRadioButton("Color on Green")};
    QRadioButton* leftBlueRButtonPtr {new QRadioButton("Color on Blue")};

    QButtonGroup* leftColorButtonGroupPtr {new QButtonGroup};
    QObject::connect(leftColorButtonGroupPtr,
                     QOverload<int, bool>::of(&QButtonGroup::buttonToggled),
                     this,&ControlWidget::leftColorToggledSlot);
    leftColorButtonGroupPtr->setExclusive(true);
    leftColorButtonGroupPtr->addButton(leftRedRButtonPtr,0);
    leftColorButtonGroupPtr->addButton(leftGreenRButtonPtr,1);
    leftColorButtonGroupPtr->addButton(leftBlueRButtonPtr,2);

    QVBoxLayout* leftColorVBoxLayoutPtr {new QVBoxLayout};
    leftColorVBoxLayoutPtr->addWidget(leftRedRButtonPtr);
    leftColorVBoxLayoutPtr->addWidget(leftGreenRButtonPtr);
    leftColorVBoxLayoutPtr->addWidget(leftBlueRButtonPtr);


    QGroupBox* leftColorGroupBoxPtr {new QGroupBox("Left")};
    leftColorGroupBoxPtr->setLayout(leftColorVBoxLayoutPtr);

    QGroupBox* rightColorGroupBoxPtr {new QGroupBox("Right")};
    QGroupBox* bottomColorGroupBoxPtr {new QGroupBox("Bottom")};

    QVBoxLayout* colorVBoxLayoutPtr {new QVBoxLayout};
    colorVBoxLayoutPtr->addWidget(leftColorGroupBoxPtr);
    colorVBoxLayoutPtr->addWidget(rightColorGroupBoxPtr);
    colorVBoxLayoutPtr->addWidget(bottomColorGroupBoxPtr);

    QGroupBox* colorGroupBoxPtr {new QGroupBox("Color")};
    colorGroupBoxPtr->setLayout(colorVBoxLayoutPtr);

    QVBoxLayout* mainVBoxLayout {new QVBoxLayout};
    mainVBoxLayout->addWidget(rotatinGroupBoxPtr);
    mainVBoxLayout->addWidget(colorGroupBoxPtr);
    mainVBoxLayout->addStretch(10);
    setLayout(mainVBoxLayout);
}

void ControlWidget::leftColorToggledSlot(int id, bool checked)
{
    if(id==0){
        emit setLeftColorSignal(1.0,0.0,0.0);
    }
    else if(id==1){
        emit setLeftColorSignal(0.0,1.0,0.0);
    }
    else if(id==2){
        emit setLeftColorSignal(0.0,0.0,1.0);
    }
}

void ControlWidget::rotationToggledSlot(int id, bool checked)
{
    QString rotationAxis {};
    if(id==0){
        rotationAxis="x";
    }
    else if(id==1){
        rotationAxis="y";
    }
    else if(id==2){
        rotationAxis="z";
    }
    emit setRotationAxisSignal(rotationAxis);
}

void ControlWidget::startButtonClickedSlot()
{
    xAxisRButtonPtr_->setChecked(true);
    emit setRotationEnabledSignal(true);
}

void ControlWidget::finishButtonClickedSlot()
{
    emit setRotationEnabledSignal(false);
}


