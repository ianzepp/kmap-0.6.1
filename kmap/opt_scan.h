/***************************************************************************
                          opt_scan.h  -  description
                             -------------------
    begin                : Fri Oct 29 1999
    copyright            : (C) 1999 by Ian Zepp
    email                : icszepp@islc.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef OPT_SCAN_H
#define OPT_SCAN_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qmultilinedit.h>
#include <qpushbutton.h>
#include <qstring.h>
#include <qtextstream.h>

/**
  *@author Ian Zepp
  */

class Opt_Scan : public QWidget  {
   Q_OBJECT
public: 
	Opt_Scan(QWidget *parent=0, const char *name=0);
	~Opt_Scan();

	QString & arguments();
	void save(); // does nothing
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();

protected:
	void toggle_Normal( int );
	void toggle_Root( int );
	void toggle_Bounce();

private:
	QButtonGroup *grp_buttons;

	QRadioButton *btn_normal;
	QRadioButton *btn_root;
	QRadioButton *btn_bounce;

	QComboBox *w_normal;
	QComboBox *w_root;
	QLineEdit *w_bounce;

	QCheckBox *w_osid;

	QString s_args;
};

#endif







