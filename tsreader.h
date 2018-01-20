/*
 * File:   tsreader.h
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



#ifndef TSREADER_H
#define TSREADER_H
#include "fileparser.h"
#include "dvbdumpreader.h"
#include <QDataStream>
#include <map>
#include <netinet/in.h>
#include <functional>

#include <QObject>

extern "C"{
#include "sectioncrc.h"
}
#define TS_PACKET_SIZE 188
#define MAX_SECTION_PACKET 4096
#define SECTION_HEADER_SIZE 3
#define SYNC_BYTE 0x47

using callbackFn = std::function<void(unsigned char * ,uint32_t)> ;
struct SectionData{
    callbackFn fn;
    unsigned char SecPayload[MAX_SECTION_PACKET];
    unsigned int section_len;
    SectionData(){
        qDebug() <<"initilizing SectionData ";
        fn=nullptr;;
        memset(SecPayload,'\0',sizeof(SecPayload));
        section_len = 0;
    }
};

class TSReader:public QObject,public FileParser{

    Q_OBJECT

    unsigned char payload[TS_PACKET_SIZE];
    //unsigned char SecPayload[MAX_SECTION_PACKET];
    QFile toOpen;
    std::map<uint16_t,bool> supportedPID;
    std::map<uint16_t,SectionData> sectionParser;
    //std::string NetworkName="unknown";

    void SaveSecPayload(uint16_t, unsigned char* , int);

    //std::map<uint16_t,ProgrammeInfo> data;
public:
    TSReader();
    ~TSReader();
    void Set(QUrl& filepath );
    void Parse() ;
    std::map<uint16_t,ProgrammeInfo>& Get();
    std::map<double,FreqInfo>& GetFMap();
    std::string& GetNetworkName(){ return patDump.GetNetworkName();};
    void RegisterPid(uint16_t ,callbackFn );
    DVBDumpReader patDump{};
signals:
    void ChannelsInstance(ProgrammeInfo p);
    void FreqInstance(FreqInfo f);
    void onNetworkNameChange(QString name);
    void onPrograsessChange(double size);
    void onStatusChange(QString status);

public slots:
    void ChannelsInstanceSlot(ProgrammeInfo p){
        qDebug() << "got signal for pid *******"<< p.PROGID << "emiting ";
        emit ChannelsInstance(p);
    };
    void FreqInstanceSlot(FreqInfo f){
            qDebug() << "got signal for freq *******"<< f.Frequency << "emiting ";
        emit FreqInstance(f);
    };
    void onNetworkNameChangeSlot(QString name){
        emit onNetworkNameChange(name);
    };
    void onPrograsessChangeSlot(double size){
       // qDebug() << "got signal fro progress  *******"<< size << "emiting ";
     emit onPrograsessChange(size);
    };
    void onStatusChangeSlot(QString status){
        emit onStatusChange(status);
    };
};

#endif // TSREADER_H
