#include "Affairwidget.h"
#include "ui_Affairwidget.h"
#include "Addaffairdialog.h"

#include <QMessageBox>
#include <QDebug>

AffairWidget::AffairWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AffairWidget)
    , m_dataSource(NULL)
    , m_standardModel(NULL)
    , m_addAffair(NULL)
    , m_menu(NULL)
    , m_actUpdate(NULL)
    , m_actDelete(NULL)
{
    ui->setupUi(this);
    qRegisterMetaType<Affair>("Affair");
    qRegisterMetaType<Affair>("Affair&");


    //实例化数据源
    m_dataSource = new MyDatabase();
    //    m_dataSource = new CDataSourceJSON();

    m_addAffair = new AddAffairDialog(this);


    //关联槽函数
    connect(m_addAffair,&AddAffairDialog::sig_addAffair,this,&AffairWidget::slot_addAffair);
    connect(m_addAffair,&AddAffairDialog::sig_updateAffair,this,&AffairWidget::slot_updateAffair);

    //初始化界面
    initUI();
}

AffairWidget::~AffairWidget()
{
    delete m_dataSource;
    delete ui;
}

bool AffairWidget::appendToModel(Affair &schedule)
{
    QStandardItem *itemId = new QStandardItem(QString("%1").arg(schedule.id(),4,10,QLatin1Char('0')));
    itemId->setCheckable(true); //添加复选框
    itemId->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemStartTime = new QStandardItem(schedule.startTime());
    itemStartTime->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemEndTime = new QStandardItem(schedule.endTime());
    itemEndTime->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemContent = new QStandardItem(schedule.content());
    itemContent->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemUrgency = new QStandardItem(schedule.urgency());
    itemUrgency->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QStandardItem *itemCategory = new QStandardItem(schedule.category());
    itemCategory->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QList<QStandardItem*> rowItem;
    rowItem.append(itemId);
    rowItem.append(itemStartTime);
    rowItem.append(itemEndTime);
    rowItem.append(itemContent);
    rowItem.append(itemUrgency);
    rowItem.append(itemCategory);

    m_standardModel->appendRow(rowItem);
    return true;
}

void AffairWidget::initUI()
{
    //实例化model
    m_standardModel = new QStandardItemModel(this);
    //实例化菜单以及菜单项
    m_menu = new QMenu(this);
    m_actUpdate = new QAction("修改",m_menu);
    m_actDelete = new QAction("删除",m_menu);
    m_menu->addAction(m_actUpdate);
    m_menu->addAction(m_actDelete);

    //设置tableView 菜单策略 customContextMenuRequested(const QPoint &pos)
    ui->table_affair->setContextMenuPolicy(Qt::CustomContextMenu);
    //关联槽函数
    connect(m_standardModel,&QStandardItemModel::itemChanged,this,&AffairWidget::slot_itemChanged); //勾选复选框槽函数
    connect(ui->table_affair,&QTableView::customContextMenuRequested,this,&AffairWidget::slot_popMenu); //弹出菜单槽函数
    connect(m_actUpdate,&QAction::triggered,this,&AffairWidget::slot_actUpdate); //修改项槽函数
    connect(m_actDelete,&QAction::triggered,this,&AffairWidget::slot_actDelete); //删除项槽函数



    //查询数据
    QList<Affair> scheduleList;
    bool res = m_dataSource->selectAffair(scheduleList);
    if(!res)
    {
        QMessageBox::information(this,"提示","查询学生信息失败");
        return;
    }
    qDebug() << scheduleList.size();
    for(int i=0;i<scheduleList.size();++i)
    {
        appendToModel(scheduleList[i]);
    }
    //添加表头
    QStringList headerList;
    headerList<<"id"<<"startTime"<<"endTime"<<"content"<<"urgency"<<"category";
    m_standardModel->setHorizontalHeaderLabels(headerList);

    ui->table_affair->verticalHeader()->setVisible(false); //隐藏垂直表头
    ui->table_affair->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_affair->setModel(m_standardModel);
    for (int col=0;col<CONST_COLUMN_SIZE;++col) {
        ui->table_affair->setColumnWidth(col,(width()-28)/6);
    }

}


void AffairWidget::on_btn_add_clicked()
{
    m_addAffair->setIsUpateDlg(false);
    m_addAffair->show();
}

