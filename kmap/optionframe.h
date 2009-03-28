/***************************************************************************
                          optionframe.h  -  description
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

#ifndef OPTIONFRAME_H
#define OPTIONFRAME_H

#include <kapp.h>

#include <qwidget.h>
#include <qevent.h>

/**
  *@author Ian Zepp
  */

class OptionTree;
class OptionStack;

class OptionFrame : public QWidget  {
   Q_OBJECT
public: 
	OptionFrame(QWidget *parent=0, const char *name=0);
	~OptionFrame();

	enum OptType { TypeScan = 1 , TypePing , TypePath , TypeDecoy ,
			TypeHostHist , TypeArgsHist , TypeLog ,
			TypeStealth , TypeFont , TypeMisc
	};

	void save();
	void load();
	void defaults();

public slots:
	void slot_Started();
	void slot_Exited();

protected slots:
	virtual void paintEvent( QPaintEvent * );

private:
	OptionTree *otree;
	OptionStack *ostack;

signals:
	void sig_loadhost();
	void sig_loadargs();
};

#endif










