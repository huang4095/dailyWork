#include "sqldatasource.h"
#include<qDebug>
#include"appInit/quiwidget.h"

#define Name(X) #X


sqlDataSource::sqlDataSource()
{

}




bool sqlDataSource:: addFormList(QString formName, QStringList fieldName,QVariantList value)
{
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    QString sqlcommand(""),field(QString("[%1]").arg(fieldName[0])),val(QString("'%1'").arg(value[0].toString()));
    if(fieldName.count()!= value.count())
    {
        QUIHelper::showMessageBoxInfo("列名个数和值个数不一致！",2) ;
        return true;

    }
    for(int i=1;i<fieldName.count();i++)
    {

        field += QString(",[%1]").arg(fieldName[i]);
        QString type=value[i].typeName();

        if(type=="float")
        {

            val += QString(",%1").arg(value[i].toFloat());
        }else if(type=="int")
        {

            val += QString(",%1").arg(value[i].toInt());
        }
        else
        {

            val += QString(",'%1'").arg(value[i].toString());
        }


    }
    sqlcommand = QString("insert into %1 (%2) values (%3)").arg(formName).arg(field).arg(val);
    qDebug()<<sqlcommand;
    bool sucess=query.exec(sqlcommand);

    if(sucess)
    {

        QUIHelper::showMessageBoxInfo("数据写入成功！",2) ;
        return true;
    }else
    {
        QUIHelper::showMessageBoxInfo("数据写入失败！",2) ;
        qDebug()<<query.lastError().text();
        return false;

    }
    sql.closeConnection(db);
}

//QList<QStringList> sqlDataSource::getFormListbyCondition(QString formName, QStringList fieldName,QString condition,QString orderField)
//{
//    QSqlDatabase db = sql.openConnection();
//    QSqlQuery query(db);
//    QString sqlcommand(""),field(QString("%1").arg(fieldName[0]));
//     QList<QStringList> listList;
//    for(int i=1;i<fieldName.count();i++)
//    {
//        field += QString(",%1").arg(fieldName[i]);
//    }

//    sqlcommand = QString("SELECT %1 FROM %2 WHERE (%3) AND [isDelete] = 0 ORDER BY %4").arg(field).arg(formName).arg(condition).arg(orderField);
//    qDebug()<<sqlcommand;
//    bool sucess=query.exec(sqlcommand);

//    if(sucess)
//    {
//        while(query.next())
//        {

//            QStringList list;
//            int j=0;

//            //qDebug()<<query.record().count();
//            while(j<query.record().count())
//            {
//                list.append(query.value(j).toString());
//                j++;
//            }
//            listList.append(list);
//        }

//        //QUIHelper::showMessageBoxInfo("数据查询成功！",2) ;

//    }else
//    {
//        QUIHelper::showMessageBoxInfo("数据查询失败！",2) ;
//        qDebug()<<query.lastError().text();

