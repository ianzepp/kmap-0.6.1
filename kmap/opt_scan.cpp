/***************************************************************************
                          opt_scan.cpp  -  description
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

#include "opt_scan.h"

Opt_Scan::Opt_Scan(QWidget *parent, const char *name ) : QWidget(parent,name) {
	// Create invis buttongroup
	grp_buttons= new QButtonGroup( this , "BtnGroup" );
	grp_buttons->setExclusive(true);
	grp_buttons->hide();

	// option widgets
	btn_normal = new QRadioButton( i18n("Normal-user scans:") , this , "BtnNormal" );
	grp_buttons->insert( btn_normal );

	btn_root = new QRadioButton( i18n("Root-only scans:") , this , "BtnRoot" );
	grp_buttons->insert( btn_root );

	btn_bounce = new QRadioButton( i18n("Ftp-server bounce:") , this , "BtnBouce" );
	grp_buttons->insert( btn_bounce );

	w_normal = new QComboBox( this , "BoxNormal" );
	w_normal->insertItem( i18n("TCP connect() scan") );
	w_normal->insertItem( i18n("TCP ping scan") );
	w_normal->insertItem( i18n("TCP/UDP rcp scan") );

	w_root = new QComboBox( this , "BoxRoot" );
	w_root->insertItem( i18n("TCP syn (half-open) scan") );
	w_root->insertItem( i18n("TCP fin scan") );
	w_root->insertItem( i18n("TCP Xmas tree scan") );
	w_root->insertItem( i18n("TCP null packet scan") );
	w_root->insertItem( i18n("UDP scan") );

	w_bounce = new QLineEdit( this , "LeBounce" );

	w_osid = new QCheckBox( i18n("Try to guess remote host's OS") , this , "CbOsid" );
	// end of widgets

	connect( btn_normal , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );
	connect( btn_root , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );
	connect( btn_bounce , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );

	defaults();
	load();
	slot_Update();
}
Opt_Scan::~Opt_Scan(){
}

QString & Opt_Scan::
arguments()
{
	s_args = "";

	if ( btn_normal->isChecked() )
	{
		if ( w_normal->currentItem() == 0 )
			s_args = "-sT ";
		else if ( w_normal->currentItem() == 1 )
			s_args = "-sP ";
		else if ( w_normal->currentItem() == 2 )
			s_args = "-sR ";
	}
	else if ( btn_root->isChecked() )
	{
		if ( w_normal->currentItem() == 0 )
			s_args = "-sS ";
		else if ( w_normal->currentItem() == 1 )
			s_args = "-sF ";
		else if ( w_normal->currentItem() == 2 )
			s_args = "-sX ";
		else if ( w_normal->currentItem() == 3 )
			s_args = "-sN ";
		else if ( w_normal->currentItem() == 4 )
			s_args = "-sU ";
	}
	else if ( btn_bounce->isChecked() )
	{
		s_args = "-b ";
	}

	if ( w_osid->isChecked() )
		s_args += "-O ";

	cout << "Opt_Scan: current arguments: " << s_args << "\n";

	return s_args;
}

void Opt_Scan::
load()
{
	QString text = kapp->getConfig()->readEntry( "Command_Arguments" );
	QString parm = "";
	QTextStream is( text , IO_ReadOnly );

	while ( !is.eof() )
	{
		is >> parm;

		if ( text.find("-sT") != -1 )
			toggle_Normal( 0 );
		if ( text.find("-sP") != -1 )
			toggle_Normal( 1 );
		if ( text.find("-sR") != -1 )
			toggle_Normal( 2 );
		if ( text.find("-sS") != -1 )
			toggle_Root( 0 );
		if ( text.find("-sF") != -1 )
			toggle_Root( 1 );
		if ( text.find("-sX") != -1 )
			toggle_Root( 2 );
		if ( text.find("-sN") != -1 )
			toggle_Root( 3 );
		if ( text.find("-sU") != -1 )
			toggle_Root( 4 );
		if ( text.find("-b") != -1 )
			toggle_Bounce();

		if ( text.find("-O") != -1 )
			w_osid->setChecked(true);
	}

	text = kapp->getConfig()->readEntry("Ftp_Bounce_Host");

	if (( !text.isEmpty() ) && ( w_bounce->text() == "" ))
		w_bounce->setText( text );
}
void Opt_Scan::
save()
{
	kapp->getConfig()->writeEntry( "Ftp_Bounce_Host" , w_bounce->text() );
}
void Opt_Scan::
defaults()
{
	toggle_Normal( 0 );
	w_osid->setChecked(false);
}

void Opt_Scan::
slot_Update()
{
	w_normal->setEnabled( btn_normal->isChecked() );
	w_root->setEnabled( btn_root->isChecked() );
	w_bounce->setEnabled( btn_bounce->isChecked() );
}

void Opt_Scan::
toggle_Normal( int index )
{
	w_normal->setCurrentItem( index );

	btn_normal->setChecked(true);
	btn_root->setChecked(false);
	btn_bounce->setChecked(false);

	slot_Update();
}
void Opt_Scan::
toggle_Root( int index )
{
	w_root->setCurrentItem( index );

	btn_normal->setChecked(false);
	btn_root->setChecked(true);
	btn_bounce->setChecked(false);

	slot_Update();
}
void Opt_Scan::
toggle_Bounce()
{
	btn_normal->setChecked(false);
	btn_root->setChecked(false);
	btn_bounce->setChecked(true);

	slot_Update();
}

void Opt_Scan::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	btn_normal->setGeometry( 5 , 5 , 150 , 25 );
	btn_root->setGeometry( 5 , 35 , 150 , 25 );
	btn_bounce->setGeometry( 5 , 65 , 150 , 25 );

	w_normal->setGeometry( 160 , 5 , width() - 165 , 25 );
	w_root->setGeometry( 160 , 35 , width() - 165 , 25 );
	w_bounce->setGeometry( 160 , 65 , width() - 165 , 25 );

	w_osid->setGeometry( 5 , 95 , width() - 10 , 25 );
}







