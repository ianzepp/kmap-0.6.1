/***************************************************************************
                          opt_stealth.cpp  -  description
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

#include "opt_stealth.h"

Opt_Stealth::Opt_Stealth(QWidget *parent, const char *name ) : QWidget(parent,name) {
	btn_nmapdef = new QCheckBox( i18n("Nmap-defined modes") , this , "BtnNmapDef" );
	btn_userdef = new QCheckBox( i18n("User-defined modes") , this , "BtnUserDef" );

	w_canned = new QComboBox( this , "ComboCanned" );
	w_canned->insertItem( i18n("Paranoid") );
	w_canned->insertItem( i18n("Sneaky") );
	w_canned->insertItem( i18n("Polite") );
	w_canned->insertItem( i18n("Normal") );
	w_canned->insertItem( i18n("Aggressive") );
	w_canned->insertItem( i18n("Insane") );

	w_host = new QCheckBox( i18n("Single host timeout (ms)") , this , "CbHost" );
	w_max_rtt = new QCheckBox( i18n("Maximum retransmit timeout (ms)") , this , "CbMaxRtt" );
	w_init_rtt = new QCheckBox( i18n("Initial retransmit timeout (ms)") , this , "CbInitRtt" );
	w_parallel = new QCheckBox( i18n("Maximum # of parallel scans") , this , "CbParallel" );
	w_delay = new QCheckBox( i18n("Minimum delay between probes (ms)") , this , "CbDelay" );

	w_host_text = new QLineEdit( this , "" );
	w_max_rtt_text = new QLineEdit( this , "" );
	w_init_rtt_text = new QLineEdit( this , "" );
	w_parallel_text = new QLineEdit( this , "" );
	w_delay_text = new QLineEdit( this , "" );

	defaults();
	load();
	slot_Update();

	connect( btn_nmapdef , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );
	connect( btn_userdef , SIGNAL(clicked()) ,
		 this , SLOT(slot_Update()) );

	connect( w_host , SIGNAL(clicked()) ,
		 this , SLOT(slot_Host()) );
	connect( w_max_rtt , SIGNAL(clicked()) ,
		 this , SLOT(slot_MaxRtt()) );
	connect( w_init_rtt , SIGNAL(clicked()) ,
		 this , SLOT(slot_InitRtt()) );
	connect( w_parallel , SIGNAL(clicked()) ,
		 this , SLOT(slot_Parallel()) );
	connect( w_delay , SIGNAL(clicked()) ,
		 this , SLOT(slot_Delay()) );
}
Opt_Stealth::~Opt_Stealth(){
}


QString & Opt_Stealth::
arguments()
{
	s_args = "";

	if ( btn_nmapdef->isChecked() )
	{
		if ( w_canned->currentItem() == 0 )
			s_args += "-T paranoid ";
		if ( w_canned->currentItem() == 1 )
			s_args += "-T sneaky ";
		if ( w_canned->currentItem() == 2 )
			s_args += "-T polite ";
		if ( w_canned->currentItem() == 3 )
			s_args += "-T normal ";
		if ( w_canned->currentItem() == 4 )
			s_args += "-T aggressive ";
		if ( w_canned->currentItem() == 5 )
			s_args += "-T insane ";
	}

	if ( btn_userdef->isChecked() )
	{
		if (( w_host->isChecked() ) && ( w_host_text->text() != "" ))
		{
			s_args += "--host_timeout ";
			s_args += w_host_text->text();
			s_args += " ";
		}

		if (( w_max_rtt->isChecked() ) && ( w_max_rtt_text->text() != "" ))
		{
			s_args += "--max_rtt_timeout ";
			s_args += w_max_rtt_text->text();
			s_args += " ";
		}

		if (( w_init_rtt->isChecked() ) && ( w_init_rtt_text->text() != "" ))
		{
			s_args += "--initial_rtt_timeout ";
			s_args += w_init_rtt_text->text();
			s_args += " ";
		}

		if (( w_parallel->isChecked() ) && ( w_parallel_text->text() != "" ))
		{
			s_args += "--max_parallelism ";
			s_args += w_parallel_text->text();
			s_args += " ";
		}

		if (( w_delay->isChecked() ) && ( w_delay_text->text() != "" ))
		{
			s_args += "--scan_delay ";
			s_args += w_delay_text->text();
			s_args += " ";
		}
	}


	cout << "Opt_Stealth: current arguments: " << s_args << "\n";

	return s_args;
}

void Opt_Stealth::
load()
{
	QString text = kapp->getConfig()->readEntry( "Command_Arguments" );
	QString parm = "";
	QTextStream is( text , IO_ReadOnly );

	while ( !is.eof() )
	{
		is >> parm;

		check_parms:
		if ( parm == "-T" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			btn_nmapdef->setChecked(true);
			btn_userdef->setChecked(false);

			if (( parm == "0" ) || ( parm = "Paranoid" ))
				w_canned->setCurrentItem(0);
			if (( parm == "1" ) || ( parm = "Sneaky" ))
				w_canned->setCurrentItem(1);
			if (( parm == "2" ) || ( parm = "Polite" ))
				w_canned->setCurrentItem(2);
			if (( parm == "3" ) || ( parm = "Normal" ))
				w_canned->setCurrentItem(3);
			if (( parm == "4" ) || ( parm = "Aggressive" ))
				w_canned->setCurrentItem(4);
			if (( parm == "5" ) || ( parm = "Insane" ))
				w_canned->setCurrentItem(5);
		}

		if ( parm == "--host_timeout" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			btn_nmapdef->setChecked(false);
			btn_userdef->setChecked(true);

			w_host->setChecked(true);
			w_host_text->setText( parm );

			slot_Host();
		}
		
		if ( parm == "--max_rtt_timeout" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			btn_nmapdef->setChecked(false);
			btn_userdef->setChecked(true);

			w_max_rtt->setChecked(true);
			w_max_rtt_text->setText( parm );

			slot_MaxRtt();
		}
		
		if ( parm == "--initial_rtt_timeout" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			btn_nmapdef->setChecked(false);
			btn_userdef->setChecked(true);

			w_init_rtt->setChecked(true);
			w_init_rtt_text->setText( parm );

			slot_InitRtt();
		}
		
		if ( parm == "--max_parallelism" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			btn_nmapdef->setChecked(false);
			btn_userdef->setChecked(true);

			w_parallel->setChecked(true);
			w_parallel_text->setText( parm );

			slot_Parallel();
		}
		
		if ( parm == "--scan_delay" )
		{
			is >> parm;
			
			if ( parm.left(1) == "-" )
				goto check_parms;

			btn_nmapdef->setChecked(false);
			btn_userdef->setChecked(true);

			w_delay->setChecked(true);
			w_delay_text->setText( parm );

			slot_Delay();
		}
	}

	slot_Update();
}
void Opt_Stealth::
save()
{
	// Save path to config even if not used.
	KConfig *config = kapp->getConfig();

	config->writeEntry( "Stealth_Host" , w_host_text->text() );
	config->writeEntry( "Stealth_Max_Rtt" , w_max_rtt_text->text() );
	config->writeEntry( "Stealth_Init_Rtt" , w_init_rtt_text->text() );
	config->writeEntry( "Stealth_Parallel" , w_parallel_text->text() );
	config->writeEntry( "Stealth_Delay" , w_delay_text->text() );
}
void Opt_Stealth::
defaults()
{
	btn_nmapdef->setChecked(false);
	btn_userdef->setChecked(false);

	w_canned->setCurrentItem( 3 ); // normal

	w_host->setChecked(false);
	w_max_rtt->setChecked(false);
	w_init_rtt->setChecked(false);
	w_parallel->setChecked(false);
	w_delay->setChecked(false);

	w_host_text->clear();
	w_max_rtt_text->clear();
	w_init_rtt_text->clear();
	w_parallel_text->clear();
	w_delay_text->clear();

	slot_Update();
}

void Opt_Stealth::
slot_Update()
{
	w_canned->setEnabled( btn_nmapdef->isChecked() );

	w_host->setEnabled( btn_userdef->isChecked() );
	w_max_rtt->setEnabled( btn_userdef->isChecked() );
	w_init_rtt->setEnabled( btn_userdef->isChecked() );
	w_parallel->setEnabled( btn_userdef->isChecked() );
	w_delay->setEnabled( btn_userdef->isChecked() );

	if ( btn_userdef->isChecked() )
	{
		slot_Host();
		slot_MaxRtt();
		slot_InitRtt();
		slot_Parallel();
		slot_Delay();
	}
	else
	{
		w_host_text->setEnabled(false);
		w_max_rtt_text->setEnabled(false);
		w_init_rtt_text->setEnabled(false);
		w_parallel_text->setEnabled(false);
		w_delay_text->setEnabled(false);
	}
}

void Opt_Stealth::
slot_Host()
{
	w_host_text->setEnabled( w_host->isChecked() );
}
void Opt_Stealth::
slot_MaxRtt()
{
	w_max_rtt_text->setEnabled( w_max_rtt->isChecked() );
}
void Opt_Stealth::
slot_InitRtt()
{
	w_init_rtt_text->setEnabled( w_init_rtt->isChecked() );
}
void Opt_Stealth::
slot_Parallel()
{
	w_parallel_text->setEnabled( w_parallel->isChecked() );
}
void Opt_Stealth::
slot_Delay()
{
	w_delay_text->setEnabled( w_delay->isChecked() );
}

void Opt_Stealth::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	btn_nmapdef->setGeometry( 5 , 5 , width() - 165 , 25 );
	w_canned->setGeometry( width() - 155 , 5 , 150 , 25 );

	btn_userdef->setGeometry( 5 , 35 , width() - 10 , 25 );

	w_host->setGeometry( 15 , 65 , width() - 120 , 25 );
	w_host_text->setGeometry( width() - 95 , 65 , 90 , 25 );

	w_max_rtt->setGeometry( 15 , 95 , width() - 120 , 25 );
	w_max_rtt_text->setGeometry( width() - 95 , 95 , 90 , 25 );

	w_init_rtt->setGeometry( 15 , 125 , width() - 120 , 25 );
	w_init_rtt_text->setGeometry( width() - 95 , 125 , 90 , 25 );

	w_parallel->setGeometry( 15 , 155 , width() - 120 , 25 );
	w_parallel_text->setGeometry( width() - 95 , 155 , 90 , 25 );

	w_delay->setGeometry( 15 , 185 , width() - 120 , 25 );
	w_delay_text->setGeometry( width() - 95 , 185 , 90 , 25 );
}




