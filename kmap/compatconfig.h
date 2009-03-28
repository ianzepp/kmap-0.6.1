/***************************************************************************
                          compatconfig.h  -  description
                             -------------------
    begin                : Thu Nov 4 1999
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

#ifndef COMPATCONFIG_H
#define COMPATCONFIG_H

#include <kapp.h>

#include <qstring.h>
#include <qstrlist.h>
#include <qfont.h>
#include <qsize.h>
#include <qcolor.h>

/**
  *@author Ian Zepp
  */

class CompatConfig {
public: 
	CompatConfig();
	~CompatConfig();
	
	static void setGroup( const char * );

	static void writeEntry( const char * , const char * );
	static void writeEntry( const char * , const QString & );
	static void writeEntry( const char * , const QStrList & );
	static void writeEntry( const char * , int );
	static void writeEntry( const char * , unsigned int );
	static void writeEntry( const char * , const QFont & );
	static void writeEntry( const char * , const QSize & );
	static void writeEntry( const char * , const QColor & );

	QString & readEntry( const char * );
	int readListEntry( const char * , QStrList & );
	int readNumEntry( const char * );
	unsigned int readUnsignedNumEntry( const char * );
	QFont & readFontEntry( const char * );
	QSize & readSizeEntry( const char * );
	QColor & readColorEntry( const char * );
};

#endif
