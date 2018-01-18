/*
 * File:   dvbdumpreader.cpp
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



#include "dvbdumpreader.h"
#include "tsreader.h"
#include <iostream>
#include <fstream>

/////
DVBDumpReader::DVBDumpReader(){

}
DVBDumpReader::~DVBDumpReader(){

}

std::map<uint16_t,ProgrammeInfo>& DVBDumpReader::Get(){
    return data;
}
std::map<double,FreqInfo>& DVBDumpReader::GetFMap(){
    for (auto & val: fdata){
        qDebug()<<" DVBDumpReader freq "<< val.first <<" and freq "<< val.second.Frequency;
    }
    return fdata;
}

static unsigned char buff[4096];
void DVBDumpReader::ParseFile(){
#if 0
    toOpen.open(QIODevice::ReadOnly | QIODevice::Unbuffered |QIODevice::Text);
    while (!toOpen.atEnd()){
        //char len[4] {0,0,0,0,};

        memset(buff,'\0',sizeof(buff));
        toOpen.read((char*)&buff, 4);
        uint16_t sec_len = (uint16_t)((buff[1] &0x0f)<< 8 | (buff[2]&0xff)) ;
        qDebug() << "\nsection length : "
                 << sec_len << " "
                 << " 0x"<<(uint32_t)(((buff[0] <<24)&0xff000000) |((buff[1]<<16)&0x00ff0000)|((buff[2]<<8)&0x0000ff00)|(buff[3]&0x000000ff))
                <<"\n";
        if (sec_len){
            uint64_t readlen = toOpen.read((char*)&buff[4], sec_len-1);
            qDebug() <<" read data " << readlen;
            ParseMemory((unsigned char *) buff,sec_len+3, nullptr);
        }
        //InFile.seekg(sec_len,std::ios_base::cur);
    }
    toOpen.close();
#else
    std::ifstream InFile(toOpen.fileName().toStdString(),std::ios::in | std::ios::binary );
    while (!InFile.eof()){
        memset(buff,'\0',sizeof(buff));
        InFile.read((char*)&buff, 4);
        uint16_t sec_len = (uint16_t)((buff[1] &0x0f)<< 8 | (buff[2]&0xff)) ;
        std::cout << "\nsection length : "
                  << sec_len << " "
                  << std::hex
                  << " 0x"<<(uint32_t)( ((buff[0] <<24)&0xff000000) |((buff[1]<<16)&0x00ff0000)|((buff[2]<<8)&0x0000ff00)|(buff[3]&0x000000ff))
                <<std::endl;
        if (sec_len){
            InFile.read((char*)&buff[4], sec_len-1);
            ParseMemory((unsigned char *) buff,sec_len+3, nullptr);
        }
        //InFile.seekg(sec_len,std::ios_base::cur);
    }
    InFile.close();

#endif
}

void DVBDumpReader::Parse(){
    QFileInfo finfo(toOpen.fileName());
    if(finfo.isDir()){
        QDir toOpenDir(toOpen.fileName());
        QFileInfoList flist= toOpenDir.entryInfoList(QStringList("*.dump"),QDir::Files,QDir::Name);
        for (auto const & data: flist){
            qDebug()<< "QFileInfoList"<<data.absoluteFilePath();
            toOpen.setFileName(data.absoluteFilePath());
            ParseFile();
        }
    }else{
        ParseFile();
    }
}
void DVBDumpReader::Clear(){
    data.clear();
    container.Clear();
}

void DVBDumpReader::ParseMemory(unsigned char*buff, uint32_t len, FileParser *bptr){

    uint8_t table_id = buff[0];
    // qDebug() << " processing memory dump of len " << len <<" table_id " << (uint32_t) table_id <<"\n";
    switch(table_id){
    case NIT_TABLEID_ACTUAL:
    case NIT_TABLEID_OTHER:
    {

        APP_UTILS::NIT_Container& cnt = (table_id==NIT_TABLEID_ACTUAL)?container.nitActual:container.nitOther;
        container.nitActual.Parse(buff,len,desciptor,container);
        if(container.nitActual.nit_descriptor.network_name.size()){

                NetworkName = container.nitActual.nit_descriptor.network_name;

        }
        for (auto  &ts_descriptor : container.nitActual.ts_descriptor ){

            if(ts_descriptor.second.network_name.size()){
                std::cout << " dvb_dump network name " <<ts_descriptor.second.network_name<<std::endl;
                if(NetworkName.size()){
                    NetworkName.append("-");
                    NetworkName.append(ts_descriptor.second.network_name);
                }else{
                    NetworkName.append(ts_descriptor.second.network_name);
                }
            }
            FreqInfo fInfo {};
            //qDebug() << ts_descriptor.first;
            if(ts_descriptor.second.cds.frequency !=0){
                fInfo.type = CABLE;
                cable_delivery_system& cds= ts_descriptor.second.cds;
                fInfo.Frequency = std::to_string(cds.frequency).c_str();
                fInfo.QAM = std::to_string((uint32_t)cds.modulation).c_str();
                fInfo.SymbolRate = std::to_string(cds.symbol_rate).c_str();
                fInfo.FEC_inner = FEC_inner_to_string(cds.FEC_inner).c_str();
                fInfo.FEC_outer = FEC_outer_to_string(cds.FEC_outer).c_str();
                fdata[cds.frequency] = fInfo;
            }
            //qDebug() << ts_descriptor.second.sds;
            if(ts_descriptor.second.sds.frequency != 0){
                fInfo.type = SATELATE;
                satellite_delivery_system& sds = ts_descriptor.second.sds;

                fInfo.Frequency = std::to_string(sds.frequency).c_str();
                fInfo.orbital_position = std::to_string(sds.orbital_position).c_str();
                fInfo.west_east_flag = west_east_flag_to_string(sds.west_east_flag).c_str();
                fInfo.polarization = polarization_to_string(sds.polarization).c_str();
                fInfo.roll_off = roll_off_to_string(sds.roll_off).c_str();
                fInfo.modulation_system = modulation_system_to_string(sds.modulation_system).c_str();
                fInfo.modulation_type = modulation_type_to_string(sds.modulation_type).c_str();
                fInfo.SymbolRate = std::to_string(sds.symbol_rate).c_str();
                fInfo.FEC_inner = FEC_inner_to_string(sds.FEC_inner).c_str();
                fdata[sds.frequency] = fInfo;
            }
            if(ts_descriptor.second.tds.centre_frequency != 0){
                fInfo.type = TERRESTRIAL;
                terrestrial_delivery_system& tds  = ts_descriptor.second.tds;
                fInfo.Frequency = std::to_string(tds.centre_frequency*10).c_str();
                fInfo.bandwidth= bandwidth_to_string(tds.bandwidth).c_str();
                fInfo.priority = priority_to_string(tds.priority).c_str();
                fInfo.Time_Slicing_indicator = used_unsued_to_string(tds.Time_Slicing_indicator).c_str();
                fInfo.MPE_FEC_indicator = used_unsued_to_string(tds.MPE_FEC_indicator).c_str();
                //uint8_t reserved_future_use1;
                fInfo.constellation = constellation_to_string(tds.constellation).c_str();
                fInfo.hierarchy_information = hierarchy_information_to_string(tds.hierarchy_information).c_str() ;
                fInfo.code_rate_HP_stream =code_rate_to_string(tds.code_rate_HP_stream).c_str() ;
                fInfo.code_rate_LP_stream =code_rate_to_string(tds.code_rate_LP_stream).c_str() ;
                fInfo.guard_interval = guard_interval_to_string(tds.guard_interval).c_str() ;
                fInfo.transmission_mode = transmission_mode_to_string(tds.transmission_mode).c_str() ;
                fInfo.other_frequency_flag = used_unsued_to_string(tds.other_frequency_flag).c_str() ;
                //uint32_t reserved_future_use2;
                fdata[tds.centre_frequency] = fInfo;
            }
            for (auto const &service_list: ts_descriptor.second.service_list){
                data[service_list.first].fInfo=fInfo;
                data[service_list.first].NetworkID = std::to_string(ts_descriptor.first.buoquet_id).c_str();
                data[service_list.first].StreamID=std::to_string(ts_descriptor.first.transport_stream_id).c_str();
                data[service_list.first].PROGID = std::to_string(service_list.first).c_str();
            }
            for (auto const& lcn : ts_descriptor.second.logiacal_channel){
                data[lcn.first].fInfo=fInfo;
                data[lcn.first].NetworkID = std::to_string(ts_descriptor.first.buoquet_id).c_str();
                data[lcn.first].StreamID=std::to_string(ts_descriptor.first.transport_stream_id).c_str();
                data[lcn.first].PROGID = std::to_string(lcn.first).c_str();
            }
            emit FreqInstance(fInfo);
        }
    }
        break;
        /*case NIT_TABLEID_OTHER:
        container.nitOther.Parse(buff,len,desciptor,container);
        for (auto const &ts_descriptor : container.nitOther.ts_descriptor ){
            FreqInfo fInfo {};
            //qDebug() << ts_descriptor.first;
            if(ts_descriptor.second.cds.frequency !=0){
            fInfo.Frequency = std::to_string(ts_descriptor.second.cds.frequency).c_str();
            fInfo.QAM = std::to_string((uint32_t)ts_descriptor.second.cds.modulation).c_str();
            fInfo.SymbolRate = std::to_string(ts_descriptor.second.cds.symbol_rate).c_str();
            fInfo.FEC_inner = std::to_string((uint32_t)ts_descriptor.second.cds.FEC_inner).c_str();
            fInfo.FEC_outer = std::to_string((uint32_t)ts_descriptor.second.cds.FEC_outer).c_str();
            }
            for (auto const &service_list: ts_descriptor.second.service_list){
                data[service_list.first].fInfo=fInfo;
                data[service_list.first].PROGID = std::to_string(service_list.first).c_str();
                data[service_list.first].NetworkID = std::to_string(ts_descriptor.first.buoquet_id).c_str();
                data[service_list.first].StreamID=std::to_string(ts_descriptor.first.transport_stream_id).c_str();
            }
            for (auto const& lcn : ts_descriptor.second.logiacal_channel){
                data[lcn.first].fInfo=fInfo;
                data[lcn.first].PROGID = std::to_string(lcn.first).c_str();
                data[lcn.first].NetworkID = std::to_string(ts_descriptor.first.buoquet_id).c_str();
                data[lcn.first].StreamID=std::to_string(ts_descriptor.first.transport_stream_id).c_str();
            }
            emit FreqInstance(fInfo);
        }
        break;*/
    case PAT_TABLEID:
        if ( 0==container.pat.Parse(buff,len,desciptor,container)){

            for (auto const & val : container.pat.pat){
                if(bptr != nullptr){
                    TSReader * ptr = static_cast<TSReader*>(bptr);
                    ptr->RegisterPid(val.second,
                                     std::bind(&DVBDumpReader::ParseMemory,
                                               &ptr->patDump,
                                               std::placeholders::_1,
                                               std::placeholders::_2,
                                               bptr));
                }
                data[val.first].PMT = std::to_string(val.second).c_str();
            }
            if (container.pat.network_PID){
                if(bptr != nullptr){
                    TSReader * ptr = static_cast<TSReader*>(bptr);
                    ptr->RegisterPid(
                                container.pat.network_PID,
                                std::bind(&DVBDumpReader::ParseMemory,
                                          &ptr->patDump,
                                          std::placeholders::_1,
                                          std::placeholders::_2,
                                          bptr));

                }
            }
        }
        container.pat.Clear();
        break;
    case BAT_TABLEID:
        container.bat.Parse(buff,len,desciptor,container);
        break;
    case SDT_TABLEID_ACTUAL:
        container.sdtActual.Parse(buff,len,desciptor,container);
        for(auto const & sdata: container.sdtActual.sdt){
            ProgrammeInfo & refUpdae = data[sdata.first.buoquet_id] ;
            refUpdae.Name = sdata.second.service_description.service_name.c_str();
            refUpdae.Encrypted = std::to_string(sdata.second.free_CA_mode).c_str();
            refUpdae.EPG = std::to_string(sdata.second.EIT_schedule_flag).c_str();
            refUpdae.running_state = APP_UTILS::running_status(sdata.second.running_status).c_str();
            refUpdae.service_type = APP_UTILS::service_type(sdata.second.service_description.service_type).c_str();
            refUpdae.PROGID = std::to_string(sdata.first.buoquet_id).c_str();
            emit ChannelsInstance(refUpdae);
        }
        container.sdtActual.Clear();
        break;
    case SDT_TABLEID_OTHER:
        container.sdtOther.Parse(buff,len,desciptor,container);
        for(auto const & sdata: container.sdtOther.sdt){
            ProgrammeInfo & refUpdae = data[sdata.first.buoquet_id] ;
            refUpdae.Name = sdata.second.service_description.service_name.c_str();
            refUpdae.Encrypted = std::to_string(sdata.second.free_CA_mode).c_str();
            refUpdae.EPG = std::to_string(sdata.second.EIT_schedule_flag).c_str();
            refUpdae.running_state = APP_UTILS::running_status(sdata.second.running_status).c_str();
            refUpdae.service_type = APP_UTILS::service_type(sdata.second.service_description.service_type).c_str();
            refUpdae.PROGID = std::to_string(sdata.first.buoquet_id).c_str();
            emit ChannelsInstance(refUpdae);
        }
        container.sdtOther.Clear();
        break;
    case PMT_TABLEID:
    {
        container.pmt.Parse(buff,len,desciptor,container);
        ProgrammeInfo& refUpdate = data[container.pmt.program_number];
        if(!refUpdate.RPID.size()){
            refUpdate.RPID = std::to_string(container.pmt.PCR_PID).c_str();
            for(auto const & val : container.pmt.Info){
                switch (val.second.stream_type) {
                case 0x03:
                {
                    refUpdate.ATYPE.append(" MPEG1 ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x04:
                {
                    /*AUDIO_MPEG2       */
                    refUpdate.ATYPE.append(" MPEG2 ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x0F:
                {
                    /*AUDIO_AAC_ADTS    */
                    refUpdate.ATYPE.append(" AAC_ADTS ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x11:
                {
                    /*AUDIO_AAC_LATM      */
                    refUpdate.ATYPE.append(" AAC_LATM ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x12:
                {
                    /*AUDIO_AAC_RAW1    */
                    refUpdate.ATYPE.append(" AAC_RAW1 ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x13:
                {

                    /*AUDIO_AAC_RAW2    */
                    refUpdate.ATYPE.append(" AAC_RAW2 ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x80:
                {
                    /*AUDIO_LPCM        */
                    refUpdate.ATYPE.append(" LPCM ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x81:
                {
                    /*AUDIO_AC3         */
                    refUpdate.ATYPE.append(" AC3 ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x82:
                {

                    /*AUDIO_DTS         */
                    refUpdate.ATYPE.append(" DTS ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x83:
                {

                    /*AUDIO_MLP         */
                    refUpdate.ATYPE.append(" MLP ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x84:
                {

                    /*AUDIO_DDPLUS      */
                    refUpdate.ATYPE.append(" DDPLUS ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x85:
                {
                    /*AUDIO_DTSHD       */
                    refUpdate.ATYPE.append(" DTSHD ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x86:
                {
                    /*AUDIO_DTSHD_XLL   */
                    refUpdate.ATYPE.append(" DTSHD_XLL ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0xA1:
                {
                    /*AUDIO_DDPLUS_2    */
                    refUpdate.ATYPE.append(" DDPLUS_2 ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0xA2:
                {

                    /*AUDIO_DTSHD_2     */
                    refUpdate.ATYPE.append(" DTSHD_2 ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0xE6:
                {

                    /*AUDIO_WMA         */
                    refUpdate.ATYPE.append(" WMA ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x06:
                {
                    /*Private pes*/
                    refUpdate.ATYPE.append(" Private pes ");
                    refUpdate.APID.append(" ");
                    refUpdate.APID.append(std::to_string(val.first).c_str());
                    refUpdate.Lang.append(" ");
                    refUpdate.Lang.append(val.second.lang.c_str());
                }
                    break;
                case 0x01:
                {
                    /*VIDEO_MPEG1      =*/
                    refUpdate.VTYPE.append(" MPEG1 ");
                    refUpdate.VPID.append(" ");
                    refUpdate.VPID.append(std::to_string(val.first).c_str());
                }
                    break;
                case 0x02:
                {
                    /*VIDEO_MPEG2      =*/
                    refUpdate.VTYPE.append(" MPEG2 ");
                    refUpdate.VPID.append(" ");
                    refUpdate.VPID.append(std::to_string(val.first).c_str());
                }
                    break;
                case 0x10:
                {
                    /*VIDEO_MPEG4P2    =*/
                    refUpdate.VTYPE.append(" MPEG4P2 ");
                    refUpdate.VPID.append(" ");
                    refUpdate.VPID.append(std::to_string(val.first).c_str());
                }
                    break;
                case 0x1B:
                {
                    /*VIDEO_MPEG4      =*/
                    refUpdate.VTYPE.append(" MPEG4 ");
                    refUpdate.VPID.append(" ");
                    refUpdate.VPID.append(std::to_string(val.first).c_str());
                }
                    break;
                case 0x42:
                {
                    /*VIDEO_AVS        =*/
                    refUpdate.VTYPE.append(" AVS ");
                    refUpdate.VPID.append(" ");
                    refUpdate.VPID.append(std::to_string(val.first).c_str());
                }
                    break;
                case 0xEA:
                {
                    /*VIDEO_VC1        =*/
                    refUpdate.VTYPE.append(" VC1 ");
                    refUpdate.VPID.append(" ");
                    refUpdate.VPID.append(std::to_string(val.first).c_str());
                }
                    break;
                default:
                    break;
                }
            }
        }
        container.pmt.Clear();
    }
        break;
    default:
        container.pmt.Parse(buff,len,desciptor,container);
        break;
    }
}


void DVBDumpReader::Set(QUrl &filepath){
    qDebug() << "Processing file " << filepath.path();
    toOpen.setFileName( filepath.path().replace("\\\\\\",""));

    if(toOpen.exists()){
        Clear();
        qDebug() << filepath.fileName() << " exists";
    }else{
        qDebug()<< filepath.path() << " dose not exists";
    }

}
