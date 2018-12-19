/*
 * File:   dvb_section.hpp
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




#ifndef DVB_SECTION_HPP
#define	DVB_SECTION_HPP
#include <memory>
#include <array>
#include <iostream>
#include <map>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <QDebug>
#include <QVariant>
#include "tables.hpp"



struct cable_delivery_system {
    double frequency;
    //reserved_future_use
    uint8_t FEC_outer;
    uint32_t modulation;
    double symbol_rate;
    uint8_t FEC_inner;
};
Q_DECLARE_METATYPE(cable_delivery_system)

struct terrestrial_delivery_system {

    uint32_t centre_frequency;
    uint8_t bandwidth;
    uint8_t priority;
    uint8_t Time_Slicing_indicator;
    uint8_t MPE_FEC_indicator;
    uint8_t reserved_future_use1;
    uint8_t constellation;
    uint8_t hierarchy_information ;
    uint8_t code_rate_HP_stream ;
    uint8_t code_rate_LP_stream ;
    uint8_t guard_interval ;
    uint8_t transmission_mode ;
    uint8_t other_frequency_flag ;
    uint32_t reserved_future_use2;
};
Q_DECLARE_METATYPE(terrestrial_delivery_system)

struct satellite_delivery_system {
    double frequency;
    double orbital_position;
    uint8_t west_east_flag;
    uint8_t polarization;
    uint8_t roll_off;
    uint8_t modulation_system;
    uint8_t modulation_type;
    double symbol_rate;
    uint8_t FEC_inner;
    friend   QDebug operator <<(QDebug debug,const satellite_delivery_system& obj)
    {
        QDebugStateSaver server(debug);
        debug.nospace()<< "\n\t frequency " << obj.frequency
                       << "\n\t orbital_position " << obj.orbital_position
                       << "\n\t west_east_flag " <<(uint32_t) obj.west_east_flag
                       << "\n\t polarization " << (uint32_t)obj.polarization
                       << "\n\t roll_off " << (uint32_t)obj.roll_off
                       << "\n\t modulation_system " << (uint32_t)obj.modulation_system
                       << "\n\t modulation_type " << (uint32_t)obj.modulation_type
                       << "\n\t symbol_rate " << obj.symbol_rate
                       << "\n\t FEC_inner "<<(uint32_t)obj.FEC_inner;
        return debug;
    }
};

Q_DECLARE_METATYPE(satellite_delivery_system)

struct ISO_639_language{
    std::string ISO_639_language_code;
    uint8_t audio_type;
};
Q_DECLARE_METATYPE(ISO_639_language)

struct Name{
    std::string name;
};
Q_DECLARE_METATYPE(Name)

struct service {
    uint8_t service_type;
    std::string service_provider_name;
    std::string service_name;
};
Q_DECLARE_METATYPE(service)


namespace APP_UTILS {


template <typename type>
inline type ValueFromByteStream(std::vector<uint8_t> data, uint8_t decimalPt = 0) {
    std::string ss;
    for (auto& val : data) {
        ss.append(std::to_string((val >> 4)&0x0f));
        ss.append(std::to_string(val & 0x0f));
    }
    if (decimalPt) {
        ss.insert(decimalPt, ".");
        return std::stod(ss);
    } else {
        return std::stoi(ss);
    }
}
struct versions {
    int8_t version;
    uint8_t size;
    std::string sectionmap;

    versions() : version {
                     -1
}
    {
    };

    ~versions() {
    };

    inline void ResizeSectionMap(uint8_t last_section_number) {
        if (sectionmap.size() != (uint32_t) (last_section_number + 1)) {
            std::string temp(last_section_number + 1, 'N');
            sectionmap = temp;
        }
        return;
    }

    inline void SetSectionMAp(uint8_t section_number) {
        if (sectionmap.size() >= section_number)
            sectionmap[section_number] = 'a';
        return;
    }

    inline bool isSectionFull(uint8_t section_number) {
        if (sectionmap.size() >= section_number)
            return sectionmap[section_number] == 'a' ? true : false;
        return false;
    }

    inline bool isSectionMapFull(uint8_t section_number, uint8_t last_section_number) {
        (void) section_number;
        std::string mask(last_section_number + 1, 'a');

        //            qDebug() << " section map " << sectionmap ;
        //            qDebug() << " section mask " << mask ;

        return mask.compare(sectionmap) == 0 ? true : false;
    };

};


//helpers
class ByteContainer {
    unsigned char* buff;
    int32_t pos;

    inline void bcdtostream(uint8_t& data, std::stringstream& ss) {
        ss << std::to_string((data >> 4)&0x0f);
        ss << std::to_string(data & 0x0f);
        return;
    }

public:

    ByteContainer(unsigned char *buff) : buff {buff}, pos{0}
    {

    }

    ~ByteContainer() {

    }

    inline uint8_t Byte(uint8_t mask = 0xff, bool advance = true) {
        uint8_t val = (uint8_t) (buff[pos] & mask);
        if (advance)
            pos++;
        //qDebug() << "a.Byte()\n";
        return val;
    };

    inline uint16_t Byte2(uint16_t mask = 0xffff, bool advance = true) {
        uint16_t val = 0;
        val = (uint16_t) ((buff[pos] << 8 | buff[pos + 1]) & mask);
        if (advance)
            pos += 2;
        //qDebug() << "a.Byte2()\n";

        return val;
    };

    inline uint32_t Byte3(uint32_t mask = 0x00ffffff, bool advance = true) {
        uint32_t val = 0;
        val = (uint32_t) ((buff[pos] << 16 | buff[pos + 1] << 8 | buff[pos + 2]) & mask);
        if (advance)
            pos += 3;
        return val;
    };

    inline uint32_t Byte4(uint32_t mask = 0xffffffff, bool advance = true) {
        uint32_t val = 0;
        val = (uint32_t) ((buff[pos] << 24 | buff[pos + 1] << 16 | buff[pos + 2] << 8 | buff[pos + 3]) & mask);
        if (advance)
            pos += 4;
        return val;
    };

    inline uint64_t Byte8(uint64_t mask = 0xffffffffffffffff, bool advance = true) {
        uint64_t val = 0;
        val = (uint64_t) (((uint64_t) (buff[pos]) << 56 | (uint64_t) (buff[pos + 1]) << 48\
                          | (uint64_t) (buff[pos + 2]) << 40 | (uint64_t) (buff[pos + 3]) << 32 | \
                                                                                             buff[pos + 4] << 24 | buff[pos + 5] << 16 | buff[pos + 6] << 8 | buff[pos + 7]) & mask);
        ;
        if (advance)
            pos += 8;
        return val;
    };

    inline void Skip(int32_t len = 0) {
        pos += len;
    };

    inline unsigned char * BuffPtr() {
        return &buff[pos];
    };

    inline uint32_t Pos() {
        return pos;
    }


};
void TableHexDump(unsigned char* pbuff ,uint32_t len);

struct TSTableHeader {
    std::string name;
    uint8_t table_id;
    uint8_t section_syntax_indicator;
    uint16_t section_length;
    uint16_t bouquet_id;
    uint8_t version_number;
    uint8_t current_next_indicator;
    uint8_t section_number;
    uint8_t last_section_number;
    //constructor table header

    TSTableHeader(std::string TableName, ByteContainer& a) {
        table_id = a.Byte();
        section_syntax_indicator = (uint8_t) (a.Byte(0x80, false) >> 0x07);
        /*if ((TableName.compare("EIT")) == 0) {
                section_length = a.Byte2(0x0fff);
            } else {
                section_length = a.Byte2(0x0fff); //as first two bits are always 00 (not applicable to eit)
                if (section_length > 1021){
                 section_length = (section_length & 0x3ff);
                }
            }*/
        section_length = a.Byte2(0x0fff);

        if ((TableName.compare("TDT")) != 0
                && (TableName.compare("TOT") != 0)) {
            bouquet_id = a.Byte2();
            version_number = (uint8_t) (a.Byte(0x3E, false) >> 1);
            current_next_indicator = a.Byte(0x01);
            section_number = a.Byte();
            last_section_number = a.Byte();
        } else {
            bouquet_id = 0xffff;
            version_number = 0x0;
            current_next_indicator = 1;
            section_number = 1;
            last_section_number = 1;
        }
        name = TableName;
    };
    //0 = valid 1 = invalid

    uint32_t CheckValidity() {
        uint32_t validity = 0;
        switch (table_id) {
        case PAT_TABLEID:
        case BAT_TABLEID:
        case NIT_TABLEID_ACTUAL:
        case NIT_TABLEID_OTHER:
        {
            if (current_next_indicator != 1) {
                qDebug() << " current_next_indicator should be 1 got"
                         << *this;
                validity = 1;
            } else if (section_length < 11 || section_length > 1021) {
                qDebug() << " section_length out of bound "
                         << *this;
                validity = 1;
            }
        }
            break;
        case PMT_TABLEID:
        {
            if (current_next_indicator != 1) {
                qDebug() << " current_next_indicator should be 1 got"
                         << *this;
                validity = 1;

            } else if (section_length < 13 || section_length > 1021) {
                qDebug()<< " section_length out of bound "
                        << *this;
                validity = 1;

            }
        }
            break;

        case SDT_TABLEID_ACTUAL:
        case SDT_TABLEID_OTHER:
        {
            if (current_next_indicator != 1) {
                qDebug()<< " current_next_indicator should be 1 got"
                        << *this;
                validity = 1;

            } else if (section_length < 12 || section_length > 1021) {
                qDebug()<< " section_length out of bound "
                        << *this;
                validity = 1;

            }
        }
            break;

        case CAT_TABLEID:
        case EIT_TABLEID_PF_ACTUAL:
        case EIT_TABLEID_PF_OTHER:
        case EIT_TABLEID_SCHEDULE_ACTUAL_LOW:
        case EIT_TABLEID_SCHEDULE_ACTUAL_HIGH:

        case EIT_TABLEID_SCHEDULE_OTHER_LOW:
        case EIT_TABLEID_SCHEDULE_OTHER_HIGH:

        case TDT_TABLEID:
        case TOT_TABLEID:
        default:
            break;
        }
        return validity;
    }
    //distroctor table header

    ~TSTableHeader() {

    };
    //to print content

    friend std::ostream& operator<<(std::ostream& os, const TSTableHeader& obj) {
        os << "\n\t " << obj.name << "  --> table_id : " << std::hex << (uint16_t) obj.table_id
           << "\n\t section_syntax_indicator : " << std::hex << (uint16_t) obj.section_syntax_indicator
           << "\n\t section_length : " << std::dec << obj.section_length
           << "\n\t transport_stream_id : " << obj.bouquet_id
           << "\n\t version_number: " << (uint32_t) obj.version_number
           << "\n\t current_next_indicator : " << (uint32_t) obj.current_next_indicator
           << "\n\t section_number : " << (uint16_t) obj.section_number
           << "\n\t last_section_number : " << std::dec << (uint16_t) obj.last_section_number;
        return os;
    };
    friend   QDebug operator <<(QDebug debug,const TSTableHeader& obj)
    {
        QDebugStateSaver server(debug);
        debug.nospace()<< "\n\t " << obj.name.c_str()
                       << "  --> table_id : " <<  (uint16_t) obj.table_id
                       << "\n\t section_syntax_indicator : " << (uint16_t) obj.section_syntax_indicator
                       << "\n\t section_length : "  << obj.section_length
                       << "\n\t transport_stream_id : " << obj.bouquet_id
                       << "\n\t version_number: " << (uint32_t) obj.version_number
                       << "\n\t current_next_indicator : " << (uint32_t) obj.current_next_indicator
                       << "\n\t section_number : " << (uint16_t) obj.section_number
                       << "\n\t last_section_number : "  << (uint16_t) obj.last_section_number;
        return debug;
    };

};
//return 0 if version matches 1 otherwise

