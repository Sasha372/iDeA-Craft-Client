#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	setWindowTitle(WINDOW_TITLE);
}

MainWindow::~MainWindow() {
    delete ui;
	qDebug() << "Close";
}

void MainWindow::setNickname(QString nick) {
	if (this->nickname != "") return;
	this->nickname = nick;
}
