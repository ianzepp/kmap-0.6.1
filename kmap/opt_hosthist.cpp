/***************************************************************************
                          opt_hosthist.cpp  -  description
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

#include "opt_hosthist.h"

Opt_HostHist::Opt_HostHist(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_label = new QLabel( this , "Label" );
	w_label->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );
	w_list = new QListBox( this , "LbList" );

	btn_positive = new QPushButton( "" , this , "BtnPos" );
	btn_negative = new QPushButton( "" , this , "BtnNeg" );

	connect( btn_positive , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnPositive()) );
	connect( btn_negative , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnNegative()) );
	connect( w_list , SIGNAL(highlighted(int)) ,
		 this , SLOT(slot_ListHighlighted(int)) );
	connect( w_list , SIGNAL(selected(int)) ,
		 this , SLOT(slot_ListSelected(int)) );

	defaults();
	load();
	slot_Update();
}
Opt_HostHist::~Opt_HostHist(){
}

void Opt_HostHist::
save()
{
	QStrList recent;

	for ( uint i = 0 ; i < w_list->count() ; i++ )
		recent.append( w_list->text(i) );

	kapp->getConfig()->writeEntry( "Recent_Host" , &recent );
}
void Opt_HostHist::
load()
{
	QStrList recent;

	kapp->getConfig()->readListEntry( "Recent_Host" , recent );

	w_list->clear();

	if ( recent.count() > 0 )
	{
		w_list->insertStrList( &recent );
		w_label->setText( i18n("No hostnames have been selected") );
	}
	
}
void Opt_HostHist::
defaults()
{
	btn_positive->setEnabled(false);
	btn_positive->setText( i18n("Use hostname") );

	btn_negative->setEnabled(false);
	btn_negative->setText( i18n("Remove") );
	
	w_label->clear();
	w_label->setText( i18n("No hostnames are available") );

	w_list->hide();

	i_modepos = Opt_HostHist::ModeUndef;
	i_modeneg = Opt_HostHist::ModeUndef;
}

void Opt_HostHist::
slot_Update()
{
	if ( w_list->count() == 0 )
		w_list->hide();
	else
		w_list->show();
}

void Opt_HostHist::
slot_BtnPositive()
{
	QString text = "";

	switch (i_modepos)
	{
		case Opt_HostHist::ModeUse:
			text = w_label->text();
		
			if ( text.isEmpty() )
				return;

			kapp->getConfig()->writeEntry( "Remote_Hostname" , text );
			emit sig_loadhost();
		break;

		default:
		break;
	}
}
void Opt_HostHist::
slot_BtnNegative()
{
	int pos = -1;

	switch (i_modeneg)
	{
		case Opt_HostHist::ModeRem:
			pos = w_list->currentItem();

			if ( pos == -1 )
				return;

			w_list->removeItem( pos );

			if ( w_list->count() == 0 )
			{
				w_list->hide();
				i_modeneg = Opt_HostHist::ModeUndef;
				btn_negative->setEnabled(false);
			}
		break;

		default:
		break;
	}
}

void Opt_HostHist::
slot_ListHighlighted( int i )
{
	if ( !btn_positive->isEnabled() )
		btn_positive->setEnabled(true);
	if ( !btn_negative->isEnabled() )
		btn_negative->setEnabled(true);

	i_modepos = Opt_HostHist::ModeUse;
	i_modeneg = Opt_HostHist::ModeRem;

	w_label->setText( w_list->text(i) );
}
void Opt_HostHist::
slot_ListSelected( int i )
{
	slot_ListHighlighted( i );    // set text
	slot_BtnPositive();           // exec any signal
}

void Opt_HostHist::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	const int w_avg = (width() - 10) / 2;

	btn_positive->setGeometry( 5 , 5 , w_avg , 20 );
	btn_negative->setGeometry( w_avg + 5 , 5 , w_avg , 20 );

	w_label->setGeometry( 5 , 30 , width() - 10 , 25 );
	w_list->setGeometry( 5 , 60 , width() - 10 , height() - 65 );
}
