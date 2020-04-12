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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ChordView : public QWidget {
    typedef QWidget _super;

    Q_OBJECT
    Q_PROPERTY(QString name MEMBER _name WRITE setName NOTIFY nameChanged)

    static constexpr int DEFAULT_FIRST_FRET     = 0;
    static constexpr int DEFAULT_NUM_STRINGS    = 6;
    static constexpr int DEFAULT_NUM_FRETS      = 5;

public:
    explicit ChordView(QWidget* parent = nullptr);
    virtual ~ChordView() = default;

    const QString& name() const {
        return _name;
    }

    void setName(const QString& name) {
        _name = name;
        emit nameChanged(_name);
    }

signals:
    void nameChanged(const QString& name);

public slots:

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString _name;
    int _firstFret;

    int _numStrings;
    int _numFrets;

    void drawFretboard(QPainter& painter, const QRect& fretBoard, const QColor& foregroundColor = Qt::black, const QColor& backgroundColor = Qt::white, int penWidth = 2);
    void drawMarker(QPainter& painer, const QRect& fretBoard, int string, int fret, const QColor& color = Qt::black);

    inline int getStringSpacing(const QRect& fretBoard) const {
        return fretBoard.width() / (_numStrings - 1);
    }

    inline int getFretSpacing(const QRect& fretBoard) const {
        return fretBoard.height() / _numFrets;
    }
};

#endif // _CHORDVIEW_H
