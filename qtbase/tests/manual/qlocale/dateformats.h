/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef DATEFORMATS_H
#define DATEFORMATS_H

#include <QWidget>
#include <QLocale>

class QLineEdit;
class QScrollArea;
class QGridLayout;
class QComboBox;

class DateFormatsWidget : public QWidget
{
    Q_OBJECT
public:
    DateFormatsWidget();

private:
    void addItem(const QString &label, QWidget *);
    QLineEdit *addItem(const QString &label);

    QScrollArea *scrollArea;
    QWidget *scrollAreaWidget;
    QGridLayout *layout;

    QLineEdit *shortDateFormat;
    QLineEdit *longDateFormat;
    QLineEdit *shortTimeFormat;
    QLineEdit *longTimeFormat;
    QLineEdit *shortDateTimeFormat;
    QLineEdit *longDateTimeFormat;
    QLineEdit *amText;
    QLineEdit *pmText;
    QLineEdit *firstDayOfWeek;
    QComboBox *monthNamesShort, *monthNamesLong;
    QComboBox *standaloneMonthNamesShort, *standaloneMonthNamesLong;
    QComboBox *dayNamesShort, *dayNamesLong;
    QComboBox *standaloneDayNamesShort, *standaloneDayNamesLong;

private slots:
    void localeChanged(QLocale locale);
};

#endif
