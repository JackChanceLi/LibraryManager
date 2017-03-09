#include "newbookdialog.h"
#include "ui_newbookdialog.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>

NewBookDialog::NewBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewBookDialog)
{
    ui->setupUi(this);
}

NewBookDialog::~NewBookDialog()
{
    delete ui;
}

void NewBookDialog::on_Button_save_quit_clicked()
{
    QDir dir;

    if(dir.exists("Books"))
        QMessageBox::warning(this, "哦", "当前文件夹已经存在了");
    else
    {
        if (dir.mkdir("Books"))
            QMessageBox::warning(this, "嗯", "创建好了");
        else
            QMessageBox::warning(this, "诶", "无法创建");
        return;
    }
    dir.setCurrent("./Books");
    QMessageBox::warning(this, "咳", "改到这个目录了: " + dir.currentPath());

    QFile f("Books.txt");
    if (!f.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "err", "cant open");
        return;
    }
    QTextStream out(&f);
    out << ui->Edit_Title->text() << '\n'
        << ui->Edit_Author->text() << '\n'
        << ui->Edit_Publisher->text() << '\n'
        << ui->Edit_Department->currentText() << '\n'
        << ui->Edit_Indate->date().year()
        << ui->Edit_Indate->date().month()
        << ui->Edit_Indate->date().day() << '\n'
        << ui->Edit_Intro->toPlainText();
    f.close();
    close();
}
