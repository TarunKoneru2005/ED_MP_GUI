// mainwindow.cpp
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QLabel *label = new QLabel("Main Window", this);
    layout->addWidget(label);

    // Initialize Power Off button
    powerOffButton = new QPushButton("Power Off", this);
    powerOffButton->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
    connect(powerOffButton, &QPushButton::clicked, this, &MainWindow::powerOff);

    // Initialize other buttons
    connectSIPButton = new QPushButton("Connect SIP", this);
    disconnectSIPButton = new QPushButton("Disconnect SIP", this);
    restartButton = new QPushButton("Restart", this);
    openTerminalButton = new QPushButton("Open Terminal", this);

    // Add buttons to the layout
    layout->addWidget(connectSIPButton);
    layout->addWidget(disconnectSIPButton);
    layout->addWidget(restartButton);
    layout->addWidget(openTerminalButton);
    layout->addWidget(powerOffButton);

    // Initialize AsteriskService
    asteriskService = new AsteriskService(this);

    // Connect button signals
    connect(connectSIPButton, &QPushButton::clicked, asteriskService, &AsteriskService::startAsterisk);
    connect(disconnectSIPButton, &QPushButton::clicked, asteriskService, &AsteriskService::stopAsterisk);
    connect(restartButton, &QPushButton::clicked, this, &MainWindow::restart);
    connect(openTerminalButton, &QPushButton::clicked, this, &MainWindow::openTerminal);

    // Connect AsteriskService signals
    connect(asteriskService, &AsteriskService::asteriskStarted, this, &MainWindow::handleAsteriskStarted);
    connect(asteriskService, &AsteriskService::asteriskStopped, this, &MainWindow::handleAsteriskStopped);
    connect(asteriskService, &AsteriskService::errorOccurred, this, &MainWindow::handleAsteriskError);

    setWindowTitle("Main Window");
    showMaximized();

    //set button sizes
    powerOffButton->setFixedSize(200, 35);
    disconnectSIPButton->setFixedSize(200, 35);
    restartButton->setFixedSize(200, 35);
    openTerminalButton->setFixedSize(200, 35);
    connectSIPButton->setFixedSize(200, 35);

    // Create status bar
    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow()
{
}

void MainWindow::handleAsteriskStarted()
{
    QString statusMessage = "Asterisk service started successfully!\n"
                            "SIP service is now connected and ready.";

    QMessageBox::information(this, "Asterisk Status", statusMessage);

    connectSIPButton->setEnabled(false);
    disconnectSIPButton->setEnabled(true);
    connectSIPButton->setText("SIP Connected");
    statusBar()->showMessage("Asterisk Running - SIP Connected");
}

void MainWindow::handleAsteriskStopped()
{
    QString statusMessage = "Asterisk service stopped.\n"
                            "SIP service is now disconnected.";

    QMessageBox::information(this, "Asterisk Status", statusMessage);

    connectSIPButton->setEnabled(true);
    disconnectSIPButton->setEnabled(false);
    connectSIPButton->setText("Connect SIP");
    statusBar()->showMessage("Asterisk Stopped - SIP Disconnected");
}

void MainWindow::handleAsteriskError(const QString &error)
{
    QString errorMessage = QString("Error with Asterisk service:\n%1\n\n"
                                   "Please check:\n"
                                   "1. Asterisk is properly installed\n"
                                   "2. You have sufficient permissions\n"
                                   "3. No other instance is running").arg(error);

    QMessageBox::critical(this, "Asterisk Error", errorMessage);

    connectSIPButton->setEnabled(true);
    disconnectSIPButton->setEnabled(true);
    connectSIPButton->setText("Connect SIP");
    statusBar()->showMessage("Asterisk Error - Check System Logs");
}

void MainWindow::openTerminal()
{
    QMessageBox::information(this, "Open Terminal", "Terminal opened successfully!");
}

void MainWindow::powerOn()
{
    QMessageBox::information(this, "Power On", "Device powered on!");
}

void MainWindow::powerOff()
{
    QMessageBox::information(this, "Power Off", "Device powered off!");
}

void MainWindow::restart()
{
    QMessageBox::information(this, "Restart", "Device restarting...");
}

void MainWindow::onLoginSuccess()
{
    powerOffButton->show();
}
