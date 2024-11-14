// loginwindow.h
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include "mainwindow.h"
#include "virtualkeyboard.h"

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void handleLogin();
    void showVirtualKeyboard();
    void handleFocusChanged(QWidget *old, QWidget *now);

private:
    void setupFocusHandling();

    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *showKeyboardButton;
    MainWindow *mainWindow;
    VirtualKeyboard *virtualKeyboard;
};

#endif // LOGINWINDOW_H
