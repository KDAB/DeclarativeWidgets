/*
  Copyright (C) 2012-2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVESTATUSBAR_P_H
#define DECLARATIVESTATUSBAR_P_H

#include "defaultwidgetcontainer.h"

#include <qqml.h>
#include <QStatusBar>

class DeclarativeStatusBarAttached : public QObject
{
  Q_OBJECT

  Q_PROPERTY(int stretch READ stretch WRITE setStretch NOTIFY stretchChanged)

  public:
    explicit DeclarativeStatusBarAttached(QObject *parent = 0);
    ~DeclarativeStatusBarAttached();

    void setStretch(int stretch);
    int stretch() const;

  Q_SIGNALS:
    void stretchChanged();

  private:
    class Private;
    Private *const d;
};

class DeclarativeStatusBar : public QStatusBar
{
  Q_OBJECT

  public:
    explicit DeclarativeStatusBar(QWidget *parent = 0);

    static DeclarativeStatusBarAttached *qmlAttachedProperties(QObject *object);
};

QML_DECLARE_TYPEINFO(DeclarativeStatusBar, QML_HAS_ATTACHED_PROPERTIES)

class StatusBarWidgetContainer : public DefaultWidgetContainer
{
  public:
    explicit StatusBarWidgetContainer(QObject *parent = 0);

    void setLayout(QLayout *layout);
    void addWidget(QWidget *widget);

  private:
    QStatusBar *extendedStatusBar() const;
};

#endif
