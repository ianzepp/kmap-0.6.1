/***************************************************************************
                          opt_misc.cpp  -  description
                             -------------------
    begin                : Wed Nov 3 1999
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

#include "opt_misc.h"

Opt_Misc::Opt_Misc(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_ident = new QCheckBox( i18n("Use TCP reverse ident scanning") , this , "CbIdent" );
	w_fast = new QCheckBox( i18n("Use fast scanning method (services only)") , this , "CbFast" );
	w_port = new QCheckBox( i18n("Specify a port range:") , this , "CbPort" );
	w_frag = new QCheckBox( i18n("Fragment SYN/FIN/XMAS/NULL headers") , this , "CbFrag" );

	w_verbose = new QCheckBox( i18n("Enable verbosity") , this , "CbVerbose" );
	w_debug = new QCheckBox( i18n("Enable debug") , this , "CbVerbose" );

	w_verbose_lvl = new QComboBox( this , "BoxVerbose" );
	w_verbose_lvl->insertItem( i18n("Level 1 verbose") );
	w_verbose_lvl->insertItem( i18n("Level 2 verbose") );
	w_verbose_lvl->insertItem( i18n("Level 3 verbose") );
	w_verbose_lvl->insertItem( i18n("Level 4 verbose") );

	w_debug_lvl = new QComboBox( this , "BoxDebug" );
	w_debug_lvl->insertItem( i18n("Level 1 debug") );
	w_debug_lvl->insertItem( i18n("Level 2 debug") );
	w_debug_lvl->insertItem( i18n("Level 3 debug") );
	w_debug_lvl->insertItem( i18n("Level 4 debug") );

	w_porttext = new QLineEdit( this , "LePort" );

	defaults();
	load();
	slot_Update();

	connect( w_port , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );
	connect( w_verbose , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );
	connect( w_debug , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );
}
Opt_Misc::~Opt_Misc(){
}

QString & Opt_Misc::
arguments()
{
	s_args = "";

	QString port = w_porttext->text();

	if ( w_ident->isChecked() )
		s_args += "-I ";

	if ( w_fast->isChecked() )
		s_args += "-F ";

	if (( w_port->isChecked() ) && ( !port.isEmpty() ))
	{
		s_args += "-p ";
		s_args += port.stripWhiteSpace();
		s_args += " ";
	}

	if ( w_frag->isChecked() )
		s_args += "-f ";

	if ( w_verbose->isChecked() )
	{
		int lvl = w_verbose_lvl->currentItem();

		if ( lvl != -1 )
		{
			for ( int i = 0 ; i <= lvl ; i++ )
				s_args += "-v ";
		}
	}

	if ( w_debug->isChecked() )
	{
		int lvl = w_debug_lvl->currentItem();

		if ( lvl != -1 )
		{
			for ( int i = 0 ; i <= lvl ; i++ )
				s_args += "-d ";
		}
	}

	cout << "Opt_Misc: current arguments: " << s_args << "\n";

	return s_args;
}

void Opt_Misc::
load()
{
	QString text = kapp->getConfig()->readEntry( "Command_Arguments" );
	QString parm = "";
	QTextStream is( text , IO_ReadOnly );

	int i_verbose = -1;
	int i_debug = -1;

	while ( !is.eof() )
	{
		is >> parm;

		check_parms:

		if ( parm == "-I" )
			w_ident->setChecked(true);

		if ( parm == "-F" )
			w_fast->setChecked(true);

		if ( parm == "-p" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			w_port->setChecked(true);
			w_porttext->setText( parm );
		}

		if ( parm == "-f" )
			w_frag->setChecked(true);

		if ( parm == "-v" )
			i_verbose++;

		if ( parm == "-d" )
			i_debug++;
	}

	// Check verbose
	if ( i_verbose > -1 )
	{
		w_verbose->setChecked(true);

		if ( i_verbose > 3 )
			w_verbose_lvl->setCurrentItem(3);
		else
			w_verbose_lvl->setCurrentItem( i_verbose );
	}

	// Check debug
	if ( i_debug > -1 )
	{
		w_debug->setChecked(true);

		if ( i_debug > 3 )
			w_debug_lvl->setCurrentItem(3);
		else
			w_debug_lvl->setCurrentItem( i_verbose );
	}

	slot_Update();
}
void Opt_Misc::
save()
{
	// Save path to config even if not used.
	KConfig *config = kapp->getConfig();

	config->writeEntry( "Specific_Ports" , w_porttext->text() );
}
void Opt_Misc::
defaults()
{
	// Clear paths
	w_porttext->clear();
	
	w_ident->setChecked(false);
	w_fast->setChecked(false);
	w_port->setChecked(false);
	w_frag->setChecked(false);

	w_verbose->setChecked(false);
	w_verbose_lvl->setCurrentItem(0);

	w_debug->setChecked(false);
	w_debug_lvl->setCurrentItem(0);

	slot_Update();
}

void Opt_Misc::
slot_Update()
{
	w_porttext->setEnabled( w_port->isChecked() );
	w_verbose_lvl->setEnabled( w_verbose->isChecked() );
	w_debug_lvl->setEnabled( w_debug->isChecked() );
}

void Opt_Misc::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	w_ident->setGeometry( 5 , 5 , width() - 10 , 25 );
	w_fast->setGeometry( 5 , 35 , width() - 10 , 25 );
	w_port->setGeometry( 5 , 65 , width() - 150 , 25 );
	w_porttext->setGeometry( width() - 145 , 65 , 140 , 25 );
	w_frag->setGeometry( 5 , 95 , width() - 10 , 25 );


	w_verbose->setGeometry( 5 , 125 , width() - 150 , 25 );
	w_verbose_lvl->setGeometry( width() - 145 , 125 , 140 , 25 );

	w_debug->setGeometry( 5 , 155 , width() - 150 , 25 );
	w_debug_lvl->setGeometry( width() - 145 , 155 , 140 , 25 );
}



