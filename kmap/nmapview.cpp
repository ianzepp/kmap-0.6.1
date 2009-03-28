/***************************************************************************
                          nmapview.cpp  -  description
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

#include "nmapview.h"

NmapView::NmapView(QWidget *parent, const char *name ) : QWidget(parent,name) {
	w_view = new QMultiLineEdit( this , "MleView" );
	w_view->setReadOnly(true);

	w_savelog = new QCheckBox( i18n( "Save to log:" ) , this , "CbSaveLog" );
	w_savelog->setEnabled(true);

	w_logfile = new QLineEdit( this , "LeLogFile" );
	w_logfile->setEnabled(false);

	btn_browse = new QPushButton( i18n( "Browse" ) , this , "BtnBrowse" );
	btn_browse->setEnabled(false);

	btn_save = new QPushButton( i18n( "Save" ) , this , "BtnSave" );
	btn_save->setEnabled(false);

	connect( w_savelog , SIGNAL(clicked()) ,
		 this , SLOT(slot_LogFile()) );
	connect( w_logfile , SIGNAL(returnPressed()) ,
		 this , SLOT(slot_BtnSave()) );
	connect( btn_browse , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnBrowse()) );
	connect( btn_save , SIGNAL(clicked()) ,
		 this , SLOT(slot_BtnSave()) );

}
NmapView::~NmapView(){
}

void NmapView::
clear()
{
	w_view->clear();
}

void NmapView::
save()
{
}
void NmapView::
load()
{
}

void NmapView::
append( const QString &text )
{
	w_view->append( text );
	w_view->setCursorPosition( w_view->numLines() , 1 );
}

void NmapView::
slot_Started()
{
}
void NmapView::
slot_Stdout( const QString &text )
{
	append( text );
}
void NmapView::
slot_Stderr( const QString &text )
{
	append( text );
}
void NmapView::
slot_Exited()
{
}

void NmapView::
slot_LogFile()
{
	w_logfile->setEnabled( w_savelog->isChecked() );
	btn_browse->setEnabled( w_savelog->isChecked() );
	btn_save->setEnabled( w_savelog->isChecked() );
}
void NmapView::
slot_BtnBrowse()
{
	QString text = QFileDialog::getSaveFileName();

	if ( text.isEmpty() )
		return;

	w_logfile->setText( text );
	kapp->getConfig()->writeEntry( "Log_File_Path" , text );
}
void NmapView::
slot_BtnSave()
{
	QString filename = w_logfile->text();

	if ( filename.isEmpty() ) {
		QMessageBox::information( 0 , i18n("Error: No filename given") ,
		 	  i18n("No filename was given. Please choose a filename first.") );
		return;
	}

	QString text = w_view->text();

	if ( text.isEmpty() ) {
		QMessageBox::information( 0 , i18n("Error: No text to save") ,
			i18n("No text in the output window to save") );
		return;
	}

	// Open file
	QFile f( filename );

	if ( f.open( IO_WriteOnly ) == false ) {
		QMessageBox::warning( 0 , i18n("Error: Unable to save") ,
			i18n("Unable to save: write permission denied") );
		return;
	}

	// Save data
	if ( f.writeBlock( text , text.length() ) == -1 ) {
		QMessageBox::warning( 0 , i18n("Error: Write error") ,
			i18n("Write error: unknown error") );
		return;
	}

	// Flush
	f.flush();

	// Done.
	QMessageBox::information( 0 , i18n("File saved") ,
		i18n("Successfully saved output text") );
}

void NmapView::
paintEvent( QPaintEvent *event )
{
	this->QWidget::paintEvent( event );

	w_view->setGeometry( 0 , 0 , width() , height() - 35 );

	w_savelog->setGeometry( 5 , height() - 30 , 90 , 25 );
	w_logfile->setGeometry( 100 , height() - 30 , width() - 300 , 25 );
	btn_browse->setGeometry( width() - 195 , height() - 30 , 90 , 25 );
	btn_save->setGeometry( width() - 95 , height() - 30 , 90 , 25 );
}







