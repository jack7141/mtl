#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_clicked()
{
    mtl_path = QFileDialog::getExistingDirectory(this, "Get Any File","/home/hgh/hgh/mtl/straight");
    ui->label_2->setText(mtl_path);
    QDir directory(mtl_path);
    mtl_files = directory.entryList(QStringList() << "*.mtl" ,QDir::Files);
}

void MainWindow::on_pushButton_2_clicked()
{
    save_path = QFileDialog::getExistingDirectory(this, "Get Any File","/home/hgh/hgh/mtl_save");
    ui->label_4->setText(save_path);
}

void MainWindow::on_pushButton_3_clicked()
{
    for (int i=0;i < mtl_files.size();i++) {
        QString file_name = mtl_files[i].section(".",0,1);
        QFile File(mtl_path+"/"+mtl_files[i]);
        QFile newData(save_path+"/"+mtl_files[i]);
        File.open(QIODevice::ReadOnly|QIODevice::Text);
        newData.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream in(&File);
        QTextStream out(&newData);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QString outline = line.replace(QString("map_Kd texture.jpg"), mtl_files[i]);
            out << outline << "\n";
        }
        QImage image(mtl_path+"/texture.jpg");
        QImage copy;
        int individual = round(image.width()/mtl_files.size());
        copy = image.copy( 0, 0, individual*(i+1), image.height());
        copy.save(save_path+"/"+file_name+".jpg");
        QPixmap org;
        org.load(save_path+"/"+file_name+".jpg");
        QPixmap img = org;
        QTransform transform;
        transform.rotate(360);
        QPixmap rotate = img.transformed(transform);
        rotate.save(save_path+"/"+file_name+".jpg", "jpg");
        File.close();
        newData.close();
    }
}
