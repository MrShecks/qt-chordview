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

#include "ChordViewDialog.h"
#include "ui_ChordViewDialog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ChordViewDialog::ChordViewDialog(QWidget* parent)
    : _super(parent),
      _ui(new Ui::ChordViewDialog) {

    _ui->setupUi(this);

    _ui->chordview1->setTitle("A major");
    _ui->chordview1->setFretMarker (4, 2);
    _ui->chordview1->setFretMarker (3, 2);
    _ui->chordview1->setFretMarker (2, 2);

    _ui->chordview2->setTitle("C major");
    _ui->chordview2->setFretMarker (2, 1);
    _ui->chordview2->setFretMarker (3, 2);
    _ui->chordview2->setFretMarker (5, 3);

    _ui->chordview3->setTitle("E minor");
    _ui->chordview3->setFretMarker (5, 2);
    _ui->chordview3->setFretMarker (4, 2);

    _ui->chordview4->setTitle("F major");
    _ui->chordview4->setFretMarker (1, 1, QString(), Qt::white, Qt::red);
    _ui->chordview4->setFretMarker (2, 1);
    _ui->chordview4->setFretMarker (3, 2);
    _ui->chordview4->setFretMarker (4, 3, QString(), Qt::white, Qt::red);
    _ui->chordview4->setFretMarker (5, 3);
    _ui->chordview4->setFretMarker (6, 1, QString(), Qt::white, Qt::red);
}

ChordViewDialog::~ChordViewDialog() {
    delete _ui;
}
