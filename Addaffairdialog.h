#ifndef ADDAFFAIRDIALOG_H
#define ADDAFFAIRDIALOG_H

#include "Affair.h"

#include <QDialog>

namespace Ui {
class AddAffairDialog;
}

class AddAffairDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAffairDialog(QWidget *parent = nullptr);
    ~AddAffairDialog();

    bool clearData();

    bool display(int id, QString startTime, QString endTime, QString content, QString urgency, QString category);

    void setIsUpateDlg(bool isUpateDlg);


signals:
    void sig_addAffair(Affair &aff);
    void sig_updateAffair(Affair &aff);


private slots:
    void on_btn_confirm_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::AddAffairDialog *ui;
    bool m_isUpateDlg; //是否是修改窗口 true: 修改  false:添加窗口

    void initUI();
};

#endif // ADDAFFAIRDIALOG_H
