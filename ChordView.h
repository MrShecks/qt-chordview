/*
 * File: ChordView.h
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

#ifndef _CHORDVIEW_H
#define _CHORDVIEW_H

#include <QWidget>
#include <QString>
#include <QMap>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ChordView : public QWidget {
    typedef QWidget _super;

    Q_OBJECT

    static constexpr int DEFAULT_NUM_FRETS      = 5;
    static constexpr int DEFAULT_PADDING        = 10;

    static constexpr float DEFAULT_FRET_MARKER_SCALE    = 0.65f;
    static constexpr qreal DEFAULT_STRING_MARKER_SCALE  = 0.40f;

public:

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class Chord {
        friend class ChordView;

        struct Marker {
            int fret;
            int finger;
            QString text;
            QColor textColor;
            QColor markerColor;

            bool isOpen() const     { return fret == STRING_MARKER_OPEN; }
            bool isMuted() const    { return fret == STRING_MARKER_MUTED; }
            bool isFretted() const  { return fret > STRING_MARKER_UNUSED; }
        };

        typedef QMap<int, Marker> TMarkerMap;

        static const int STRING_MARKER_UNUSED   =  0;
        static const int STRING_MARKER_OPEN     = -1;
        static const int STRING_MARKER_MUTED    = -2;

        static const int DEFAULT_STRING_COUNT   = 6;

        public:
            Chord(const QString& name = QString(), int stringCount = DEFAULT_STRING_COUNT)
                : _name(name), _stringCount(stringCount) {
            }

            virtual ~Chord() = default;

            void setName(const QString& name)   { _name = name; }

            void setMarker(int string, int fret, const QColor& markerColor = Qt::black, int finger = 0);
            void setMarker(int string, int fret, const QString& text, const QColor& textColor = Qt::white, const QColor& markerColor = Qt::black, int finger = 0);

            void setOpenMarker(int string);
            void setMutedMarker(int string);

            const QString& name() const         { return _name; }
            int stringCount() const             { return _stringCount; }

            bool hasName() const                { return !_name.isEmpty(); }
            bool isEmpty() const                { return _markers.isEmpty(); }

            void clear()                        { _markers.clear(); }

        private:
            QString _name;
            TMarkerMap _markers;
            int _stringCount;

            const TMarkerMap& getMarkers() const;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    explicit ChordView(QWidget* parent = nullptr);
    virtual ~ChordView() = default;

    const Chord& chord() const {
        return _chord;
    }

    void setChord(const Chord& chord);

signals:
    void chordChanged(const Chord& chord);

public slots:

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    Chord _chord;
    int _numFrets;
    int _padding;

    QRectF drawTitle(QPainter& painter, const QRectF& bounds, const QString& title);
    void drawChordBox(QPainter& painter, const QRectF& bounds, const QColor& foregroundColor, const QColor& backgroundColor, int spacing, int penWidth = 2);

    void drawMarker(QPainter& painter, const QRectF& bounds, const Chord::Marker& marker);
    void drawStringMarker(QPainter& painter, int x, int y, int size, int type);

    void drawFingerMarker(QPainter& painter, const QRectF& bounds, int numStrings, int string, int spacing, int finger);

    void drawFretMarker(QPainter& painer, const QRectF& bounds, int numStrings, int string, int fret, const QColor& color, int spacing, float markerScale = DEFAULT_FRET_MARKER_SCALE);
};

#endif // _CHORDVIEW_H
