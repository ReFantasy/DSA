#include "cwidgetadditionalinfo.h"
#include "ui_cwidgetadditionalinfo.h"
#include <QHash>
#include <QString>
#include <functional>
#include <QSqlTableModel>

const QString headNameBool_PCI_ZBB_T[] = {"gxy","gxz","sgnxj","fqjss" ,"PCI","CABG","wwxgjb","mxfb","tnb","txzl","xjgs","xlsj","jqxys","gxbjzs","nxgjb","xlsj","xjgs"};
const QString headNameBool_PCI_ZBB_FB1_T[] = {"USEIVUS","USEFFR","szbfz","USESpecail"};
const QString nameOfComboBox_1[] = {"bbtd","sqxzcd","timi","dssftgbb","bbcyxz","shtimi"};
const QString nameOfTextEdit_1[] = {"dsgc","dsjk","qngc","qnjk"};
const std::vector<QString> nameOfMedicalUse = {"强生","波士顿","美敦力","雅培","贝朗","吉威","乐普","微创","垠艺","福基阳光","其他"};


void CWidgetAdditionalInfo::SetSysCaseId(const QString pSysCaseId)
{
    this->m_CaseID = pSysCaseId;
    this->m_sSysCaseID=pSysCaseId;

    this->SetSqDB();
}

void CWidgetAdditionalInfo::UpdateUIFromDatabase()
{

}

