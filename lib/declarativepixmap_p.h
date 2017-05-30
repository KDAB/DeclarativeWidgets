/*
  Copyright (C) 2013 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
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

#ifndef DECLARATIVEPIXMAP_P_H
#define DECLARATIVEPIXMAP_P_H

#include <QObject>
#include <QPixmap>
#include <qqml.h>
#include <QStringList>

class DeclarativePixmapAttached : public QObject
{
  Q_OBJECT

  public:
    explicit DeclarativePixmapAttached(QObject *parent = 0);

    Q_INVOKABLE QPixmap fromFileName(const QString &fileName);
};

class DeclarativePixmap : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QPixmap Pixmap READ pixmap WRITE setPixmap NOTIFY pixmapChanged)
  Q_PROPERTY(int width READ width NOTIFY widthChanged)
  Q_PROPERTY(int height READ height NOTIFY heightChanged)
  Q_PROPERTY(bool isNull READ isNull NOTIFY isNullChanged)

  public:
    explicit DeclarativePixmap(QObject *parent = 0);
    ~DeclarativePixmap();

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap);

    int height() const;
    int width() const;

    bool isNull() const;

    static DeclarativePixmapAttached *qmlAttachedProperties(QObject *parent);

  Q_SIGNALS:
    void pixmapChanged(const QPixmap &Pixmap);
    void heightChanged(int height);
    void widthChanged(int width);
    void isNullChanged(bool isNull);

  private:
    class Private;
    Private *const d;
};

QML_DECLARE_TYPEINFO(DeclarativePixmap, QML_HAS_ATTACHED_PROPERTIES)

#endif // DECLARATIVEPIXMAP_P_H
