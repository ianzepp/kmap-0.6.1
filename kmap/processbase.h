/***************************************************************************
                          processbase.h  -  description
                             -------------------
    begin                : Sun Oct 24 1999
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

#ifndef PROCESSBASE_H
#define PROCESSBASE_H

#include <iostream.h>
#include <qobject.h>
#include <qstring.h>
#include <qtextstream.h>
#include <kprocess.h>

/**
  *@author Ian Zepp
  */

class ProcessBase : public QObject {
	Q_OBJECT
public:
	ProcessBase();
	~ProcessBase();

	const QString & command();

	int exitStatus();

	bool running();
	bool start();
	bool kill();

	int totalStdout();
	int totalStderr();

	void reset();
	void setCommand( const QString & );

	void setVerbose( bool );
	void setStdout( bool );
	void setStderr( bool );

private slots:
	void slot_Stdout( KProcess * , char * , int );
	void slot_Stderr( KProcess * , char * , int );
	void slot_Exited( KProcess * );

private:
	KProcess proc;

	QString s_command;
	QString s_lastout;
	QString s_lasterr;

	QString s_pout;
	QString s_perr;

	int i_totalout;
	int i_totalerr;

	bool b_verbose;
	bool b_comm_stdout;
	bool b_comm_stderr;

signals:
	void sig_started();
	void sig_stdout( const QString & );
	void sig_stderr( const QString & );
	void sig_exited();
};

#endif

























