#pragma once

#include <QObject>
#include <QVariantMap>

class QMqttClient;
class QMqttSubscription;

// If extending, you want to create an Entity of type BinarySensor, Button or Switch
// Generally these class abstract the connected state of the mqtt server and discovery
// but plugins are able to have low level access if they want to

class HaControl : public QObject {
public:
    HaControl();
    ~HaControl();
    static QMqttClient *mqttClient() {
        return s_self->m_client;
    }
private:
    static HaControl *s_self;
    QMqttClient *m_client;
    // QNetworkConfigurationManager m_networkConfigurationManager;
};

class Entity: public QObject
{
    Q_OBJECT
public:
    void sendRegistration();

    void setId(const QString &newId);
    QString id() const;

    void setName(const QString &newName);
    QString name() const;

    void setDiscoveryConfig(const QString &key, const QVariant &value);
    void setHaConfig(const QVariantMap &newHaConfig);

protected:
    Entity(QObject *parent);
    QString hostname() const;
    QString baseTopic() const;

    void setHaType(const QString &newHaType);
    QString haType() const;

private:
    QString m_id;
    QString m_name;
    QString m_haType;
    QVariantMap m_haConfig;
};

class BinarySensor : public Entity
{
    Q_OBJECT
public:
    BinarySensor(QObject *parent);
    void setState(bool state);
private:
    bool m_state = false;
};

class Button : public Entity
{
    Q_OBJECT
public:
    Button(QObject *parent);
Q_SIGNALS:
    void triggered();
private:
    QScopedPointer<QMqttSubscription> m_subscription;
};

class Switch : public Entity
{
    Q_OBJECT
public:
    Switch(QObject *parent);
    void setState(bool state);
Q_SIGNALS:
    void stateChangeRequested(bool state);
private:
    bool m_state = false;
    QScopedPointer<QMqttSubscription> m_subscription;
};


