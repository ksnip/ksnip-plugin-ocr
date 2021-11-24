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

#include <QApplication>
#include <QMainWindow>
#include <QPluginLoader>
#include <QDebug>
#include <QDir>

#include "IPluginOcrOther.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QMainWindow mainWindow;
	mainWindow.show();

	qDebug() << "Checking for plugins";
	QDir pluginsDir(QLatin1String("../src/"));
	const QStringList entries = pluginsDir.entryList(QDir::Files);
	for (const QString &fileName : entries) {
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
		auto plugin = pluginLoader.instance();
		if (plugin) {
			auto pluginOcr = qobject_cast<IPluginOcrOther*>(plugin);
			if (pluginOcr) {
				pluginOcr->doSomething();
			} else {
				qDebug() << "Unable to cast to interface";
			}
			pluginLoader.unload();
		} 
	}
	qDebug() << "Finished checking for plugins";

	return app.exec();
}
