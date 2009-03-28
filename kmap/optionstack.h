/***************************************************************************
                          optionstack.h  -  description
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

#ifndef OPTIONSTACK_H
#define OPTIONSTACK_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qstring.h>
#include <qlist.h>
#include <qwidgetstack.h>
#include <qpushbutton.h>

#include "optionframe.h"

/**
  *@author Ian Zepp
  */

class Opt_Scan;
class Opt_Ping;
class Opt_Path;
class Opt_Decoy;
class Opt_HostHist;
class Opt_ArgsHist;
class Opt_Log;
class Opt_Stealth;
class Opt_Font;
class Opt_Misc;

class OptionStack : public QWidget  {
   Q_OBJECT
public: 
	OptionStack(QWidget *parent=0, const char *name=0);
	~OptionStack();

	void save();
	void load();
	void defaults();

	void init_Applets();

public slots:
	void slot_BtnDefaults();
	void slot_BtnCancel();
	void slot_BtnSave();

	void slot_Selected( OptionFrame::OptType );

protected slots:
	void paintEvent( QPaintEvent * );

private:
	QList<QWidget> l_widgets;
	QWidgetStack *w_ostack;

	int i_someid;

	Opt_Scan *o_scan;
	Opt_Ping *o_ping;
	Opt_Path *o_path;
	Opt_Decoy *o_decoy;
	Opt_HostHist *o_hosthist;
	Opt_ArgsHist *o_argshist;
	Opt_Log *o_log;
	Opt_Stealth *o_stealth;
	Opt_Font *o_font;
	Opt_Misc *o_misc;

	QPushButton *btn_defaults;
	QPushButton *btn_cancel;
	QPushButton *btn_save;

signals:
	void sig_loadhost();
	void sig_loadargs();
};

#endif