void CWidgetAdditionalInfo::UpdateDatabaseFromUI()
{
    // 先清空所有记录
    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());

    // 更新信息
    QString sSqlJWBS="update PCI_ZBB_T set gxy='"+this->GetJWBS().sGXY+"'"
            ",wzxgjb='"+this->GetJWBS().sWZXGJB+"',txzl='"+this->GetJWBS().sTXZL+"',"
            "jqxys='"+this->GetJWBS().sJQXYS+"',gxz='"+this->GetJWBS().sGXZ+"',"
            "mxfb='"+this->GetJWBS().sMXFB+"',xjgs='"+this->GetJWBS().sXJGS+"',"
            "gxbjzs='"+this->GetJWBS().sGXBJZS+"',sgnsj='"+this->GetJWBS().sSGNSJ+"',"
            "tnb='"+this->GetJWBS().sTNB+"',xlsj='"+this->GetJWBS().sXLSJ+"',"
            "nxgjb='"+this->GetJWBS().sNXGJB+"',bmsss='"+this->GetJWBS().sBMSSS+"',"
            "bmsssrq='"+this->GetJWBS().sBMSSRQ+"',pcis='"+this->GetJWBS().sPCIS+"',"
            "pcisrq='"+this->GetJWBS().sPCIRQ+"',cabgs='"+this->GetJWBS().sCABGS+"',"
            "cabgsrq='"+this->GetJWBS().sCABGRQ+"',tbr='"+this->GetJWBS().sWriter+"',"
            "tbrq='"+this->GetJWBS().sWriteDate+"' where SysCaseID ='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJWBS);


    for(int i=0;i<m_lstVessel.size();i++)
    {
        CWgtTargetVessel *TargetVessel=m_lstVessel[i];

        QString sVesselName=m_lstTargetVessel[i].sXGMC;

        QString sSqlVessel="update PCI_ZBB_FB1_T set USEIVUS='"+TargetVessel->GetTagetVessel().sXGNCS+"'"
                 ",IVUS_val1='"+TargetVessel->GetTagetVessel().sMJXZ+"',IVUS_val2='"+TargetVessel->GetTagetVessel().sZXGQ+"',"
                 "USEFFR='"+TargetVessel->GetTagetVessel().sXLCBFS+"',SZBFZ='"+TargetVessel->GetTagetVessel().sSZBFZ+"',"
                 "USESpecail='"+TargetVessel->GetTagetVessel().sTSQC+"' where SysCaseID ='"+m_sSysCaseID+"' and xgmc='"+sVesselName+"'";
        sqlReport->exec(sSqlVessel);
    }


    QString sSqlJrqInfo="delete from BBB_JRQ where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrqInfo);
    QString sSqlJrhInfo="delete from BBB_JRH where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrhInfo);

    QString sSqlJrqOCT="delete from BBB_JRQ_OCT where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrqOCT);
    QString sSqlJrqIVUS="delete from BBB_JRQ_IVUS where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrqIVUS);
    QString sSqlJrqQCA="delete from BBB_JRQ_QCA where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrqQCA);

    QString sSqlJrhOCT="delete from BBB_JRH_OCT where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrhOCT);
    QString sSqlJrhIVUS="delete from BBB_JRH_IVUS where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrhIVUS);
    QString sSqlJrhQCA="delete from BBB_JRH_QCA where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJrhQCA);

    for(int i=0;i<ui->m_tabBBB->count();i++)
    {
        CWgtTargetPathology *CurrPathology=m_lstPathology[i];

        sSqlJrqInfo="insert into BBB_JRQ(bbwz,bbfw,bbxt,bbsfcj,bbwx,gh,timi,sfwqbs,bbtd,bblx,jdxgwqd,"
                    "mcczxgzj,mcbbbcd,mcsqzxgqzj,mcxzcd,qca,ivus,oct,ffr,szbfz,SysCaseID"
                    ") values('"+CurrPathology->GetJrqInfo().sBBWZ+"','"+CurrPathology->GetJrqInfo().sBBFW+"',"
                    "'"+CurrPathology->GetJrqInfo().sBBXT+"','"+CurrPathology->GetJrqInfo().sBBCJ+"',"
                    "'"+CurrPathology->GetJrqInfo().sBBWX+"','"+CurrPathology->GetJrqInfo().sGH+"',"
                    "'"+CurrPathology->GetJrqInfo().sTIMI+"','"+CurrPathology->GetJrqInfo().sWQBS+"',"
                    "'"+CurrPathology->GetJrqInfo().sBBTD+"','"+CurrPathology->GetJrqInfo().sBBLX+"',"
                    "'"+CurrPathology->GetJrqInfo().sJDXGWQ+"','"+CurrPathology->GetJrqInfo().sSQMCXGZJ+"',"
                    "'"+CurrPathology->GetJrqInfo().sSQMCBBBCD+"','"+CurrPathology->GetJrqInfo().sSQMCZXGQ+"',"
                    "'"+CurrPathology->GetJrqInfo().sSQMCXZCD+"','"+CurrPathology->GetJrqInfo().sSQQCA+"',"
                    "'"+CurrPathology->GetJrqInfo().sSQIVUS+"','"+CurrPathology->GetJrqInfo().sSQOCT+"',"
                    "'"+CurrPathology->GetJrqInfo().sSQFFR+"','"+CurrPathology->GetJrqInfo().sSZBFZ+"',"
                    "'"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrqInfo);

        sSqlJrhInfo="insert into BBB_JRH(mcczxgzj,shxzcd,shzxgqzj,qca,ivus,oct,ffr,bbwz,SysCaseID"
                    ") values('"+CurrPathology->GetJrhInfo().sSHMCXGZJ+"','"+CurrPathology->GetJrhInfo().sSHMCXZCD+"',"
                    "'"+CurrPathology->GetJrhInfo().sSHMCZXGQ+"','"+CurrPathology->GetJrhInfo().sSHQCA+"',"
                    "'"+CurrPathology->GetJrhInfo().sSHIVUS+"','"+CurrPathology->GetJrhInfo().sSHOCT+"',"
                    "'"+CurrPathology->GetJrhInfo().sSHFFR+"','"+CurrPathology->GetJrhInfo().sBBWZ+"',"
                    "'"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrhInfo);

        QString sCurrBBWZ=CurrPathology->GetJrqInfo().sBBWZ;

        sSqlJrqOCT="insert into BBB_JRQ_OCT(eemcsa,eemdmax,eemdmin,stentcsa,stentdmax,stentdmin,lumencsa,lumendmax,lumendmin,bbwz,SysCaseID"
                   ") values('"+CurrPathology->GetSqOCT().sEEM_CSA+"','"+CurrPathology->GetSqOCT().sEEM_Dmax+"',"
                    "'"+CurrPathology->GetSqOCT().sEEM_Dmin+"','"+CurrPathology->GetSqOCT().sStent_CSA+"',"
                    "'"+CurrPathology->GetSqOCT().sStent_Dmax+"','"+CurrPathology->GetSqOCT().sStent_Dmin+"',"
                    "'"+CurrPathology->GetSqOCT().sLumen_CSA+"','"+CurrPathology->GetSqOCT().sLumen_Dmax+"',"
                    "'"+CurrPathology->GetSqOCT().sLumen_Dmin+"','"+sCurrBBWZ+"',"
                    "'"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrqOCT);

        sSqlJrqIVUS="insert into BBB_JRQ_IVUS(eemcsa,eemdmax,eemdmin,stentcsa,stentdmax,stentdmin,lumencsa,lumendmax,lumendmin,bbwz,SysCaseID"
                    ") values('"+CurrPathology->GetSqIVUS().sEEM_CSA+"','"+CurrPathology->GetSqIVUS().sEEM_Dmax+"',"
                     "'"+CurrPathology->GetSqIVUS().sEEM_Dmin+"','"+CurrPathology->GetSqIVUS().sStent_CSA+"',"
                     "'"+CurrPathology->GetSqIVUS().sStent_Dmax+"','"+CurrPathology->GetSqIVUS().sStent_Dmin+"',"
                     "'"+CurrPathology->GetSqIVUS().sLumen_CSA+"','"+CurrPathology->GetSqIVUS().sLumen_Dmax+"',"
                     "'"+CurrPathology->GetSqIVUS().sLumen_Dmin+"','"+sCurrBBWZ+"',"
                     "'"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrqIVUS);

        sSqlJrqQCA="insert into BBB_JRQ_QCA(czxgzj,sqbbcd,sqxzcd,sqzxgqzj,qnyclhxzcd,qnyclhzxgqzj,bbwz,SysCaseID"
                   ") values('"+CurrPathology->GetSqQCA().sCZXGZJ+"','"+CurrPathology->GetSqQCA().sBBCD+"',"
                   "'"+CurrPathology->GetSqQCA().sXZCD+"','"+CurrPathology->GetSqQCA().sZXGQZJ+"',"
                   "'"+CurrPathology->GetSqQCA().sQNCLXZCD+"','"+CurrPathology->GetSqQCA().sQNCLZXGQ+"',"
                   "'"+sCurrBBWZ+"','"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrqQCA);

        sSqlJrhOCT="insert into BBB_JRH_OCT(eemcsa,eemdmax,eemdmin,stentcsa,stentdmax,stentdmin,lumencsa,lumendmax,lumendmin,bbwz,SysCaseID"
                   ") values('"+CurrPathology->GetShOCT().sEEM_CSA+"','"+CurrPathology->GetShOCT().sEEM_Dmax+"',"
                    "'"+CurrPathology->GetShOCT().sEEM_Dmin+"','"+CurrPathology->GetShOCT().sStent_CSA+"',"
                    "'"+CurrPathology->GetShOCT().sStent_Dmax+"','"+CurrPathology->GetShOCT().sStent_Dmin+"',"
                    "'"+CurrPathology->GetShOCT().sLumen_CSA+"','"+CurrPathology->GetShOCT().sLumen_Dmax+"',"
                    "'"+CurrPathology->GetShOCT().sLumen_Dmin+"','"+sCurrBBWZ+"',"
                    "'"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrhOCT);
        sSqlJrhIVUS="insert into BBB_JRH_IVUS(eemcsa,eemdmax,eemdmin,stentcsa,stentdmax,stentdmin,lumencsa,lumendmax,lumendmin,bbwz,SysCaseID"
                    ") values('"+CurrPathology->GetShIVUS().sEEM_CSA+"','"+CurrPathology->GetShIVUS().sEEM_Dmax+"',"
                    "'"+CurrPathology->GetShIVUS().sEEM_Dmin+"','"+CurrPathology->GetShIVUS().sStent_CSA+"',"
                    "'"+CurrPathology->GetShIVUS().sStent_Dmax+"','"+CurrPathology->GetShIVUS().sStent_Dmin+"',"
                    "'"+CurrPathology->GetShIVUS().sLumen_CSA+"','"+CurrPathology->GetShIVUS().sLumen_Dmax+"',"
                    "'"+CurrPathology->GetShIVUS().sLumen_Dmin+"','"+sCurrBBWZ+"',"
                    "'"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrhIVUS);
        sSqlJrhQCA="insert into BBB_JRH_QCA(shczxgzj,zjnshxzcd,bbnshxzcd,zjnzxgqzj,bbnzxgqzj,qnyclhzxgqzj,qnyclhxzcd,zjzcd,zjcdcd,bbwz,SysCaseID"
                   ") values('"+CurrPathology->GetShQCA().sCZXGZJ+"','"+CurrPathology->GetShQCA().sZJCYXZ+"',"
                   "'"+CurrPathology->GetShQCA().sBBCYXZ+"','"+CurrPathology->GetShQCA().sZJZXGQ+"',"
                   "'"+CurrPathology->GetShQCA().sBBZXGQZJ+"','"+CurrPathology->GetShQCA().sQNZXGQZJ+"',"
                   "'"+CurrPathology->GetShQCA().sQNCLXZCD+"','"+CurrPathology->GetShQCA().sZJZCD+"',"
                   "'"+CurrPathology->GetShQCA().sZJCDCD+"','"+sCurrBBWZ+"',"
                   "'"+m_sSysCaseID+"')";
        sqlReport->exec(sSqlJrhQCA);
    }
}

