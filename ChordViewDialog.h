/*
 * File: %{Cpp:License:FileName}
 * Created: 2020-4-12
 *
 * Copyright (c) shecks 2020 <shecks@gmail.com>
 * All rights reserved.
 *
 * This file is part of %QT_PROJECT_NAME%.
 *
 * %QT_PROJECT_NAME% is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * %QT_PROJECT_NAME% is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with %QT_PROJECT_NAME%.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef _CHORDVIEWDIALOG_H
#define _CHORDVIEWDIALOG_H

#include <QDialog>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QT_BEGIN_NAMESPACE
namespace Ui {
    class ChordViewDialog;
}
QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ChordViewDialog : public QDialog {
    typedef QDialog _super;

    Q_OBJECT

public:
    ChordViewDialog(QWidget* parent = nullptr);
    ~ChordViewDialog();

private:
    Ui::ChordViewDialog* _ui;
};

#endif // _CHORDVIEWDIALOG_H
