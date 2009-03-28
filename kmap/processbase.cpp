/***************************************************************************
                          processbase.cpp  -  description
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

#include "processbase.h"

ProcessBase::ProcessBase() : QObject() {
	reset();

	connect( &proc , SIGNAL(receivedStdout(KProcess *,char *,int)) ,
		 this , SLOT(slot_Stdout(KProcess *,char *,int)) );
	connect( &proc , SIGNAL(receivedStderr(KProcess *,char *,int)) ,
		 this , SLOT(slot_Stderr(KProcess *,char *,int)) );
	connect( &proc , SIGNAL(processExited(KProcess *)) ,
		 this , SLOT(slot_Exited(KProcess *)) );
}
ProcessBase::~ProcessBase(){
}

const QString & ProcessBase::
command()
{
	return s_command;
}

int ProcessBase::
exitStatus()
{
	return proc.exitStatus();
}

bool ProcessBase::
running()
{
	return proc.isRunning();
}

bool ProcessBase::
start()
{
	// I hope you reset() before ..
	cout << "ProcessBase: starting\n";

	if ( s_command.isEmpty() )
	{
		cerr << "ProcessBase: no command given to execute";
		return false;
	}

	proc.clearArguments();
	
	// Add in arguments
	QTextStream ts( s_command , IO_ReadOnly );
	QString tmpstring;

	while ( !ts.eof() ) {
		ts >> tmpstring;
		proc << tmpstring;
	}

	cout << "ProcessBase: executing: " << s_command << "\n";

	emit sig_started();

	return proc.start( KProcess::NotifyOnExit , KProcess::AllOutput );
}

bool ProcessBase::
kill()
{
	cout << "ProcessBase: committing suicide\n";

	return proc.kill();
}

int ProcessBase::
totalStdout()
{
	return i_totalout;
}
int ProcessBase::
totalStderr()
{
	return i_totalerr;
}

void ProcessBase::
reset()
{
	if ( proc.isRunning() ) {
		cerr << "ProcessBase: transient error: ";
		cerr << "process still running\n";
		kill();		
	}

	cout << "ProcessBase: resetting\n";

	proc.clearArguments();

	s_command = "";
	s_lastout = "";
	s_lasterr = "";

	s_pout = "";
	s_perr = "";

	i_totalout = 0;
	i_totalerr = 0;

	b_verbose = false;
	b_comm_stdout = true;
	b_comm_stderr = true;
}
void ProcessBase::
setCommand( const QString &text )
{
	cout << "ProcessBase: set command: " << text << "\n";

	s_command = text;
}
void ProcessBase::
setVerbose( bool b )
{
	cout << "ProcessBase: set verbose: " << b << "\n";
	b_verbose = b;
}
void ProcessBase::
setStdout( bool b )
{
	cout << "ProcessBase: set comm stdout: " << b << "\n";
	b_comm_stdout = b;
}
void ProcessBase::
setStderr( bool b )
{
	cout << "ProcessBase: set comm stderr: " << b << "\n";
	b_comm_stderr = b;
}

void ProcessBase::
slot_Stdout( KProcess *p , char *buffer , int buflen )
{
	QString line;
	QString text = buffer;
	text = text.left( buflen );

	// Prepend partial if it exists
	if ( !s_pout.isEmpty() )
	{
		text = s_pout + text;
		s_pout = "";
	}

	int i;

	while ( (i = text.find("\n")) != -1 )
	{
		line = text.left( i );
		text = text.mid( i + 1 , text.length() );

		if ( b_verbose )
			cout << "ProcessBase: stdout: "  << line << "\n";

		if ( b_comm_stdout )
			emit sig_stdout( line );
	}

	if ( !text.isEmpty() )
		s_pout = text;

	i_totalout += buflen;
}
void ProcessBase::
slot_Stderr( KProcess *p , char *buffer , int buflen )
{
	QString line;
	QString text = buffer;
	text = text.left( buflen );

	// Prepend partial if it exists
	if ( !s_perr.isEmpty() )
	{
		text = s_pout + text;
		s_perr = "";
	}

	int i;

	while ( (i = text.find("\n")) != -1 )
	{
		line = text.left( i );
		text = text.mid( i + 1 , text.length() );

		if ( b_verbose )
			cout << "ProcessBase: stderr: "  << line << "\n";

		if ( b_comm_stderr )
			emit sig_stderr( line );
	}

	if ( !text.isEmpty() )
		s_perr = text;

	i_totalerr += buflen;
}

void ProcessBase::
slot_Exited( KProcess *p )
{
	// Flush out buffers
	if (( !s_perr.isEmpty() ) && ( b_comm_stderr ))
		emit sig_stderr( s_perr );
	if (( !s_pout.isEmpty() ) && ( b_comm_stdout ))
		emit sig_stdout( s_pout );
		
	// Check status
	if ( p->normalExit() )
		if ( p->exitStatus() )
			cout << "ProcessBase: exited with errors\n";
		else
			cout << "ProcessBase: exited normally\n";
	else
		cerr << "ProcessBase: exited with unknown errors\n";

	emit sig_exited();
}




























