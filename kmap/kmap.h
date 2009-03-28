/***************************************************************************
                          kmap.h  -  description
                             -------------------
    begin                : Thu Oct 28 14:00:30 EST 1999
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
#ifndef KMAP_H
#define KMAP_H

#include <kapp.h>
#include <ktmainwindow.h>
#include <qwidget.h>
#include <qstring.h>
#include <qstrlist.h>
#include <qdir.h>
#include <qfile.h>
#include <qfileinfo.h>

class ProcessBase;
class MainView;
class OptionFrame;

class Kmap : public KTMainWindow {
	Q_OBJECT
public: 
	/** construtor */
	Kmap(QWidget*parent=0,const char* name=0);
	/** destructor */
	~Kmap();

public slots:
	void slot_Started();
	void slot_Stdout( const QString & );
	void slot_Stderr( const QString & );
	void slot_Exited();

	void slot_StartCmd();
	void slot_StopCmd();

protected:
	void init_ProcessBase();
	void init_MainView();
	void init_Session();

	void init_MenuBar();
	void init_ToolBar();
	void init_StatusBar();

	void save_Session();

	void createDirPath();
	void locateNmap();

private:
	ProcessBase *pbase;
	MainView *w_mainview;
};
#endif











