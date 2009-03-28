/***************************************************************************
                          opt_ping.cpp  -  description
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

#include "opt_ping.h"

Opt_Ping::Opt_Ping(QWidget *parent, const char *name ) : QWidget(parent,name) {
	lbl_ping = new QLabel( this , "LblPing" );
	lbl_ping->setText( i18n("Available ping options:") );

	w_ping = new QComboBox( this , "BoxPing" );
	w_ping->insertItem( i18n("Don't ping the target host") );
	w_ping->insertItem( i18n("Use TCP ping instead of ICMP") );
	w_ping->insertItem( i18n("Use ICMP ping instead of TCP") );
	w_ping->insertItem( i18n("Use TCP & ICMP in parallel") );

	w_useport = new QCheckBox( this , "BoxPort" );
	w_useport->setText( i18n("Set TCP ping to port:") );

	w_useporttext = new QLineEdit( this , "LePortText" );

	w_usesyn = new QCheckBox( this , "BoxSyn" );
	w_usesyn->setText( i18n("Use SYN instead of ACK for TCP packets") );

	connect( w_ping , SIGNAL(activated(int)) ,
		 this , SLOT(slot_Update()) );
	connect( w_useport , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnUsePort()) );

	defaults();
	load();
	slot_Update();
}
Opt_Ping::~Opt_Ping(){
}

QString & Opt_Ping::
arguments()
{
	s_args = "";

	if ( w_ping->currentItem() == 0 ) // no ping
	{
		s_args = "-P0 ";
	}
	else if ( w_ping->currentItem() == 1 ) // tcp ping
	{
		// Special handling for this one
		if ( w_useport->isChecked() )
		{
			s_args = "-PT";
			s_args += w_useporttext->text();
			s_args += " ";
		}

		if ( w_usesyn->isChecked() )
			s_args += "-PS ";
	}
	else if ( w_ping->currentItem() == 2 ) // icmp ping
	{
		s_args = "-PI ";
	}
	else if ( w_ping->currentItem() == 3 ) // both icmp & tcp ping
	{
		// Special hanlding for this one too
		if ( w_useport->isChecked() )
		{
			s_args = "-PB";
			s_args += w_useporttext->text();
			s_args += " ";
		}

		if ( w_usesyn->isChecked() )
			s_args += "-PS ";
	}

	cout << "Opt_Ping: current arguments: " << s_args << "\n";

	return s_args;
}

void Opt_Ping::
load()
{
	QString text = kapp->getConfig()->readEntry( "Command_Arguments" );
        QString parm;
	QTextStream is( text , IO_ReadOnly );

	while ( !is.eof() )
	{
		is >> parm;

		if ( parm == "-P0" )
		{
			w_ping->setCurrentItem( 0 ); // no ping
		}

		if ( parm.left(3) == "-PT" )
		{
			w_ping->setCurrentItem( 1 ); // no ping

			// Check for a specific port
			parm = parm.mid( 3 , parm.length() );

			if ( !parm.isEmpty() )
			{
				w_useport->setChecked(true);
				w_useporttext->setText( parm );
			}
		}

		if ( parm == "-PI" )
		{
			w_ping->setCurrentItem( 2 ); // icmp
		}

		if ( parm.left(3) == "-PB" )
		{
			w_ping->setCurrentItem( 1 ); // icmp & tcp

			// Check for a specific port
			parm = parm.mid( 3 , parm.length() );

			if ( !parm.isEmpty() )
			{
				w_useport->setChecked(true);
				w_useporttext->setText( parm );
			}
		}

		// Check for syn targeting
		if ( parm == "-PS" )
		{
			w_usesyn->setChecked(true);
		}
	}

	// Also load old port setting even if it is not used.
	QString oldport = kapp->getConfig()->readEntry("Ping_Use_Port");

	if (( !oldport.isEmpty() ) && ( w_useporttext->text() != "" ))
		w_useporttext->setText( oldport );
}
void Opt_Ping::
save()
{
	QString port = w_useporttext->text();

	kapp->getConfig()->writeEntry( "Ping_Use_Port" , port );
}
void Opt_Ping::
defaults()
{
	w_ping->setCurrentItem( 3 ); //icmp & tcp
	w_useport->setChecked(false);
	w_useporttext->setText("");
	w_usesyn->setChecked(false);

	slot_Update();
}

void Opt_Ping::
slot_Update()
{
	switch (w_ping->currentItem())
	{
		case 1: // tcp
		case 3: // icmp and tcp
			w_useport->setEnabled(true);
			w_useporttext->setEnabled( w_useport->isChecked() );
			w_usesyn->setEnabled(true);
		break;

		default:
			w_useport->setEnabled(false);
			w_useporttext->setEnabled(false);
			w_usesyn->setEnabled(false);
		break;
	}
}

void Opt_Ping::
slot_BtnUsePort()
{
	w_useporttext->setEnabled( w_useport->isChecked() );
}

void Opt_Ping::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	lbl_ping->setGeometry( 5 , 5 , 150 , 25 );
	w_ping->setGeometry( 155 , 5 , width() - 160 , 25 );

	w_useport->setGeometry( 15 , 35 , width() - 90 , 25 );
	w_useporttext->setGeometry( width() - 75 , 35 , 70 , 25 );

	w_usesyn->setGeometry( 15 , 65 , width() - 20 , 25 );
}







