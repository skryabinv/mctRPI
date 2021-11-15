#pragma once

#include <QObject>

// Ручной режим управления
class ManualModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString description MEMBER mDescription CONSTANT)
public:
    explicit ManualModeController(QObject *parent = nullptr);

signals:
private:
    const QString mDescription = tr("Режим ручного управления");

};

