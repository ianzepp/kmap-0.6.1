/***************************************************************************
                          opt_font.cpp  -  description
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

#include "opt_font.h"

Opt_Font::Opt_Font(QWidget *parent, const char *name ) : QWidget(parent,name) {
	defaults();
	load();
	slot_Update();
}
Opt_Font::~Opt_Font(){
}

void Opt_Font::
load()
{
}
void Opt_Font::
save()
{
}
void Opt_Font::
defaults()
{
}

void Opt_Font::
slot_Update()
{
}

void Opt_Font::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );
}




