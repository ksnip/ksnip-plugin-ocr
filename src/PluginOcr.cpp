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

#include "PluginOcr.h"

QString PluginOcr::recognize(const QPixmap &pixmap) const
{
	return mOcrWrapper.recognize(pixmap);
}

QString PluginOcr::recognize(const QPixmap &pixmap, const QString &dataPath) const
{
	return mOcrWrapper.recognize(pixmap, dataPath);
}

QString PluginOcr::version() const
{
	return QLatin1String(PROJECT_VERSION);
}
