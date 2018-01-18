/***************************************************************************
 *   Copyright (C) 2009 by Guy Rutenberg   *
 *   guyrutenberg@gmail.com   *
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
#include <QtGui>

#include "main_window.h"

MainWindow::MainWindow()
    : QMainWindow()
{
	setupUi(this);
	cancelButton->hide();
	progressBar->hide();

	setFixedHeight(sizeHint().height());
}

void MainWindow::on_calculateButton_clicked()
{
	checksumEdit->setText("");

	QFile file(fileEdit->text());
	file.open(QIODevice::ReadOnly);

	const int block_size = (file.size() > 1024*1024) ? 10*1024 : 1024;
	char buffer[10*1024]; // allocate enough space for both cases so msvc will be happy
	int bytes_read;

	int progress_max = file.size()/block_size;
	progress_max = (progress_max > 0) ? progress_max : 1;
	progressBar->setMaximum(progress_max);
	progressBar->reset();

	QCryptographicHash::Algorithm hash_alg = static_cast<QCryptographicHash::Algorithm>(hashSelector->currentIndex());
	QCryptographicHash hash(hash_alg);

	cancel_calculation = false;

	while( (!cancel_calculation && (bytes_read = file.read(buffer, block_size))>0) ) {
		hash.addData(buffer, bytes_read);
		progressBar->setValue(progressBar->value()+1);
		QCoreApplication::processEvents();
	}
	
	progressBar->hide();

	if (!cancel_calculation) {
		checksumEdit->setText(hash.result().toHex());
	}

	progressBar->hide();
	checksumEdit->show();
	
	cancelButton->hide();
	calculateButton->show();
	file.close();
}

void MainWindow::on_cancelButton_clicked()
{
	cancel_calculation = true;
}

void MainWindow::on_fileEdit_textChanged(const QString &text)
{
	QFileInfo f_info(text);
	if(f_info.isFile()) {
		calculateButton->setEnabled(true);
	} else {
		calculateButton->setEnabled(false);
	}
}

void MainWindow::on_browseButton_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Load file..."));
	if(!filename.isEmpty()) {
		fileEdit->setText(filename);
	}
	QFileInfo f_info(filename);
	if(f_info.isFile()) {
		calculateButton->click();
	}

}

void MainWindow::on_copyButton_clicked()
{
	QApplication::clipboard()->setText(checksumEdit->text());
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty())
		return;

	QString fileName = urls.first().toLocalFile();
	fileEdit->setText(fileName);
	calculateButton->click();
}
