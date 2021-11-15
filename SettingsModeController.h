#pragma once

#include <QObject>

// Режим настроек
class SettingsModeController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString descritpion MEMBER mDescription CONSTANT)
public:
    explicit SettingsModeController(QObject *parent = nullptr);
    void loadFromFile(const QString& path);
signals:
public slots:
    void saveToFile(const QString& path) const;
private:
    const QString mDescription = tr("Настройки");
};

