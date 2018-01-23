/***************************************************************************
 *   Copyright (C) 2009 by AmR EiSa   *
 *   amreisa@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QMainWindow>

#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT
public:
    MainWindow();

protected:
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );

private slots:
    void on_calculateButton_clicked();
    void on_cancelButton_clicked();
    void on_fileEdit_textChanged( const QString &text );
    void on_browseButton_clicked();
    void on_copyButton_clicked();

    void on_actionOpen_triggered();

    void on_actionAbout_triggered();

    void on_comparePushButton_clicked();

private:
    bool cancel_calculation;
};

#endif