bool AffairWidget::slot_addAffair(Affair &schdule)
{
    bool res = m_dataSource->addAffair(schdule);
    if(!res)
    {
        QMessageBox::information(this,"提示","插入失败！！！");
        return false;
    }
    appendToModel(schdule);
    return true;
}

bool AffairWidget::slot_updateAffair(Affair &schdule)
{
    int res = m_dataSource->updateAffair(schdule);
    if(!res)
    {
        QMessageBox::information(this,"提示","修改失败！！！");
        return false;
    }
    int row = ui->table_affair->currentIndex().row();
    m_standardModel->setData(m_standardModel->item(row,CONST_COL_startTime)->index(),schdule.startTime());
    m_standardModel->setData(m_standardModel->item(row,CONST_COL_endTime)->index(),schdule.endTime());
    m_standardModel->setData(m_standardModel->item(row,CONST_COL_content)->index(),schdule.content());
    m_standardModel->setData(m_standardModel->item(row,CONST_COL_urgency)->index(),schdule.urgency());
    m_standardModel->setData(m_standardModel->item(row,CONST_COL_category)->index(),schdule.category());

    QMessageBox::information(this,"提示","修改成功！！！");
    return true;
}

bool AffairWidget::slot_itemChanged(QStandardItem *item)
{
    if(m_standardModel->indexFromItem(item).column()>0) return false;
    for(int row = 0;row<m_standardModel->rowCount();++row)
    {
        if(m_standardModel->item(row)->checkState()!=Qt::Checked)
        {
            ui->selectAll->setChecked(false);
            return false;
        }

    }
    ui->selectAll->setChecked(true);
    return true;
}

bool AffairWidget::slot_popMenu(const QPoint &pos)
{
    if(m_standardModel->itemFromIndex(ui->table_affair->indexAt(pos))!=NULL)
        m_menu->exec(QCursor::pos());
    return true;
}

void AffairWidget::on_selectAll_clicked(bool checked)
{
    for(int row = 0;row<m_standardModel->rowCount();++row)
    {
        if(checked)
            m_standardModel->item(row)->setCheckState(Qt::Checked);
        else
            m_standardModel->item(row)->setCheckState(Qt::Unchecked);
    }
}

bool AffairWidget::slot_actUpdate()
{
    m_addAffair->setIsUpateDlg(true); //设置修改标识
    int row = ui->table_affair->currentIndex().row();
    int id = m_standardModel->item(row,CONST_COL_ID)->text().toInt();
    QString startTime = m_standardModel->item(row,CONST_COL_startTime)->text();
    QString endTime = m_standardModel->item(row,CONST_COL_endTime)->text();
    QString content = m_standardModel->item(row,CONST_COL_content)->text();
    QString urgency = m_standardModel->item(row,CONST_COL_urgency)->text();
    QString category = m_standardModel->item(row,CONST_COL_category)->text();
    m_addAffair->display(id,startTime,endTime,content,urgency,category);
    m_addAffair->show();
    return true;
}

bool AffairWidget::slot_actDelete()
{
    int row =  ui->table_affair->currentIndex().row();
    int id = m_standardModel->item(row)->text().toInt();
    m_dataSource->deleteAffair(id);
    m_standardModel->removeRow(row);
    return true;
}

void AffairWidget::on_btn_delete_clicked()
{
    QMap<int,QStandardItem*> delRowsMap;  //待删除的行
    for(int row = 0;row<m_standardModel->rowCount();++row)
    {
        QStandardItem *item = m_standardModel->item(row);
        if(item->checkState() == Qt::Checked)
        {
            delRowsMap.insert(row,item);
        }
    }

    if(delRowsMap.size()<1)
        return;

    //弹出删除提示
    int res = QMessageBox::information(this,"提示","是否真的要删除",QMessageBox::Yes|QMessageBox::No);
    if(res == QMessageBox::No) return;

    QList<int> keyList = delRowsMap.keys();
    //1.删除数据库中的数据
    for(int key=keyList.size()-1;key>=0;--key)
    {
        if(m_dataSource->deleteAffair(delRowsMap.value(keyList[key])->text().toInt()))
        {
            //2.删除窗口中的数据
            m_standardModel->removeRow(keyList[key]);
        }
    }


}