uint32_t TableSectionVersionCheck(versions& verinfo, TSTableHeader& tstblhdr);
//forward declaration
class dvb_sections_discriptor;
class SectionContaniner;

//network,bouquet,component

struct multilingual1 {
    std::string ISO_639_language_code;
    std::string name;
};

//servcie

struct multilingual2 {
    std::string ISO_639_language_code;
    std::string name1;
    std::string name2;
};

struct CA_identifire {
    std::vector<uint16_t> CA_system_id;
};

/* BAT section Info
     */
struct BAT_Pirmary_Key {
    uint16_t transport_stream_id;
    uint16_t original_network_id;
    uint16_t buoquet_id;
};

struct country_availability {
    uint8_t country_availability_flag;
    std::string country_code;
};

struct BAT_Descriptor {
    std::string bouquet_name;
    std::map <uint16_t, uint16_t> logiacal_channel; //service_id ,logical_channel_number
    std::map <uint16_t, uint8_t> service_list;
    country_availability ca;
    multilingual1 bouquet;
    CA_identifire caid;
};
//
//    struct BAT_Transport_Stream_Descriptor {
//    };

struct BAT_Container {
    std::map<uint16_t, versions> version; //version information of bouquet
    std::map<uint16_t, BAT_Descriptor> bat_descriptor;
    uint32_t private_data_specifier;
    std::map<BAT_Pirmary_Key, BAT_Descriptor/*BAT_Transport_Stream_Descriptor*/> ts_descriptor;
    uint32_t Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor &dtable,SectionContaniner& container);
    void Clear(){
        version.clear();
        bat_descriptor.clear();
        ts_descriptor.clear();
        private_data_specifier=0;
    }
};

