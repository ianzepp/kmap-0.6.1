/***************************************************************************
                          optiontree.h  -  description
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

#ifndef OPTIONTREE_H
#define OPTIONTREE_H

#include <iostream.h>

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>
#include <qlistview.h>

#include "optionframe.h"

/**
  *@author Ian Zepp
  */

class OptionTree : public QWidget  {
   Q_OBJECT
public: 
	OptionTree(QWidget *parent=0, const char *name=0);
	~OptionTree();

	void save();
	void load();
	void defaults();

	void init_Applets();

protected slots:
	virtual void paintEvent( QPaintEvent * );
	void slot_Selected( QListViewItem * );

private:
	QListView *w_tree;

signals:
	void sig_selected( OptionFrame::OptType );
};

#endif