CWidgetAdditionalInfo::CWidgetAdditionalInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CWidgetAdditionalInfo)
{
    ui->setupUi(this);
    for(auto& e:this->findChildren<QRadioButton *>()){
        e->setAutoExclusive(true);
        e->setChecked(true);
    }
}

CWidgetAdditionalInfo::~CWidgetAdditionalInfo()
{
    delete ui;
}

void CWidgetAdditionalInfo::SetSqDB()
{

    QSqlQuery *sqlReport=new QSqlQuery(SQLDB::GetDfytCathLab());


    /******** 初始化既往病史 ********/
    QString sSqlJWBS="select gxy,wzxgjb,txzl,jqxys,gxz,mxfb,xjgs,gxbjzs,sgnsj,tnb,xlsj,nxgjb,bmsss,bmsssrq,pcis,"
                     "pcisrq,cabgs,cabgsrq,tbr,tbrq from PCI_ZBB_T where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlJWBS);
    while (sqlReport->next())
    {
        m_JWBS.sGXY=sqlReport->value(0).toString();
        m_JWBS.sWZXGJB=sqlReport->value(1).toString();
        m_JWBS.sTXZL=sqlReport->value(2).toString();
        m_JWBS.sJQXYS=sqlReport->value(3).toString();
        m_JWBS.sGXZ=sqlReport->value(4).toString();
        m_JWBS.sMXFB=sqlReport->value(5).toString();
        m_JWBS.sXJGS=sqlReport->value(6).toString();
        m_JWBS.sGXBJZS=sqlReport->value(7).toString();
        m_JWBS.sSGNSJ=sqlReport->value(8).toString();
        m_JWBS.sTNB=sqlReport->value(9).toString();
        m_JWBS.sXLSJ=sqlReport->value(10).toString();
        m_JWBS.sNXGJB=sqlReport->value(11).toString();
        m_JWBS.sBMSSS=sqlReport->value(12).toString();
        m_JWBS.sBMSSRQ=sqlReport->value(13).toDateTime().toString(csDateTimeStyle);
        m_JWBS.sPCIS=sqlReport->value(14).toString();
        m_JWBS.sPCIRQ=sqlReport->value(15).toDateTime().toString(csDateTimeStyle);
        m_JWBS.sCABGS=sqlReport->value(16).toString();
        m_JWBS.sCABGRQ=sqlReport->value(17).toDateTime().toString(csDateTimeStyle);
        m_JWBS.sWriter=sqlReport->value(18).toString();
        m_JWBS.sWriteDate=sqlReport->value(19).toDateTime().toString(csDateTimeStyle);
    }


    /******** 初始化靶血管 ********/
    QString sSqlBBG="select xgmc,sqxzcd,bbtd,timi,dssftgbb,bbcyxz,shtimi,USEIVUS,IVUS_val1,IVUS_val2,"
                    "USEFFR,SZBFZ,USESpecail from PCI_ZBB_FB1_T where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlBBG);
    m_lstTargetVessel.clear();
    while (sqlReport->next())
    {
        STargetVessel TagetVessel;
        TagetVessel.sXGMC=sqlReport->value(0).toString();
        TagetVessel.sSQXZCD=sqlReport->value(1).toString();
        TagetVessel.sBBTD=sqlReport->value(2).toString();
        TagetVessel.sSQTIMI=sqlReport->value(3).toString();
        TagetVessel.sDSTGBB=sqlReport->value(4).toString();
        TagetVessel.sBBCYXZ=sqlReport->value(5).toString();
        TagetVessel.sSHTIMI=sqlReport->value(6).toString();
        TagetVessel.sXGNCS=sqlReport->value(7).toString();
        TagetVessel.sMJXZ=sqlReport->value(8).toString();
        TagetVessel.sZXGQ=sqlReport->value(9).toString();
        TagetVessel.sXLCBFS=sqlReport->value(10).toString();
        TagetVessel.sSZBFZ=sqlReport->value(11).toString();
        TagetVessel.sTSQC=sqlReport->value(12).toString();
        m_lstTargetVessel.append(TagetVessel);
    }


    /******** 初始化器材使用 ********/
    QString sSqlTool="select xgmc,dsgc,dsjk,qngc,qnjk,zjgcdes,zjjkdes,zjgcbms,zjjkbms from PCI_ZBB_FB2_T where SysCaseID='"+m_sSysCaseID+"'";
    sqlReport->exec(sSqlTool);
    m_lstToolUse.clear();
    while (sqlReport->next())
    {
        SToolUse ToolUse;
        ToolUse.sXGMC=sqlReport->value(0).toString();
        ToolUse.sDSGC=sqlReport->value(1).toString();
        ToolUse.sDSJK=sqlReport->value(2).toString();
        ToolUse.sQNGC=sqlReport->value(3).toString();
        ToolUse.sQNJK=sqlReport->value(4).toString();
        ToolUse.sDESGC=sqlReport->value(5).toString();
        ToolUse.sDESJK=sqlReport->value(6).toString();
        ToolUse.sBMSGC=sqlReport->value(7).toString();
        ToolUse.sBMSJK=sqlReport->value(8).toString();
        m_lstToolUse.append(ToolUse);
    }




    QString sSqlNewBB="select BBB_JRQ.bbwz,BBB_JRQ.bbfw,BBB_JRQ.bbxt,BBB_JRQ.bbsfcj,BBB_JRQ.bbwx,BBB_JRQ.gh,BBB_JRQ.timi,"
                      "BBB_JRQ.sfwqbs,BBB_JRQ.bbtd,BBB_JRQ.bblx,BBB_JRQ.jdxgwqd,"
                      "BBB_JRQ.mcczxgzj,BBB_JRQ.mcbbbcd,BBB_JRQ.mcsqzxgqzj,BBB_JRQ.mcxzcd,"
                      "BBB_JRQ.qca,BBB_JRQ.ivus,BBB_JRQ.oct,BBB_JRQ.ffr,BBB_JRQ.szbfz,"
                      "BBB_JRH.mcczxgzj,BBB_JRH.shxzcd,BBB_JRH.shzxgqzj,BBB_JRH.qca,BBB_JRH.ivus,BBB_JRH.oct,BBB_JRH.ffr "
                      "from BBB_JRQ inner join BBB_JRH on BBB_JRQ.SysCaseID=BBB_JRH.SysCaseID "
                      "where BBB_JRQ.bbwz=BBB_JRH.bbwz and BBB_JRQ.SysCaseID='"+m_sSysCaseID+"'";
    qDebug()<<sSqlNewBB;
    sqlReport->exec(sSqlNewBB);
    m_lstJrqInfo.clear();
    m_lstJrhInfo.clear();
    while (sqlReport->next())
    {
        SJrqInfo JrqInfo;
        JrqInfo.sBBWZ=sqlReport->value(0).toString();
        JrqInfo.sBBFW=sqlReport->value(1).toString();
        JrqInfo.sBBXT=sqlReport->value(2).toString();
        JrqInfo.sBBCJ=sqlReport->value(3).toString();
        JrqInfo.sBBWX=sqlReport->value(4).toString();
        JrqInfo.sGH=sqlReport->value(5).toString();
        JrqInfo.sTIMI=sqlReport->value(6).toString();
        JrqInfo.sWQBS=sqlReport->value(7).toString();
        JrqInfo.sBBTD=sqlReport->value(8).toString();
        JrqInfo.sBBLX=sqlReport->value(9).toString();
        JrqInfo.sJDXGWQ=sqlReport->value(10).toString();

        JrqInfo.sSQMCXGZJ=sqlReport->value(11).toString();
        JrqInfo.sSQMCBBBCD=sqlReport->value(12).toString();
        JrqInfo.sSQMCZXGQ=sqlReport->value(13).toString();
        JrqInfo.sSQMCXZCD=sqlReport->value(14).toString();

        JrqInfo.sSQQCA=sqlReport->value(15).toString();
        JrqInfo.sSQIVUS=sqlReport->value(16).toString();
        JrqInfo.sSQOCT=sqlReport->value(17).toString();
        JrqInfo.sSQFFR=sqlReport->value(18).toString();
        JrqInfo.sSZBFZ=sqlReport->value(19).toString();

        SJrhInfo JrhInfo;
        JrhInfo.sSHMCXGZJ=sqlReport->value(20).toString();
        JrhInfo.sSHMCXZCD=sqlReport->value(21).toString();
        JrhInfo.sSHMCZXGQ=sqlReport->value(22).toString();
        JrhInfo.sSHQCA=sqlReport->value(23).toString();
        JrhInfo.sSHIVUS=sqlReport->value(24).toString();
        JrhInfo.sSHOCT=sqlReport->value(25).toString();
        JrhInfo.sSHFFR=sqlReport->value(26).toString();

        m_lstJrqInfo.append(JrqInfo);
        m_lstJrhInfo.append(JrhInfo);
    }

    int nNumberBB=m_lstJrqInfo.size();

    m_vSqOCT.clear();
    m_vSqIVUS.clear();
    m_vSqQCA.clear();
    m_vShOCT.clear();
    m_vShIVUS.clear();
    m_vShQCA.clear();
    m_vSqOCT.resize(nNumberBB);
    m_vSqIVUS.resize(nNumberBB);
    m_vSqQCA.resize(nNumberBB);
    m_vShOCT.resize(nNumberBB);
    m_vShIVUS.resize(nNumberBB);
    m_vShQCA.resize(nNumberBB);

    QString sSqlBBInfo="";
    for(int i=0;i<nNumberBB;i++)
    {
        QString sName=m_lstJrqInfo[i].sBBWZ;

        SOCT SqOCT={"","","","","","","","",""};
        sSqlBBInfo="select eemcsa,eemdmax,eemdmin,stentcsa,stentdmax,stentdmin,lumencsa,lumendmax,lumendmin "
                   "from BBB_JRQ_OCT where SysCaseID='"+m_sSysCaseID+"' and bbwz='"+sName+"'";
        sqlReport->exec(sSqlBBInfo);
        while (sqlReport->next())
        {
            SqOCT.sEEM_CSA=sqlReport->value(0).toString();
            SqOCT.sEEM_Dmax=sqlReport->value(1).toString();
            SqOCT.sEEM_Dmin=sqlReport->value(2).toString();

            SqOCT.sStent_CSA=sqlReport->value(3).toString();
            SqOCT.sStent_Dmax=sqlReport->value(4).toString();
            SqOCT.sStent_Dmin=sqlReport->value(5).toString();

            SqOCT.sLumen_CSA=sqlReport->value(6).toString();
            SqOCT.sLumen_Dmax=sqlReport->value(7).toString();
            SqOCT.sLumen_Dmin=sqlReport->value(8).toString();
        }
        m_vSqOCT[i]=SqOCT;

        SIVUS SqIVUS={"","","","","","","","",""};
        sSqlBBInfo="select eemcsa,eemdmax,eemdmin,stentcsa,stentdmin,stentdmax,lumencsa,lumendmin,lumendmax "
                   "from BBB_JRQ_IVUS where SysCaseID='"+m_sSysCaseID+"' and bbwz='"+sName+"'";
        sqlReport->exec(sSqlBBInfo);
        while (sqlReport->next())
        {
            SqIVUS.sEEM_CSA=sqlReport->value(0).toString();
            SqIVUS.sEEM_Dmax=sqlReport->value(1).toString();
            SqIVUS.sEEM_Dmin=sqlReport->value(2).toString();

            SqIVUS.sStent_CSA=sqlReport->value(3).toString();
            SqIVUS.sStent_Dmax=sqlReport->value(4).toString();
            SqIVUS.sStent_Dmin=sqlReport->value(5).toString();

            SqIVUS.sLumen_CSA=sqlReport->value(6).toString();
            SqIVUS.sLumen_Dmax=sqlReport->value(7).toString();
            SqIVUS.sLumen_Dmin=sqlReport->value(8).toString();
        }
        m_vSqIVUS[i]=SqIVUS;


        SSqQCA SqQCA={"","","","","",""};
        sSqlBBInfo="select czxgzj,sqbbcd,sqxzcd,sqzxgqzj,qnyclhxzcd,qnyclhzxgqzj "
                   "from BBB_JRQ_QCA where SysCaseID='"+m_sSysCaseID+"' and bbwz='"+sName+"'";
        sqlReport->exec(sSqlBBInfo);
        while (sqlReport->next())
        {
            SqQCA.sCZXGZJ=sqlReport->value(0).toString();
            SqQCA.sBBCD=sqlReport->value(1).toString();
            SqQCA.sXZCD=sqlReport->value(2).toString();

            SqQCA.sZXGQZJ=sqlReport->value(3).toString();
            SqQCA.sQNCLXZCD=sqlReport->value(4).toString();
            SqQCA.sQNCLZXGQ=sqlReport->value(5).toString();
        }
        m_vSqQCA[i]=SqQCA;



        SOCT ShOCT={"","","","","","","","",""};
        sSqlBBInfo="select eemcsa,eemdmax,eemdmin,stentcsa,stentdmax,stentdmin,lumencsa,lumendmax,lumendmin "
                   "from BBB_JRH_OCT where SysCaseID='"+m_sSysCaseID+"' and bbwz='"+sName+"'";
        sqlReport->exec(sSqlBBInfo);
        while (sqlReport->next())
        {
            ShOCT.sEEM_CSA=sqlReport->value(0).toString();
            ShOCT.sEEM_Dmax=sqlReport->value(1).toString();
            ShOCT.sEEM_Dmin=sqlReport->value(2).toString();

            ShOCT.sStent_CSA=sqlReport->value(3).toString();
            ShOCT.sStent_Dmax=sqlReport->value(4).toString();
            ShOCT.sStent_Dmin=sqlReport->value(5).toString();

            ShOCT.sLumen_CSA=sqlReport->value(6).toString();
            ShOCT.sLumen_Dmax=sqlReport->value(7).toString();
            ShOCT.sLumen_Dmin=sqlReport->value(8).toString();
        }
        m_vShOCT[i]=ShOCT;

        SIVUS ShIVUS={"","","","","","","","",""};
        sSqlBBInfo="select eemcsa,eemdmax,eemdmin,stentcsa,stentdmin,stentdmax,lumencsa,lumendmin,lumendmax "
                   "from BBB_JRH_IVUS where SysCaseID='"+m_sSysCaseID+"' and bbwz='"+sName+"'";
        sqlReport->exec(sSqlBBInfo);
        while (sqlReport->next())
        {
            ShIVUS.sEEM_CSA=sqlReport->value(0).toString();
            ShIVUS.sEEM_Dmax=sqlReport->value(1).toString();
            ShIVUS.sEEM_Dmin=sqlReport->value(2).toString();

            ShIVUS.sStent_CSA=sqlReport->value(3).toString();
            ShIVUS.sStent_Dmax=sqlReport->value(4).toString();
            ShIVUS.sStent_Dmin=sqlReport->value(5).toString();

            ShIVUS.sLumen_CSA=sqlReport->value(6).toString();
            ShIVUS.sLumen_Dmax=sqlReport->value(7).toString();
            ShIVUS.sLumen_Dmin=sqlReport->value(8).toString();
        }
        m_vShIVUS[i]=ShIVUS;


        SShQCA ShQCA={"","","","","","","","",""};
        sSqlBBInfo="select shczxgzj,zjnshxzcd,bbnshxzcd,zjnzxgqzj,bbnzxgqzj,qnyclhzxgqzj,qnyclhxzcd,zjzcd,zjcdcd "
                   "from BBB_JRH_QCA where SysCaseID='"+m_sSysCaseID+"' and bbwz='"+sName+"'";
        sqlReport->exec(sSqlBBInfo);
        while (sqlReport->next())
        {
            ShQCA.sCZXGZJ=sqlReport->value(0).toString();
            ShQCA.sZJCYXZ=sqlReport->value(1).toString();
            ShQCA.sBBCYXZ=sqlReport->value(2).toString();

            ShQCA.sZJZXGQ=sqlReport->value(3).toString();
            ShQCA.sBBZXGQZJ=sqlReport->value(4).toString();
            ShQCA.sQNZXGQZJ=sqlReport->value(5).toString();

            ShQCA.sQNCLXZCD=sqlReport->value(6).toString();
            ShQCA.sZJZCD=sqlReport->value(7).toString();
            ShQCA.sZJCDCD=sqlReport->value(8).toString();
        }
        m_vShQCA[i]=ShQCA;
    }

    delete sqlReport;
    sqlReport=NULL;

    // 更新UI页面
    this->UpdateShow();
}

