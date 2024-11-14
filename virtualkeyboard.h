// virtualkeyboard.h
#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>

class VirtualKeyboard : public QWidget
{
    Q_OBJECT

public:
    explicit VirtualKeyboard(QWidget *parent = nullptr);
    void setCurrentLineEdit(QLineEdit *lineEdit);

private slots:
    void handleKeyClick(const QString &key);
    void handleBackspace();
    void handleSpace();
    void handleShift();
    void handleClear();

private:
    void setupKeys();
    void updateKeyLabels();

    QGridLayout *layout;
    QLineEdit *currentLineEdit;
    bool isUpperCase;
    QList<QPushButton*> keys;
    QPushButton *backspaceButton;
    QPushButton *spaceButton;
    QPushButton *shiftButton;
    QPushButton *clearButton;
    QPushButton *closebutton;
};

#endif // VIRTUALKEYBOARD_H
