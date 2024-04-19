#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SceneWidget;
class ControlWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    SceneWidget* sceneWidgetPtr_ {nullptr};
    ControlWidget* controlWidgetPtr_ {nullptr};
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow()=default;
signals:

};

#endif // MAINWINDOW_H