/**
 * @brief CWidgetAdditionalInfo::UpdateShow
 */
void CWidgetAdditionalInfo::UpdateShow()
{
    // 初始化既往病史
    this->InitWidgetRadBtn(ui->m_wgtGXY,m_JWBS.sGXY);
    this->InitWidgetRadBtn(ui->m_wgtWZXGJB,m_JWBS.sWZXGJB);
    this->InitWidgetRadBtn(ui->m_wgtTXZL,m_JWBS.sTXZL);
    this->InitWidgetRadBtn(ui->m_wgtJQXYS,m_JWBS.sJQXYS);
    this->InitWidgetRadBtn(ui->m_wgtGXZ,m_JWBS.sGXZ);
    this->InitWidgetRadBtn(ui->m_wgtMXFB,m_JWBS.sMXFB);
    this->InitWidgetRadBtn(ui->m_wgtXJGS,m_JWBS.sXJGS);
    this->InitWidgetRadBtn(ui->m_wgtGXBJZS,m_JWBS.sGXBJZS);
    this->InitWidgetRadBtn(ui->m_wgtSGNSJ,m_JWBS.sSGNSJ);
    this->InitWidgetRadBtn(ui->m_wgtTNB,m_JWBS.sTNB);
    this->InitWidgetRadBtn(ui->m_wgtXLSJ,m_JWBS.sXLSJ);
    this->InitWidgetRadBtn(ui->m_wgtNXGJB,m_JWBS.sNXGJB);
    this->InitWidgetRadBtn(ui->m_wgtBMSSS,m_JWBS.sBMSSS);
    this->InitWidgetRadBtn(ui->m_wgtPCIS,m_JWBS.sPCIS);
    this->InitWidgetRadBtn(ui->m_wgtCABGS,m_JWBS.sCABGS);


    if(m_JWBS.sBMSSS=="否")
    {
        ui->m_wgtBMSSRQ->setEnabled(0);

    }
    else
    {
        ui->m_wgtBMSSRQ->setEnabled(1);
        ui->m_dtmBMSSRQ->setDateTime(QDateTime::fromString(m_JWBS.sBMSSRQ,csDateTimeStyle));
    }

    if(m_JWBS.sPCIS=="否")
    {
        ui->m_wgtPCIRQ->setEnabled(0);

    }
    else
    {
        ui->m_wgtPCIRQ->setEnabled(1);
        ui->m_dtmPCIRQ->setDateTime(QDateTime::fromString(m_JWBS.sPCIRQ,csDateTimeStyle));
    }


    if(m_JWBS.sCABGS=="否")
    {
        ui->m_wgtCABGRQ->setEnabled(0);

    }
    else
    {
        ui->m_wgtCABGRQ->setEnabled(1);
        ui->m_dtmCABGRQ->setDateTime(QDateTime::fromString(m_JWBS.sCABGRQ,csDateTimeStyle));
    }


    ui->m_dtmWrite->setDateTime(QDateTime::fromString(m_JWBS.sWriteDate,csDateTimeStyle));
    ui->m_lineWriter->setText(m_JWBS.sWriter);


    // 初始靶血管
    for(int i=0;i<m_lstTargetVessel.size();i++)
    {
        CWgtTargetVessel *wgtBXG=new CWgtTargetVessel(this);
        m_lstVessel.append(wgtBXG);
        wgtBXG->SetTagetVessel(m_lstTargetVessel[i]);
        ui->m_layoutBXG->addWidget(wgtBXG);
    }

    // 初始器材使用
    for(int i=0;i<m_lstToolUse.size();i++)
    {
        CWgtToolUse *wgtTool=new CWgtToolUse(this);
        wgtTool->SetTool(m_lstToolUse[i]);
        ui->m_layoutToolUse->addWidget(wgtTool);
    }



    // 初始靶病变
    for(int i=0;i<m_lstJrqInfo.size();i++)
    {

        CWgtTargetPathology *wgtTarget = new CWgtTargetPathology;
        m_lstPathology.append(wgtTarget);
        wgtTarget->SetNewPathology(m_lstJrqInfo[i],m_lstJrhInfo[i]);
        wgtTarget->SetSqOCT(m_vSqOCT[i]);
        wgtTarget->SetSqQCA(m_vSqQCA[i]);
        wgtTarget->SetSqIVUS(m_vSqIVUS[i]);

        wgtTarget->SetShOCT(m_vShOCT[i]);
        wgtTarget->SetShQCA(m_vShQCA[i]);
        wgtTarget->SetShIVUS(m_vShIVUS[i]);


        int nCurrIndex = ui->m_tabBBB->addTab(wgtTarget,"病变");
        ui->m_tabBBB->setCurrentIndex(0);
    }
}

