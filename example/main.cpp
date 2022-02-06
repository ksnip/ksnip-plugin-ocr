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
#include <QDir>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>

#include "IPluginOcrOther.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QMainWindow mainWindow;

	auto centralWidget = new QWidget(&mainWindow);
	auto imageLabel = new QLabel(&mainWindow);
	auto textLabel = new QLabel(&mainWindow);
	auto layout = new QVBoxLayout(centralWidget);

	mainWindow.setCentralWidget(centralWidget);

	layout->addWidget(imageLabel);
	layout->addWidget(textLabel);

	centralWidget->setFixedWidth(510);
	centralWidget->setFixedHeight(600);

	QPixmap pixmap(500, 500);
	pixmap.fill(Qt::gray);
	QPainter painter(&pixmap);
	painter.setFont( QFont("Times", 30) );
	painter.drawText( QPoint(50, 150), "Hello, this is a simple," );
	painter.drawText( QPoint(50, 190), "Test" );
	painter.drawText( QPoint(50, 230), "and some additional text..." );

	imageLabel->setPixmap(pixmap);
	imageLabel->setFixedWidth(500);
	imageLabel->setFixedHeight(500);

	textLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

	QDir pluginsDir(QLatin1String("../src/"));

#if  defined(_WIN32)
	// Under Windows the 3rd Party Dlls are next to the plugin in the same directory
	// in order to find them we set the current directory to the plugin directory
	QDir::setCurrent(pluginsDir.path());
#endif

	const QStringList entries = pluginsDir.entryList(QDir::Files);
	for (const QString &fileName : entries) {
		QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
		auto plugin = pluginLoader.instance();
		if (plugin == nullptr) {
			if (!pluginLoader.metaData().isEmpty()) {
				qDebug() << "Error loading plugin" << fileName << pluginLoader.errorString();
			} else {
				qDebug() << "Checked" << fileName << "and it's not a plugin.";
			}
		}  else {
			auto pluginOcr = qobject_cast<IPluginOcrOther*>(plugin);
			if (pluginOcr) {
				qDebug() << "Loaded plugin " << fileName << " with version " << pluginOcr->version();
				auto text = pluginOcr->recognize(pixmap);
				textLabel->setText(text);
			} else {
				qCritical() << "Unable to cast to interface";
			}
			pluginLoader.unload();
		}
	}

	mainWindow.show();

	return app.exec();
}
