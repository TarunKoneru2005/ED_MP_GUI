// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStatusBar>
#include <QMessageBox>
#include "asteriskservice.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleAsteriskStarted();
    void handleAsteriskStopped();
    void handleAsteriskError(const QString &error);
    void openTerminal();
    void powerOn();
    void powerOff();
    void restart();
    void onLoginSuccess();

private:
    QPushButton *connectSIPButton;
    QPushButton *disconnectSIPButton;
    QPushButton *restartButton;
    QPushButton *openTerminalButton;
    QPushButton *powerOffButton;
    AsteriskService *asteriskService;
};

#endif // MAINWINDOW_H
