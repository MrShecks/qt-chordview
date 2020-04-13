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
    Q_PROPERTY(QString title MEMBER _title WRITE setTitle NOTIFY titleChanged)

    static constexpr int DEFAULT_FIRST_FRET     = 0;
    static constexpr int DEFAULT_NUM_STRINGS    = 6;
    static constexpr int DEFAULT_NUM_FRETS      = 5;
    static constexpr int DEFAULT_PADDING        = 10;

    static constexpr float DEFAULT_MARKER_SCALE = 0.65f;

    struct FretMarker {
        QString text;
        QColor textColor;
        QColor markerColor;
        int fret;
    };

    typedef QMap<int, FretMarker> TFretMarkerMap;

public:
    static const int FRETTED_POSITION_NONE      = 0;
    static const int FRETTED_POSITION_OPEN      = -1;
    static const int FRETTED_POSITION_MUTED     = -2;

    explicit ChordView(QWidget* parent = nullptr);
    virtual ~ChordView() = default;

    const QString& title() const {
        return _title;
    }

    void setTitle(const QString& name);
    bool setFretMarker(int string, int fret, const QString& text = QString(), const QColor& textColor = Qt::white, const QColor& markerColor = Qt::black);

signals:
    void titleChanged(const QString& title);

public slots:

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    TFretMarkerMap _fretMarkers;
    QString _title;


    int _numStrings;
    int _numFrets;

    int _padding;

    QRectF drawTitle(QPainter& painter, const QRectF& bounds, const QString& title);
    void drawChordBox(QPainter& painter, const QRectF& bounds, const QColor& foregroundColor = Qt::black, const QColor& backgroundColor = Qt::white, int penWidth = 2);
    void drawFretMarker(QPainter& painer, const QRectF& bounds, int string, int fret, const QColor& color = Qt::black, float markerScale = DEFAULT_MARKER_SCALE);
};

#endif // _CHORDVIEW_H
