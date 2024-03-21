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

OcrWrapper::OcrWrapper() :
	mTessApi(QSharedPointer<TessBaseAPI>(new TessBaseAPI()))
{
}

OcrWrapper::~OcrWrapper()
{
	mTessApi->End();
}

QString OcrWrapper::recognize(const QPixmap &pixmap) const
{
	return recognizeInner(pixmap, nullptr);
}

QString OcrWrapper::recognize(const QPixmap &pixmap, const QString &dataPath) const
{
	return recognizeInner(pixmap, dataPath.toLocal8Bit().data());
}

QString OcrWrapper::recognizeInner(const QPixmap &pixmap, char * dataPath) const
{
	if (mTessApi->Init(dataPath, "por") == 0)
	{
		auto pix = makePixFromPixmap(pixmap);
		mTessApi->SetImage(pix);

		auto recognizedText = QSharedPointer<char>(mTessApi->GetUTF8Text());

		pixDestroy(&pix);

        return QString::fromUtf8(recognizedText.data());

        } else {
		qCritical("Failed to initialize Tesseract");
		return {};
	}
}

PIX* OcrWrapper::makePixFromPixmap(const QPixmap &pixmap)
{
	QByteArray byteArray;
	QBuffer buffer(&byteArray);
	buffer.open(QIODevice::WriteOnly);
	pixmap.save(&buffer, "BMP");

	return pixReadMemBmp((l_uint8 *)byteArray.constData(), byteArray.size());
}
