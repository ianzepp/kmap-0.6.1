/***************************************************************************
                          mainview.h  -  description
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

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <kapp.h>
#include <ktabctl.h>

#include <qwidget.h>
#include <qevent.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>

#include "scanview.h"
#include "treeview.h"
#include "nmapview.h"
#include "optionframe.h"

/**
  *@author Ian Zepp
  */

class MainView : public QWidget  {
   Q_OBJECT
public: 
	MainView(QWidget *parent=0, const char *name=0);
	~MainView();

	void save();
	void load();

public slots:
	void slot_Started();
	void slot_Stdout( const QString & );
	void slot_Stderr( const QString & );
	void slot_Exited();

protected slots:
	void paintEvent( QPaintEvent * );

	void slot_ExecClicked();
	void slot_LoadHost();
	void slot_LoadArgs();

private:
	KTabCtl *w_ktab;

	QLabel *lbl_host;
	QLabel *lbl_args;

	QLineEdit *w_host;
	QLineEdit *w_args;

	QPushButton *btn_exec;
	QPushButton *btn_setup;

	ScanView *w_scanview;		
	TreeView *w_treeview;		
	NmapView *w_nmapview;		
	OptionFrame *w_optframe;

	bool b_running;

signals:
	void sig_start();
	void sig_stop();
};

#endif









