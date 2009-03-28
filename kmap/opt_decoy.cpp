/***************************************************************************
                          opt_decoy.cpp  -  description
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

#include "opt_decoy.h"

Opt_Decoy::Opt_Decoy(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_edit = new QLineEdit( this , "LeEdit" );
	w_list = new QListBox( this , "LbList" );

	btn_positive = new QPushButton( i18n("<undef>") , this , "BtnPos" );
	btn_negative = new QPushButton( i18n("<undef>") , this , "BtnNeg" );

	connect( btn_positive , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnPositive()) );
	connect( btn_negative , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnNegative()) );
	connect( w_edit , SIGNAL(textChanged(const char *)) ,
		 this , SLOT(slot_EditChanged(const char *)) );
	connect( w_list , SIGNAL(highlighted(int)) ,
		 this , SLOT(slot_ListHighlighted(int)) );

	defaults();
	load();
	slot_Update();
}
Opt_Decoy::~Opt_Decoy(){
}

void Opt_Decoy::
save()
{
}
void Opt_Decoy::
load()
{
}
void Opt_Decoy::
defaults()
{
	btn_positive->setEnabled(false);
	btn_positive->setText( i18n("Add") );

	btn_negative->setEnabled(false);
	btn_negative->setText( i18n("Remove") );
	
	w_edit->clear();
	w_edit->setEnabled(true);

	w_list->hide();

	i_modepos = Opt_Decoy::ModeUndef;
	i_modeneg = Opt_Decoy::ModeUndef;
}

QString & Opt_Decoy::
arguments()
{
	s_args = "";

	for ( uint i = 0 ; i < w_list->count() ; i++ )
	{
		s_args += w_list->text(i);
		s_args += ",";
	}

	cout << "Opt_Decoy: current arguments: " << s_args << "\n";

	return s_args;
}

void Opt_Decoy::
slot_Update()
{
}

void Opt_Decoy::
slot_BtnPositive()
{
	QString text = "";

	switch (i_modepos)
	{
		case Opt_Decoy::ModeAdd:
			text = w_edit->text();

			if ( text.isEmpty() )
				return;

			w_list->insertItem( text , -1 );
			w_list->show();
			w_edit->clear();

			i_modepos = Opt_Decoy::ModeUndef;
			btn_positive->setEnabled(false);
		break;

		default:
		break;
	}
}
void Opt_Decoy::
slot_BtnNegative()
{
	QString text = "";
	int pos = -1;

	switch (i_modeneg)
	{
		case Opt_Decoy::ModeRem:
			pos = w_list->currentItem();

			if ( pos == -1 )
				return;

			w_list->removeItem( pos );

			if ( w_list->count() == 0 )
			{
				w_list->hide();
				i_modeneg = Opt_Decoy::ModeUndef;
				btn_negative->setEnabled(false);
			}
		break;

		default:
		break;
	}
}

void Opt_Decoy::
slot_EditChanged( const char *text )
{
	if ( strlen(text) > 0 )
	{
		if ( !btn_positive->isEnabled() )
			btn_positive->setEnabled(true);

		i_modepos = Opt_Decoy::ModeAdd;
	}
	else
	{
		if ( btn_positive->isEnabled() )
			btn_positive->setEnabled(false);

		i_modepos = Opt_Decoy::ModeUndef;
	}
}
void Opt_Decoy::
slot_ListHighlighted( int i )
{
	if ( i > -1 )
	{
		if ( !btn_negative->isEnabled() )
			btn_negative->setEnabled(true);

		i_modeneg = Opt_Decoy::ModeRem;
	}
	else
	{
		if ( btn_negative->isEnabled() )
			btn_negative->setEnabled(false);

		i_modeneg = Opt_Decoy::ModeUndef;
	}
}

void Opt_Decoy::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	const int w_avg = (width() - 10) / 2;

	btn_positive->setGeometry( 5 , 5 , w_avg , 20 );
	btn_negative->setGeometry( w_avg + 5 , 5 , w_avg , 20 );

	w_edit->setGeometry( 5 , 30 , width() - 10 , 25 );
	w_list->setGeometry( 5 , 60 , width() - 10 , height() - 65 );
}
