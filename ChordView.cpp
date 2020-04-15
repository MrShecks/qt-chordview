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
      _numFrets(DEFAULT_NUM_FRETS),
      _padding(DEFAULT_PADDING) {

}

void ChordView::setChord(const Chord& chord) {
    _chord = chord;

    update();
    emit chordChanged(_chord);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChordView::paintEvent(QPaintEvent* event) {
    if(!_chord.isEmpty()) {
        QPainter painter(this);
        const QColor foregroundColor = palette().color(QPalette::ButtonText);
        const QColor fretboardColor = palette().color(QPalette::AlternateBase);
        const QRect bounds = rect().adjusted(_padding, _padding, -_padding, -_padding);
        const int numStrings = _chord.stringCount();
        const qreal spacing = bounds.width() / numStrings;
        qreal chordBoxOffset = 0;

        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(), palette().base());

        if(_chord.hasName()) {
            const QRectF textBounds = drawTitle (painter, bounds, _chord.name());

            chordBoxOffset = textBounds.height() + _padding;
        }

        const qreal stringMarkerSize = spacing * DEFAULT_STRING_MARKER_SCALE;

        const QRectF chordBoxBounds(
            bounds.left() + spacing * 0.5f,
            bounds.top() + chordBoxOffset + stringMarkerSize + 5,
            bounds.width() - spacing,
            _numFrets * spacing
        );

        drawChordBox(painter, chordBoxBounds, foregroundColor, fretboardColor, spacing, 2);

        const Chord::TMarkerMap& markers = _chord.getMarkers();
        Chord::TMarkerMap::const_iterator it = markers.constBegin();
        Chord::TMarkerMap::const_iterator limit = markers.constEnd();

        for(; it != limit; ++it) {
            const Chord::Marker& marker = it.value();

            if(marker.isFretted())
                drawFretMarker(painter, chordBoxBounds, numStrings, it.key(), marker.fret, marker.markerColor, spacing);
            else {
                drawStringMarker(
                    painter,
                    chordBoxBounds.left() + ((numStrings - it.key()) * spacing),
                    chordBoxBounds.top() - stringMarkerSize - 5,
                    stringMarkerSize,
                    marker.fret
                );
            }
        }
    }

    Q_UNUSED(event)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QRectF ChordView::drawTitle(QPainter& painter, const QRectF& bounds, const QString& title) {
    QRectF textBounds;

    // TODO: Parse title and format any extensions/inversions etc characters using smaller subscript font (e.g A7, Amin7)
    painter.drawText(bounds, Qt::AlignTop|Qt::AlignHCenter, title, &textBounds);

    return textBounds;
}

void ChordView::drawChordBox(QPainter& painter, const QRectF& bounds, const QColor& foregroundColor, const QColor& backgroundColor, int spacing, int penWidth /* = 2 */) {
    const int numStrings = _chord.stringCount();

    painter.setPen(QPen(foregroundColor, penWidth));
    painter.fillRect(bounds, backgroundColor);

    for(int string=0; string < numStrings; ++string) {
        painter.drawLine(
            QPointF(bounds.left() + (string * spacing), bounds.top()),
            QPoint(bounds.left() + (string * spacing), bounds.bottom())
        );
    }

    for(int fret=0; fret < _numFrets + 1; ++fret) {
        painter.drawLine(
            QPoint(bounds.left() + penWidth * 0.5f, bounds.top() + (fret * spacing)),
            QPoint(bounds.right() - penWidth, bounds.top() + (fret * spacing))
        );
    }
}

void ChordView::drawMarker(QPainter& painter, const QRectF& bounds, const Chord::Marker& marker) {

}

void ChordView::drawStringMarker(QPainter& painter, int x, int y, int size, int type) {
    const QRectF rc(x - (size * 0.5f), y, size, size);

    painter.setPen(Qt::black);

    if(type == Chord::STRING_MARKER_OPEN)
        painter.drawText(rc, Qt::AlignCenter|Qt::TextDontClip, "O");
    else if(type == Chord::STRING_MARKER_MUTED)
        painter.drawText(rc, Qt::AlignCenter|Qt::TextDontClip, "X");
}

void ChordView::drawFingerMarker(QPainter& painter, const QRectF& bounds, int numStrings, int string, int spacing, int finger) {

}

void ChordView::drawFretMarker(QPainter& painter, const QRectF& bounds, int numStrings, int string, int fret, const QColor& color, int spacing, float markerScale /* = DEFAULT_MARKER_SCALE */) {
    const qreal markerSize = spacing * markerScale;
    const QRectF rc(
        bounds.left() - (markerSize * 0.5f) + ((numStrings - string) * spacing),
        bounds.top() + ((fret - 1) * spacing) + ((spacing - markerSize) * 0.5f),
        markerSize,
        markerSize
    );

    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawEllipse(rc);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ChordView::Chord
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ChordView::Chord::setMarker(int string, int fret, const QColor& markerColor /* = Qt::black */, int finger /* = 0 */) {
    _markers.insert(string, { fret, finger, QString(), Qt::white, markerColor });
}

void ChordView::Chord::setMarker(int string, int fret, const QString& text, const QColor& textColor /* = Qt::white */, const QColor& markerColor /* = Qt::black */, int finger /* = 0 */) {
    _markers.insert(string, { fret, finger, text, textColor, markerColor });
}

void ChordView::Chord::setOpenMarker(int string) {
    _markers.insert(string, { STRING_MARKER_OPEN, 0, QString(), Qt::white, Qt::black });
}

void ChordView::Chord::setMutedMarker(int string) {
    _markers.insert(string, { STRING_MARKER_MUTED, 0, QString(), Qt::white, Qt::black });
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const ChordView::Chord::TMarkerMap& ChordView::Chord::getMarkers() const {
    return _markers;
}

