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

#include "OcrWrapper.h"

#include <QDebug>

QString OcrWrapper::recognize(const QPixmap &pixmap)
{
	qDebug() << "recognize";

	char *outText;

	auto api = new tesseract::TessBaseAPI();

	// Initialize tesseract-ocr with English, without specifying tessdata path
	if (api->Init(NULL, "eng"))
	{
		fprintf(stderr, "Could not initialize tesseract.\n");
		exit(1);
	}

	qDebug() << "tes init";

//	// Open input image with leptonica library
	Pix *imagePix = makePIXFromQImage(pixmap.toImage());
	api->SetImage(imagePix);

//	auto name = "/home/dporobic/tes-temp.png";
//	pixmap.save(name);

	// Open input image with leptonica library
//	Pix *imagePix = pixRead(name);
//	api->SetImage(imagePix);

	qDebug() << "create pix";

	// Get OCR result
	outText = api->GetUTF8Text();

	// Destroy used object and release memory
	api->End();
	pixDestroy(&imagePix);

	qDebug() << "finished";

	return QString::fromLatin1(outText);
}

PIX* OcrWrapper::makePIXFromQImage(const QImage &image)
{
	PIX * pixs;
	l_uint32 *lines;

	auto image2 = image.rgbSwapped();
	int width = image2.width();
	int height = image2.height();
	int depth = image2.depth();
	int wpl = image2.bytesPerLine() / 4;

	pixs = pixCreate(width, height, depth);
	pixSetWpl(pixs, wpl);
	pixSetColormap(pixs, NULL);
	l_uint32 *datas = pixs->data;

	for (int y = 0; y < height; y++) {
		lines = datas + y * wpl;
		QByteArray a((const char*)image2.scanLine(y), image2.bytesPerLine());
		for (int j = 0; j < a.size(); j++) {
			*((l_uint8 *)lines + j) = a[j];
		}
	}
	return pixEndianByteSwapNew(pixs);
}
