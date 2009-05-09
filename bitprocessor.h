/*
 * bitprocessor.h - bit processing widget declarations
 * This file is part of Bit Inspector.
 *
 * Copyright (C) 2009  Denver Gingerich <denver@ossguy.com>
 *
 * The contents of this file can be redistributed and/or modified under the
 * terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see http://www.gnu.org/licenses/.
 *
 */

#ifndef H_BITPROCESSOR
#define H_BITPROCESSOR

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class BitProcessor : public QWidget
{
	Q_OBJECT

public:
	BitProcessor(QWidget* parent = 0);

public slots:
	void decodeBits();

private:
	QTextEdit* input;
	QPushButton* inspect;
	QLineEdit* out_t1;
	QLineEdit* out_t2;
	QLineEdit* out_t3;
	QPushButton* show_input;
	QPushButton* hide_input;
	QPushButton* another;
};

#endif // H_BITPROCESSOR
