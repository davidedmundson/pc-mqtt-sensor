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
    QApplication app(argc, argv);
    HaControl appControl;
    app.exec();
}

// There are 3 bits of code:
// HaControl, main daemon class, does connecting and whatnot
// Entity, represents an entity in HA. Subclassed into the different types
// Plugins (components.cpp). These are grouped by desktop related activities. Each plugin can have multiple entities.

/*
 Config
 [general]
 host=some.host
 port=1883
 user=myUsername
 password=myPassword
 */
