/*
 *  Copyright (C) 2016, Mike Walters <mike@flomp.net>
 *
 *  This file is part of inspectrum.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <memory>
#include "abstractsamplesource.h"
#include "plot.h"
#include "util.h"

class TracePlot : public Plot
{
    Q_OBJECT

public:
    TracePlot(std::shared_ptr<AbstractSampleSource> source);

    void paintMid(QPainter &painter, QRect &rect, range_t<size_t> sampleRange);
    std::shared_ptr<AbstractSampleSource> source() { return sampleSource; };

signals:
    void imageReady(QString key, QImage image);

public slots:
    void handleImage(QString key, QImage image);

private:
    QSet<QString> tasks;
    const int tileWidth = 1000;

    QPixmap getTile(size_t tileID, size_t sampleCount);
    void drawTile(QString key, const QRect &rect, range_t<size_t> sampleRange);
    void plotTrace(QPainter &painter, const QRect &rect, float *samples, size_t count, int step);
};
