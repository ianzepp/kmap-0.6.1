/***************************************************************************
                          opt_path.h  -  description
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

#ifndef OPT_PATH_H
#define OPT_PATH_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qstring.h>

#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qmessagebox.h>

/**
  *@author Ian Zepp
  */

class Opt_Path : public QWidget  {
   Q_OBJECT
public: 
	Opt_Path(QWidget *parent=0, const char *name=0);
	~Opt_Path();

	void save();
	void load();
	void defaults();

protected slots:
	virtual void paintEvent( QPaintEvent * );

	void slot_Update();

	void slot_BtnPath();

private:
	QLabel *lbl_path;
	QLineEdit *w_path;
	QPushButton *btn_path;
};

#endif
