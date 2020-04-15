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

    ChordView::Chord chord1("A major");

    chord1.setMutedMarker(6);
    chord1.setOpenMarker(5);
    chord1.setMarker(4, 2);
    chord1.setMarker(3, 2);
    chord1.setMarker(2, 2);
    chord1.setOpenMarker(1);

    _ui->chordview1->setChord(chord1);

    ChordView::Chord chord2("C major");

    chord2.setMutedMarker(6);
    chord2.setMarker(5, 3);
    chord2.setOpenMarker(4);
    chord2.setMarker(3, 2);
    chord2.setMarker(2, 1);
    chord2.setOpenMarker(1);

    _ui->chordview2->setChord(chord2);

    ChordView::Chord chord3("E minor");

    chord3.setOpenMarker(6);
    chord3.setMarker(5, 2);
    chord3.setMarker(4, 2);
    chord3.setOpenMarker(3);
    chord3.setOpenMarker(2);
    chord3.setOpenMarker(1);

    _ui->chordview3->setChord(chord3);

    ChordView::Chord chord4("F major");

    chord4.setMarker(1, 1, Qt::red);
    chord4.setMarker(2, 1);
    chord4.setMarker(3, 2);
    chord4.setMarker(4, 3, Qt::red);
    chord4.setMarker(5, 3);
    chord4.setMarker(6, 1, Qt::red);

    _ui->chordview4->setChord(chord4);
}

ChordViewDialog::~ChordViewDialog() {
    delete _ui;
}
