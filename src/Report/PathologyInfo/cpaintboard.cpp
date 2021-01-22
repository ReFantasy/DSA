#include "cpaintboard.h"
#include "ui_cpaintboard.h"
#include "cwidgetpathologyinfo.h"

CPaintBoard::CPaintBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPaintBoard)
{
    ui->setupUi(this);
    ui->label->installEventFilter(this);

    m_wgtTip=new CWgtTip();
    m_wgtTip->setAttribute(Qt::WA_ShowModal, true);

    //将血管添加到哈希表中
    m_hashColorBalance.insert(QString("128,0,128"),QString("第一钝缘支"));
    m_hashColorBalance.insert(QString("192,0,192"),QString("第二钝缘支"));
    m_hashColorBalance.insert(QString("224,0,224"),QString("第三钝缘支"));
    m_hashColorBalance.insert(QString("224,0,96"),QString("第一左左室后支"));
    m_hashColorBalance.insert(QString("224,128,160"),QString("第二左左室后支"));
    m_hashColorBalance.insert(QString("224,64,128"),QString("第三左左室后支"));
    m_hashColorBalance.insert(QString("0,192,128"),QString("左后降支"));
    m_hashColorBalance.insert(QString("64,64,64"),QString("中间支"));
    m_hashColorBalance.insert(QString("96,0,64"),QString("第一间隔支"));
    m_hashColorBalance.insert(QString("224,0,128"),QString("第二间隔支"));
    m_hashColorBalance.insert(QString("224,64,192"),QString("第三间隔支"));
    m_hashColorBalance.insert(QString("224,128,224"),QString("第四间隔支"));
    m_hashColorBalance.insert(QString("128,128,128"),QString("第一对角支"));
    m_hashColorBalance.insert(QString("160,164,160"),QString("第二对角支"));
    m_hashColorBalance.insert(QString("192,192,192"),QString("第三对角支"));
    m_hashColorBalance.insert(QString("96,128,128"),QString("左前降支"));
    m_hashColorBalance.insert(QString("192,64,0"),QString("第一锐缘支"));
    m_hashColorBalance.insert(QString("192,64,0"),QString("第一锐缘支"));
    m_hashColorBalance.insert(QString("192,64,0"),QString("第一锐缘支"));



}

CPaintBoard::~CPaintBoard()
{
    delete ui;
    delete m_imgHash;

    delete m_wgtTip;
}


void CPaintBoard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bLIsPressed = true;
        // 一条线段的开始，因此这里构建新对象
        vector<QPoint> vLine;
        vLine.push_back(event->pos());
        m_vLines.push_back(vLine);//将新线条添加到线条集合
    }
    else if(event->button() == Qt::RightButton)
    {
        //记录点击位置坐标  p为相对窗口坐标 p1为lable的坐标 p-p1为在图片中的坐标
        QPoint ptEvent = event->pos();
        QPoint ptLabel = ui->label->pos();

        double dRadioW=(double)m_imgHash->size().width()/ui->label->width();
        double dRadioH=(double)m_imgHash->size().height()/ui->label->height();

        //计算变换后的坐标
        int nNewX = (ptEvent.x()-ptLabel.x())*dRadioW;
        int nNewY = (ptEvent.y()-ptLabel.y())*dRadioH;

        QColor color = m_imgHash->pixelColor(nNewX,nNewY);
        QString sColor  = tr("%1,%2,%3").arg(color.red()).arg(color.blue()).arg(color.green());
        this->m_sCurrVessel=sColor;

        //打开新窗口 把对应的血管名填进去
        // 这里得判断改血管位置是否存在标签
        if(m_hashColorBalance.count(sColor))
        {
            // 打开标签编辑框
            m_wgtTip->show();

            // 没有标签
            if(IsExistTip(this->m_sCurrVessel)==NULL)
            {
                QLabel* lblTip = new QLabel(this);
                m_lstTip.append(lblTip);
                lblTip->setStyleSheet("QLabel{background-color:rgb(0,120,220);color:white}");
                lblTip->setText(m_hashColorBalance[sColor]);
                lblTip->adjustSize();
                lblTip->move(ptEvent);
                lblTip->show();
            }
        }

        if(IsExistTip(this->m_sCurrVessel)!=NULL)
        {
            m_wgtTip->SetVesselLabel(IsExistTip(this->m_sCurrVessel));
            m_wgtTip->SetVesselName(m_hashColorBalance[sColor]);
        }
    }
}

void CPaintBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bLIsPressed=false;
        // 线条当前结束
        m_vLines[m_vLines.size()-1].push_back(event->pos());
    }
}

void CPaintBoard::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bLIsPressed)
    {
        if(m_vLines.size()<=0) return;
        m_vLines[m_vLines.size()-1].push_back(event->pos());

        auto aWindow=this->size();
        update();
    }
}

