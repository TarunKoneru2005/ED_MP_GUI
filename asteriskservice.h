// asteriskservice.h
#ifndef ASTERISKSERVICE_H
#define ASTERISKSERVICE_H

#include <QObject>
#include <QProcess>
#include <QDebug>
#include <QThread>

class AsteriskService : public QObject
{
    Q_OBJECT

public:
    explicit AsteriskService(QObject *parent = nullptr);
    ~AsteriskService();

    bool startAsterisk();
    bool stopAsterisk();
    bool isRunning() const;

signals:
    void asteriskStarted();
    void asteriskStopped();
    void errorOccurred(const QString &error);

private:
    QProcess *asteriskProcess;
};

#endif // ASTERISKSERVICE_H