/**
 * @brief CWidgetAdditionalInfo::GetJWBS
 * @return
 */
SJWBS CWidgetAdditionalInfo::GetJWBS()
{
    SJWBS JWBS;
    JWBS.sGXY=this->GetWidgetRadBtn(ui->m_wgtGXY);
    JWBS.sWZXGJB=this->GetWidgetRadBtn(ui->m_wgtWZXGJB);
    JWBS.sTXZL=this->GetWidgetRadBtn(ui->m_wgtTXZL);
    JWBS.sJQXYS=this->GetWidgetRadBtn(ui->m_wgtJQXYS);

    JWBS.sGXZ=this->GetWidgetRadBtn(ui->m_wgtGXZ);
    JWBS.sMXFB=this->GetWidgetRadBtn(ui->m_wgtMXFB);
    JWBS.sXJGS=this->GetWidgetRadBtn(ui->m_wgtXJGS);
    JWBS.sGXBJZS=this->GetWidgetRadBtn(ui->m_wgtGXBJZS);
    JWBS.sSGNSJ=this->GetWidgetRadBtn(ui->m_wgtSGNSJ);
    JWBS.sTNB=this->GetWidgetRadBtn(ui->m_wgtTNB);
    JWBS.sXLSJ=this->GetWidgetRadBtn(ui->m_wgtXLSJ);
    JWBS.sNXGJB=this->GetWidgetRadBtn(ui->m_wgtNXGJB);
    JWBS.sBMSSS=this->GetWidgetRadBtn(ui->m_wgtBMSSS);
    JWBS.sBMSSRQ=ui->m_dtmBMSSRQ->dateTime().toString(csDateTimeStyle);
    JWBS.sPCIS=this->GetWidgetRadBtn(ui->m_wgtPCIS);
    JWBS.sPCIRQ=ui->m_dtmPCIRQ->dateTime().toString(csDateTimeStyle);
    JWBS.sCABGS=this->GetWidgetRadBtn(ui->m_wgtCABGS);
    JWBS.sCABGRQ=ui->m_dtmCABGRQ->dateTime().toString(csDateTimeStyle);

    JWBS.sWriter=ui->m_lineWriter->text();
    JWBS.sWriteDate=ui->m_dtmWrite->dateTime().toString(csDateTimeStyle);

    return  JWBS;
}

