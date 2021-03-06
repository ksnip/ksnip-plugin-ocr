/*
 * Copyright (C) 2021 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef PLUGIN_OCR_PLUGINOCR_H
#define PLUGIN_OCR_PLUGINOCR_H

#include <QObject>
#include <QtPlugin>

#include "IPluginOcr.h"
#include "OcrWrapper.h"

#include "BuildConfig.h"

class PluginOcr : public QObject, public IPluginOcr
{
Q_OBJECT
	Q_PLUGIN_METADATA(IID IPluginOcr_iid)
	Q_INTERFACES(IPluginOcr)

public:
	~PluginOcr() override = default;
	QString recognize(const QPixmap &pixmap) const override;
	QString recognize(const QPixmap &pixmap, const QString &dataPath) const override;
	QString version() const override;

private:
	OcrWrapper mOcrWrapper;
};

#endif //PLUGIN_OCR_PLUGINOCR_H