//    }
//    sql.closeConnection(db);
//     return listList;
//}
QList<QStringList> sqlDataSource::getFormListbyCondition(QString formName, QStringList fieldName,QStringList condition,QStringList orderField)
{
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    QString sqlcommand("");
    QString fieldList(QString("%1").arg(fieldName[0]));
    QString conditionList(QString("%1").arg(condition[0]));
    QString orderFieldList(QString("%1").arg(orderField[0]));


    for(int i=1;i<fieldName.count();i++)
    {
        fieldList += QString(",%1").arg(fieldName[i]);
    }
    for(int i=1;i<condition.count();i++)
    {
        conditionList += QString(" %1").arg(condition[i]);
    }
    for(int i=1;i<orderField.count();i++)
    {
        orderFieldList += QString(",%1").arg(orderField[i]);
    }
    QList<QStringList> listList;

    sqlcommand = QString("SELECT %1 FROM %2 WHERE (%3) AND [isDelete] = 0 ORDER BY %4").arg(fieldList).arg(formName).arg(conditionList).arg(orderFieldList);
    qDebug()<<sqlcommand;
    bool sucess=query.exec(sqlcommand);

    if(sucess)
    {
        while(query.next())
        {

            QStringList list;
            int j=0;

            //qDebug()<<query.record().count();
            while(j<query.record().count())
            {
                list.append(query.value(j).toString());
                j++;
            }
            listList.append(list);
        }

        //QUIHelper::showMessageBoxInfo("数据查询成功！",2) ;

    }else
    {
        QUIHelper::showMessageBoxInfo("数据查询失败！",2) ;
        qDebug()<<query.lastError().text();      

    }
    sql.closeConnection(db);
     return listList;
}
QList<QStringList> sqlDataSource::getFormListbyCondition(QString formName, QString fieldName,QStringList condition,QString orderField)
{
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    QString sqlcommand("");

    QString conditionList(QString("%1").arg(condition[0]));

    for(int i=1;i<condition.count();i++)
    {
        conditionList += QString(" %1").arg(condition[i]);
    }

    QList<QStringList> listList;

    sqlcommand = QString("SELECT %1 FROM %2 WHERE (%3) AND [isDelete] = 0 ORDER BY %4").arg(fieldName).arg(formName).arg(conditionList).arg(orderField);
    qDebug()<<sqlcommand;
    bool sucess=query.exec(sqlcommand);

    if(sucess)
    {
        while(query.next())
        {

            QStringList list;
            int j=0;

            //qDebug()<<query.record().count();
            while(j<query.record().count())
            {
                list.append(query.value(j).toString());
                j++;
            }
            listList.append(list);
        }

        //QUIHelper::showMessageBoxInfo("数据查询成功！",2) ;

    }else
    {
        QUIHelper::showMessageBoxInfo("数据查询失败！",2) ;
        qDebug()<<query.lastError().text();

    }
    sql.closeConnection(db);
     return listList;
}
QList<QStringList> sqlDataSource::getFormListbyCondition(QString formName, QString fieldName,QString orderField)
{
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    QString sqlcommand("");

    QList<QStringList> listList;

    sqlcommand = QString("SELECT %1 FROM %2 WHERE   [isDelete] = 0 ORDER BY %3").arg(fieldName).arg(formName).arg(orderField);
    qDebug()<<sqlcommand;
    bool sucess=query.exec(sqlcommand);

    if(sucess)
    {
        while(query.next())
        {

            QStringList list;
            int j=0;

            //qDebug()<<query.record().count();
            while(j<query.record().count())
            {
                list.append(query.value(j).toString());
                j++;
            }
            listList.append(list);
        }

        //QUIHelper::showMessageBoxInfo("数据查询成功！",2) ;

    }else
    {
        QUIHelper::showMessageBoxInfo("数据查询失败！",2) ;
        qDebug()<<query.lastError().text();

    }
    sql.closeConnection(db);
     return listList;
}
QList<QStringList> sqlDataSource::getFormListbyCondition(QString formName, QStringList fieldName,QString orderField)
{
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    QString sqlcommand("");
    QList<QStringList> listList;

    QString fieldList(QString("%1").arg(fieldName[0]));
    for(int i=1;i<fieldName.count();i++)
    {
        fieldList += QString(",%1").arg(fieldName[i]);
    }
    sqlcommand = QString("SELECT %1 FROM %2 WHERE   [isDelete] = 0 ORDER BY %3").arg(fieldList).arg(formName).arg(orderField);
    qDebug()<<sqlcommand;
    bool sucess=query.exec(sqlcommand);

    if(sucess)
    {
        while(query.next())
        {

            QStringList list;
            int j=0;

            //qDebug()<<query.record().count();
            while(j<query.record().count())
            {
                list.append(query.value(j).toString());
                j++;
            }
            listList.append(list);
        }

        //QUIHelper::showMessageBoxInfo("数据查询成功！",2) ;

    }else
    {
        QUIHelper::showMessageBoxInfo("数据查询失败！",2) ;
        qDebug()<<query.lastError().text();

    }
    sql.closeConnection(db);
     return listList;
}
QList<QStringList> sqlDataSource::getFormListbyCondition(QString formName, QStringList fieldName,QStringList condition,QString orderField)
{
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    QString sqlcommand("");
    QString fieldList(QString("%1").arg(fieldName[0]));
    QString conditionList(QString("%1").arg(condition[0]));



    for(int i=1;i<fieldName.count();i++)
    {
        fieldList += QString(",%1").arg(fieldName[i]);
    }
    for(int i=1;i<condition.count();i++)
    {
        conditionList += QString(" %1").arg(condition[i]);
    }

    QList<QStringList> listList;

    sqlcommand = QString("SELECT %1 FROM %2 WHERE (%3) AND [isDelete] = 0 ORDER BY %4").arg(fieldList).arg(formName).arg(conditionList).arg(orderField);
    qDebug()<<sqlcommand;
    bool sucess=query.exec(sqlcommand);

    if(sucess)
    {
        while(query.next())
        {

            QStringList list;
            int j=0;

            //qDebug()<<query.record().count();
            while(j<query.record().count())
            {
                list.append(query.value(j).toString());
                j++;
            }
            listList.append(list);
        }

        //QUIHelper::showMessageBoxInfo("数据查询成功！",2) ;

    }else
    {
        QUIHelper::showMessageBoxInfo("数据查询失败！",2) ;
        qDebug()<<query.lastError().text();

    }
    sql.closeConnection(db);
     return listList;
}

