/***************************************************************************
                          kmap.cpp  -  description
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
#include "kmap.h"

#include "processbase.h"
#include "mainview.h"
#include "optionframe.h"

Kmap::Kmap(QWidget*parent,const char* name):KTMainWindow(name){
	init_MenuBar();
	init_ToolBar();
	init_StatusBar();

	init_Session();
	init_ProcessBase();
	init_MainView();

	locateNmap();
}
Kmap::~Kmap(){
	save_Session();
}

void Kmap::
init_ProcessBase()
{
	pbase = new ProcessBase();
	pbase->setVerbose(true);
	pbase->setStdout(true);
	pbase->setStderr(true);

	connect( pbase , SIGNAL(sig_started()) ,
		 this , SLOT(slot_Started()) );
	connect( pbase , SIGNAL(sig_stdout(const QString &)) ,
		 this , SLOT(slot_Stdout(const QString &)) );
	connect( pbase , SIGNAL(sig_stderr(const QString &)) ,
		 this , SLOT(slot_Stderr(const QString &)) );
	connect( pbase , SIGNAL(sig_exited()) ,
		 this , SLOT(slot_Exited()) );
}
void Kmap::
init_MainView()
{
	w_mainview = new MainView( this , "MainView" );
	w_mainview->load();

	setView( w_mainview );

	// Connect view -> this
	connect( w_mainview , SIGNAL(sig_start()) ,
		 this , SLOT(slot_StartCmd()) );
	connect( w_mainview , SIGNAL(sig_stop()) ,
		 this , SLOT(slot_StopCmd()) );

	// Connect pbase -> view
	connect( pbase , SIGNAL(sig_started()) ,
		 w_mainview , SLOT(slot_Started()) );
	connect( pbase , SIGNAL(sig_stdout(const QString &)) ,
		 w_mainview , SLOT(slot_Stdout(const QString &)) );
	connect( pbase , SIGNAL(sig_stderr(const QString &)) ,
		 w_mainview , SLOT(slot_Stderr(const QString &)) );
	connect( pbase , SIGNAL(sig_exited()) ,
		 w_mainview , SLOT(slot_Exited()) );
}
void Kmap::
init_Session()
{
	KConfig *config = kapp->getConfig();

	int i_width = config->readNumEntry( "Geometry_Width" , 400 );
	int i_height = config->readNumEntry( "Geometry_Height" , 200 );

	this->resize( i_width , i_height );
}

void Kmap::
init_MenuBar()
{
}
void Kmap::
init_ToolBar()
{
}
void Kmap::
init_StatusBar()
{
	statusBar()->message( i18n("Ready") );
}

void Kmap::
save_Session()
{
	statusBar()->message( i18n("Saving session") , 3 );

	kapp->getConfig()->writeEntry( "Geometry_Width" , width() );
	kapp->getConfig()->writeEntry( "Geometry_Height" , height() );
	kapp->getConfig()->sync();
}

void Kmap::
createDirPath()
{
}
void Kmap::
locateNmap()
{
	QFileInfo finfo;
	QString path = kapp->getConfig()->readEntry("Nmap_Executable");

	finfo.setFile( path );
	if ( finfo.isExecutable() )
	{
		cout << "Kmap: found nmap: " << path << "\n";
		return;
	}

	QStrList list;
	QString text;

	list.append( text = "/bin/nmap" );
	list.append( text = "/sbin/nmap" );
	list.append( text = "/usr/bin/nmap" );
	list.append( text = "/usr/sbin/nmap" );
	list.append( text = "/usr/local/bin/nmap" );
	list.append( text = "/usr/local/sbin/nmap" );
	list.append( text = QDir::homeDirPath() + "/bin/nmap" ); // possibly
	list.append( text = kapp->kde_bindir() + "/nmap" ); // ???
	list.append( text = "/opt/bin/nmap" ); // ???
	list.append( text = "/opt/sbin/nmap" ); // ???

	for ( uint i = 0 ; i < list.count() ; i++ )
	{
		path = list.at(i);

		finfo.setFile( path );

		if ( finfo.isExecutable() )
		{
			cout << "Kmap: found nmap: " << path << "\n";
			kapp->getConfig()->writeEntry( "Nmap_Executable" , path );
			return;
		}
		else
		{
			cout << "Kmap: nope, nmap's not here: " << path << "\n";
		}
	}

	cerr << "Kmap: unable to locate nmap, please set path manually\n";
}

void Kmap::
slot_Started()
{
	statusBar()->message( "Started nmap" );
}
void Kmap::
slot_Stdout( const QString &text )
{
	statusBar()->message( text );
}
void Kmap::
slot_Stderr( const QString &text )
{
	statusBar()->message( text );
}
void Kmap::
slot_Exited()
{
	statusBar()->message( "Exited nmap" );
}

void Kmap::
slot_StartCmd()
{
	// Retrieve command from config files.
	KConfig *config = kapp->getConfig();

	QString proc = config->readEntry( "Nmap_Executable" );
	QString args = config->readEntry( "Command_Arguments" );
	QString host = config->readEntry( "Remote_Hostname" );
	QString cmdline = proc + " " + args + " " + host;

	pbase->setCommand( cmdline.stripWhiteSpace() );
	pbase->start();

	// Save/add to recent lists
	QStrList r_host;
	QStrList r_args;

	config->readListEntry( "Recent_Host" , r_host );
	config->readListEntry( "Recent_Args" , r_args );

	if ( r_host.find( host ) == -1 )
	{
		r_host.append( host );
		config->writeEntry( "Recent_Host" , r_host );
	}

	if ( r_args.find( args ) == -1 )
	{
		r_args.append( args );
		config->writeEntry( "Recent_Args" , r_args );
	}
}
void Kmap::
slot_StopCmd()
{
	pbase->kill();
}




















