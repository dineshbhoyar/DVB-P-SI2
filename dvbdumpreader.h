/*
 * File:   dvbdumpreader.h
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



#ifndef DVBDUMPREADER_H
#define DVBDUMPREADER_H

#include "fileparser.h"
#include "DVB/tables.hpp"
#include "DVB/dvb_section.hpp"
#include "DVB/utils.h"
#include <iostream>
#include <QObject>



class DVBDumpReader:public QObject,public FileParser{

    Q_OBJECT

    APP_UTILS::SectionContaniner container;
    APP_UTILS::dvb_sections_discriptor desciptor;
    std::map<uint16_t,ProgrammeInfo> data;
    std::map<double,FreqInfo> fdata;
    QFile toOpen;
    std::string NetworkName="unknown";

public:
    DVBDumpReader();
    ~DVBDumpReader();
    void Set(QUrl& filepath );
    void Clear();
    void Parse() ;
    std::map<uint16_t,ProgrammeInfo>& Get();
    std::map<double,FreqInfo>& GetFMap();
    std::string& GetNetworkName(){ return NetworkName;};

    void ParseMemory(unsigned char*buff, uint32_t len, FileParser*bptr);
    void ParseFile();
signals:
    void ChannelsInstance(ProgrammeInfo p);
    void FreqInstance(FreqInfo f);
    void onNetworkNameChange(QString name);
    void onPrograsessChange(size_t size);
    void onStatusChange(QString status);

public slots:

};
#endif // DVBDUMPREADER_H
