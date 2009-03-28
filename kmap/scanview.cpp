/***************************************************************************
                          scanview.cpp  -  description
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

#include "scanview.h"

ScanView::ScanView(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_lv = new QListView( this , "ScanViewList" );
	w_lv->setAllColumnsShowFocus(true);
	w_lv->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );

	w_lv->addColumn( i18n("Address") );
	w_lv->addColumn( i18n("Port") );
	w_lv->addColumn( i18n("State") );
	w_lv->addColumn( i18n("Protocol") );
	w_lv->addColumn( i18n("Service") );

	b_inlist = false;
	b_pingscan = false;
	s_ipaddr = "<unknown>";
}
ScanView::~ScanView(){
}

void ScanView::
clear()
{
	w_lv->clear();
}
void ScanView::
save()
{
}
void ScanView::
load()
{
}

void ScanView::
slot_Started()
{
	b_inlist = false;

	// Is this a ping scan?
	QString args = kapp->getConfig()->readEntry( "Command_Arguments" );

	if ( args.find( "-sP" ) == -1 )
		b_pingscan = false;
	else
		b_pingscan = true;

	// TODO: add an option to clear or not in here
	clear();
}
void ScanView::
slot_Stdout( const QString &text )
{
	if ( b_inlist )
		handle_PortEntry( text );

	if ( text.find( QRegExp( "^Interesting ports on " ) ) != -1 )
		handle_IpAddress( text );

	if ( b_pingscan )
	{
		if ( text.find( QRegExp( "^Host [a-zA-Z\\s]") ) != -1 )
			handle_PingState( text , true );
		else
			/* handle_PingState( text , false ) */ ;
	}

	if (( !b_inlist ) && ( text.find( QRegExp( "^Port " ) ) != -1 ))
		b_inlist = true;
}
void ScanView::
slot_Stderr( const QString &text )
{
	// normal messages don't come on stderr
}
void ScanView::
slot_Exited()
{
	b_inlist = false;
	b_pingscan = false; // reset it anyways
}

void ScanView::
handle_IpAddress( const QString &text )
{
	int start = text.find( "(" ) + 1;
	int stop = text.find( ")" );
	int len = stop - start;

	s_ipaddr = text.mid( start , len );
}
void ScanView::
handle_PingState( const QString &text , bool state )
{
	int start = text.find( "(" ) + 1;
	int stop = text.find( ")" );
	int len = stop - start;

	s_ipaddr = text.mid( start , len );

	if ( state )
		(void) new QListViewItem( w_lv , s_ipaddr , "" , "Up" , "" , "" );
	else
		(void) new QListViewItem( w_lv , s_ipaddr , "" , "Down" , "" , "" );

}
void ScanView::
handle_PortEntry( const QString &text )
{
	if ( text.isEmpty() )
	{
		b_inlist = false;
		return;
	}

	QTextStream instream( text , IO_ReadOnly );
	QString w[4];

	for ( int i = 0 ; i < 4 ; i++ )
		instream >> w[i];

	QListViewItem *item = new QListViewItem( w_lv , s_ipaddr , w[0] , w[1] , w[2] , w[3] );
	(void) new QListViewItem( item , s_ipaddr , w[0] , "" , w[2] , "" );
}

void ScanView::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	// Setup each column width
	int w_ipaddr = 80;
	int w_avg = (width() - w_ipaddr - 20) / 4; // 20 for scroll bar

	w_lv->setGeometry( 0 , 0 , width() , height() );	
	w_lv->setColumnWidth( 0 , w_ipaddr );  // ip address
	w_lv->setColumnWidth( 1 , w_avg );     // port number
	w_lv->setColumnWidth( 2 , w_avg );     // state (open/filtered/closed)
	w_lv->setColumnWidth( 3 , w_avg );     // protocal
	w_lv->setColumnWidth( 4 , w_avg );     // service
}




























