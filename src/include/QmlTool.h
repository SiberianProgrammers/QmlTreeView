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
        /** Returns current Window displaying the item. */
        Q_INVOKABLE QQuickWindow* parentWindow(QQuickItem* item)
        {
            if (!item) {
                return nullptr;
            }

            return item->window();
        }

        /** Return cursor position relative the item. */
        Q_INVOKABLE QPointF cursorPosInItem(QQuickItem* item)
        {
            auto cursorPos = QCursor::pos();
            auto itemPos = item->mapToGlobal(QPoint(0,0));
            return cursorPos - itemPos;
        }
};
}
