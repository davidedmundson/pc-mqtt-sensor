#include "components.h"

#include <QHostInfo>
#include <QMqttClient>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <KNotification>
#include <KIdleTime>

#include <QDBusConnection>
#include "login1_manager_interface.h"


Notifications::Notifications(QObject *parent):
    Entity(parent)
{
    setId("notifications");
    setName("Notifications");

    connect(HaControl::mqttClient(), &QMqttClient::connected, this, [this]() {
        auto watcher = HaControl::mqttClient()->subscribe(baseTopic());
        connect(watcher, &QMqttSubscription::messageReceived, this, &Notifications::notificationCallback);
    });
}

void Notifications::notificationCallback(const QMqttMessage &message)
{
    auto docs = QJsonDocument::fromJson(message.payload());
    auto objs = docs.object();
    const QString title = objs["title"].toString();
    const QString body = objs["message"].toString();
    KNotification::event(KNotification::Notification, title, body);
}

ActiveSensor::ActiveSensor(QObject *parent):
    BinarySensor(parent)
{
    setId("active");
    setName("Active");
    setHaType("binary_sensor");
    setDiscoveryConfig("device_class", "presence");

    auto kidletime = KIdleTime::instance();
    auto id = kidletime->addIdleTimeout(5 * 60 * 1000);
    connect(kidletime, &KIdleTime::resumingFromIdle, this, [this]() {
        setState(true);
    });
    connect(kidletime, &KIdleTime::timeoutReached, this, [this, id, kidletime](int _id) {
        if (_id != id) {
            return;
        }
        setState(false);
        kidletime->catchNextResumeEvent();
    });
    setState(true);
}

SuspendSwitch::SuspendSwitch(QObject *parent)
    : Button(parent)
{
    setId("suspend");
    setName("Suspend");

    connect(this, &Button::triggered, this, []() {
        qDebug() << "suspend triggered";
        OrgFreedesktopLogin1ManagerInterface logind(QStringLiteral("org.freedesktop.login1"),
                                                    QStringLiteral("/org/freedesktop/login1"),
                                                    QDBusConnection::systemBus());
        logind.Suspend(true).waitForFinished();
    });
}

LockedState::LockedState(QObject *parent)
    : Switch(parent)
{
    setId("locked");
    setName("Locked");
    setHaType("switch");

    setDiscoveryConfig("device_class", "lock");


    QDBusConnection::sessionBus().connect(QStringLiteral("org.freedesktop.ScreenSaver"),
                                          QStringLiteral("/ScreenSaver"),
                                          QStringLiteral("org.freedesktop.ScreenSaver"),
                                          QStringLiteral("ActiveChanged"),
                                          this, SLOT(screenLockedChanged(bool)));

    connect(this, &Switch::stateChangeRequested, this, &LockedState::stateChangeRequested);

    auto isLocked = QDBusMessage::createMethodCall("org.freedesktop.ScreenSaver",
                                   "/ScreenSaver",
                                   "org.freedesktop.ScreenSaver",
                                   "GetActive");
    auto pendingCall = QDBusConnection::sessionBus().asyncCall(isLocked);
    pendingCall.waitForFinished();
    bool locked = pendingCall.reply().arguments().at(0).toBool();
    setState(locked);
}

void LockedState::screenLockedChanged(bool active)
{
    setState(active);
}

void LockedState::stateChangeRequested(bool state)
{
    //     OrgFreedesktopLogin1ManagerInterface login1Session(QStringLiteral("org.freedesktop.login1"),
    //                                                  QStringLiteral("/org/freedesktop/session/auto"),
    //                                                  QDBusConnection::systemBus());
    //     if (message.payload() == "locked") {
    //         // login1Session.Lock();
    //     } else if (message.payload() == "unlocked") {
    //         // login1Session.Unlock();
    //     }
}

