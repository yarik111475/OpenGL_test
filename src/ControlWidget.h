#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>

class QRadioButton;
class ControlWidget : public QWidget
{
    Q_OBJECT
private:
    QRadioButton* xAxisRButtonPtr_ {nullptr};
    QRadioButton* yAxisRButtonPtr_ {nullptr};
    QRadioButton* zAxisRButtonPtr_ {nullptr};
public:
    explicit ControlWidget(QWidget *parent = nullptr);
    virtual ~ControlWidget()=default;
signals:
    void setRotationAxisSignal(const QString& axis);
    void setRotationEnabledSignal(bool enable);
    void setLeftColorSignal(float red,float green,float blue);
private slots:
    void leftColorToggledSlot(int id,bool checked);
    void rotationToggledSlot(int id,bool checked);
    void startButtonClickedSlot();
    void finishButtonClickedSlot();

};

#endif // CONTROLWIDGET_H
