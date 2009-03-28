/***************************************************************************
                          optionstack.cpp  -  description
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

#include "optionstack.h"

#include "opt_scan.h"
#include "opt_ping.h"
#include "opt_path.h"
#include "opt_decoy.h"
#include "opt_hosthist.h"
#include "opt_argshist.h"
#include "opt_log.h"
#include "opt_stealth.h"
#include "opt_font.h"
#include "opt_misc.h"
//#include "opt_.h"
//#include "opt_.h"

OptionStack::OptionStack(QWidget *parent, const char *name ) : QWidget(parent,name) {
	l_widgets.setAutoDelete(true);

	w_ostack = new QWidgetStack( this , "OptStack" );
	w_ostack->setFrameStyle( QFrame::WinPanel | QFrame::Sunken );

	btn_defaults = new QPushButton( i18n("Defaults") , this , "BtnDefaults" );
	btn_cancel = new QPushButton( i18n("Cancel") , this , "BtnCancel" );
	btn_save = new QPushButton( i18n("Save") , this , "BtnSave" );

	i_someid = 0;

	connect( btn_defaults , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnDefaults()) );
	connect( btn_cancel , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnCancel()) );
	connect( btn_save , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnSave()) );

	init_Applets();
	slot_Selected( OptionFrame::TypeScan );
}
OptionStack::~OptionStack(){
}

void OptionStack::
save()
{
	// While this usually doesn't have any effect, some applets
	// do need to save independant info in the config file. So
	// save em all anyway.
	o_scan->save();
	o_ping->save();
	o_path->save();
	o_decoy->save();
	o_hosthist->save();
	o_argshist->save();
	o_log->save();
	o_stealth->save();
//	o_font->save();
	o_misc->save();

	// Get the total of args from each applet
	QString s_args = "";

	s_args += o_scan->arguments();
	s_args += o_ping->arguments();
	s_args += o_decoy->arguments();
	s_args += o_log->arguments();
	s_args += o_stealth->arguments();
	s_args += o_misc->arguments();

	s_args += "-- ";

	cout << "OptionStack: sving arguments: " << s_args << "\n";

	kapp->getConfig()->writeEntry( "Command_Arguments" , s_args );
	emit sig_loadargs();
}
void OptionStack::
load()
{
	o_scan->load();
	o_ping->load();
	o_path->load();
	o_decoy->load();
	o_hosthist->load();
	o_argshist->load();
	o_log->load();
	o_stealth->load();
//	o_font->load();
	o_misc->load();
}
void OptionStack::
defaults()
{
	o_scan->defaults();
	o_ping->defaults();
	o_path->defaults();
	o_decoy->defaults();
	o_hosthist->defaults();
	o_argshist->defaults();
	o_log->defaults();
	o_stealth->defaults();
//	o_font->defaults();
	o_misc->defaults();
}

void OptionStack::
init_Applets()
{
	cout << "OptionStack: initializing setup applets\n";

	////////////////////////////////////////////////
	// Opt_Scan applet
	o_scan = new Opt_Scan( this , "Opt_Scan" );
	w_ostack->addWidget( o_scan , ++i_someid );

	////////////////////////////////////////////////
	// Opt_Ping applet
	o_ping = new Opt_Ping( this , "Opt_Ping" );
	w_ostack->addWidget( o_ping , ++i_someid );

	////////////////////////////////////////////////
	// Opt_Path applet
	o_path = new Opt_Path( this , "Opt_Path" );
	w_ostack->addWidget( o_path , ++i_someid );

	////////////////////////////////////////////////
	// Opt_Decoy applet
	o_decoy = new Opt_Decoy( this , "Opt_Decoy" );
	w_ostack->addWidget( o_decoy , ++i_someid );

	////////////////////////////////////////////////
	// Opt_HostHist applet
	o_hosthist = new Opt_HostHist( this , "Opt_HostHist" );
	w_ostack->addWidget( o_hosthist , ++i_someid );

	connect( o_hosthist , SIGNAL(sig_loadhost()) ,
		 this , SIGNAL(sig_loadhost()) );

	////////////////////////////////////////////////
	// Opt_ArgsHist applet
	o_argshist = new Opt_ArgsHist( this , "Opt_ArgsHist" );
	w_ostack->addWidget( o_argshist , ++i_someid );

	connect( o_argshist , SIGNAL(sig_loadargs()) ,
		 this , SIGNAL(sig_loadargs()) );

	////////////////////////////////////////////////
	// Opt_Log applet
	o_log = new Opt_Log( this , "Opt_Log" );
	w_ostack->addWidget( o_log , ++i_someid );

	////////////////////////////////////////////////
	// Opt_Stealth applet
	o_stealth = new Opt_Stealth( this , "Opt_Stealth" );
	w_ostack->addWidget( o_stealth , ++i_someid );

	////////////////////////////////////////////////
	// Opt_Font applet
	o_font = new Opt_Font( this , "Opt_Font" );
	w_ostack->addWidget( o_font , ++i_someid );

	////////////////////////////////////////////////
	// Opt_Misc applet
	o_misc = new Opt_Misc( this , "Opt_Misc" );
	w_ostack->addWidget( o_misc , ++i_someid );

	cout << "OptionStack: " << i_someid << " applets initialized\n";
}

void OptionStack::
slot_BtnSave()
{
	save();
}
void OptionStack::
slot_BtnDefaults()
{
	defaults();
}
void OptionStack::
slot_BtnCancel()
{
	load();
}

void OptionStack::
slot_Selected( OptionFrame::OptType type )
{
	cout << "OptionStack: received selection: " << type << "\n";

	switch (type)
	{
		case OptionFrame::TypeScan:
			cout << "  raising scan widget\n";
			w_ostack->raiseWidget( o_scan );
		break;

		case OptionFrame::TypePing:
			cout << "  raising ping widget\n";
			w_ostack->raiseWidget( o_ping );
		break;

		case OptionFrame::TypePath:
			cout << "  raising path widget\n";
			w_ostack->raiseWidget( o_path );
		break;

		case OptionFrame::TypeDecoy:
			cout << "  raising decoy widget\n";
			w_ostack->raiseWidget( o_decoy );
		break;

		case OptionFrame::TypeHostHist:
			cout << "  raising hosthist widget\n";
			w_ostack->raiseWidget( o_hosthist );
		break;

		case OptionFrame::TypeArgsHist:
			cout << "  raising argshist widget\n";
			w_ostack->raiseWidget( o_argshist );
		break;

		case OptionFrame::TypeLog:
			cout << "  raising log widget\n";
			w_ostack->raiseWidget( o_log );
		break;

		case OptionFrame::TypeStealth:
			cout << "  raising stealth widget\n";
			w_ostack->raiseWidget( o_stealth );
		break;

		case OptionFrame::TypeFont:
			cout << "  raising font widget\n";
			w_ostack->raiseWidget( o_font );
		break;

		case OptionFrame::TypeMisc:
			cout << "  raising misc widget\n";
			w_ostack->raiseWidget( o_misc );
		break;

		default:
		break;
	}
}

void OptionStack::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	w_ostack->setGeometry( 0 , 0 , width() , height() - 35 );

	btn_defaults->setGeometry( 5 , height() - 30 , 90 , 25 );
	btn_cancel->setGeometry( 95 , height() - 30 , 90 , 25 );
	btn_save->setGeometry( width() - 95 , height() - 30 , 90 , 25 );
}



















