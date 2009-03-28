/***************************************************************************
                          optionframe.cpp  -  description
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

#include "optionframe.h"
#include "optiontree.h"
#include "optionstack.h"

OptionFrame::OptionFrame(QWidget *parent, const char *name ) : QWidget(parent,name) {
	otree = new OptionTree( this , "OptionTree" );
	ostack = new OptionStack( this , "OptionStack" );

	connect( otree , SIGNAL(sig_selected(OptionFrame::OptType)) ,
		 ostack , SLOT(slot_Selected(OptionFrame::OptType)) );

	connect( ostack , SIGNAL(sig_loadhost()) ,
		 this , SIGNAL(sig_loadhost()) );
	connect( ostack , SIGNAL(sig_loadargs()) ,
		 this , SIGNAL(sig_loadargs()) );

	
}
OptionFrame::~OptionFrame(){
}

void OptionFrame::
save()
{
	otree->save(); // does nothing
	ostack->save();
}
void OptionFrame::
load()
{
	otree->load(); // does nothing
	ostack->load();
}
void OptionFrame::
defaults()
{
	otree->defaults(); // does nothing
	ostack->defaults();
}

void OptionFrame::
slot_Started()
{
	// nothing doing here
}
void OptionFrame::
slot_Exited()
{
	// reload options
	ostack->defaults();
	ostack->load();
}

void OptionFrame::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	otree->setGeometry( 0 , 0 , 150 , height() );
	ostack->setGeometry( 150 , 0 , width() - 150 , height() );
}





















