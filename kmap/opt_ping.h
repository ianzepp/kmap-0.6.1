/***************************************************************************
                          opt_ping.h  -  description
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

#ifndef OPT_PING_H
#define OPT_PING_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qdialog.h>
#include <qlabel.h>
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

class Opt_Ping : public QWidget  {
   Q_OBJECT
public: 
	Opt_Ping(QWidget *parent=0, const char *name=0);
	~Opt_Ping();

	QString & arguments();

	void save(); // does nothing
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();
	void slot_BtnUsePort();

protected:
	QLabel *lbl_ping;

	QComboBox *w_ping;
	QCheckBox *w_useport;
	QCheckBox *w_usesyn;

	QLineEdit *w_useporttext;

	QString s_args;

private:
};

#endif