bool CPaintBoard::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->label && event->type()==QEvent::Paint)
    {
        labelPaintEvent();
    }
    return QWidget::eventFilter(obj,event);
}

void CPaintBoard::labelPaintEvent()
{
    QPainter Painter(ui->label);
    QPen Pen;
    Pen.setColor(Qt::black);
    Pen.setWidth(3);
    Painter.setPen(Pen);
    Painter.setBrush(QBrush(Qt::black));

    // 线条的个数
    for (int i=0;i<m_vLines.size();i++)
    {
        const vector<QPoint>&vLine = m_vLines[i];//取出一条线条
        if(vLine.size()>2)
        {
            // 起点、终点半径
            int nR=4;
            // 绘制起点
            Painter.drawEllipse(vLine[0], nR, nR);
            for(int j=0; j<vLine.size()-1; j++)//将线条的所有线段描绘出
            {
                Painter.drawLine(vLine.at(j), vLine[j+1]);
            }
            // 绘制终点
            Painter.drawEllipse(vLine[vLine.size()-1], nR, nR);
        }
    }
}

/**
 * @brief CPaintBoard::SetVesselTree
 * @param pType
 */
void CPaintBoard::SetVesselTree(int pType)
{
    m_wgtTip->SetVesselType(pType);

    ui->label->clear();

    m_imgHash=new QImage;

    if(pType==CWidgetPathologyInfo::Right)
    {
        ui->label->setStyleSheet("border-image:url(:/VesselTree/Right.bmp)");
        m_imgHash->load(":/VesselTree/AARight.bmp");
    }
    else if(pType==CWidgetPathologyInfo::Left)
    {
        ui->label->setStyleSheet("border-image:url(:/VesselTree/Left.bmp)");
        m_imgHash->load(":/VesselTree/AALeft.bmp");
    }
    else if(pType==CWidgetPathologyInfo::Balance)
    {
        ui->label->setStyleSheet("border-image:url(:/VesselTree/Balance.bmp)");
        m_imgHash->load(":/VesselTree/AABalance.bmp");
    }
}

void CPaintBoard::on_m_btnCleanTip_clicked()
{
    for(int i=0;i<m_lstTip.size();i++)
    {
        m_lstTip[i]->clear();
        delete m_lstTip[i];
        m_lstTip[i]=NULL;
    }
    m_lstTip.clear();
}

///**
// * @brief CPaintBoard::UpdateTipSlot
// * @param pInfo
// */
//void CPaintBoard::UpdateTipSlot(QString pInfo)
//{
//    auto aCurrTip=IsExistTip(this->m_sCurrVessel);
//    if(aCurrTip!=NULL)
//    {
//        aCurrTip->setText(pInfo);
//    }
//}

/**
 * @brief CPaintBoard::IsExistTip
 * @param pColor
 */
QLabel * CPaintBoard::IsExistTip(QString pColor)
{
    QLabel *lblCurrTip=NULL;
    // 遍历所有标签
    for(int i=0;i<m_lstTip.size();i++)
    {
        QPoint ptTipPos=m_lstTip[i]->pos();

        double dRadioW=(double)m_imgHash->size().width()/ui->label->width();
        double dRadioH=(double)m_imgHash->size().height()/ui->label->height();
        QPoint ptLabel = ui->label->pos();
        //计算变换后的坐标
        int nNewX = (ptTipPos.x()-ptLabel.x())*dRadioW;
        int nNewY = (ptTipPos.y()-ptLabel.y())*dRadioH;

        QColor color = m_imgHash->pixelColor(nNewX,nNewY);
        QString sColor  = tr("%1,%2,%3").arg(color.red()).arg(color.blue()).arg(color.green());
        if(sColor==pColor)
        {
            lblCurrTip=m_lstTip[i];
            break;
        }
    }
    return lblCurrTip;
}

/**
 * @brief 撤销上次搭桥
 */
void CPaintBoard::on_m_btnCancelQ_clicked()
{
    if(m_vLines.size()>0)
    {
    this->m_vLines.pop_back();
    update();
    }
}

/**
 * @brief 清空所有搭桥
 */
void CPaintBoard::on_m_btnCleanQ_clicked()
{
    if(m_vLines.size()>0)
    {
        this->m_vLines.clear();
        update();
    }
}

void CPaintBoard::on_m_btnCancelTip_clicked()
{
    if(m_lstTip.size()>0)
    {
        this->m_lstTip[m_lstTip.size()-1]->clear();
        delete m_lstTip[m_lstTip.size()-1];
        m_lstTip[m_lstTip.size()-1]=NULL;
        this->m_lstTip.pop_back();
    }
}
