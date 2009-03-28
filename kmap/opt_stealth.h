/***************************************************************************
                          opt_stealth.h  -  description
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

#ifndef OPT_STEALTH_H
#define OPT_STEALTH_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qstring.h>
#include <qradiobutton.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qtextstream.h>
#include <qbuttongroup.h>

/**
  *@author Ian Zepp
  */

class Opt_Stealth : public QWidget  {
   Q_OBJECT
public: 
	Opt_Stealth(QWidget *parent=0, const char *name=0);
	~Opt_Stealth();

	QString & arguments();
	void save(); // does nothing
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();

	void slot_Host();
	void slot_MaxRtt();
	void slot_InitRtt();
	void slot_Parallel();
	void slot_Delay();

private:
	QCheckBox *btn_nmapdef;
	QCheckBox *btn_userdef;

	QComboBox *w_canned;

	QCheckBox *w_host;
	QCheckBox *w_max_rtt;
	QCheckBox *w_init_rtt;
	QCheckBox *w_parallel;
	QCheckBox *w_delay;

	QLineEdit *w_host_text;
	QLineEdit *w_max_rtt_text;
	QLineEdit *w_init_rtt_text;
	QLineEdit *w_parallel_text;
	QLineEdit *w_delay_text;

	QString s_args;
};

#endif
