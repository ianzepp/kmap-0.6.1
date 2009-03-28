/***************************************************************************
                          treeview.cpp  -  description
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

#include "treeview.h"

TreeView::TreeView(QWidget *parent, const char *name ) : QWidget(parent,name) {
	pix = new QPixmap();
	w_tree = new QListView( this , "TreeViewList" );
	w_tree->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );
	w_tree->setAllColumnsShowFocus(true);
	w_tree->setRootIsDecorated(true);
	w_tree->setSorting( 0 , true );
	w_tree->addColumn( i18n("The Problem") );
	w_tree->addColumn( i18n("The Solution") );

	clear();
}
TreeView::~TreeView(){
}

void TreeView::
clear()
{
	w_tree->clear();

	i_cnt = 0;
	b_inlist = false;
	b_inprint = false;

	s_ipaddr = "";
	s_ports_tcp = "";
	s_ports_udp = "";
	s_ports_misc = "";

	s_problem = "";
	s_solution = "";

	// Reset current ip item
//	p_currentip = new QListViewItem( w_tree , "" , "" );
	// this places a blank first line in the treelist
}
void TreeView::
save()
{
}
void TreeView::
load()
{
}

void TreeView::
slot_Started()
{
	clear();
}
void TreeView::
slot_Stdout( const QString &text )
{
	if ( b_inlist )
	{
		handle_PortEntry( text );

		if ( text.isEmpty() )
			b_inlist = false;

		return; // no more parsing allowed here
	}

	if ( b_inprint )
	{
		handle_PrintEntry( text );

		if ( text.isEmpty() )
			b_inprint = false;

		return; // no more parsing allowed here
	}

	if ( text.find( QRegExp( "^Port " ) ) != -1 )
		b_inlist = true;

	if ( text.find( QRegExp( "^TCP/IP fingerprint:" ) ) != -1 )
		b_inprint = true;

	if ( text.find( QRegExp( "^No OS matches for host " ) ) != -1 )
		handle_UnknownOS( text );

	if ( text.find( QRegExp( "^Interesting ports on " ) ) != -1 )
		handle_IpAddress( text );

	if ( text.find( QRegExp( "Class=" ) ) != -1 )
		handle_Class( text ); // in middle of line

	if ( text.find( QRegExp( "Difficulty=" ) ) != -1 )
		handle_Difficulty( text ); // in middle of line

	if ( text.find( QRegExp( "^Sequence numbers:" ) ) != -1 )
		handle_Sequence( text );

	if ( text.find( QRegExp( "^Remote operating system guess:" ) ) != -1 )
		handle_RemoteOS( text );

	if ( text.find( QRegExp( "^Remote OS guesses:" ) ) != -1 )
		handle_RemoteOS( text );

}
void TreeView::
slot_Stderr( const QString &text )
{
}
void TreeView::
slot_Exited()
{
}

void TreeView::
handle_PortEntry( const QString &text )
{
	if ( text.isEmpty() ) // handle this first
	{
		if ( !s_ports_tcp.isEmpty() )
		{
			s_problem  = i18n("Open TCP ports:");
			s_solution = s_ports_tcp;

			(void) new QListViewItem( p_currentip , s_problem , s_solution );
		}

		if ( !s_ports_udp.isEmpty() )
		{
			s_problem  = i18n("Open UDP ports:");
			s_solution = s_ports_udp;

			(void) new QListViewItem( p_currentip , s_problem , s_solution );
		}

		if ( !s_ports_misc.isEmpty() )
		{
			s_problem  = i18n("Unknown-type ports:");
			s_solution = s_ports_misc;

			(void) new QListViewItem( p_currentip , s_problem , s_solution );
		}

		b_inlist = false;

		return;
	}

	QString port = text.left( text.find(" ") );

	if ( text.find( QRegExp( "tcp" ) ) != -1 )
		s_ports_tcp += port + ",";
	else if ( text.find( QRegExp( "udp" ) ) != -1 )
		s_ports_udp += port + ",";
	else
		s_ports_misc += port + ",";

}
void TreeView::
handle_PrintEntry( const QString &text )
{
	// For now just ignore the fingerprint
}
void TreeView::
handle_IpAddress( const QString &text )
{
	int start = text.find( "(" ) + 1;
	int stop = text.find( ")" );
	int len = stop - start;

	s_ipaddr = text.mid( start , len );
	s_ports_tcp = "";
	s_ports_udp = "";
	s_ports_misc = "";

	// Name to problem
	s_problem = s_ipaddr;

	// Try to extract a hostname
	s_solution = text.left( start - 1 );
	s_solution.replace( QRegExp("^Interesting ports on ") , "" );
	s_solution.replace( QRegExp("\\s") , "" );

	if ( s_solution.isEmpty() )
		s_solution = i18n("IP address did not resolve");
	else
		s_solution.prepend( i18n("IP address resolved to: ") );

	// Set current ip address and add in ..
	p_currentip = new QListViewItem( w_tree , s_problem , s_solution );
}
void TreeView::
handle_Class( const QString &text )
{
	s_problem = i18n("Sequence class: ");
	s_solution = text.mid( text.find("=") + 1 , text.length() );
	s_solution.stripWhiteSpace();

	(void) new QListViewItem( p_currentip , s_problem , s_solution );
}
void TreeView::
handle_Difficulty( const QString &text )
{
	s_problem = i18n("Sequence difficulty: ");
	s_solution = text.mid( text.find("=") + 1 , text.length() );
	s_solution.stripWhiteSpace();

	(void) new QListViewItem( p_currentip , s_problem , s_solution );
}
void TreeView::
handle_Sequence( const QString &text )
{
	s_problem = i18n("Sequence numbers: ");
	s_solution = text.mid( text.find(":") + 1 , text.length() );
	s_solution.stripWhiteSpace();

	(void) new QListViewItem( p_currentip , s_problem , s_solution );
}
void TreeView::
handle_RemoteOS( const QString &text )
{
	s_problem = i18n("Remote OS: ");
	s_solution = text.mid( text.find(":") + 1 , text.length() );
	s_solution.stripWhiteSpace();

	(void) new QListViewItem( p_currentip , s_problem , s_solution );
}
void TreeView::
handle_UnknownOS( const QString &text )
{
	s_problem = i18n("Unknown OS: ");
	s_solution = i18n("No OS matches for host");
	s_solution.stripWhiteSpace();

	(void) new QListViewItem( p_currentip , s_problem , s_solution );
}


void TreeView::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	int w_prob = 150;

	w_tree->setGeometry( 0 , 0 , width() , height() );	
	w_tree->setColumnWidth( 0 , w_prob );
	w_tree->setColumnWidth( 1 , width() - w_prob - 20 );
}


