/*
     * NIT section Info
     */
struct NIT_Pirmary_Key {
    uint16_t transport_stream_id;
    uint16_t original_network_id;
    uint16_t buoquet_id;
    bool operator <(const NIT_Pirmary_Key& rhs) const {
        bool retval = false;
        if (transport_stream_id < rhs.transport_stream_id)
            retval =true;
        else if (original_network_id < rhs.original_network_id)
            retval=true;
        else if (buoquet_id < rhs.buoquet_id)
            retval =true;
        //        qDebug() <<"compairing original_network_id : ("
        //                <<transport_stream_id <<" vs " << rhs.transport_stream_id<<")"
        //               <<" original_network_id :("<<original_network_id << " vs " << rhs.original_network_id <<")"
        //              << " bouquet_id : ("<<buoquet_id << " vs " << rhs.buoquet_id<<")"
        //              << " bool : " << retval;
        return retval;
    };
    friend QDebug operator <<(QDebug debug,const NIT_Pirmary_Key& obj)
    {
        QDebugStateSaver server(debug);
        debug.nospace()<< " original_network_id : " << obj.original_network_id
                       << " transport_stream_id : " << obj.transport_stream_id
                       << " buoquet_id : " << obj.buoquet_id;
        return debug;
    };
};



struct NIT_Descriptor {
    std::map <uint16_t, uint16_t> logiacal_channel; //service_id ,logical_channel_number
    std::map <uint16_t, uint8_t> service_list;
    std::string network_name;
    satellite_delivery_system sds;
    cable_delivery_system cds;
    terrestrial_delivery_system tds;
    multilingual1 network;

};

