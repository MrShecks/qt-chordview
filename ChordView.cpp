/*
 * File: ChordView.cpp
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

#include "ChordView.h"

#include <QPainter>
#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ChordView
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ChordView::ChordView(QWidget* parent /* = nullptr */)
    : _super(parent),
      _firstFret(DEFAULT_FIRST_FRET),
      _numStrings(DEFAULT_NUM_STRINGS),
      _numFrets(DEFAULT_NUM_FRETS) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChordView::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    const QRect fretBoard = rect().adjusted (20, 40, -20, -20);

    drawFretboard (painter, fretBoard, Qt::black, /* QColor(0xfe, 0xfe, 0x9c)*/ Qt::white, 2);
    drawMarker (painter, fretBoard, 6, 1);
    drawMarker (painter, fretBoard, 5, 1);
    drawMarker (painter, fretBoard, 4, 2);
    drawMarker (painter, fretBoard, 3, 3);
    drawMarker (painter, fretBoard, 2, 3);
    drawMarker (painter, fretBoard, 1, 1);

    Q_UNUSED(event)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChordView::drawFretboard(QPainter& painter, const QRect& fretBoard, const QColor& foregroundColor /* = Qt::black */,
                              const QColor& backgroundColor /* = Qt::white */, int penWidth /* = 2 */) {
    const int stringSpacing = getStringSpacing(fretBoard);
    const int fretSpacing = getFretSpacing(fretBoard);

    painter.setPen(QPen(foregroundColor, penWidth));
    painter.fillRect(fretBoard, backgroundColor);

    for(int strings=0; strings < _numStrings; ++strings) {
        painter.drawLine(
            fretBoard.left() + (strings * stringSpacing),
            fretBoard.top(),
            fretBoard.left() + (strings * stringSpacing),
            fretBoard.bottom()
        );
    }

    for(int fret=0; fret < _numFrets + 1; ++fret) {
        painter.drawLine(
            fretBoard.left(),
            fretBoard.top() + (fret * fretSpacing),
            fretBoard.right(),
            fretBoard.top() + (fret * fretSpacing)
        );
    }
}

void ChordView::drawMarker(QPainter& painter, const QRect& fretBoard, int string, int fret, const QColor& color /* = Qt::black */) {
    const int stringSpacing = getStringSpacing(fretBoard);
    const int fretSpacing = getFretSpacing(fretBoard);
    const int markerSize = qMin(stringSpacing, fretSpacing) * 0.70;

    const QRect rc(
        fretBoard.left() - (markerSize / 2) + ((string - 1) * stringSpacing),
        fretBoard.top() + ((fret - 1) * fretSpacing) + ((fretSpacing - markerSize) / 2),
        markerSize,
        markerSize
    );

    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(rc);
}
