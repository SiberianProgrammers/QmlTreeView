#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlEngine>

#include "QmlTreeViewRegister.h"

using namespace sp;

//------------------------------------------------------------------------------
TreeItemInterface* createItem(TreeItemInterface* parent, const QString& name)
{
    TreeItem* item = new TreeItem(parent);
    item->setName(name);
    return item;
}

//------------------------------------------------------------------------------
void fillTreeItemModel(TreeItemModel* model)
{
    auto rootItem = model->rootItem();
    rootItem->setName(QObject::tr("Root"));

    createItem(rootItem, QObject::tr("Item 0.1"));
    createItem(rootItem, QObject::tr("Item 0.2"));
    createItem(rootItem, QObject::tr("Item 0.3"));

    auto category1 = createItem(rootItem, QObject::tr("Category 1"));
    auto category2 = createItem(rootItem, QObject::tr("Category 2"));

    createItem(category1, QObject::tr("Item 1.1"));
    createItem(category1, QObject::tr("Item 1.2"));
    createItem(rootItem, QObject::tr("Item 0.4"));

    createItem(category2, QObject::tr("Item 2.1"));
    auto category3 = createItem(category2, QObject::tr("Category 3"));
    createItem(category2, QObject::tr("Item 2.2"));
    createItem(category2, QObject::tr("Item 2.3"));

    createItem(category3, QObject::tr("Item 3.1"));
    createItem(category3, QObject::tr("Item 3.2"));

    model->refillByRoot();
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Important - without register classes, qml doesn't work correct
    QmlTreeViewRegister::appRegister();

    // Generate & fill TreeItemModel.
    QQmlContext* context = engine.rootContext();
    TreeItemModel* model = new TreeItemModel();
    context->setContextProperty("TreeItemModel", model);
    fillTreeItemModel(model);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine
                    , &QQmlApplicationEngine::objectCreated
                    , &app
                    , [url](QObject *obj, const QUrl &objUrl) {
                        if (!obj && url == objUrl)
                            QCoreApplication::exit(-1);
                       }
                    , Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