QString sqlDataSource::idToName(QString id,QString from)
{

    //qDebug()<<id<<from;
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    query.exec("SELECT name from "+from+" where id = '"+id+"'");
    if(query.next())
    {

        return query.value(0).toString();
    }else
    {
        return "";
    }
    sql.closeConnection(db);
}



bool sqlDataSource::updateForm(QString id,QString fromName,QStringList field,QVariantList value)
{
    QSqlDatabase db = sql.openConnection();
    QSqlQuery query(db);
    bool success=true;
    if(field.count()!=value.count()){
        qDebug()<<"updateForm:列和值个数不一致";
         return false;
    }
    for(int i=0;i<field.count();i++)
    {
        QString type=value[i].typeName();
        bool sucs=false;
        if(type=="float")
        {
            sucs=query.exec(QString("UPDATE "+fromName+" SET "+field.at(i)+" = %1 "
                 "WHERE id = '"+id+"' and isDelete = 0 ").arg(value.at(i).toFloat()));
        }else if(type=="float")
        {
            sucs=query.exec(QString("UPDATE "+fromName+" SET "+field.at(i)+" = %1 "
                 "WHERE id = '"+id+"' and isDelete = 0 ").arg(value.at(i).toInt()));
        }else
        {
            sucs=query.exec(QString("UPDATE "+fromName+" SET "+field.at(i)+" = '%1' "
                 "WHERE id = '"+id+"' and isDelete = 0 ").arg(value.at(i).toString()));
        }
        if(!sucs)
        {
            success=false;
        }
    }
    if(!success)
    {      
        QUIHelper::showMessageBoxInfo("数据更新失败！",1);
        return false;
    }
    sql.closeConnection(db);
    QUIHelper::showMessageBoxInfo("数据更新成功！",1);
    return true;
}
//void sqlDataSource::updateFormFloat(QString id,QString fromName,QStringList field,QList<float> value)
//{
//    QSqlDatabase db = sql.openConnection();
//    QSqlQuery query(db);
//    bool success=true;
//    for(int i=0;i<field.count();i++)
//    {
//        bool sucs=query.exec(QString("UPDATE "+fromName+" SET "+field.at(i)+" = %1 "
//                    "WHERE id = '"+id+"' and isDelete = 0 ").arg(value.at(i)));
//        if(!sucs)
//        {
//            success=false;
//        }
//    }
//    if(success)
//    {

//        QUIHelper::showMessageBoxInfo("数据更新成功！",1);
//    }else
//    {

//        QUIHelper::showMessageBoxInfo("数据更新失败！",1);
//    }
//    sql.closeConnection(db);

