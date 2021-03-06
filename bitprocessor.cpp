/*
 * bitprocessor.cpp - bit processing widget for decoding bits
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

#include "bitprocessor.h"
#include "bitconvert.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

BitProcessor::BitProcessor(QWidget* parent)
	: QWidget(parent)
{
	instructions = new QLabel;
	example_bits = new QLabel;
	links = new QMessageBox;
	more_info = new QPushButton(tr("&More Information"));
	license_info = new QMessageBox;
	licensing = new QPushButton(tr("&Licensing"));
	input = new QTextEdit;
	inspect = new QPushButton(tr("&Inspect"));
	status = new QLabel;
	label_input = new QLabel;
	label_t1 = new QLabel;
	label_t2 = new QLabel;
	label_t3 = new QLabel;
	out_t1 = new QLabel;
	out_t2 = new QLabel;
	out_t3 = new QLabel;
	fields = new QTableWidget;
	show_input = new QPushButton(tr("S&how Input"));
	hide_input = new QPushButton(tr("&Hide Input"));
	another = new QPushButton(tr("Inspect &Another"));

	// configure the instructions label
	instructions->setText(tr("If you have a Bit Reader USB or compatible "
		"device connected to this computer, swipe a card and click "
		"\"Inspect\".  You can also paste a raw bitstream (1s and 0s) "
		"into the textbox.  If you don't have a bitstream, you can "
		"copy and paste this one into the textbox:"));
	instructions->setWordWrap(true);

	// configure the label showing an example bitstream
	example_bits->setText(tr(
		"00000001010001001011010100101100111001011011111000000000\n"
		"000001101010000010001100100100101011111100000"));
	// the following line is from
	//  http://www.virtualbox.org/browser/trunk/src/VBox/Frontends/VirtualBox/src/QILabel.cpp?rev=16304&format=html#L304
	// make the text in example_bits label selectable
	example_bits->setTextInteractionFlags(Qt::TextBrowserInteraction);

	// configure the message box with links to bitstreams and contact info
	links->setWindowTitle(tr("Bit Inspector - More Information"));
	links->setText(tr("Additional example bitstreams are available at:<br>"
		"<a href=\"http://github.com/ossguy/libbitconvert/tree/master/test_data\">http://github.com/ossguy/libbitconvert/tree/master/test_data</a><br><br>"
		"The textbox is expected to contain up to 3 lines.  Lines 1 "
		"and 3 are assumed to use the ALPHA encoding while line 2 is "
		"assumed to use the BCD encoding.  Lines should begin with the "
		"start sentinel, should end with the end sentinel, and can be "
		"preceded and succeeded by an arbitrary number of 0s.  For "
		"details on these encodings so you can construct your own "
		"bitstreams, see the charts at:<br>"
		"<a href=\"http://www.cyberd.co.uk/support/technotes/isocards.htm\">http://www.cyberd.co.uk/support/technotes/isocards.htm</a><br><br>"
		"Please report any problems with Bit Inspector or suggestions "
		"for improvement to Denver Gingerich "
		"&lt;<a href=\"mailto:denver@ossguy.com\">denver@ossguy.com</a>&gt;."
		"<br><br>"
		"Bit Inspector home page: <a href=\"http://github.com/ossguy/bitinspector\">http://github.com/ossguy/bitinspector</a>"
		));

	// configure the message box with licensing information
	license_info->setWindowTitle(tr("Bit Inspector - Licensing"));
	license_info->setText(tr(
		"Bit Inspector is Copyright &copy; 2009  Denver Gingerich "
		"&lt;<a href=\"mailto:denver@ossguy.com\">denver@ossguy.com</a>&gt;<br><br>"
		"Qt, used in Bit Inspector, is Copyright &copy; 2009  Nokia "
		"Corporation and/or its subsidiary(-ies).  Contact: Qt "
		"Software Information "
		"&lt;<a href=\"mailto:qt-info@nokia.com\">qt-info@nokia.com</a>&gt;<br><br>"
		"This program is free software: you can redistribute it and/or "
		"modify it under the terms of the GNU General Public License "
		"version 3.<br><br>"
		"This program is distributed in the hope that it will be "
		"useful, but WITHOUT ANY WARRANTY; without even the implied "
		"warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR "
		"PURPOSE.  See the GNU General Public License for more "
		"details.<br><br>"
		"A copy of the GNU General Public License can be found in "
		"COPYING.txt, which is distributed with this program."
		"<br><br><br>"
		"A list of licenses and copyright information for other "
		"projects used in Bit Inspector is available in licenses.html, "
		"which is distributed with this program."
		));

	// set name for status label; allows us to set stylesheet
	status->setObjectName("status");

	// configure the input and track labels
	label_input->setText(tr("Input: "));
	label_t1->setText(tr("Track 1: "));
	label_t2->setText(tr("Track 2: "));
	label_t3->setText(tr("Track 3: "));
	out_t1->setTextInteractionFlags(Qt::TextBrowserInteraction);
	out_t2->setTextInteractionFlags(Qt::TextBrowserInteraction);
	out_t3->setTextInteractionFlags(Qt::TextBrowserInteraction);

	// configure the fields table
	fields->setRowCount(0);
	fields->setColumnCount(3);
	fields->setHorizontalHeaderLabels(QStringList()
		<< QString(tr("Field name")) << QString(tr("Track"))
		<< QString(tr("Value on card")));

	// arrange input and output widgets in layout
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(instructions);
	layout->addWidget(example_bits);
	QHBoxLayout* info = new QHBoxLayout;
	info->addWidget(more_info);
	info->addWidget(licensing);
	layout->addLayout(info);
	layout->addWidget(status);

	QGridLayout* grid = new QGridLayout;
	grid->addWidget(label_input, 0, 0, Qt::AlignTop);
	grid->addWidget(label_t1, 1, 0);
	grid->addWidget(label_t2, 2, 0);
	grid->addWidget(label_t3, 3, 0);
	grid->addWidget(input, 0, 1);
	grid->addWidget(out_t1, 1, 1);
	grid->addWidget(out_t2, 2, 1);
	grid->addWidget(out_t3, 3, 1);
	grid->setColumnStretch(1, 1); // force track output to fill width
	layout->addLayout(grid);

	layout->addWidget(inspect); // at the bottom in input mode
	layout->addWidget(fields);

	QHBoxLayout* out_buttons = new QHBoxLayout;
	out_buttons->addWidget(show_input);
	out_buttons->addWidget(hide_input);
	out_buttons->addWidget(another);
	layout->addLayout(out_buttons);

	setLayout(layout);

	// hide widgets for output mode
	status->hide();
	label_input->hide();
	label_t1->hide();
	label_t2->hide();
	label_t3->hide();
	out_t1->hide();
	out_t2->hide();
	out_t3->hide();
	fields->hide();
	show_input->hide();
	hide_input->hide();
	another->hide();


	setWindowTitle(tr("Bit Inspector 1.0 Beta 1a"));

	// put focus on the input textbox at startup
	input->setFocus();

	// on "Inspect", decode the bits in the input box
	connect(inspect, SIGNAL(released()), this, SLOT(decodeBits()));

	// on "Inspect", hide input widgets and show output widgets
	connect(inspect, SIGNAL(released()), instructions, SLOT(hide()));
	connect(inspect, SIGNAL(released()), example_bits, SLOT(hide()));
	connect(inspect, SIGNAL(released()), more_info, SLOT(hide()));
	connect(inspect, SIGNAL(released()), licensing, SLOT(hide()));
	connect(inspect, SIGNAL(released()), input, SLOT(hide()));
	connect(inspect, SIGNAL(released()), inspect, SLOT(hide()));
	connect(inspect, SIGNAL(released()), status, SLOT(show()));
	connect(inspect, SIGNAL(released()), label_t1, SLOT(show()));
	connect(inspect, SIGNAL(released()), label_t2, SLOT(show()));
	connect(inspect, SIGNAL(released()), label_t3, SLOT(show()));
	connect(inspect, SIGNAL(released()), out_t1, SLOT(show()));
	connect(inspect, SIGNAL(released()), out_t2, SLOT(show()));
	connect(inspect, SIGNAL(released()), out_t3, SLOT(show()));
	connect(inspect, SIGNAL(released()), fields, SLOT(show()));
	connect(inspect, SIGNAL(released()), show_input, SLOT(show()));
	connect(inspect, SIGNAL(released()), another, SLOT(show()));

	// on "Inspect Another", show input widgets and hide output widgets
	connect(another, SIGNAL(released()), instructions, SLOT(show()));
	connect(another, SIGNAL(released()), example_bits, SLOT(show()));
	connect(another, SIGNAL(released()), more_info, SLOT(show()));
	connect(another, SIGNAL(released()), licensing, SLOT(show()));
	connect(another, SIGNAL(released()), input, SLOT(show()));
	connect(another, SIGNAL(released()), inspect, SLOT(show()));
	connect(another, SIGNAL(released()), status, SLOT(hide()));
	connect(another, SIGNAL(released()), label_input, SLOT(hide()));
	connect(another, SIGNAL(released()), label_t1, SLOT(hide()));
	connect(another, SIGNAL(released()), label_t2, SLOT(hide()));
	connect(another, SIGNAL(released()), label_t3, SLOT(hide()));
	connect(another, SIGNAL(released()), out_t1, SLOT(hide()));
	connect(another, SIGNAL(released()), out_t2, SLOT(hide()));
	connect(another, SIGNAL(released()), out_t3, SLOT(hide()));
	connect(another, SIGNAL(released()), fields, SLOT(hide()));
	connect(another, SIGNAL(released()), show_input, SLOT(hide()));
	connect(another, SIGNAL(released()), hide_input, SLOT(hide()));
	connect(another, SIGNAL(released()), another, SLOT(hide()));

	// on "Inspect Another", put focus on input textbox and select the text
	connect(another, SIGNAL(released()), input, SLOT(setFocus()));
	connect(another, SIGNAL(released()), input, SLOT(selectAll()));

	// on "Show Input", show the input textbox and replace with "Hide Input"
	connect(show_input, SIGNAL(released()), label_input, SLOT(show()));
	connect(show_input, SIGNAL(released()), input, SLOT(show()));
	connect(show_input, SIGNAL(released()), show_input, SLOT(hide()));
	connect(show_input, SIGNAL(released()), hide_input, SLOT(show()));

	// on "Hide Input", hide the input textbox and replace with "Show Input"
	connect(hide_input, SIGNAL(released()), label_input, SLOT(hide()));
	connect(hide_input, SIGNAL(released()), input, SLOT(hide()));
	connect(hide_input, SIGNAL(released()), hide_input, SLOT(hide()));
	connect(hide_input, SIGNAL(released()), show_input, SLOT(show()));

	// on "More Information", show links message box
	connect(more_info, SIGNAL(released()), links, SLOT(exec()));

	// on "Licensing", show license information message box
	connect(licensing, SIGNAL(released()), license_info, SLOT(exec()));
}

void BitProcessor::decodeBits()
{
	struct bc_input in;
	struct bc_decoded result;

	QStringList tracks = input->toPlainText().split('\n');

	if (tracks.isEmpty()) {
		in.t1 = NULL;
	} else {
		std::string t1 = tracks.takeFirst().toStdString();
		in.t1 = (char*)malloc(t1.length() + 1);
		strcpy(in.t1, t1.c_str());
	}

	if (tracks.isEmpty()) {
		in.t2 = NULL;
	} else {
		std::string t2 = tracks.takeFirst().toStdString();
		in.t2 = (char*)malloc(t2.length() + 1);
		strcpy(in.t2, t2.c_str());
	}

	if (tracks.isEmpty()) {
		in.t3 = NULL;
	} else {
		std::string t3 = tracks.takeFirst().toStdString();
		in.t3 = (char*)malloc(t3.length() + 1);
		strcpy(in.t3, t3.c_str());
	}

	int rv = bc_decode(&in, &result);

	// check if output for all tracks is empty
	bool output_empty = true;

	// populate the fields; result fields will be sane even if rv is error
	if (NULL == result.t1) {
		out_t1->clear();
	} else {
		out_t1->setText(QString(result.t1));
		output_empty = false;
	}
	if (NULL == result.t2) {
		out_t2->clear();
	} else {
		out_t2->setText(QString(result.t2));
		output_empty = false;
	}
	if (NULL == result.t3) {
		out_t3->clear();
	} else {
		out_t3->setText(QString(result.t3));
		output_empty = false;
	}

	// clear the fields table
	while (fields->rowCount() > 0) {
		fields->removeRow(0);
	}

	if (rv) {
		// NOTE: style sheets are not supported on Mac OS X; see
		//  http://doc.trolltech.com/4.5/qwidget.html#styleSheet-prop
		setStyleSheet("QLabel#status { color: red }");

		if (BCERR_PARITY_MISMATCH == rv) {
			status->setText(tr("Decode error: input must be ALPHA "
				"or BCD - see \"More Information\" for "
				"details; partial results shown"));
		} else {
			status->setText(tr("Decode error: ") +
				QString(bc_strerror(rv)));
		}
	} else if (output_empty) {
		// NOTE: style sheets are not supported on Mac OS X; see
		//  http://doc.trolltech.com/4.5/qwidget.html#styleSheet-prop
		setStyleSheet("");

		status->setText(tr("Nothing to decode - click \"Inspect "
			"Another\", enter a bitstream into the textbox, and "
			"click \"Inspect\""));
	} else {
		rv = bc_find_fields(&result);
		if (rv) {
			QString prefix;

			// NOTE: style sheets are not supported on Mac OS X; see
			//  http://doc.trolltech.com/4.5/qwidget.html#styleSheet-prop
			if (BCERR_NO_MATCHING_FORMAT == rv) {
				setStyleSheet("");
				prefix = tr("Unknown card: ");
			} else {
				setStyleSheet("QLabel#status { color: red }");
				prefix = tr("Find fields error: ");
				if (rv & BCERR_MASK_FORMAT &&
					BCERR_NO_FORMAT_FILE != rv) {

					prefix += tr("problem in formats "
						"file: ");
				}
			}

			status->setText(prefix + QString(bc_strerror(rv)));
		} else {
			// NOTE: style sheets are not supported on Mac OS X; see
			//  http://doc.trolltech.com/4.5/qwidget.html#styleSheet-prop
			setStyleSheet("");

			// put the card name in the status bar
			status->setText(tr("Card name: ") +
				QString(result.name));

			int i;

			// add new card data to the table
			for (i = 0; result.field_names[i] != NULL; i++) {
				fields->insertRow(i);
				fields->setItem(i, 0,
					new QTableWidgetItem(
					QString(result.field_names[i])) );

				/* NOTE: you should verify that the BC_TRACK_*
				 * constants in the version of libbitconvert
				 * that you are using map cleanly onto integers
				 * if you wish to print the tracks using the
				 * method below; the library may change to
				 * allow tracks such as BC_TRACK_JIS_II, which
				 * would not print correctly using this method
				 */
				fields->setItem(i, 1,
					new QTableWidgetItem(
					QString::number(result.field_tracks[i]))
					);

				fields->setItem(i, 2,
					new QTableWidgetItem(
					QString(result.field_values[i])) );
			}
			fields->resizeColumnsToContents();
		}
	}

	free(in.t1);
	free(in.t2);
	free(in.t3);

	bc_decoded_free(&result);
}
