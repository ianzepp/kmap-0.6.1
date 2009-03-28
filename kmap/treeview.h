/***************************************************************************
                          treeview.h  -  description
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

#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <kapp.h>
//#include <ktreelist.h>

#include <qwidget.h>
#include <qstring.h>
#include <qevent.h>
#include <qregexp.h>
#include <qtextstream.h>
#include <qpixmap.h>
#include <qlistview.h>

/**
  *@author Ian Zepp
  */

class TreeView : public QWidget  {
   Q_OBJECT
public: 
	TreeView(QWidget *parent=0, const char *name=0);
	~TreeView();

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
	void handle_PortEntry( const QString & );
	void handle_PrintEntry( const QString & );
	void handle_IpAddress( const QString & );

	void handle_Class( const QString & );
	void handle_Difficulty( const QString & );
	void handle_Sequence( const QString & );
	void handle_RemoteOS( const QString & );
	void handle_UnknownOS( const QString & );

private:
	QListView *w_tree;

	int i_cnt;
	bool b_inlist;
	bool b_inprint;

	QPixmap *pix;
	QListViewItem *p_currentip;

	QString s_ipaddr;
	QString s_ports_tcp;
	QString s_ports_udp;
	QString s_ports_misc;

	QString s_problem;
	QString s_solution;
};

#endif









