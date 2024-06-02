#ifndef AFFAIRWIDGET_H
#define AFFAIRWIDGET_H

#include "Mydatabase.h"
#include "Addaffairdialog.h"

#include <QWidget>
#include <QStandardItemModel>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class AffairWidget; }
QT_END_NAMESPACE

const int CONST_COLUMN_SIZE = 6;     //表的列数
const int CONST_COL_ID = 0;           //id列
const int CONST_COL_startTime = 1;         //startTime列
const int CONST_COL_endTime = 2;          //endTime列
const int CONST_COL_content = 3;        //content列
const int CONST_COL_urgency = 4;         //urgency列
const int CONST_COL_category = 5;          //category列



class AffairWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AffairWidget(QWidget *parent = nullptr);
    ~AffairWidget();

    bool appendToModel(Affair &schedule);



private slots:
    void on_btn_add_clicked();

    void on_btn_delete_clicked();

    void on_btn_finish_clicked();

    void on_btn_update_clicked();

    void on_selectAll_clicked(bool checked);

    bool slot_addAffair(Affair &schedule);

    bool slot_actUpdate();

    bool slot_actDelete();

    bool slot_updateAffair(Affair &schedule);

    bool slot_itemChanged(QStandardItem *item);

    bool slot_popMenu(const QPoint &pos);


private:
    void initUI();
private:
    Ui::AffairWidget *ui;
    MyDatabase  *m_dataSource;  //数据源
    QStandardItemModel *m_standardModel; //model
    AddAffairDialog *m_addAffair;  //添加学生信息窗口
    QMenu *m_menu;  //菜单
    QAction *m_actUpdate; //修改菜单项
    QAction *m_actDelete; //删除菜单项

};

#endif // AFFAIRWIDGET_H
