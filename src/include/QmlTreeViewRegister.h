/// @author Gribanov Aleksey

#include "TreeItem.h"
#include "TreeItemModel.h"
#include "QmlTool.h"

#include <QMetaType>
#include <QObject>

namespace sp {
namespace QmlTreeViewRegister {

    /** Register C++ classes for usage in QML. */
    static void appRegister()
    {
        qRegisterMetaType<TreeItem*>("TreeItem*");
        qRegisterMetaType<TreeItemModel*>("TreeItemModel*");
        qmlRegisterType<sp::QmlTool>("SP", 1, 0, "QmlTool");
    }
}
}
