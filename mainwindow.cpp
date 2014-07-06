#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filePath.clear();
}

void MainWindow::prepareData()
{
    QFile inputfile, outputFile;
    inputfile.setFileName(filePath);
    outputFile.setFileName(filePath + "PARSE.csv");
    inputfile.open(QIODevice::ReadOnly);
    outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
    if(inputfile.isOpen() && outputFile.isOpen())
    {
        QTextStream inp(&inputfile),
                    out(&outputFile);
        QString inputFileString = inp.readAll();
        inputFileString.replace(" !", "!");
        inputFileString.replace(" ,", ",");
        inputFileString.replace(" .", ".");
        inputFileString.replace(" ?", "?");
        inputFileString.replace("- ", "-");
        inputFileString.replace(" -", "-");
        inputFileString.replace(" :", ":");
        inputFileString.replace(" ;", ";");
        inputFileString.replace('#', "\n#");
        inputFileString.remove('&');
        inputFileString.remove('#');
        inputFileString.replace("\n\n", "\n");
        inputFileString.replace(0, 1, "");
        out << inputFileString;
        inputfile.close();
        outputFile.close();
        ui->textEdit->append("END");
    }
    else
    {
        if(!inputfile.isOpen())
            ui->textEdit->append("Input file open error.");
        if(!outputFile.isOpen())
            ui->textEdit->append("Output file open error.");

    }
    filePath.clear();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    filePath = QFileDialog::getOpenFileName(this, tr("Open file"), "",   tr("Files (*.*)"));
    ui->textEdit->append(filePath);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!filePath.isEmpty())
        prepareData();
}
