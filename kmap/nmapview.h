/***************************************************************************
                          nmapview.h  -  description
                             -------------------
    begin                : Thu Oct 28 1999
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

#ifndef NMAPVIEW_H
#define NMAPVIEW_H

#include <kapp.h>

#include <qstring.h>
#include <qmultilinedit.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qpushbutton.h>

#include <qfile.h>
#include <qfiledialog.h>
#include <qmessagebox.h>

/**
  *@author Ian Zepp
  */

class NmapView : public QWidget  {
   Q_OBJECT
public: 
	NmapView(QWidget *parent=0, const char *name=0);
	~NmapView();

	void clear();
	void save();
	void load();
	void append( const QString & );

public slots:
	void slot_Started();
	void slot_Stdout( const QString & );
	void slot_Stderr( const QString & );
	void slot_Exited();

protected slots:
	void slot_LogFile();
	void slot_BtnBrowse();
	void slot_BtnSave();

	void paintEvent( QPaintEvent * );

private:
	QMultiLineEdit *w_view;

	QCheckBox *w_savelog;
	QLineEdit *w_logfile;
	QPushButton *btn_browse;
	QPushButton *btn_save;
};

#endif







