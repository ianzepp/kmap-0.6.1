/***************************************************************************
                          scanview.h  -  description
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

#ifndef SCANVIEW_H
#define SCANVIEW_H

#include <iostream.h>

#include <kapp.h> // for i18n

#include <qwidget.h>
#include <qevent.h>
#include <qlistview.h>
#include <qregexp.h> // for the stdout/stderr stuff
#include <qtextstream.h>

/**
  *@author Ian Zepp
  */

class ScanView : public QWidget  {
   Q_OBJECT
public: 
	ScanView(QWidget *parent=0, const char *name=0);
	~ScanView();

	void clear();
	void save();
	void load();

public slots:
	void slot_Started();
	void slot_Stdout( const QString & );
	void slot_Stderr( const QString & );
	void slot_Exited();

protected slots:
	void paintEvent( QPaintEvent * );

protected:
	void handle_IpAddress( const QString & );
	void handle_PingState( const QString & , bool );
	void handle_PortEntry( const QString & );

private:
	QListView *w_lv;
	QString s_ipaddr;

	bool b_inlist;
	bool b_pingscan;
};

#endif










