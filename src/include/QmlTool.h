/// @author Gribanov Aleksey

#include <QQuickItem>
#include <QWindow>
#include <QQuickWindow>

namespace sp {

/***************************************************************************//**
 * @brief Asset tools for usage C++ methods from QML.
 ******************************************************************************/
class QmlTool: public QObject
{
    Q_OBJECT

    public:
        Q_INVOKABLE QQuickWindow* parentWindow(QQuickItem* item)
        {
            if (!item) {
                return nullptr;
            }

            return item->window();
        }
};
}
