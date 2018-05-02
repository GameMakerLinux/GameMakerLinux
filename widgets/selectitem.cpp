#include "selectitem.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListView>

SelectItem::SelectItem()
{
    setWindowTitle("Select parent");

    auto listView = new QListView;
    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    auto layout = new QVBoxLayout(this);
    layout->addWidget(listView);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &SelectItem::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &SelectItem::reject);
}
