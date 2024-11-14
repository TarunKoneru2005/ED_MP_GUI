// asteriskservice.cpp
#include "asteriskservice.h"

AsteriskService::AsteriskService(QObject *parent)
    : QObject(parent), asteriskProcess(new QProcess(this))
{
}

AsteriskService::~AsteriskService()
{
    if (asteriskProcess) {
        asteriskProcess->close();
        delete asteriskProcess;
    }
}

bool AsteriskService::startAsterisk()
{
    if (isRunning()) {
        qDebug() << "Asterisk is already running";
        emit asteriskStarted();
        return true;
    }

    qDebug() << "Attempting to start Asterisk...";

    // First try systemctl
    QProcess systemctl;
    systemctl.start("systemctl", QStringList() << "start" << "asterisk");
    systemctl.waitForFinished();

    // Check if systemctl worked
    if (systemctl.exitCode() == 0) {
        // Verify Asterisk is actually running
        QProcess asteriskCheck;
        asteriskCheck.start("asterisk", QStringList() << "-rx" << "core show version");
        asteriskCheck.waitForFinished();

        if (asteriskCheck.exitCode() == 0) {
            QString version = asteriskCheck.readAllStandardOutput();
            qDebug() << "Asterisk started successfully. Version:" << version;
            emit asteriskStarted();
            return true;
        }
    }

    qDebug() << "Systemctl start failed, trying direct start...";

    // If systemctl fails, try starting asterisk directly
    asteriskProcess->setProcessChannelMode(QProcess::MergedChannels);
    asteriskProcess->start("asterisk", QStringList() << "-c");

    bool started = asteriskProcess->waitForStarted(5000);

    if (started) {
        // Wait a moment for Asterisk to initialize
        QThread::msleep(2000);

        // Verify Asterisk is responding
        QProcess asteriskCheck;
        asteriskCheck.start("asterisk", QStringList() << "-rx" << "core show version");
        asteriskCheck.waitForFinished();

        if (asteriskCheck.exitCode() == 0) {
            QString version = asteriskCheck.readAllStandardOutput();
            qDebug() << "Asterisk started successfully. Version:" << version;
            emit asteriskStarted();
            return true;
        } else {
            QString error = "Asterisk process started but not responding";
            qDebug() << error;
            emit errorOccurred(error);
            return false;
        }
    } else {
        QString error = "Failed to start Asterisk: " + asteriskProcess->errorString();
        qDebug() << error;
        emit errorOccurred(error);
        return false;
    }
}

bool AsteriskService::stopAsterisk()
{
    if (!isRunning()) {
        qDebug() << "Asterisk is not running";
        emit asteriskStopped();
        return true;
    }

    QProcess systemctl;
    systemctl.start("systemctl", QStringList() << "stop" << "asterisk");
    systemctl.waitForFinished();

    if (systemctl.exitCode() == 0) {
        emit asteriskStopped();
        return true;
    }

    return false;
}

bool AsteriskService::isRunning() const
{
    QProcess asteriskCheck;
    asteriskCheck.start("asterisk", QStringList() << "-rx" << "core show version");
    asteriskCheck.waitForFinished();

    if (asteriskCheck.exitCode() == 0) {
        qDebug() << "Asterisk is running. Output:" << asteriskCheck.readAllStandardOutput();
        return true;
    }

    qDebug() << "Asterisk is not running";
    return false;
}
