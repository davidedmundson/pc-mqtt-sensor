cmake_minimum_required(VERSION 3.16)

project(linux-ha-control)
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
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

set(SOURCES main.cpp core.cpp components.cpp login1_manager_interface.cpp)
add_executable(linux-ha-control ${SOURCES})
target_link_libraries(linux-ha-control Qt6::Gui Qt6::Widgets Qt6::Mqtt Qt6::DBus KF6::IdleTime KF6::Notifications KF6::ConfigCore)

install(TARGETS linux-ha-control ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
# install( PROGRAMS net.davidedmundson.ha-receiver.desktop  DESTINATION )


feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

