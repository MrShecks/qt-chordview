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
      _numStrings(DEFAULT_NUM_STRINGS),
      _numFrets(DEFAULT_NUM_FRETS),
      _padding(DEFAULT_PADDING) {

}

void ChordView::setTitle(const QString& name) {
    _title = name;

    // FIXME: Should probably only invlidate the title bounding rect
    update();

    emit titleChanged(_title);
}

bool ChordView::setFretMarker(int string, int fret, const QString& text /* = QString() */,
                              const QColor& textColor /* = Qt::white */, const QColor& markerColor /* = Qt::black */) {
    bool result = false;

    if(string >= 1 && string <= _numStrings && fret >= 1) {
        _fretMarkers.insert(string, { text, textColor, markerColor, fret });
        update();

        result = true;
    }

    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChordView::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    const QColor foregroundColor = palette().color(QPalette::ButtonText);
    const QColor fretboardColor = palette().color(QPalette::AlternateBase);
    const QRect bounds = rect().adjusted(_padding, _padding, -_padding, -_padding);
    qreal chordBoxOffset = 0;

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), palette().base());

    if(!_title.isEmpty ()) {
        const QRectF textBounds = drawTitle (painter, bounds, _title);

        chordBoxOffset = textBounds.height() + _padding;
    }

    const QRect fretBoard = bounds.adjusted(10, chordBoxOffset, -10, 0);

    drawChordBox (painter, fretBoard, foregroundColor, fretboardColor, 2);

    TFretMarkerMap::const_iterator it = _fretMarkers.constBegin();
    TFretMarkerMap::const_iterator limit = _fretMarkers.constEnd();

    for(; it != limit; ++it) {
        const FretMarker& marker = it.value();

        drawFretMarker(painter, fretBoard, it.key(), marker.fret, marker.markerColor);
    }

    Q_UNUSED(event)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QRectF ChordView::drawTitle(QPainter& painter, const QRectF& bounds, const QString& title) {
    const QFontMetrics fm = painter.fontMetrics();

    // TODO: Parse title and format any extensions/inversions etc characters using smaller subscript font (e.g A7, Amin7)
    painter.drawText(bounds, Qt::AlignTop|Qt::AlignHCenter, title);

    return fm.boundingRect(title);
}

void ChordView::drawChordBox(QPainter& painter, const QRectF& bounds, const QColor& foregroundColor /* = Qt::black */,
                              const QColor& backgroundColor /* = Qt::white */, int penWidth /* = 2 */) {
    const qreal cellSize = bounds.width() / _numStrings;
    const qreal padding = cellSize * 0.5f;
    const QRectF rect = QRectF(
        bounds.left() + padding,
        bounds.top(),
        bounds.width() - cellSize,
        cellSize * _numFrets
    );

    painter.setPen(QPen(foregroundColor, penWidth));
    painter.fillRect(rect, backgroundColor);

    for(int string=0; string < _numStrings; ++string) {
        painter.drawLine(
            QPointF(rect.left() + (string * cellSize), rect.top()),
            QPoint(rect.left() + (string * cellSize), rect.bottom())
        );
    }

    for(int fret=0; fret < _numFrets + 1; ++fret) {
        painter.drawLine(
            QPoint(rect.left(), rect.top() + (fret * cellSize)),
            QPoint(rect.right(), rect.top() + (fret * cellSize))
        );
    }
}

void ChordView::drawFretMarker(QPainter& painter, const QRectF& bounds, int string, int fret, const QColor& color /* = Qt::black */, float markerScale /* = DEFAULT_MARKER_SCALE */) {
    const qreal cellSize = bounds.width() / _numStrings;
    const qreal padding = cellSize * 0.5f;
    const qreal markerSize = cellSize * markerScale;

    const QRectF rc(
        bounds.left() + padding - (markerSize * 0.5f) + ((_numStrings - string) * cellSize),
        bounds.top() + ((fret - 1) * cellSize) + ((cellSize - markerSize) * 0.5f),
        markerSize,
        markerSize
    );

    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(rc);
}
