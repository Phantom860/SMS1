#include "Addaffairdialog.h"
#include "ui_Addaffairdialog.h"

AddAffairDialog::AddAffairDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddAffairDialog)
{
    ui->setupUi(this);
    initUI();
}

AddAffairDialog::~AddAffairDialog()
{
    delete ui;
}

bool AddAffairDialog::clearData()
{
    ui->edit_startTime->clear();
    ui->edit_endTime->clear();
    ui->edit_content->clear();
    ui->cmb_urgency->clear();
    ui->cmb_category->clear();

    return true;
}

bool AddAffairDialog::display(int id, QString startTime, QString endTime, QString content, QString urgency, QString category)
{
    QTime stime = QTime::fromString(startTime,"yyyy/M/d H:mm");
    QTime etime = QTime::fromString(endTime,"yyyy/M/d H:mm");
    ui->edit_startTime->setTime(stime);
    ui->edit_endTime->setTime(etime);
    ui->edit_content->setText(content);
    ui->cmb_urgency->setCurrentText(urgency);
    ui->cmb_category->setCurrentText(category);
    return true;
}

void AddAffairDialog::setIsUpateDlg(bool isUpateDlg)
{
    m_isUpateDlg = isUpateDlg;
}

void AddAffairDialog::on_btn_confirm_clicked()
{
    int id = NULL;
    QString startTime = ui->edit_startTime->text();
    QString endTime = ui->edit_endTime->text();
    QString content = ui->edit_content->text();
    QString urgency = ui->cmb_urgency->currentText();
    QString category = ui->cmb_category->currentText();
    Affair aff;
    aff.setData(id,startTime,endTime,content,urgency,category);

    if(m_isUpateDlg)
    {
        emit sig_updateAffair(aff);
    }
    else
    {
        emit sig_addAffair(aff);
        clearData();
    }
    this->close();
}


void AddAffairDialog::on_btn_cancel_clicked()
{
    this->close();
}

void AddAffairDialog::initUI()
{
    //设置窗口标题
    this->setWindowTitle("add and update");

    ui->cmb_urgency->addItem("very urgent");
    ui->cmb_urgency->addItem("urgent");
    ui->cmb_urgency->addItem("not urgent");
    ui->cmb_urgency->addItem("unknown");

    ui->cmb_category->addItem("study");
    ui->cmb_category->addItem("work");
    ui->cmb_category->addItem("life");
}



