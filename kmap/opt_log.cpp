/***************************************************************************
                          opt_log.cpp  -  description
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

#include "opt_log.h"

Opt_Log::Opt_Log(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_hlog = new QCheckBox( i18n("Log in human format") , this , "CbHlog" );
	w_mlog = new QCheckBox( i18n("Log in machine format") , this , "CbMlog" );

	w_hlogpath = new QLineEdit( this , "LeHlog" );
	w_mlogpath = new QLineEdit( this , "LeMlog" );

	connect( w_hlog , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );
	connect( w_mlog , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );

	defaults();
	load();
	slot_Update();
}
Opt_Log::~Opt_Log(){
}

QString & Opt_Log::
arguments()
{
	s_args = "";

	QString hpath = w_hlogpath->text();
	QString mpath = w_mlogpath->text();

	if (( w_hlog->isChecked() ) && ( !hpath.isEmpty() ))
	{
		s_args += "-o ";
		s_args += hpath.stripWhiteSpace();
		s_args += " ";
	}

	if (( w_mlog->isChecked() ) && ( !mpath.isEmpty() ))
	{
		s_args += "-m ";
		s_args += mpath.stripWhiteSpace();
		s_args += " ";
	}

	cout << "Opt_Log: current arguments: " << s_args << "\n";

	return s_args;
}

void Opt_Log::
load()
{
	QString text = kapp->getConfig()->readEntry( "Command_Arguments" );
	QString parm = "";
	QTextStream is( text , IO_ReadOnly );

	while ( !is.eof() )
	{
		is >> parm;

		check_parms:
		if ( parm == "-o" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			w_hlog->setChecked(true);
			w_hlogpath->setText( parm );
		}

		if ( parm == "-m" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			w_mlog->setChecked(true);
			w_mlogpath->setText( parm );
		}
	}

	slot_Update();
}
void Opt_Log::
save()
{
	// Save path to config even if not used.
	KConfig *config = kapp->getConfig();

	config->writeEntry( "Path_Log_Human" , w_hlogpath->text() );
	config->writeEntry( "Path_Log_Machine" , w_mlogpath->text() );
}
void Opt_Log::
defaults()
{
	// Clear paths
	w_hlogpath->clear();
	w_mlogpath->clear();
	
	w_hlog->setChecked(false);
	w_mlog->setChecked(false);

	slot_Update();
}

void Opt_Log::
slot_Update()
{
	w_hlogpath->setEnabled( w_hlog->isChecked() );
	w_mlogpath->setEnabled( w_mlog->isChecked() );
}

void Opt_Log::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	w_hlog->setGeometry( 5 , 5 , 150 , 25 );
	w_mlog->setGeometry( 5 , 35 , 150 , 25 );

	w_hlogpath->setGeometry( 155 , 5 , width() - 160 , 25 );
	w_mlogpath->setGeometry( 155 , 35 , width() - 160 , 25 );
}


