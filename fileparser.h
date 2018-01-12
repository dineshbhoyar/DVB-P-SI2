/*
 * File:   fileparser.h
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



#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QString>
#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDebug>



enum Tuner_Type{
    CABLE=1,
    SATELATE,
    TERRESTRIAL
};

struct FreqInfo{
    Tuner_Type type;
    //cable
    QString Frequency,QAM,SymbolRate,FEC_inner,FEC_outer;
    //terrestrial
    QString bandwidth,priority,Time_Slicing_indicator,MPE_FEC_indicator;
    QString constellation,hierarchy_information,code_rate_HP_stream;
    QString code_rate_LP_stream,guard_interval,transmission_mode,other_frequency_flag;
    //satelite
    QString /*frequency,*/orbital_position,west_east_flag,polarization,roll_off,modulation_system;
    QString modulation_type/*,symbol_rate,FEC_inner*/;
    bool isEmpty(){
        if (!Frequency.size())
            return true;
        /*else if (!QAM.size())
            return true;
        else if (!SymbolRate.size())
            return true;
        else if (!FEC.size()) //fec dosent make any sence
            return true;*/
        else
            return false;
    }
    void Print()
    {
        switch(type)
        {
        case CABLE:
            qDebug() << "Cable : "
                     << " Frequency : "<<Frequency
                     << " QAM : " << QAM
                     << " SymbolRate : "<<SymbolRate
                     << " FEC_inner : "<< FEC_inner
                     << " FEC_outer : "<<FEC_outer;
            break;
        case SATELATE:
            qDebug() << "Sattelatie : "
                     << " Frequency : " <<Frequency
                     << " orbital_position : " << orbital_position
                     << " west_east_flag : " << west_east_flag
                     << " polarization : " << polarization
                     << " roll_off : " << roll_off
                     << " modulation_system : " << modulation_system
                     << " modulation_type : " << modulation_type;
            break;
        case TERRESTRIAL:
            break;
        default:
            break;
        }
    }
};

struct ProgrammeInfo {
    QString Name;
    FreqInfo fInfo;
    QString PROGID, APID, VPID, RPID, PMT,ATYPE, VTYPE,SID,EPG;
    QString StreamID,Encrypted,NetworkID,Lang;
    QString running_state,service_type;

    bool isEmpty(){
        if (!Name.size())
            return true;
        else if (!PROGID.size())
            return true;
        return false;
    }
    void Print() {
        auto obj = *this;
        qDebug()<<obj.Name<<","
               <<obj.fInfo.QAM<<","
              <<obj.fInfo.Frequency<<","
             <<obj.fInfo.SymbolRate<<","
            <<obj.fInfo.FEC_inner<<","
           <<obj.fInfo.FEC_outer<<","
          <<obj.PROGID<<","<< obj.APID<<","
         << obj.VPID<<","<< obj.RPID<<","
         << obj.PMT<<","<<obj.ATYPE<<","
         <<obj.VTYPE<<","<<obj.SID<<","
        <<obj.EPG<<","<<obj.StreamID<<","
        <<obj.Encrypted<<","<<obj.NetworkID<<","
        <<obj.Lang<<","<<obj.running_state<<","
        <<obj.service_type;
        //return os;

    };

    friend std::ostream& operator>>(std::ostream& is, const ProgrammeInfo & obj) {
        // Read obj from stream
        if (0/* no valid object of T found in stream */)
            is.setstate(std::ios::failbit);
        qDebug() << " Not Yet implemented ";
        return is;
    };

};

class FileParser{
public:
    //FileParse();
    virtual ~FileParser(){};
    virtual void Set(QUrl&  filepath )=0;
    virtual void Parse() = 0;
    virtual   std::map<uint16_t,ProgrammeInfo> & Get()=0;
};

class DummyParser:public FileParser
{
    std::map<uint16_t,ProgrammeInfo> arg;
public:
    DummyParser(){};
    ~DummyParser(){};

    void Set(QUrl& filepath ){qDebug() << "Processing file " << filepath.path();};
    void Parse() {};
    std::map<uint16_t,ProgrammeInfo>& Get(){  return arg; };
};

#endif // FILEPARSER_H