//    struct NIT_Transport_Stream_Descriptor {
//    };

struct NIT_Container {
    std::map<uint16_t, versions> version; //version information of bouquet
    //std::map<uint16_t, NIT_Descriptor> nit_descriptor;
    NIT_Descriptor nit_descriptor;
    std::map<NIT_Pirmary_Key, NIT_Descriptor> ts_descriptor;
    uint32_t private_data_specifier;
    bool isFristLoop;
    uint32_t Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor &dtable,SectionContaniner& container);
    //    void ConsumeLoop1(QVariant var);
    //    void ConsumeLoop2(QVariant var);

    NIT_Container(){
        isFristLoop=true;
        private_data_specifier=0;
    }
    void Clear(){
        isFristLoop=true;
        private_data_specifier=0;
        version.clear();
        //nit_descriptor.clear();
        ts_descriptor.clear();
    }

    ~NIT_Container(){

    }
};

/* SDT section Info
     */
struct SDT_Pirmary_Key {
    uint16_t transport_stream_id;
    uint16_t original_network_id;
    uint16_t buoquet_id;
    bool operator <(const SDT_Pirmary_Key& rhs) const {
        bool retval =false;
        if (transport_stream_id < rhs.transport_stream_id)
            retval = true;
        else if (original_network_id < rhs.original_network_id)
            retval = true;
        else if(buoquet_id < rhs.buoquet_id)
            retval = true;
        return retval;
    };
};


struct SDT_Descriptor {
    //header
    uint16_t service_id;
    //reserved_future_use
    uint8_t EIT_schedule_flag;
    uint8_t EIT_present_following_flag;
    uint8_t running_status;
    uint8_t free_CA_mode;
    //payload
    service service_description;
    country_availability ca;
    multilingual2 service_ml;
    CA_identifire caid;
};

struct SDT_Container {
    std::map<uint16_t, versions> version; //version information of bouquet
    uint32_t private_data_specifier;
    std::map<SDT_Pirmary_Key, SDT_Descriptor> sdt;
    uint32_t Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor &dtable,SectionContaniner& container);
    void Clear(){
        version.clear();
        private_data_specifier=0;
        sdt.clear();
    }

    //TODO
};
struct PAT_Container {
    uint16_t transport_stream_id;
    uint16_t network_PID;
    uint32_t private_data_specifier;
    std::map<uint16_t, versions> version;

