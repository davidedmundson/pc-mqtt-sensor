cmake_minimum_required(VERSION 3.16)

project(kde-ha)
set(PROJECT_VERSION "6.0.80")
set(PROJECT_VERSION_MAJOR 6)

set(PROJECT_DEP_VERSION "6.0.80")
set(QT_MIN_VERSION "6.6.0")
set(KF6_MIN_VERSION "5.240.0")
set(KDE_COMPILERSETTINGS_LEVEL "5.82")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(ECM ${KF6_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMOptionalAddSubdirectory)
include(FeatureSummary)
include(KDEClangFormat)
include(ECMSetupVersion)
include(ECMQtDeclareLoggingCategory)
include(ECMQmlModule)
include(ECMConfiguredInstall)


find_package(Qt6 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    DBus
    Widgets
    Mqtt
)

set(KF6_MIN_VERSION "5.240.0")
find_package(KF6 ${KF6_MIN_VERSION} REQUIRED COMPONENTS
    Config
    Notifications
    IdleTime
    GlobalAccel
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(SOURCES main.cpp core.cpp)

add_subdirectory(integrations)

add_executable(kde-ha ${SOURCES}
    dbusproperty.h dbusproperty.cpp)
target_link_libraries(
    kde-ha
    Qt6::Gui
    Qt6::Widgets
    Qt6::Mqtt
    Qt6::DBus
    KDEHAIntegrations
    KF6::IdleTime
    KF6::GlobalAccel
    KF6::Notifications
    KF6::ConfigCore
)

install(TARGETS kde-ha ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
ecm_install_configured_files(INPUT net.davidedmundson.kde-ha.desktop.in @ONLY DESTINATION ${KDE_INSTALL_AUTOSTARTDIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
