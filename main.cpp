/*
 * File:   main.cpp
 * Author: Dinesh M. Bhoyar
 *
 * Created on 6 10 2017
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

//for native ui
#if QT_NATIVE_UI
#include "nativeui/mainwindow.h"
#include <QApplication>
#endif

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QScopedArrayPointer>
#include <QQmlContext>
#include <QtQuick/QQuickView>

#include "csvdata.h"
int main(int argc, char *argv[])
{

#if QT_NATIVE_UI
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

#else
    QGuiApplication app(argc, argv);
    QScopedPointer<csvdata> data (new csvdata);
    TuningParametrModel tParams;
//    tParams.addTuningParametr(TuningParametr("64","306","6900","0"));
//    tParams.addTuningParametr(TuningParametr("256","330","6875","0"));
//    tParams.addTuningParametr(TuningParametr("256","338","6875","0"));
//    tParams.addTuningParametr(TuningParametr("256","346","6875","0"));
    ChannelInfoModel tChannel;
//    QString chdata[] ={"DD NEWS,256,362,6900,0,1285,1794,502,502,41,MPEG2,MPEG2,62,1,5,1,42833,eng,digital television service,running",
//                       "DD LOKSABHA,256,362,6900,0,1286,1446,1286,1286,1462,MPEG2,MPEG2,63,1,5,1,42833,N/A,digital television service,running",
//                       "DD RAJYASABHA,256,362,6900,0,1287,1447,1287,1287,1463,MPEG2,MPEG2,64,1,5,1,42833,eng,digital television service,running",
//                       "DD BANGLA,256,362,6900,0,1290,606,1290,1290,38,MPEG2,MPEG2,67,1,5,1,42833,N/A,digital television service,running",
//                       "DD KASHIR,256,362,6900,0,1291,5201,1291,5201,1467,MPEG2,MPEG2,68,1,5,1,42833,hin,digital television service,running",
//                       "DD MALAYALAM,256,362,6900,0,1292,1452,1292,1292,1468,MPEG2,MPEG2,69,1,5,1,42833,eng,digital television service,running",
//                       "DD GIRNAR,256,362,6900,0,1293,608,508,508,45,MPEG2,MPEG2,70,1,5,1,42833,N/A,digital television service,running",
//                       "DD KISAN,256,362,6900,0,1296,1456,1296,1296,1472,MPEG1,MPEG2,72,1,5,1,42833,N/A,digital television service,running",
//                       "DD ODIA,256,370,6900,0,1537,622,522,522,52,MPEG2,MPEG2,79,1,6,1,42833,N/A,digital television service,running",
//                       "DD INDIA,256,370,6900,0,1539,604,504,504,40,MPEG2,MPEG2,81,1,6,1,42833,fre,digital television service,running",
//                       "DD BHARATI,256,370,6900,0,1540,1700,1540,1540,1716,MPEG2,MPEG2,82,1,6,1,42833,eng,digital television service,running",
//                       "DD SAPTAGIRI,256,370,6900,0,1541,256,N/A,8191,1717,MPEG2,N/A,83,1,6,1,42833,eng,digital television service,running",
//                       "DD URDU,256,370,6900,0,1543,1703,1543,1543,1719,MPEG2,MPEG2,85,1,6,1,42833,fre,digital television service,running",
//                       "DD PODIGHAI,256,370,6900,0,1545,1705,1545,1545,1721,MPEG2,MPEG2,87,1,6,1,42833,N/A,digital television service,running",
//                       "DD CHANDANA,256,370,6900,0,1550,1710,1550,1550,1726,MPEG2,MPEG2,90,1,6,1,42833,N/A,digital television service,running",
//                       "DD SAHYADRI,256,402,6900,0,2567,2727,2567,2567,2743,MPEG2,MPEG2,154,1,10,1,42833,eng,digital television service,running",
//                       "DD NATIONAL,256,490,6900,0,5892,32,5892,5892,6068,MPEG2,MPEG2,317,1,21,1,42833,eng,digital television service,running",
//                       "DD NATIONAL,256,490,6900,0,5892,601,5892,5892,6068,MPEG2,MPEG2,317,1,21,1,42833,eng,digital television service,running",
//                       "DD SPORTS,256,490,6900,0,5893,703,5893,5893,6069,MPEG2,MPEG2,318,1,21,1,42833,eng,digital television service,running",
//                       "DD NORTH EAST,256,498,6900,0,6145,6305,6145,6145,6321,MPEG2,MPEG2,336,1,22,1,42833,tam,digital television service,running",
//                       "DD BIHAR,256,498,6900,0,6146,6306,6146,6146,6322,MPEG2,MPEG2,337,1,22,1,42833,hin,digital television service,running",
//                       "DD RAJASTHAN,256,498,6900,0,6147,6307,6147,6307,6323,MPEG2,MPEG2,338,1,22,1,42833,eng,digital television service,running",
//                       "DD UTARPRADESH,256,498,6900,0,6148,6308,6148,6148,193,MPEG2,MPEG2,339,1,22,1,42833,eng,digital television service,running",
//                       "DD PUNJABI,256,498,6900,0,6149,6309,6149,6149,6325,MPEG2,MPEG2,340,1,22,1,42833,N/A,digital television service,running",
//                       "DD MADHYAPRADESH,256,498,6900,0,6150,6310,6150,6150,6326,MPEG1,MPEG2,341,1,22,1,42833,N/A,digital television service,running"};
//    for (auto const & data :chdata){
//        QStringList lst = data.split(",");
//        qDebug() << "lst count "<< lst.count();
//        if (lst.count() >=20){
//            tChannel.addChannelInfo(ChannelInfo(lst.at(0),lst.at(1),
//                                                lst.at(2),lst.at(3),
//                                                lst.at(4),lst.at(5),
//                                                lst.at(6),lst.at(7),
//                                                lst.at(8),lst.at(9),
//                                                lst.at(10),lst.at(11),
//                                                lst.at(12),lst.at(13),
//                                                lst.at(14),lst.at(15),
//                                                lst.at(16),lst.at(17),
//                                                lst.at(18),lst.at(19)));
//          qDebug()<< "info" << lst.at(0)<<lst.at(1)<<
//                         lst.at(2)<<lst.at(3)<<
//                         lst.at(4)<<lst.at(5)<<
//                         lst.at(6)<<lst.at(7)<<
//                         lst.at(8)<<lst.at(9)<<
//                         lst.at(10)<<lst.at(11)<<
//                         lst.at(12)<<lst.at(13)<<
//                         lst.at(14)<<lst.at(15)<<
//                         lst.at(16)<<lst.at(17)<<
//                         lst.at(18)<<lst.at(19);
//        }
//    }
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("csv",data.data());
    engine.rootContext()->setContextProperty("tParams",&data->tParams);
    engine.rootContext()->setContextProperty("tChannel",&data->tChannel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
#endif
    return app.exec();
}
