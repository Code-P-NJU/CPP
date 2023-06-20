#pragma once
#include "config.h"
#include <QPixmap>
#include <QRect>
class Medicine
{
public:
	QPixmap img;
	int healing=10;
	QRect rect;
	Medicine(QPoint p) :rect(p.x(), p.y(), 15, 15)
	{
		img.load(MEDICINE_IMG);
	}
};