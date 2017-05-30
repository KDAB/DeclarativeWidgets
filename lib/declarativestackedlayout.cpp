/*
  Copyright (C) 2012-2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Kevin Krammer, kevin.krammer@kdab.com
  Author: Tobias Koenig, tobias.koenig@kdab.com

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "declarativestackedlayout_p.h"

#include "declarativespaceritem_p.h"
#include "layoutcontainerinterface_p.h"

#include <QQmlInfo>
#include <QWidget>

DeclarativeStackedLayout::DeclarativeStackedLayout(QObject *parent)
  : QStackedLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

class StackedLayoutContainer : public LayoutContainerInterface
{
  public:
    explicit StackedLayoutContainer(QStackedLayout *layout)
      : m_layout(layout)
    {
      Q_ASSERT(m_layout);
    }

    void addLayout(QLayout *layout);
    void addSpacer(DeclarativeSpacerItem *spacerItem);
    void addWidget(QWidget *widget);
    void setContentsMargins(int left, int top, int right, int bottom);
    void getContentsMargins(int &left, int &top, int &right, int &bottom);

  private:
    QStackedLayout *m_layout;
};

DeclarativeStackedLayoutExtension::DeclarativeStackedLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(new StackedLayoutContainer(qobject_cast<QStackedLayout*>(parent)), parent)
{
}

int DeclarativeStackedLayoutExtension::count() const
{
  QStackedLayout *stackedLayout = qobject_cast<QStackedLayout*>(extendedLayout());
  Q_ASSERT(stackedLayout);

  return stackedLayout->count();
}

void StackedLayoutContainer::addLayout(QLayout*)
{
    qmlInfo(m_layout) << "StackedLayout does not support child layouts";
}

void StackedLayoutContainer::addSpacer(DeclarativeSpacerItem *spacerItem)
{
    qWarning() << Q_FUNC_INFO << "Using QStackedLayout::addItem for spacer item";
    m_layout->addItem(spacerItem->spacer());
}

void StackedLayoutContainer::addWidget(QWidget *widget)
{
  m_layout->addWidget(widget);
}

void StackedLayoutContainer::setContentsMargins(int left, int top, int right, int bottom)
{
  m_layout->setContentsMargins(left, top, right, bottom);
}

void StackedLayoutContainer::getContentsMargins(int &left, int &top, int &right, int &bottom)
{
  m_layout->getContentsMargins(&left, &top, &right, &bottom);
}