//}
//QList<QStringList> sqlDataSource::getFormList(QString formName,QString orderField,QString id)
//{
//    if(id=="")
//    {
//        id="%";
//    }
//    QList<QStringList> listList;
//    QSqlDatabase db = sql.openConnection();
//    QSqlQuery query(db);
//    //qDebug()<<formName<<orderField;
//    query.exec("SELECT * from "+formName+"  where id like '"+id+"' and isDelete = 0 order by "+orderField +" ");
//    while(query.next())
//    {

//        QStringList list;
//        int j=0;

//        //qDebug()<<query.record().count();
//        while(j<query.record().count())
//        {
//            list.append(query.value(j).toString());
//            j++;
//        }
//        listList.append(list);
//    }
//    sql.closeConnection(db);
//    return listList;
//}
//QList<QStringList> sqlDataSource::getFieldList(QString formName,QStringList FieldName,QString orderField,QString id)
//{
//    if(id=="")
//    {
//        id="%";
//    }

//    QString Fieldlist;
//    if(FieldName.isEmpty())
//    {
//        Fieldlist="*";
//    }else{

//        Fieldlist.append(FieldName.at(0));
//        for(int i=1;i<FieldName.count();i++)
//        {

//            Fieldlist.append(","+FieldName.at(i));
//        }
//    }


//    QList<QStringList> listList;


//    QSqlDatabase db = sql.openConnection();
//    QSqlQuery query(db);

//    QString command;
//    command = QString("SELECT %1 FROM %2 WHERE id LIKE '%3' and  isDelete = 0 order by %4 ").arg(Fieldlist).arg(formName).arg(id).arg(orderField);
//    qDebug()<<command;
//    query.exec(command);
//    while(query.next())
//    {

//        QStringList list;
//        int j=0;


//        while(j<query.record().count())
//        {
//            list.append(query.value(j).toString());
//            j++;
//        }
//        listList.append(list);
//    }
//    sql.closeConnection(db);
//    return listList;
//}

//QList<QStringList> sqlDataSource::getFormListByField(QString formName,QString orderField,QStringList Field,QStringList value)
//{



//    QString searchfield;
//    for(int i=0;i<Field.count();i++)
//    {
//        //qDebug()<<Field.at(i)+"="+value.at(i);
//        searchfield.append(" and "+Field.at(i)+" = '"+value.at(i)+"'");
//    }

//    QList<QStringList> listList;
//    QSqlDatabase db = sql.openConnection();
//    QSqlQuery query(db);

//    query.exec("SELECT * from "+formName+"  where isDelete = 0 "+searchfield+"  order by "+orderField +" ");
//    while(query.next())
//    {

//        QStringList list;
//        int j=0;

//        //qDebug()<<query.record().count();
//        while(j<query.record().count())
//        {
//            list.append(query.value(j).toString());
//            j++;
//        }
//        listList.append(list);
//    }
//    sql.closeConnection(db);
//    return listList;
//}
//QList<QStringList> sqlDataSource::getFormListByFieldOr(QString formName,QString orderField,QStringList Field,QStringList value)
//{



//    QString searchfield;
//    for(int i=0;i<Field.count();i++)
//    {
//        //qDebug()<<Field.at(i)+"="+value.at(i);
//        searchfield.append(Field.at(i)+" = '"+value.at(i)+"'"+" or ");
//    }
//    //qDebug()<<searchfield.mid(0,searchfield.length()-4);
//    searchfield=searchfield.mid(0,searchfield.length()-4);
//    QList<QStringList> listList;
//    QSqlDatabase db = sql.openConnection();

//    QSqlQuery query(db);
//    QString sqlcommand = QString("SELECT * from %1  where isDelete = 0 and  (%2)  order by %3").arg(formName).arg(searchfield).arg(orderField);
//    query.exec(sqlcommand);
//    while(query.next())
//    {

//        QStringList list;
//        int j=0;

//        //qDebug()<<query.record().count();
//        while(j<query.record().count())
//        {
//            list.append(query.value(j).toString());
//            j++;
//        }
//        listList.append(list);
//    }
//    sql.closeConnection(db);
//    return listList;
//}
//QList<QStringList>  sqlDataSource::getFieldListByField(QString formName,QStringList FieldName, QString orderField,QStringList Field,QStringList value)
//{
//    QString searchfield;