    std::map<uint16_t, uint16_t> pat; //program_number(service_id), program_map_PID
    uint32_t Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor &dtable,SectionContaniner& container);
    PAT_Container() {
        private_data_specifier = 0;
        transport_stream_id = 0;
        network_PID = 0;
    }
    void Clear(){
        private_data_specifier = 0;
        transport_stream_id = 0;
        network_PID = 0;
        version.clear();
        pat.clear();
    }
    ~PAT_Container() {

    }
};

struct PrgInfo {
    // uint32_t tspid;
    uint8_t stream_type;
    uint16_t elementary_PID;
    std::string lang;
    uint8_t langType;

    PrgInfo() : /* tspid {
                0
            }, */stream_type {
                     0xff
}, elementary_PID{0}, lang{"N/A"}, langType{0xff}
    {

    }

    void Print() {
        qDebug() << " *** stream_type : " << (uint32_t) stream_type
                 << " elementary_PID : " << (uint32_t) elementary_PID
                 << " lang : " << lang.c_str()
                 << " langType : " << (uint32_t) langType;
    }
};
struct PMT_Container {
    uint16_t PCR_PID;
    uint16_t program_number;
    uint32_t private_data_specifier;

    std::map<uint16_t, versions> version;
    std::map<uint16_t,PrgInfo> Info; //prog no and pes id info
    uint32_t Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor &dtable,SectionContaniner& container);
    PMT_Container() {
        PCR_PID = 0;
        program_number = 0;
        private_data_specifier = 0;
    }
    void Clear(){
        PCR_PID = 0;
        program_number = 0;
        private_data_specifier = 0;
        version.clear();
        Info.clear();
    }
    ~PMT_Container() {

    }
};
struct SectionContaniner {
    uint16_t currentTableIdInUse;
    PAT_Container pat;
    PMT_Container pmt;
    NIT_Container nitActual;
    NIT_Container nitOther;
    SDT_Container sdtActual;
    SDT_Container sdtOther;
    BAT_Container bat;
    void Clear(){
        pat.Clear();
        pmt.Clear();
        nitActual.Clear();
        nitOther.Clear();
        sdtActual.Clear();
        sdtOther.Clear();
        bat.Clear();
    }
};

//
using fnptr = std::function<QVariant(uint8_t,uint32_t,SectionContaniner&,ByteContainer&) >;

class dvb_sections_discriptor {
    std::array<fnptr, 256> descriptor{};
    SectionContaniner sections;
public:
    dvb_sections_discriptor();
    ~dvb_sections_discriptor();
    fnptr& get(uint8_t des);

};

QVariant f_default_descriptor(uint8_t descriptor,uint32_t length,SectionContaniner& sections,ByteContainer&a
                              );
//  descriptor_tag TS PS Identification
//0 n/a n/a Reserved
//1 n/a n/a Reserved

QVariant f_reserved_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                               );
//2 X X

QVariant f_video_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   );
//3 X X

QVariant f_audio_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//4 X X

QVariant f_hierarchy_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                );
//5 X X

QVariant f_registration_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   );
//6 X X

QVariant f_data_stream_alignment_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                            );
//7 X X

QVariant f_target_background_grid_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             );
//8 X X

QVariant f_Video_window_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   );
//9 X X

QVariant f_CA_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                         ) ;
//10 X X

QVariant f_ISO_639_language_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                       );
//11 X X

QVariant f_System_clock_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//12 X X

QVariant f_Multiplex_buffer_utilization_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                   ) ;
//13 X X

QVariant f_Copyright_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) ;
//14 X

QVariant f_Maximum_bitrate_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) ;
//15 X X

QVariant f_Private_data_indicator_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) ;
//16 X X

QVariant f_Smoothing_buffer_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                       ) ;
//17 X

QVariant f_STD_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) ;
// 18 X X

QVariant f_IBP_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) ;
//19-26 X Defined in ISO/IEC 13818-6 DSM_CC extension
//27 X X

QVariant f_MPEG_4_video_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//28 X X

QVariant f_MPEG_4_audio_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//29 X X

QVariant f_IOD_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) ;
//30 X

