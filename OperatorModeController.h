#pragma once

#include <QObject>

// Режим работы оператора
class OperatorModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString description MEMBER mDescription CONSTANT)
public:
    explicit OperatorModeController(QObject *parent = nullptr);

signals:
private:
    const QString mDescription = tr("Режим оператора");

};

