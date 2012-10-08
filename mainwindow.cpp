/*****************************************************************************
qprocess-read-pipe, A shell-like pipe reader that reads a process with args and shows the text output
Copyright (C) 2012 MD: Minhazul Haque;
mdminhazulhaque@gmail.com.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process = new QProcess(this);
    connect (process, SIGNAL(readyReadStandardOutput()), this, SLOT(printOutput()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::printOutput()
{
    ui->display->setPlainText(process->readAllStandardOutput());
}

void MainWindow::on_read_clicked()
{
    options.clear();
#if defined(Q_OS_LINUX)
    options << "-c" << ui->command->text();
    process->start("/bin/sh", options);
#elif defined(Q_OS_WIN)
    process->start(ui->command->text(), options);
#endif
    process->waitForFinished();
}
