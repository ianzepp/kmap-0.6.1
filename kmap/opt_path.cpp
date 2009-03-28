/***************************************************************************
                          opt_path.cpp  -  description
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

#include "opt_path.h"

Opt_Path::Opt_Path(QWidget *parent, const char *name ) : QWidget(parent,name) {
	lbl_path = new QLabel( i18n("Nmap executable:") , this , "LblPath" );
	w_path = new QLineEdit( this , "LePath" );
	btn_path = new QPushButton( i18n("Browse") , this , "BtnPath" );

	defaults();
	load();

	slot_Update();

	connect( btn_path , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnPath()) );
}
Opt_Path::~Opt_Path(){
}

void Opt_Path::
save()
{
	QString path = w_path->text();

	if ( !path.isEmpty() )
		kapp->getConfig()->writeEntry( "Nmap_Executable" , path );
}
void Opt_Path::
load()
{
	w_path->setText( kapp->getConfig()->readEntry("Nmap_Executable") );
}
void Opt_Path::
defaults()
{
}

void Opt_Path::
slot_Update()
{
}

void Opt_Path::
slot_BtnPath()
{
	QString text = QFileDialog::getOpenFileName( "/usr/bin" );
	
	if ( text.isEmpty() )
		return;

	w_path->setText( text );
}

void Opt_Path::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	lbl_path->setGeometry( 5 , 5 , 150 , 25 );
	w_path->setGeometry( 160 , 5 , width() - 260 , 25 );
	btn_path->setGeometry( width() - 95 , 5 , 90 , 25 );
}


