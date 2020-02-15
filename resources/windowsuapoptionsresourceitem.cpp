#include "windowsuapoptionsresourceitem.h"

WindowsUAPOptionsResourceItem::WindowsUAPOptionsResourceItem()
    : ResourceItem { ResourceType::WindowsUAPOptions }
{

}

void WindowsUAPOptionsResourceItem::load(QJsonObject object)
{
    setName(object["name"].toString());
}

QString WindowsUAPOptionsResourceItem::filename() const
{
    return "options/windowsuap/options_windowsuap.yy";
}
