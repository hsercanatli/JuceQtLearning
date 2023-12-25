#include "QMLApplication.h"
#include <QFontDatabase>
#include <QQmlContext>
#include <QString>
#include <QQmlEngine>


namespace {
    const QUrl MAIN_QML(u"qrc:/sercan.com/imports/Sercan/src/QML/main.qml"_qs);
    const QString IMPORT_PATH(":/sercan.com/imports");
}// namespace

QMLApplication::QMLApplication(std::shared_ptr<juce::AudioProcessorValueTreeState> apvts)
    : mApvts(apvts), qmlView(std::make_shared<QQuickView>()) {
    initializeModels();
    initializeControllers();

    registerContent();

    auto engine = qmlView->engine();
    engine->addImportPath(IMPORT_PATH);

    qmlView->setSource(MAIN_QML);
    qmlView->setResizeMode(QQuickView::SizeRootObjectToView);
}

void QMLApplication::initializeModels() {
    mGainModel = std::make_shared<GainModel>(mApvts);
}

void QMLApplication::initializeControllers() {
    mGainController = std::make_unique<GainController>(mGainModel);
}

void QMLApplication::registerContent() {
    QQmlContext *context = qmlView->rootContext();

    qmlRegisterSingletonInstance("com.sercan.JuceQtLearning", 1, 0, "GainModel", mGainModel.get());
    qmlRegisterSingletonInstance("com.sercan.JuceQtLearning", 1, 0, "GainController", mGainController.get());

    // others
    // Exposing the system's default monospaced font
    QFont monoSpacedFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    monoSpacedFont.setPixelSize(12);
    context->setContextProperty("monoSpacedFont", monoSpacedFont);
}
