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

Q_DECLARE_LOGGING_CATEGORY(log_main);
Q_LOGGING_CATEGORY(log_main, "pt3.main");

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

    int fontVMreg = QFontDatabase::addApplicationFont("://../3rdparty/VictorMono-Regular.otf");
    QStringList familyNames = QFontDatabase::applicationFontFamilies(fontVMreg);

    QApplication app(argc, argv);

    bool is_mac = QOperatingSystemVersion::current().type() == QOperatingSystemVersion::MacOS;

    QString app_working_dir(QDir::cleanPath(QDir(".").absolutePath()));
    QString app_dir((is_mac) ? QDir::cleanPath(QCoreApplication::applicationDirPath()+"/../../..")
                    : QCoreApplication::applicationDirPath());
    QString bundle_dir((is_mac) ? QDir::cleanPath(QCoreApplication::applicationDirPath()+"/../..")
                       : QCoreApplication::applicationDirPath());


    // parsing commandline
    QCommandLineParser parser;
    parser.setApplicationDescription(QString("PT3 is a qml prototyping environment."));

    const QCommandLineOption versionOption = parser.addVersionOption();
    const QCommandLineOption helpOption = parser.addHelpOption();


    QCommandLineOption fullScreenOption(QStringList() << "f" << "fullscreen", QCoreApplication::translate("main", "start PT3 in fullscreen mode."));
    parser.addOption(fullScreenOption);

    QCommandLineOption watchOption(QStringList() << "w" << "watch", QCoreApplication::translate("main", "watch for changes in prototype and autoreload."));
    parser.addOption(watchOption);

    QCommandLineOption moveToScreenOption(QStringList() << "s" <<"start-on-screen", QCoreApplication::translate("main","starts PT3 on <screen>. Where <screen> is the name or index of the target screen."), "screen");
    parser.addOption(moveToScreenOption);

    QCommandLineOption additionaImportPath(QStringList() << "i" <<"import-path", QCoreApplication::translate("main","adds <folder> as additional import path."), "folder");
    parser.addOption(additionaImportPath);

    QCommandLineOption startupLanguage(QStringList() << "l" <<"language", QCoreApplication::translate("main","loads <lang> translator on startup. (eg. -l de)"), "lang");
    parser.addOption(startupLanguage);

    parser.addPositionalArgument("proto-folder", QCoreApplication::translate("main", "path to a <.proto> folder"));

    parser.process(app);

    setupUpdater();
    Logger::init();

    qInfo(log_main) << app.applicationVersion() << Constants::GIT_VERSION;
    for(auto p : familyNames) {
        qDebug(log_main) << " + " << p;
    }


    MainWindow win;

    win.setListViewModel(Logger::messageModel);
    win.addUpdateButton(Updater::instance().getAction());

    if(parser.isSet(fullScreenOption)) {
        win.showFullScreen();
    } else {
        win.show();
    }

    return app.exec();
}
