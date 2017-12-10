/*
 * File:   tsreader.cpp
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



#include "tsreader.h"


TSReader::TSReader(){
    connect(&patDump,&DVBDumpReader::ChannelsInstance,this,&TSReader::ChannelsInstanceSlot);
    connect(&patDump,&DVBDumpReader::FreqInstance,this,&TSReader::FreqInstanceSlot);
}
TSReader::~TSReader(){

    disconnect(&patDump,&DVBDumpReader::ChannelsInstance,this,&TSReader::ChannelsInstanceSlot);
    disconnect(&patDump,&DVBDumpReader::FreqInstance,this,&TSReader::FreqInstanceSlot);
}
std::map<uint16_t, ProgrammeInfo> &TSReader::Get(){
    return patDump.Get();
}
std::map<double,FreqInfo>& TSReader::GetFMap(){
    return patDump.GetFMap();
}

void TSReader::RegisterPid(uint16_t pid, callbackFn fn)
{
    if(supportedPID[pid] == true){
        qDebug() << " pid "<<pid<<" already registred ";
        return;
    }
    if(fn){
        auto& data =  sectionParser[pid] ;
        data.fn = fn;
        //sectionParser[pid].fn = fn;
        supportedPID[pid] =true;
        qDebug() << " callback registerd for pid " << pid;
    }
}

void TSReader::SaveSecPayload(uint16_t pid , unsigned char *buff, int len)
{
    if(supportedPID[pid] == true){
        //qDebug()<<"Pid "<< pid<< " len "<< len <<" processing ";
        auto & data =  sectionParser[pid] ;
        unsigned short section_header_len = 0;
        unsigned int payload = 0;
        unsigned int crc = 0;
        unsigned int bidx=0;
        //int written = 0;

        while (len > 0) {

            while (data.section_len < SECTION_HEADER_SIZE) { /* current section is without a complete header */

                /* get header bytes */
                data.SecPayload[data.section_len] = buff[bidx];
                data.section_len += 1;
                bidx += 1;
                len -= 1;

                /* check if it is header or padding */
                if (data.section_len == SECTION_HEADER_SIZE) {
                    if(data.SecPayload[0] == 0xFF) {
                        data.SecPayload[0] = data.SecPayload[1];
                        data.SecPayload[1] = data.SecPayload[2];
                        data.section_len = 2;
                    }
                }

                /* chek if there is more payload */
                if (len <= 0) {
                    return;
                }

            }

            /* get section size from the header */
            //memcpy(&section_header_len, data.SecPayload + 1, 2);
            //section_header_len = ntohs(section_header_len);
            //section_header_len &= 0x0FFF;
            section_header_len = ((( data.SecPayload[1] << 8)|data.SecPayload[2])&0x0fff);
            section_header_len += SECTION_HEADER_SIZE;

            /* add payload without padding */
            if (section_header_len - data.section_len >= (unsigned short)len) {
                payload = len;
            } else {
                payload = section_header_len - data.section_len;
            }
            //qDebug() <<" section_len"<< data.section_len << " bidx "<< bidx << "payload " << payload;
            memcpy(&data.SecPayload[ data.section_len], &buff[bidx], payload);
            data.section_len += payload;
            bidx+= payload;
            len -= payload;

            /* output the section only if completed */
            if (data.section_len == section_header_len) {
                if (data.section_len >= 4) {
                    crc = sectioncrc(data.SecPayload, data.section_len - 4);
                    if ( (data.SecPayload[data.section_len - 4] == ((crc >> 24) & 0xFF)) &&
                         (data.SecPayload[data.section_len - 3] == ((crc >> 16) & 0xFF)) &&
                         (data.SecPayload[data.section_len - 2] == ((crc >> 8) & 0xFF)) &&
                         (data.SecPayload[data.section_len - 1] == (crc & 0xFF))
                         )  {
                        if (data.fn)
                            data.fn(data.SecPayload,data.section_len);
                        else
                            qDebug() << " unfortunatly no function registerd for pid " << pid;

                    } else {
                        fprintf(stderr, "crc failed: %x [%x] %x [%x] %x [%x] %x [%x]\n",
                                data.SecPayload[data.section_len - 4], ((crc >> 24) & 0xFF),
                                data.SecPayload[data.section_len - 3], ((crc >> 16) & 0xFF),
                                data.SecPayload[data.section_len - 2], ((crc >> 8) & 0xFF),
                                data.SecPayload[data.section_len - 1], (crc & 0xFF)
                                );
                        //exit(0);
                    }
                    data.section_len = 0;
                } else {
                    qDebug() << "section len too small" <<data.section_len;
                    data.section_len = 0;
                    len = 0;
                }
            }else {
                //qDebug() << " section_len " << data.section_len
                //       <<" section_header_len" <<section_header_len;
            }
        }


    }else{
        //     qDebug()<<"Pid "<< pid<< " len "<< len <<" not registred ";
    }
}
void TSReader::Parse(){

    if(toOpen.open(QIODevice::ReadOnly )){

        while(!toOpen.atEnd()){

            uint64_t readByte = toOpen.read((char*)&payload,TS_PACKET_SIZE);
            if(payload[0] == SYNC_BYTE){
                uint8_t transport_error_indicator = (uint8_t)((payload[1]&0x80) >>7)&0x01;
                uint8_t payload_unit_start_indicator = (uint8_t)((payload[1]&0x40) >>6)&0x01;
                uint8_t transport_priority =(uint8_t) ((payload[1]&0x20)>>5)&0x01;
                uint16_t pid = (uint16_t)((payload[1] << 8 |payload[2])&0x1fff);
                uint8_t transport_scrambling_control =(uint8_t)((payload[3]& 0xc0) >>6)&0x03;
                uint8_t adaptation_field_control =(uint8_t)((payload[3]&0x30)>>4)&0x03;
                uint8_t continuity_counter = (uint8_t)(payload[3]&0x0f);
                /* qDebug() << "got PID : " << pid << " of size " << readByte
                         << "transport_error_indicator : " <<(uint16_t) transport_error_indicator
                         <<" payload_unit_start_indicator : " <<(uint16_t)payload_unit_start_indicator
                        <<" transport_priority : " << (uint16_t)transport_priority
                       <<" transport_scrambling_control : "<<(uint16_t)transport_scrambling_control
                      <<"adaptation_field_control : "<<(uint16_t)adaptation_field_control
                     <<"continuity_counter : "<<(uint16_t)continuity_counter;*/
                if(adaptation_field_control == 0){
                }else if(adaptation_field_control == 2){
                    //adaptation_field() //only adaptation field
                }else if(adaptation_field_control == 1 || adaptation_field_control == 3) {
                    uint8_t ts_packet_header_size =4;
                    if(adaptation_field_control ==3){
                        uint8_t adaptation_field_length = payload[ts_packet_header_size];
                        ts_packet_header_size +=adaptation_field_length+1;
                    }
                    uint8_t ts_packet_payload_size = TS_PACKET_SIZE -ts_packet_header_size;
                    //qDebug() <<"processing payload of " <<ts_packet_payload_size
                    //      <<" with header of "<<ts_packet_header_size ;
                    if (ts_packet_payload_size <= TS_PACKET_SIZE){
                        if(payload_unit_start_indicator){
                            //process "pointer field" first if present
                            uint8_t pointer_field = payload[ts_packet_header_size+1];
                            if(pointer_field > 0 )
                                SaveSecPayload(pid,&payload[ts_packet_header_size+1],payload[ts_packet_header_size]);
                            SaveSecPayload(pid,&payload[ts_packet_header_size+1+payload[ts_packet_header_size]],TS_PACKET_SIZE-ts_packet_header_size-1-payload[ts_packet_header_size]);

                        }else{
                            SaveSecPayload(pid,&payload[ts_packet_header_size],TS_PACKET_SIZE-ts_packet_header_size);
                        }
                    }else{
                        qDebug() << "invalid ts payload of " << ts_packet_payload_size <<" bytes skipping";
                    }
                }
            }else{
                qDebug()<< "invalid TS packet ,no sync byte";
                break;
            }
        }
        qDebug() << "done";
    }else{
        qDebug() << "unable to open file " << toOpen.errorString();
    }
    return;
}
void TSReader::Set(QUrl &filepath){
    qDebug() << "Processing file " << filepath.path();
    toOpen.setFileName( filepath.path().replace("\\\\\\",""));

    if(toOpen.exists()){
        patDump.Clear();
        qDebug() << filepath.fileName() << " exists";

        //PAT :- get pat, pid 16 which is nit, and PMT
        RegisterPid(PAT_PID,
                    std::bind(&DVBDumpReader::ParseMemory,
                              &patDump,
                              std::placeholders::_1,
                              std::placeholders::_2,
                              this));
        //NIT
        RegisterPid(NIT_PID,
                    std::bind(&DVBDumpReader::ParseMemory,
                              &patDump,
                              std::placeholders::_1,
                              std::placeholders::_2,
                              this));
        //SDT/BAT
        RegisterPid(SDT_PID,
                    std::bind(&DVBDumpReader::ParseMemory,
                              &patDump,
                              std::placeholders::_1,
                              std::placeholders::_2,
                              this));
    }else{
        qDebug()<< filepath.path() << " dose not exists";
    }
}