//    for(int i=0;i<Field.count();i++)
//    {        //qDebug()<<Field.at(i)+"="+value.at(i);
//        searchfield.append(" and "+Field.at(i)+" = '"+value.at(i)+"'");
//    }
//    //qDebug()<<searchfield;
//    QString Fieldlist;
//    if(FieldName.isEmpty())
//    {
//        Fieldlist="*";
//    }else{

//        Fieldlist.append(FieldName.at(0));
//        for(int i=1;i<FieldName.count();i++)
//        {

//            Fieldlist.append(","+FieldName.at(i));
//        }
//    }


//    QList<QStringList> listList;
//    QSqlDatabase db = sql.openConnection();
//    QSqlQuery query(db);

//    query.exec("SELECT "+Fieldlist+" from "+formName+"  where isDelete = 0 "+searchfield+"  order by "+orderField +" ");
//    while(query.next())
//    {

//        QStringList list;
//        int j=0;

//        //qDebug()<<query.record().count();
//        while(j<query.record().count())
//        {
//            list.append(query.value(j).toString());
//            j++;
//        }
//        listList.append(list);
//    }
//    sql.closeConnection(db);
//    return listList;

//}
void sqlDataSource::tableWidgetShow(QStringList HStrList,QList<QStringList> date,QTableWidget *tableWidget)
{

    int HlableCnt = HStrList.count();
    int rowCount =date.count();
    tableWidget->setRowCount(rowCount);
    tableWidget->setColumnCount(HlableCnt);

    //设置列标签
    tableWidget->setHorizontalHeaderLabels(HStrList);

    for(int i=0;i<rowCount;i++)
    {
        for(int j=0;j<HlableCnt;j++)
        {
            QString str=date.at(i).at(j);
            tableWidget->setItem(i, j, new QTableWidgetItem(str));
        }
    }

    tableWidget->setColumnHidden(0,true);
    tableWidget->setColumnHidden(1,true);
    tableWidget->setColumnHidden(2,true);
    tableWidget->resizeColumnsToContents();
    tableWidget->setSortingEnabled(true);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->horizontalHeader()->setStretchLastSection(true);//充满表宽
    //tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //tableWidget->resizeRowsToContents();

//    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
//QList<QStringList> sqlDataSource::getFieldListByFieldOr(QString formName,QStringList FieldName, QString orderField,QStringList Field,QStringList value)
//{



//    QString searchfield;
//    for(int i=0;i<Field.count();i++)
//    {
//        //qDebug()<<Field.at(i)+"="+value.at(i);
//        searchfield.append(Field.at(i)+" = '"+value.at(i)+"'"+" or ");
//    }
//    //qDebug()<<searchfield.mid(0,searchfield.length()-4);
//    searchfield=searchfield.mid(0,searchfield.length()-4);

//    QString Fieldlist;
//    if(FieldName.isEmpty()){
//        Fieldlist = "*";
//    }else{
//        Fieldlist.append(FieldName.at(0));
//        for(int i=1;i<FieldName.count();i++)
//        {

//            Fieldlist.append(","+FieldName.at(i));
//        }
//    }

//    QList<QStringList> listList;
//    QSqlDatabase db = sql.openConnection();
//    QSqlQuery query(db);
//    QString sqlcommand = QString("SELECT %1 from %2  where isDelete = 0 and  (%3)  order by %4").arg(Fieldlist).arg(formName).arg(searchfield).arg(orderField);
//    qDebug()<<sqlcommand;
//    query.exec(sqlcommand);
//    while(query.next())
//    {

//        QStringList list;
//        int j=0;

//        //qDebug()<<query.record().count();
//        while(j<query.record().count())
//        {
//            list.append(query.value(j).toString());
//            j++;
//        }
//        listList.append(list);
//    }
//    sql.closeConnection(db);
//    return listList;
//}