/**
 * @brief CWidgetAdditionalInfo::InitGroupBox
 * @param pWidget
 * @param pQuery
 */
void CWidgetAdditionalInfo::InitWidgetRadBtn(QWidget *pWidget, QString pQuery)
{
    QObjectList lstObject=pWidget->children();
    for(int i=0;i<lstObject.length();i++)
    {
        if(lstObject.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(lstObject.at(i));
            QString sControl=aControl->text();
            if(sControl==pQuery)
            {
                aControl->setChecked(1);
                break;
            }
        }
    }
}

/**
 * @brief CWidgetAdditionalInfo::GetWidgetRadBtn
 * @param pWidget
 * @return
 */
QString CWidgetAdditionalInfo::GetWidgetRadBtn(QWidget *pWidget)
{
    QString sAns="";
    QObjectList lstObject=pWidget->children();
    for(int i=0;i<lstObject.length();i++)
    {
        if(lstObject.at(i)->inherits("QRadioButton"))
        {
            auto aControl=qobject_cast<QRadioButton*>(lstObject.at(i));
            if(aControl->isChecked())
            {
                sAns=aControl->text();
                break;
            }
        }
    }
    return sAns;
}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBJrqInfo
 */
void CWidgetAdditionalInfo::UpdateDBJrqInfo()
{

}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBJrhInfo
 */
