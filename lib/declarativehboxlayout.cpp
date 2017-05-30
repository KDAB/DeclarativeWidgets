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

#include "declarativehboxlayout_p.h"

#include "declarativespaceritem_p.h"
#include "layoutcontainerinterface_p.h"

#include <QQmlInfo>
#include <QWidget>

DeclarativeHBoxLayout::DeclarativeHBoxLayout(QObject *parent)
  : QHBoxLayout()
{
  setParent(qobject_cast<QWidget*>(parent));
}

DeclarativeBoxLayoutAttached *DeclarativeHBoxLayout::qmlAttachedProperties(QObject *parent)
{
  QWidget *widget = qobject_cast<QWidget*>(parent);
  if (widget)
    return new DeclarativeBoxLayoutAttached(widget, parent);

  QLayout *layout = qobject_cast<QLayout*>(parent);
  if (layout)
    return new DeclarativeBoxLayoutAttached(layout, parent);

  DeclarativeSpacerItem *spacerItem = qobject_cast<DeclarativeSpacerItem*>(parent);
  if (spacerItem)
    return new DeclarativeBoxLayoutAttached(spacerItem, parent);

  qmlInfo(parent) << "Can only attach HBoxLayout to widgets, spacers and layouts";
  return 0;
}

class HBoxLayoutContainer : public LayoutContainerInterface
{
  public:
    explicit HBoxLayoutContainer(QHBoxLayout *layout)
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
    QHBoxLayout *m_layout;
};

DeclarativeHBoxLayoutExtension::DeclarativeHBoxLayoutExtension(QObject *parent)
  : DeclarativeLayoutExtension(new HBoxLayoutContainer(qobject_cast<QHBoxLayout*>(parent)), parent)
{
}

void HBoxLayoutContainer::addLayout(QLayout *layout)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(layout, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_layout);
  }

  m_layout->addLayout(layout, stretch);
  m_layout->setAlignment(layout, alignment);
}

void HBoxLayoutContainer::addSpacer(DeclarativeSpacerItem *spacerItem)
{
    m_layout->addSpacerItem(spacerItem->spacer());
}

void HBoxLayoutContainer::addWidget(QWidget *widget)
{
  int stretch = 0;
  Qt::Alignment alignment = 0;

  QObject *attachedProperties = qmlAttachedPropertiesObject<DeclarativeHBoxLayout>(widget, false);
  DeclarativeBoxLayoutAttached *properties = qobject_cast<DeclarativeBoxLayoutAttached*>(attachedProperties);
  if (properties) {
    stretch = properties->stretch();
    alignment = properties->alignment();

    properties->setParentLayout(m_layout);
  }

  m_layout->addWidget(widget, stretch, alignment);
}

void HBoxLayoutContainer::setContentsMargins(int left, int top, int right, int bottom)
{
  m_layout->setContentsMargins(left, top, right, bottom);
}

void HBoxLayoutContainer::getContentsMargins(int &left, int &top, int &right, int &bottom)
{
  m_layout->getContentsMargins(&left, &top, &right, &bottom);
}
