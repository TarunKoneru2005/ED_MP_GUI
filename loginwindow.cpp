#include "loginwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), mainWindow(nullptr), virtualKeyboard(nullptr)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Username
    QHBoxLayout *userLayout = new QHBoxLayout();
    QLabel *userLabel = new QLabel("Username:", this);
    usernameEdit = new QLineEdit(this);
    userLayout->addWidget(userLabel);
    userLayout->addWidget(usernameEdit);

    // Password
    QHBoxLayout *passLayout = new QHBoxLayout();
    QLabel *passLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    passLayout->addWidget(passLabel);
    passLayout->addWidget(passwordEdit);

    // Buttons
    loginButton = new QPushButton("Login", this);
    showKeyboardButton = new QPushButton("Show Keyboard", this);

    mainLayout->addLayout(userLayout);
    mainLayout->addLayout(passLayout);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(showKeyboardButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(showKeyboardButton, &QPushButton::clicked, this, &LoginWindow::showVirtualKeyboard);

    setupFocusHandling();

    setWindowTitle("Login");
    setFixedSize(220, 380);
}

LoginWindow::~LoginWindow()
{
    delete mainWindow;
    delete virtualKeyboard;
}

void LoginWindow::setupFocusHandling()
{
    connect(qApp, &QApplication::focusChanged,
            this, &LoginWindow::handleFocusChanged);

    usernameEdit->setFocusPolicy(Qt::StrongFocus);
    passwordEdit->setFocusPolicy(Qt::StrongFocus);
}

void LoginWindow::handleFocusChanged(QWidget *old, QWidget *now)
{
    Q_UNUSED(old);

    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(now);
    if (lineEdit && (lineEdit == usernameEdit || lineEdit == passwordEdit)) {
        if (virtualKeyboard && virtualKeyboard->isVisible()) {
            virtualKeyboard->setCurrentLineEdit(lineEdit);
        }
    }
}

void LoginWindow::handleLogin()
{
    if (usernameEdit->text() == "admin" && passwordEdit->text() == "password") {
        if (!mainWindow) {
            mainWindow = new MainWindow();
        }
        mainWindow->show();
        this->hide();
        if (virtualKeyboard) {
            virtualKeyboard->hide();
        }
    } else {
        QMessageBox::warning(this, "Error", "Invalid credentials!");
    }
}

void LoginWindow::showVirtualKeyboard()
{
    if (!virtualKeyboard) {
        virtualKeyboard = new VirtualKeyboard();
    }

    QWidget *focusWidget = QApplication::focusWidget();
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(focusWidget);
    if (lineEdit) {
        virtualKeyboard->setCurrentLineEdit(lineEdit);
    } else {
        virtualKeyboard->setCurrentLineEdit(usernameEdit);
        usernameEdit->setFocus();
    }

    // Calculate the position to place the virtual keyboard on the left side
    int keyboardWidth = virtualKeyboard->width();
    int x = this->x() - keyboardWidth;
    int y = this->y();

    // Ensure the keyboard is positioned correctly on the screen
    virtualKeyboard->move(x, y);
    virtualKeyboard->show();
    virtualKeyboard->raise();
}
