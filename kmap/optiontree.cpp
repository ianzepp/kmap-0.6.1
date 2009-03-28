/***************************************************************************
                          optiontree.cpp  -  description
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

#include "optiontree.h"

OptionTree::OptionTree(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_tree = new QListView( this , "TreeListView" );
	w_tree->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );
	w_tree->setAllColumnsShowFocus(true);
	w_tree->setRootIsDecorated(true);
	w_tree->setSorting( -1 ); // disabled

	w_tree->addColumn( i18n("Options") );

	connect( w_tree , SIGNAL(selectionChanged(QListViewItem *)) ,
		 this , SLOT(slot_Selected(QListViewItem *)) );

	init_Applets();
}
OptionTree::~OptionTree(){
}

void OptionTree::
save()
{
	// exists for uniformity ; does nothing
}
void OptionTree::
load()
{
	// exists for uniformity ; does nothing
}
void OptionTree::
defaults()
{
}

void OptionTree::
init_Applets()
{
	cout << "OptionTree: initializing setup applets\n";

	QListViewItem *item;


	item = new QListViewItem( w_tree , i18n("File Options") );
	item->sortChildItems( 0 , true );
	item->setOpen(true);
	(void) new QListViewItem( item , i18n("Nmap path") );
	(void) new QListViewItem( item , i18n("Logging") );

	item = new QListViewItem( w_tree , i18n("Scan Options") );
	item->sortChildItems( 0 , true );
	item->setOpen(true);
	(void) new QListViewItem( item , i18n("Miscellaneous") );
	(void) new QListViewItem( item , i18n("Stealth") );
	(void) new QListViewItem( item , i18n("Setup decoys") );
	(void) new QListViewItem( item , i18n("Setup pings") );
	(void) new QListViewItem( item , i18n("Scan type") );

	item = new QListViewItem( w_tree , i18n("Recent args") );
	item = new QListViewItem( w_tree , i18n("Recent hosts") );

	cout << "OptionTree: applet names initialized\n";
}

void OptionTree::
slot_Selected( QListViewItem *item )
{
	QString text = item->text( 0 );

	cout << "OptionTree: selected: " << text << "\n";

	// Here we go.. only way to match em
	if ( text == i18n("Recent hosts") )
	{
		emit sig_selected( OptionFrame::TypeHostHist );
		return;
	}

	if ( text == i18n("Recent args") )
	{
		emit sig_selected( OptionFrame::TypeArgsHist );
		return;
	}

	if ( text == i18n("Scan type") )
	{
		emit sig_selected( OptionFrame::TypeScan );
		return;
	}

	if ( text == i18n("Setup pings") )
	{
		emit sig_selected( OptionFrame::TypePing );
		return;
	}

	if ( text == i18n("Stealth") )
	{
		emit sig_selected( OptionFrame::TypeStealth );
		return;
	}

	if ( text == i18n("Setup decoys") )
	{
		emit sig_selected( OptionFrame::TypeDecoy );
		return;
	}

	if ( text == i18n("Miscellaneous") )
	{
		emit sig_selected( OptionFrame::TypeMisc );
		return;
	}

	if ( text == i18n("Nmap path") )
	{
		emit sig_selected( OptionFrame::TypePath );
		return;
	}

	if ( text == i18n("Logging") )
	{
		emit sig_selected( OptionFrame::TypeLog );
		return;
	}
}

void OptionTree::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );
	w_tree->setGeometry( 0 , 0 , width() , height() );
	w_tree->setColumnWidth( 0 , width() - 20 );
}























