
#include <QApplication>
#include <QtNetwork>
#include <QtWidgets>


#include "constants.h"
#include "mainwindow.h"

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

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    setupUpdater();

    MainWindow win;    
    //win.menuBar()->addAction(Updater::instance().getAction());
    win.addUpdateButton(Updater::instance().getAction());
    win.show();

    return app.exec();
}
