/***************************************************************************
                          mainview.cpp  -  description
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

#include "mainview.h"

MainView::MainView(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_ktab = new KTabCtl( this , "KTab" );

	lbl_host = new QLabel( i18n( "Hostname:" ) , this , "LblHost" );
	lbl_args = new QLabel( i18n( "Arguments:" ) , this , "LblArgs" );

	w_host = new QLineEdit( this , "EdHost" );
	w_args = new QLineEdit( this , "EdArgs" );

	btn_exec = new QPushButton( i18n( "Start" ) , this , "BtnExec" );

	w_scanview = new ScanView( w_ktab , "ScanView" );
	w_ktab->addTab( w_scanview , i18n("Port Listing") );

	w_treeview = new TreeView( w_ktab , "TreeView" );
	w_ktab->addTab( w_treeview , i18n("OS Ident") );

	w_nmapview = new NmapView( w_ktab , "NmapView" );
	w_ktab->addTab( w_nmapview , i18n("Nmap Output") );

	w_optframe = new OptionFrame( w_ktab , "Options" );
	w_ktab->addTab( w_optframe , i18n("Options") );

	connect( btn_exec , SIGNAL(clicked()) ,
		 this , SLOT(slot_ExecClicked()) );
	connect( w_optframe , SIGNAL(sig_loadhost()) ,
		 this , SLOT(slot_LoadHost()) );
	connect( w_optframe , SIGNAL(sig_loadargs()) ,
		 this , SLOT(slot_LoadArgs()) );

	b_running = false;
}
MainView::~MainView(){
}

void MainView::
save()
{
	QString host = w_host->text();
	QString args = w_args->text();

	kapp->getConfig()->writeEntry( "Remote_Hostname" , host );
	kapp->getConfig()->writeEntry( "Command_Arguments" , args );

	w_scanview->save();
	w_treeview->save();
	w_nmapview->save();
	w_optframe->save();
}
void MainView::
load()
{
	w_host->setText( kapp->getConfig()->readEntry("Remote_Hostname") );
	w_args->setText( kapp->getConfig()->readEntry("Command_Arguments") );

	w_scanview->load();
	w_treeview->load();
	w_nmapview->load();
	w_optframe->load();
}

void MainView::
slot_Started()
{
	b_running = true;

	// Disable widgets
	lbl_host->setEnabled(false);
	lbl_args->setEnabled(false);
	w_host->setEnabled(false);
	w_args->setEnabled(false);

	// Change labels
	btn_exec->setText( i18n("Stop") );

	// Tell sub widgets
	w_scanview->slot_Started();
	w_treeview->slot_Started();
	w_nmapview->slot_Started();
	w_optframe->slot_Started();

	w_ktab->setTabEnabled( i18n("Options") , false );
}
void MainView::
slot_Stdout( const QString &text )
{
	w_scanview->slot_Stdout( text );
	w_treeview->slot_Stdout( text );
	w_nmapview->slot_Stdout( text );
}
void MainView::
slot_Stderr( const QString &text )
{
	w_scanview->slot_Stderr( text );
	w_treeview->slot_Stderr( text );
	w_nmapview->slot_Stderr( text );
}
void MainView::
slot_Exited()
{
	b_running = false;

	// Disable widgets
	lbl_host->setEnabled(true);
	lbl_args->setEnabled(true);
	w_host->setEnabled(true);
	w_args->setEnabled(true);

	// Change labels
	btn_exec->setText( i18n("Start") );

	// Tell sub widgets
	w_scanview->slot_Exited();
	w_treeview->slot_Exited();
	w_nmapview->slot_Exited();
	w_optframe->slot_Exited();

	w_ktab->setTabEnabled( i18n("Options") , true );
}

void MainView::
slot_ExecClicked()
{
	if ( b_running )
	{
		emit sig_stop();
	}
	else
	{
		save();
		emit sig_start();
	}
}
void MainView::
slot_LoadHost()
{
	w_host->setText( kapp->getConfig()->readEntry("Remote_Hostname") );
}
void MainView::
slot_LoadArgs()
{
	w_args->setText( kapp->getConfig()->readEntry("Command_Arguments") );
}

void MainView::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	lbl_host->setGeometry( 5 , 5 , 100 , 25 );
	lbl_args->setGeometry( 5 , 35 , 100 , 25 );

	w_host->setGeometry( 110 , 5 , width() - 210 , 25 );
	w_args->setGeometry( 110 , 35 , width() - 115 , 25 );

	btn_exec->setGeometry( width() - 95 , 5 , 90 , 25 );

	w_ktab->setGeometry( 0 , 65 , width() , height() - 70 );
}





















