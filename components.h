#pragma once

#include <QString>
#include <QObject>
#include <QVariantMap>
#include <QMqttClient>

#include "core.h"

class ActiveSensor: public BinarySensor
{
    Q_OBJECT
public:
    ActiveSensor(QObject *parent);
};

class Notifications: public Entity
{
    Q_OBJECT
public:
    Notifications(QObject *parent);

    void notificationCallback(const QMqttMessage &message);
};

class SuspendSwitch : public Button
{
    Q_OBJECT
public:
    SuspendSwitch(QObject *parent);
};

class LockedState : public Switch
{
    Q_OBJECT
public:
    LockedState(QObject *parent);

private Q_SLOTS:
    void screenLockedChanged(bool active);
    void stateChangeRequested(bool state);
};


