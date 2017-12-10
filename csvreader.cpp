/*
 * File:   csvreader.cpp
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



#include "csvreader.h"


////
CSVReader::CSVReader(){

}
CSVReader::~CSVReader(){

}
std::map<uint16_t, ProgrammeInfo> &CSVReader::Get(){
    //return data;
    for(auto& val:data)
        val.second.Print();
    return data;
}
std::map<double,FreqInfo>& CSVReader::GetFMap(){
    return fdata;
}

void CSVReader::Parse(){
    if(toOpen.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in (&toOpen);
        QString line = in.readLine();

        qDebug() << line;
        line = in.readLine();
        qDebug() << line;
        while(!in.atEnd()){
            line = in.readLine();
            // qDebug() << line ;
            if(!line.isEmpty()){
                QStringList items {line.split(",")};
                if(items.count() >= 20 ){
                    bool ok;
                    uint16_t service_id =items.at(5).toUShort(&ok,10);
                    double freq = items.at(2).toDouble(&ok);
                            qDebug() << "Processing service id " << service_id <<" / " <<items.at(5);
                    if(ok){
                        auto& ref = data[service_id];
                        ref.Name = items.at(0);
                        ref.fInfo.type =CABLE;
                        ref.fInfo.QAM = items.at(1);
                        ref.fInfo.Frequency= items.at(2);
                        ref.fInfo.SymbolRate= items.at(3);
                        ref.fInfo.FEC_inner= items.at(4);
                        ref.fInfo.FEC_outer="0";
                        ref.PROGID= items.at(5);
                        ref.APID= items.at(6);
                        ref.VPID= items.at(7);
                        ref.RPID= items.at(8);
                        ref.PMT= items.at(9);
                        ref.ATYPE= items.at(10);
                        ref.VTYPE= items.at(11);
                        ref.SID= items.at(12);
                        ref.EPG= items.at(13);
                        ref.StreamID= items.at(14);
                        ref.Encrypted= items.at(15);
                        ref.NetworkID= items.at(16);
                        ref.Lang =items.at(17);
                        ref.running_state= items.at(18);
                        ref.service_type= items.at(19);

                        fdata[freq] = ref.fInfo;
                    }
                }else{
                    qDebug () <<"total count " << items.count();
                }
            }

            //qDebug()<< items ;
        }
        qDebug() << "done";
    }else{
        qDebug()<<"Error:" << toOpen.errorString() << toOpen.fileName();
    }

}
void CSVReader::Set(QUrl& filepath){
    qDebug() << "Processing file " << filepath.path();

    toOpen.setFileName(filepath.path().replace("\\\\\\",""));
    if(toOpen.exists()){
        qDebug() << filepath.path() << "exists";
        data.empty();
    }else{
        qDebug() << filepath.path() << "dose not exists";
    }

    return;
}

