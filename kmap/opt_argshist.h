/***************************************************************************
                          opt_argshist.h  -  description
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

#ifndef OPT_ARGSHIST_H
#define OPT_ARGSHIST_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qstring.h>
#include <qstrlist.h>
#include <qlistbox.h>
#include <qlabel.h>
#include <qpushbutton.h>

/**
  *@author Ian Zepp
  */

class Opt_ArgsHist : public QWidget  {
   Q_OBJECT
public: 
	Opt_ArgsHist(QWidget *parent=0, const char *name=0);
	~Opt_ArgsHist();

	enum { ModeUndef , ModeUse , ModeRem };

	void save();
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();

	void slot_BtnPositive();
	void slot_BtnNegative();
	void slot_ListHighlighted( int );
	void slot_ListSelected( int );

private:
	QLabel *w_label;
	QListBox *w_list;

	QPushButton *btn_positive;
	QPushButton *btn_negative;

	int i_modepos;
	int i_modeneg;

signals:
	void sig_loadargs();
};

#endif
