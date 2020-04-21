/*
 *
 * Copyright (C) 2020 Georg Zotti
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
 */


#include "VecMath.hpp"

// Here are a few variant constructors which gcc cannot inline and therefore would cause link errors if included in the VecMath.hpp.

// Obtains a Vec2i/Vec2f/Vec2d from a stringlist with the form x,y  (use C++11 type delegating constructors)
template<> Vec2i::Vector2(QStringList s) : Vector2{s.value(0, "0").toInt(),s.value(1, "0").toInt()}
{
	if (s.size()!=2)
		qWarning() << "Vec2i from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec2f::Vector2(QStringList s) : Vector2{s.value(0, "0.").toFloat(),s.value(1, "0.").toFloat()}
{
	if (s.size()!=2)
		qWarning() << "Vec2f from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec2d::Vector2(QStringList s) : Vector2{s.value(0, "0.").toDouble(),s.value(1, "0.").toDouble()}
{
	if (s.size()!=2)
		qWarning() << "Vec2d from StringList of unexpected length" << s.size() << ":" << s.join("/");
}

// Obtains a Vec2i/Vec2f/Vec2d from a string with the form "x,y"
template<class T> Vector2<T>::Vector2(QString s) : Vector2{s.split(",")}{}

template<> QString Vec2i::toStr() const
{
	return QString("%1,%2").arg(v[0]).arg(v[1]);
}
template<> QString Vec2f::toStr() const
{
	return QString("%1,%2")
			.arg(static_cast<double>(v[0]),0,'f',6)
			.arg(static_cast<double>(v[1]),0,'f',6);
}
template<> QString Vec2d::toStr() const
{
	return QString("%1,%2")
			.arg(v[0],0,'f',10)
			.arg(v[1],0,'f',10);
}



// Obtains a Vec3i/Vec3f/Vec3d from a stringlist with the form x,y,z  (use C++11 type delegating constructors)
template<> Vec3i::Vector3(QStringList s) : Vector3{s.value(0, "0").toInt(),s.value(1, "0").toInt(),s.value(2, "0").toInt()}
{
	if (s.size()!=3)
		qWarning() << "Vec3i from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec3f::Vector3(QStringList s) : Vector3{s.value(0, "0.").toFloat(),s.value(1, "0.").toFloat(),s.value(2, "0.").toFloat()}
{
	if (s.size()!=3)
		qWarning() << "Vec3f from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec3d::Vector3(QStringList s) : Vector3{s.value(0, "0.").toDouble(),s.value(1, "0.").toDouble(),s.value(2, "0.").toDouble()}
{
	if (s.size()!=3)
		qWarning() << "Vec3d from StringList of unexpected length" << s.size() << ":" << s.join("/");
}

// Obtains a Vec3i/Vec3f/Vec3d from a string with the form "x,y,z"
template<class T> Vector3<T>::Vector3(QString s) : Vector3{s.split(",")}{}

template<> Vec3i::Vector3(QColor c) : Vector3{c.red(), c.green(), c.blue()}{}
template<> Vec3f::Vector3(QColor c) : Vector3{static_cast<float>(c.redF()), static_cast<float>(c.greenF()), static_cast<float>(c.blueF())}{}
template<> Vec3d::Vector3(QColor c) : Vector3{c.redF(), c.greenF(), c.blueF()}{}

template<> Vec3i Vector3<int>::setFromHtmlColor(QString s)
{
	QRegExp re("^#([0-9a-fA-F]{2})([0-9a-fA-F]{2})([0-9a-fA-F]{2})$");
	if (re.exactMatch(s))
	{
		v[0] = re.capturedTexts().at(1).toInt(Q_NULLPTR, 16);
		v[1] = re.capturedTexts().at(2).toInt(Q_NULLPTR, 16);
		v[2] = re.capturedTexts().at(3).toInt(Q_NULLPTR, 16);
	}
	else
	{
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;
	}
	return *this;
}

template<> Vec3f Vector3<float>::setFromHtmlColor(QString s)
{
	QRegExp re("^#([0-9a-fA-F]{2})([0-9a-fA-F]{2})([0-9a-fA-F]{2})$");
	if (re.exactMatch(s))
	{
		int i = re.capturedTexts().at(1).toInt(Q_NULLPTR, 16);
		v[0] = static_cast<float>(i) / 255.f;
		i = re.capturedTexts().at(2).toInt(Q_NULLPTR, 16);
		v[1] = static_cast<float>(i) / 255.f;
		i = re.capturedTexts().at(3).toInt(Q_NULLPTR, 16);
		v[2] = static_cast<float>(i) / 255.f;
	}
	else
	{
		v[0] = 0.f;
		v[1] = 0.f;
		v[2] = 0.f;
	}
	return *this;
}

template<> Vec3d Vector3<double>::setFromHtmlColor(QString s)
{
	QRegExp re("^#([0-9a-fA-F]{2})([0-9a-fA-F]{2})([0-9a-fA-F]{2})$");
	if (re.exactMatch(s))
	{
		int i = re.capturedTexts().at(1).toInt(Q_NULLPTR, 16);
		v[0] = static_cast<double>(i) / 255.;
		i = re.capturedTexts().at(2).toInt(Q_NULLPTR, 16);
		v[1] = static_cast<double>(i) / 255.;
		i = re.capturedTexts().at(3).toInt(Q_NULLPTR, 16);
		v[2] = static_cast<double>(i) / 255.;
	}
	else
	{
		v[0] = 0.;
		v[1] = 0.;
		v[2] = 0.;
	}
	return *this;
}

template<> QString Vec3i::toStr() const
{
	return QString("%1,%2,%3").arg(v[0]).arg(v[1]).arg(v[2]);
}
template<> QString Vec3f::toStr() const
{
	return QString("%1,%2,%3")
			.arg(static_cast<double>(v[0]),0,'f',6)
			.arg(static_cast<double>(v[1]),0,'f',6)
			.arg(static_cast<double>(v[2]),0,'f',6);
}
template<> QString Vec3d::toStr() const
{
	return QString("%1,%2,%3")
			.arg(v[0],0,'f',10)
			.arg(v[1],0,'f',10)
			.arg(v[2],0,'f',10);
}

template<> QString Vec3i::toHtmlColor() const
{
	return QString("#%1%2%3")
		.arg(qMin(255, v[0]), 2, 16, QChar('0'))
		.arg(qMin(255, v[1]), 2, 16, QChar('0'))
		.arg(qMin(255, v[2]), 2, 16, QChar('0'));
}
template<> QString Vec3f::toHtmlColor() const
{
	return QString("#%1%2%3")
		.arg(qMin(255, int(v[0] * 255)), 2, 16, QChar('0'))
		.arg(qMin(255, int(v[1] * 255)), 2, 16, QChar('0'))
		.arg(qMin(255, int(v[2] * 255)), 2, 16, QChar('0'));
}
template<> QString Vec3d::toHtmlColor() const
{
	return QString("#%1%2%3")
		.arg(qMin(255, int(v[0] * 255)), 2, 16, QChar('0'))
		.arg(qMin(255, int(v[1] * 255)), 2, 16, QChar('0'))
		.arg(qMin(255, int(v[2] * 255)), 2, 16, QChar('0'));
}

template<> QColor Vec3i::toQColor() const
{
	return QColor(v[0], v[1], v[2]);
}

template<> QColor Vec3f::toQColor() const
{
	return QColor::fromRgbF(static_cast<qreal>(v[0]), static_cast<qreal>(v[1]), static_cast<qreal>(v[2]));
}

template<> QColor Vec3d::toQColor() const
{
	return QColor::fromRgbF(v[0], v[1], v[2]);
}


// Obtains a Vec4i/Vec4f/Vec4d from a stringlist with the form x,y,z,w  (use C++11 type delegating constructors)
template<> Vec4i::Vector4(QStringList s) : Vector4{s.value(0, "0").toInt(),s.value(1, "0").toInt(),s.value(2, "0").toInt(),s.value(3, "0").toInt()}
{
	if (s.size()!=4)
		qWarning() << "Vec4i from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec4f::Vector4(QStringList s) : Vector4{s.value(0, "0.").toFloat(),s.value(1, "0.").toFloat(),s.value(2, "0.").toFloat(),s.value(3, "0.").toFloat()}
{
	if (s.size()!=4)
		qWarning() << "Vec4f from StringList of unexpected length" << s.size() << ":" << s.join("/");
}
template<> Vec4d::Vector4(QStringList s) : Vector4{s.value(0, "0.").toDouble(),s.value(1, "0.").toDouble(),s.value(2, "0.").toDouble(),s.value(3, "0.").toDouble()}
{
	if (s.size()!=4)
		qWarning() << "Vec4d from StringList of unexpected length" << s.size() << ":" << s.join("/");
}

// Obtains a Vec4i/Vec4f/Vec4d from a string with the form "x,y,z,w"
template<class T> Vector4<T>::Vector4(QString s) : Vector4{s.split(",")}{}

template<> Vec4i::Vector4(QColor c) : Vector4{c.red(), c.green(), c.blue(), c.alpha()}{}
template<> Vec4f::Vector4(QColor c) : Vector4{static_cast<float>(c.redF()), static_cast<float>(c.greenF()), static_cast<float>(c.blueF()), static_cast<float>(c.alphaF())}{}
template<> Vec4d::Vector4(QColor c) : Vector4{c.redF(), c.greenF(), c.blueF(), c.alphaF()}{}

template<> QString Vec4i::toStr() const
{
	return QString("%1,%2,%3,%4").arg(v[0]).arg(v[1]).arg(v[2]).arg(v[3]);
}
template<> QString Vec4f::toStr() const
{
	return QString("%1,%2,%3,%4")
			.arg(static_cast<double>(v[0]),0,'f',6)
			.arg(static_cast<double>(v[1]),0,'f',6)
			.arg(static_cast<double>(v[2]),0,'f',6)
			.arg(static_cast<double>(v[3]),0,'f',6);
}
template<> QString Vec4d::toStr() const
{
	return QString("%1,%2,%3,%4")
			.arg(v[0],0,'f',10)
			.arg(v[1],0,'f',10)
			.arg(v[2],0,'f',10)
			.arg(v[3],0,'f',10);
}

template<> QColor Vec4i::toQColor() const
{
	return QColor(v[0], v[1], v[2], v[3]);
}

template<> QColor Vec4f::toQColor() const
{
	return QColor::fromRgbF(static_cast<qreal>(v[0]), static_cast<qreal>(v[1]), static_cast<qreal>(v[2]), static_cast<qreal>(v[3]));
}

template<> QColor Vec4d::toQColor() const
{
	return QColor::fromRgbF(v[0], v[1], v[2], v[3]);
}
