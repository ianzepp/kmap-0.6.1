/***************************************************************************
                          opt_misc.h  -  description
                             -------------------
    begin                : Wed Nov 3 1999
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

#ifndef OPT_MISC_H
#define OPT_MISC_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qstring.h>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qtextstream.h>

/**
  *@author Ian Zepp
  */

class Opt_Misc : public QWidget  {
   Q_OBJECT
public: 
	Opt_Misc(QWidget *parent=0, const char *name=0);
	~Opt_Misc();

	QString & arguments();
	void save(); // does nothing
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();

private:
	QCheckBox *w_ident;
	QCheckBox *w_fast;
	QCheckBox *w_port;
	QCheckBox *w_frag;

	QCheckBox *w_verbose;
	QCheckBox *w_debug;

	QComboBox *w_verbose_lvl;
	QComboBox *w_debug_lvl;

	QLineEdit *w_porttext;

	QString s_args;
};

#endif