void CWidgetAdditionalInfo::UpdateDBJrhInfo()
{

}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBSqOCT
 */
void CWidgetAdditionalInfo::UpdateDBSqOCT()
{


}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBSqIVUS
 */
void CWidgetAdditionalInfo::UpdateDBSqIVUS()
{

}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBSqQCA
 */
void CWidgetAdditionalInfo::UpdateDBSqQCA()
{

}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBShOCT
 */
void CWidgetAdditionalInfo::UpdateDBShOCT()
{

}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBShIVUS
 */
void CWidgetAdditionalInfo::UpdateDBShIVUS()
{

}

/**
 * @brief CWidgetAdditionalInfo::UpdateDBShQCA
 */
void CWidgetAdditionalInfo::UpdateDBShQCA()
{

}

void CWidgetAdditionalInfo::on_m_radBMSST_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtBMSSRQ->setEnabled(1);
    }
}

void CWidgetAdditionalInfo::on_m_radBMSSF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtBMSSRQ->setEnabled(0);
    }
}

void CWidgetAdditionalInfo::on_m_radPCIT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtPCIRQ->setEnabled(1);
    }
}

void CWidgetAdditionalInfo::on_m_radPCIF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtPCIRQ->setEnabled(0);
    }
}

void CWidgetAdditionalInfo::on_m_radCABGT_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtCABGRQ->setEnabled(1);
    }
}

void CWidgetAdditionalInfo::on_m_radCABGF_clicked(bool checked)
{
    if(checked)
    {
        ui->m_wgtCABGRQ->setEnabled(0);
    }
}

/**
 * @brief CWidgetAdditionalInfo::on_m_btnAddBBB_clicked
 */
void CWidgetAdditionalInfo::on_m_btnAddBBB_clicked()
{
    CWgtTargetPathology *wgtTarget = new CWgtTargetPathology;
    m_lstPathology.append(wgtTarget);
    int index = ui->m_tabBBB->addTab(wgtTarget,"病变");
    ui->m_tabBBB->setCurrentIndex(index);
}

/**
 * @brief CWidgetAdditionalInfo::on_m_btnDelBBB_clicked
 */
void CWidgetAdditionalInfo::on_m_btnDelBBB_clicked()
{
    int nCurrIndex = ui->m_tabBBB->currentIndex();
    m_lstPathology.removeAt(nCurrIndex);


    ui->m_tabBBB->removeTab(ui->m_tabBBB->currentIndex());

}