QVariant f_SL_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                         ) ;
//31 X X

QVariant f_FMC_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) ;
//32 X X

QVariant f_External_ES_ID_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) ;
//33 X X

QVariant f_MuxCode_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                              ) ;
//34 X X

QVariant f_FmxBufferSize_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                    ) ;
//35 X

QVariant f_MultiplexBuffer_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      );
//36-63 n/a n/a ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved
//64-255 n/a n/a User Private

//0x40

QVariant f_network_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//0x41

QVariant f_service_list_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//0x42

QVariant f_stuffing_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                               ) ;
//0x43

QVariant f_satellite_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) ;
//0x44

QVariant f_cable_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                            ) ;
QVariant gf_cable_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) ;
//0x45

QVariant f_VBI_data_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                               ) ;
//0x45

QVariant f_VBI_teletext_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//0x46

QVariant f_bouquet_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//0x47

QVariant f_service_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                              ) ;
//0x48

QVariant f_country_availability_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                           ) ;
//0x49

QVariant f_linkage_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                              ) ;
//0x4A

QVariant f_NVOD_reference_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) ;
//0x4B

QVariant f_time_shifted_service_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                           ) ;
//0x4C

QVariant f_short_event_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                  ) ;
//0x4D

QVariant f_extended_event_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     );
//0x4E

QVariant f_time_shifted_event_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                         ) ;
//0x4f

QVariant f_component_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) ;
//0x50

QVariant f_mosaic_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                             ) ;
//0x51

QVariant f_stream_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) ;
//0x52

QVariant f_CA_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                    ) ;
//0x53

QVariant f_content_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                              ) ;
//0x54

QVariant f_parental_rating_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      );
//0x55

QVariant f_teletext_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                               ) ;
//0x56

QVariant f_telephone_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) ;
//0x57

QVariant f_local_time_offset_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) ;
//0x58

QVariant f_subtitling_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                 ) ;
//0x59

QVariant f_terrestrial_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                  ) ;
//0x5A

QVariant f_multilingual_network_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) ;
//0x5B

QVariant f_multilingual_bouquet_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) ;
//0x5C

QVariant f_multilingual_service_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) ;
//0x5D

QVariant f_multilingual_component_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) ;
//0x5E

QVariant f_private_data_specifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) ;
//0x5f

QVariant f_service_move_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) ;
//0x60

QVariant f_short_smoothing_buffer_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) ;
//0x61

QVariant f_frequency_list_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) ;
//0x62

QVariant f_partial_transport_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                               ) ;
//0x63

QVariant f_data_broadcast_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) ;
//0x64

QVariant f_scrambling_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                 ) ;
//0x65

QVariant f_data_broadcast_id_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) ;
//0x66

QVariant f_transport_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                       ) ;
//0x67

QVariant f_DSNG_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                           ) ;
//0x68

QVariant f_PDC_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) ;
//0x69

QVariant f_AC_3_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                           ) ;
//0x6A

QVariant f_ancillary_data_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) ;
//0x6B

QVariant f_cell_list_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) ;
//0x6C

QVariant f_cell_frequency_link_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                          ) ;
//0x6D

QVariant f_announcement_support_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                           );
//0x6E

QVariant f_application_signalling_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             );
//0x6f

QVariant f_adaptation_field_data_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                            ) ;
//0x70

QVariant f_service_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                         ) ;
//0x71

QVariant f_service_availability_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                           );
//0x72

QVariant f_default_authority_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) ;
//0x73

QVariant f_related_content_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) ;
//0x74

QVariant f_TVA_id_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                             ) ;
//0x75

QVariant f_content_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                         );
//0x76

QVariant f_time_slice_fec_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) ;
//0x77
QVariant f_ECM_repetition_rate_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                          );
//0x78
QVariant f_S2_satellite_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                   );
//0x79
QVariant f_enhanced_AC_3_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                    );
//0x7A
QVariant f_DTS_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          );
//0x7B
QVariant f_AAC_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          );
//0x7C
QVariant f_XAIT_location_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                    ) ;
//0x7D
QVariant f_FTA_content_management_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             );
//0x7E
QVariant f_extension_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                );
// 0x83
QVariant f_logical_channel_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) ;

std::string running_status(uint8_t val);
std::string service_type (uint8_t val);
std::string private_data_specifier_name(uint32_t private_data_specifier);
};

#endif	/* DVB_SECTION_HPP */

