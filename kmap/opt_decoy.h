/***************************************************************************
                          opt_decoy.h  -  description
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

#ifndef OPT_DECOY_H
#define OPT_DECOY_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qstring.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlineedit.h>

/**
  *@author Ian Zepp
  */

class Opt_Decoy : public QWidget  {
   Q_OBJECT
public: 
	Opt_Decoy(QWidget *parent=0, const char *name=0);
	~Opt_Decoy();

	enum { ModeUndef , ModeAdd , ModeRem };

	QString & arguments();

	void save();
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();

	void slot_BtnPositive();
	void slot_BtnNegative();
	void slot_EditChanged( const char * );
	void slot_ListHighlighted( int );

private:
	QLineEdit *w_edit;
	QListBox *w_list;

	QPushButton *btn_positive;
	QPushButton *btn_negative;

	int i_modepos;
	int i_modeneg;

	QString s_args;

signals:
	void sig_loadhost();
};

#endif
