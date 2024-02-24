#include <QApplication>
#include <QDebug>
#include <QMqttClient>
#include <QtGlobal>
// #include <QNetworkConfigurationManager>

#include <KConfig>
#include <KSharedConfig>
#include <KConfigGroup>

#include "core.h"

int main(int argc, char ** argv)
{
    //TODO app name and stuff
    QApplication app(argc, argv);
    HaControl appControl;
    app.exec();
}


/**
 * Topics
 *
 * READ:
 * $hostname/connected [on/off]
 * $hostname/active [active/idle] (set after 5 minutes)

 * Note: you can use the update time of active to calculate how long we've been inactive, remember to add 5minutes

 * WRITE:
 * $hostname/suspend/set [on]
 * $hostname/notifications JSON{"title":"someTitle", "message": "someMessage"}

 Konversation queue (knotification plugin....or manually add Execute line in the relevant place?)
 Deliberately Invasive UI (i.e prevent work until you empty the washing machine - like rsibreak)
 Shortcut pressed event?
 Lock status?
 Battery?
 Only try to connect on certain wifi networks?
 NightMode

 Config
 [general]
 host=some.host
 port=1883
 user=myUsername
 password=myPassword

 */




// $hostname/locked

