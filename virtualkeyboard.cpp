#include "virtualkeyboard.h"
#include <QVBoxLayout>
#include <QPushButton>

VirtualKeyboard::VirtualKeyboard(QWidget *parent)
    : QWidget(parent), currentLineEdit(nullptr), isUpperCase(false)
{
    layout = new QGridLayout(this);
    setupKeys();

    // Add backspace, space, shift, clear and close buttons
    backspaceButton = new QPushButton("⬅️", this);
    spaceButton = new QPushButton("  ", this);
    shiftButton = new QPushButton("⬆️", this);
    clearButton = new QPushButton("Clr", this);
    closebutton = new QPushButton("❌", this);

    layout->addWidget(backspaceButton, 4, 0);
    layout->addWidget(spaceButton, 4, 1);
    layout->addWidget(shiftButton, 4, 2);
    layout->addWidget(clearButton, 4, 3);
    layout->addWidget(closebutton, 4, 4);

    connect(backspaceButton, &QPushButton::clicked, this, &VirtualKeyboard::handleBackspace);
    connect(spaceButton, &QPushButton::clicked, this, &VirtualKeyboard::handleSpace);
    connect(shiftButton, &QPushButton::clicked, this, &VirtualKeyboard::handleShift);
    connect(clearButton, &QPushButton::clicked, this, &VirtualKeyboard::handleClear);
    connect(closebutton, &QPushButton::clicked, this, &VirtualKeyboard::close);

    setWindowTitle("Virtual Keyboard");
    setFixedSize(380, 220);

    closebutton->setFixedSize(30, 30);
    backspaceButton->setFixedSize(30, 30);
    spaceButton->setFixedSize(30, 30);
    shiftButton->setFixedSize(30, 30);
    clearButton->setFixedSize(30, 30);
}

void VirtualKeyboard::setCurrentLineEdit(QLineEdit *lineEdit)
{
    currentLineEdit = lineEdit;
}

void VirtualKeyboard::setupKeys()
{
    QStringList keysLayout = {
        "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "A", "S", "D", "F", "G", "H", "J", "K", "L",
        "Z", "X", "C", "V", "B", "N", "M"
    };

    int row = 0;
    int col = 0;
    for (const QString &key : keysLayout) {
        QPushButton *keyButton = new QPushButton(key, this);
        keyButton->setFixedSize(30, 30);
        keys.append(keyButton);
        layout->addWidget(keyButton, row, col);

        connect(keyButton, &QPushButton::clicked, this, [this, key]() { handleKeyClick(key); });

        col++;
        if (col > 9) {
            col = 0;
            row++;
        }
    }
}

void VirtualKeyboard::handleKeyClick(const QString &key)
{
    if (currentLineEdit) {
        QString buttonText = isUpperCase ? key.toUpper() : key.toLower();
        currentLineEdit->insert(buttonText);
    }
}

void VirtualKeyboard::handleBackspace()
{
    if (currentLineEdit) {
        currentLineEdit->backspace();
    }
}

void VirtualKeyboard::handleSpace()
{
    if (currentLineEdit) {
        currentLineEdit->insert(" ");
    }
}

void VirtualKeyboard::handleShift()
{
    isUpperCase = !isUpperCase;  // Toggle the case
    updateKeyLabels();
}

void VirtualKeyboard::handleClear()
{
    if (currentLineEdit) {
        currentLineEdit->clear();
    }
}

void VirtualKeyboard::updateKeyLabels()
{
    for (QPushButton *keyButton : keys) {
        QString text = keyButton->text();
        keyButton->setText(isUpperCase ? text.toUpper() : text.toLower());
    }
}
