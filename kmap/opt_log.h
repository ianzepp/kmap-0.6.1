/***************************************************************************
                          opt_log.h  -  description
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

#ifndef OPT_LOG_H
#define OPT_LOG_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qstring.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qtextstream.h>

/**
  *@author Ian Zepp
  */

class Opt_Log : public QWidget  {
   Q_OBJECT
public: 
	Opt_Log(QWidget *parent=0, const char *name=0);
	~Opt_Log();

	QString & arguments();
	void save(); // does nothing
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();

private:
	QCheckBox *w_hlog;
	QCheckBox *w_mlog;

	QLineEdit *w_hlogpath;
	QLineEdit *w_mlogpath;

	QString s_args;
};

#endif
