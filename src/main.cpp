#include <QApplication>
#include <QtNetwork>
#include <QtWidgets>


#include "constants.h"
#include "mainwindow.h"
#include "logger.h"

#include "updater.h"
#include "simplexmlparser.h"
#ifdef UPDATER_SPARKLE
#include "sparkleupdater.h"
#else
#include "defaultupdater.h"
#endif

void setupUpdater() {
#ifdef UPDATER_SPARKLE
    Updater::setInstance(new updater::SparkleUpdater());
#else
    auto updater = new updater::DefaultUpdater();
    updater->setManifestUrl(QUrl("https://pt3.bckmnn.com/release.xml"));
    updater->setParser(new updater::SimpleXmlParser());
    Updater::setInstance(updater);
#endif
}

int main(int argc, char **argv) {

    QCoreApplication::setApplicationName(Constants::NAME);
    QCoreApplication::setApplicationVersion(Constants::VERSION);

    QCoreApplication::setOrganizationDomain(Constants::ORG_DOMAIN);
    QCoreApplication::setOrganizationName(Constants::ORG_NAME);

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    setupUpdater();
    Logger::init();

    MainWindow win;

    win.addUpdateButton(Updater::instance().getAction());
    win.show();

    return app.exec();
}
