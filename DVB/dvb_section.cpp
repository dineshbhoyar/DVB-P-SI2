/*
 * File:   dvb_section.cpp
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



#include "dvb_section.hpp"
namespace APP_UTILS {

dvb_sections_discriptor::dvb_sections_discriptor() {
    descriptor.fill(f_default_descriptor);
    descriptor.at(0x01) = descriptor.at(0x00) = f_reserved_descriptor;
    descriptor.at(0x02) = f_video_stream_descriptor;
    descriptor.at(0x03) = f_audio_stream_descriptor;
    descriptor.at(0x04) = f_hierarchy_descriptor;
    descriptor.at(0x05) = f_registration_descriptor;
    descriptor.at(0x06) = f_data_stream_alignment_descriptor;
    descriptor.at(0x07) = f_target_background_grid_descriptor;
    descriptor.at(0x08) = f_Video_window_descriptor;
    descriptor.at(0x09) = f_CA_descriptor;
    descriptor.at(0x0a) = f_ISO_639_language_descriptor;
    descriptor.at(0x0b) = f_System_clock_descriptor;
    descriptor.at(0x0c) = f_Multiplex_buffer_utilization_descriptor;
    descriptor.at(0x0d) = f_Copyright_descriptor;
    descriptor.at(0x0e) = f_Maximum_bitrate_descriptor;
    descriptor.at(0x0f) = f_Private_data_indicator_descriptor;

    descriptor.at(0x10) = f_Smoothing_buffer_descriptor;

    descriptor.at(0x11) = f_STD_descriptor;
    descriptor.at(0x12) = f_IBP_descriptor;
    // TODO:- X Defined in ISO/IEC 13818-6 DSM_CC extension
    /*descriptor.at(19)=descriptor.at(26)=descriptor.at(26)=descriptor.at(26)=descriptor.at(26)=descriptor.at(26)=descriptor.at(26)=descriptor.at(26)= */

    descriptor.at(27) = f_MPEG_4_video_descriptor;
    descriptor.at(28) = f_MPEG_4_audio_descriptor;
    descriptor.at(29) = f_IOD_descriptor;
    descriptor.at(30) = f_SL_descriptor;
    descriptor.at(31) = f_FMC_descriptor;
    descriptor.at(32) = f_External_ES_ID_descriptor;
    descriptor.at(33) = f_MuxCode_descriptor;
    descriptor.at(34) = f_FmxBufferSize_descriptor;
    descriptor.at(35) = f_MultiplexBuffer_descriptor;
    //descriptor.at(36)-descriptor.at(63) n/a n/a ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved

    //64-255 n/a n/a User Private

    descriptor.at(network_name_descriptor) = f_network_name_descriptor;
    descriptor.at(service_list_descriptor) = f_service_list_descriptor;
    descriptor.at(stuffing_descriptor) = f_stuffing_descriptor;
    descriptor.at(satellite_delivery_system_descriptor) = f_satellite_delivery_system_descriptor;
    descriptor.at(cable_delivery_system_descriptor) = f_cable_delivery_system_descriptor;
    descriptor.at(VBI_data_descriptor) = f_VBI_data_descriptor;
    descriptor.at(VBI_teletext_descriptor) = f_VBI_teletext_descriptor;
    descriptor.at(bouquet_name_descriptor) = f_bouquet_name_descriptor;
    descriptor.at(service_descriptor) = f_service_descriptor;
    descriptor.at(country_availability_descriptor) = f_country_availability_descriptor;
    descriptor.at(linkage_descriptor) = f_linkage_descriptor;
    descriptor.at(NVOD_reference_descriptor) = f_NVOD_reference_descriptor;
    descriptor.at(time_shifted_service_descriptor) = f_time_shifted_service_descriptor;
    descriptor.at(short_event_descriptor) = f_short_event_descriptor;
    descriptor.at(extended_event_descriptor) = f_extended_event_descriptor;
    descriptor.at(time_shifted_event_descriptor) = f_time_shifted_event_descriptor;
    descriptor.at(component_descriptor) = f_component_descriptor;
    descriptor.at(mosaic_descriptor) = f_mosaic_descriptor;
    descriptor.at(stream_identifier_descriptor) = f_stream_identifier_descriptor;
    descriptor.at(CA_identifier_descriptor) = f_CA_identifier_descriptor;
    descriptor.at(content_descriptor) = f_content_descriptor;
    descriptor.at(parental_rating_descriptor) = f_parental_rating_descriptor;
    descriptor.at(teletext_descriptor) = f_teletext_descriptor;
    descriptor.at(telephone_descriptor) = f_telephone_descriptor;
    descriptor.at(local_time_offset_descriptor) = f_local_time_offset_descriptor;
    descriptor.at(subtitling_descriptor) = f_subtitling_descriptor;
    descriptor.at(terrestrial_delivery_system_descriptor) = f_terrestrial_delivery_system_descriptor;
    descriptor.at(multilingual_network_name_descriptor) = f_multilingual_network_name_descriptor;
    descriptor.at(multilingual_bouquet_name_descriptor) = f_multilingual_bouquet_name_descriptor;
    descriptor.at(multilingual_service_name_descriptor) = f_multilingual_service_name_descriptor;
    descriptor.at(multilingual_component_descriptor) = f_multilingual_component_descriptor;
    descriptor.at(private_data_specifier_descriptor) = f_private_data_specifier_descriptor;
    descriptor.at(service_move_descriptor) = f_service_move_descriptor;
    descriptor.at(short_smoothing_buffer_descriptor) = f_short_smoothing_buffer_descriptor;
    descriptor.at(frequency_list_descriptor) = f_frequency_list_descriptor;
    descriptor.at(partial_transport_stream_descriptor) = f_partial_transport_stream_descriptor;
    descriptor.at(data_broadcast_descriptor) = f_data_broadcast_descriptor;
    descriptor.at(scrambling_descriptor) = f_scrambling_descriptor;
    descriptor.at(data_broadcast_id_descriptor) = f_data_broadcast_id_descriptor;
    descriptor.at(transport_stream_descriptor) = f_transport_stream_descriptor;
    descriptor.at(DSNG_descriptor) = f_DSNG_descriptor;
    descriptor.at(PDC_descriptor) = f_PDC_descriptor;
    descriptor.at(AC_3_descriptor) = f_AC_3_descriptor;
    descriptor.at(ancillary_data_descriptor) = f_ancillary_data_descriptor;
    descriptor.at(cell_list_descriptor) = f_cell_list_descriptor;
    descriptor.at(cell_frequency_link_descriptor) = f_cell_frequency_link_descriptor;
    descriptor.at(announcement_support_descriptor) = f_announcement_support_descriptor;
    descriptor.at(application_signalling_descriptor) = f_application_signalling_descriptor;
    descriptor.at(adaptation_field_data_descriptor) = f_adaptation_field_data_descriptor;
    descriptor.at(service_identifier_descriptor) = f_service_identifier_descriptor;
    descriptor.at(service_availability_descriptor) = f_service_availability_descriptor;
    descriptor.at(default_authority_descriptor) = f_default_authority_descriptor;
    descriptor.at(related_content_descriptor) = f_related_content_descriptor;
    descriptor.at(TVA_id_descriptor) = f_TVA_id_descriptor;
    descriptor.at(content_identifier_descriptor) = f_content_identifier_descriptor;
    descriptor.at(time_slice_fec_identifier_descriptor) = f_time_slice_fec_identifier_descriptor;
    descriptor.at(ECM_repetition_rate_descriptor) = f_ECM_repetition_rate_descriptor;
    descriptor.at(S2_satellite_delivery_system_descriptor) = f_S2_satellite_delivery_system_descriptor;
    descriptor.at(enhanced_AC_3_descriptor) = f_enhanced_AC_3_descriptor;
    descriptor.at(DTS_descriptor) = f_DTS_descriptor;
    descriptor.at(AAC_descriptor) = f_AAC_descriptor;
    descriptor.at(XAIT_location_descriptor) = f_XAIT_location_descriptor;
    descriptor.at(FTA_content_management_descriptor) = f_FTA_content_management_descriptor;
    descriptor.at(extension_descriptor) = f_extension_descriptor;
    //added as part of observation
    descriptor.at(0x83) = descriptor.at(0xe2) = descriptor.at(0x81) = f_logical_channel_descriptor;

}

dvb_sections_discriptor::~dvb_sections_discriptor() {

};

fnptr& dvb_sections_discriptor::get(uint8_t des) {

    return descriptor[des];
};

uint32_t NIT_Container::Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor& dtable, SectionContaniner &container){
    if (buff == nullptr) {
        qDebug() << "nit timeout .....\n";
        return -1;
    }
    uint32_t retval = 0;

    ByteContainer a(buff);
    TSTableHeader nithdr("NIT", a);

    if (sectionno - nithdr.section_length != 3) {
        qDebug() << " section_length out of bound ... \n"
                 << nithdr;
        return -1;
    }
    if (nithdr.current_next_indicator != 1) {
        qDebug() << " current_next_indicator should be 1 got \n"
                 << nithdr;
        return -1;
    } else if (nithdr.section_length < 11 ) {
        qDebug() << " section_length out of bound  \n"
                 << nithdr;
        return -1;
    } else if (nithdr.section_number > nithdr.last_section_number) {
        qDebug() << " section_number invalid  \n"
                 << nithdr;
        return -1;
    }

    auto& verinfo = version[nithdr.bouquet_id];

    if (TableSectionVersionCheck(verinfo, nithdr)) {

        qDebug() << nithdr<<"\n";
        //check for while loop section_length
        uint16_t section_length = nithdr.section_length;


        int16_t network_descriptors_length = a.Byte2(0x0fff);
        //required for tsloop check
        int16_t network_descriptors_length_bk = network_descriptors_length ;
        // qDebug() << "network_descriptors_length : " << network_descriptors_length;
        if (network_descriptors_length > section_length) {
            qDebug() << " ERROR: network_descriptors_length : " << network_descriptors_length
                     << " is gretor than section_length len : " << (uint32_t) section_length
                     <<"\n";
            return -1;
        }

        if (network_descriptors_length) {
            while (network_descriptors_length > 0) {
                uint8_t des = a.Byte();
                uint8_t dlen = a.Byte();
                //                qDebug() << " n/w des type : "  << (uint32_t) des <<
                //                            " des len : " << (uint32_t) dlen <<
                //                            " network_descriptors_length remaining : " <<
                //                            std::dec << network_descriptors_length<<
                //                            "\n";
                if (network_descriptors_length < dlen) {
                    network_descriptors_length -= 2;
                    a.Skip(network_descriptors_length);
                    qDebug() << " ERROR: network_descriptors_length : "
                             << network_descriptors_length
                             << " is smaller than descriptor len : " << (uint32_t) dlen
                             <<"\n";
                    // verinfo.version = -1;
                    retval = -1;
                    break;
                }
                QVariant fdata = dtable.get(des)(des,dlen,container,a);
                switch (des) {
                case network_name_descriptor:
                    if(fdata.canConvert<Name>()){
                        Name name = fdata.value<Name>();
                        nit_descriptor.network_name = name.name;
                        qDebug() <<" nit network name " << nit_descriptor.network_name.c_str();
                    }else{
                     //   qDebug() << " error for key " << key;
                    }
                    break;
                default:
                    break;
                }
                network_descriptors_length -= 2+dlen;
                // a.Skip(dlen);
            }
        }else{
            qDebug() << "network_descriptors_length " << network_descriptors_length;
        }
        uint16_t tslooplen = a.Byte2(0x07ff);
        qDebug() << "ts loop len : " << tslooplen
                 << " remaining network_descriptors_length :  "
                 << network_descriptors_length<<"\n";
        section_length-=2;

        if ((network_descriptors_length_bk + tslooplen) > section_length) {
            qDebug() << " ERROR: network_descriptors_length+ tslooplen : "
                     << network_descriptors_length_bk + tslooplen
                     << " is gretor than section_length len : "
                     << (uint32_t) section_length
                     <<"\n";
            //verinfo.version = -1;

            return -1;
        }

        section_length -= network_descriptors_length_bk;

        for (int i = 0; i < tslooplen;) {
            NIT_Pirmary_Key key;
            isFristLoop =false;
            key.buoquet_id = nithdr.bouquet_id;
            key.transport_stream_id = a.Byte2();
            key.original_network_id = a.Byte2();
            auto& data =ts_descriptor[key];

            qDebug() << " NIT original_network_id :" << key.original_network_id
                     << " transport_stream_id : " << key.transport_stream_id
                     << " buoquet_id : " << key.buoquet_id;

            uint16_t transport_descriptors_length = a.Byte2(0x0fff);

            if (transport_descriptors_length > section_length) {
                qDebug() << " ERROR: transport_descriptors_length : "
                         << transport_descriptors_length
                         << " is gretor than section_length  : "
                         <<     (uint32_t) section_length<<"\n";
                // verinfo.version = -1;
                TableHexDump(buff,sectionno);
                retval = -1;
                break;
            }
            if (transport_descriptors_length) {
                i += 6;
                while (transport_descriptors_length > 0) {
                    uint8_t dsc = a.Byte();
                    uint8_t dlen = a.Byte();
                    qDebug() << " got ts descriptor :0x"
                             << (uint32_t) dsc << " of len : " <<
                                (uint32_t) dlen<<"\n";
                    if (transport_descriptors_length < dlen) {
                        transport_descriptors_length -= 2;
                        a.Skip(transport_descriptors_length);
                        qDebug() << " ERROR: transport_descriptors_length : "
                                 << transport_descriptors_length
                                 << " is smaller than descriptor len : "
                                 << (uint32_t) dlen<<"\n";
                        retval = -1;
                        break;
                    }
                    QVariant fdata = dtable.get(dsc)(dsc,dlen,container,a);
                    switch (dsc) {
                    case cable_delivery_system_descriptor:
                        if(fdata.canConvert<cable_delivery_system>()){
                            cable_delivery_system cds = fdata.value<cable_delivery_system>();
                            data.cds = cds;

                        }else{
                            qDebug() << " error for key " << key;
                        }
                        break;
                    case satellite_delivery_system_descriptor:
                        if(fdata.canConvert<satellite_delivery_system>()){
                            satellite_delivery_system sds = fdata.value<satellite_delivery_system>();
                            data.sds = sds;
                            qDebug()<< data.sds;
                        }else{
                            qDebug() << " error for key " << key;
                        }
                        break;
                    case terrestrial_delivery_system_descriptor:
                        if(fdata.canConvert<terrestrial_delivery_system>()){
                            terrestrial_delivery_system tds = fdata.value<terrestrial_delivery_system>();
                            data.tds = tds;

                        }else{
                            qDebug() << " error for key " << key;
                        }
                        break;
                    case network_name_descriptor:
                        if(fdata.canConvert<Name>()){
                            Name name = fdata.value<Name>();
                            data.network_name = name.name;
                        }else{
                            qDebug() << " error for key " << key;
                        }
                        break;
                    case service_list_descriptor:
                        if(fdata.canConvert<std::map<uint16_t,uint8_t>>()){
                            std::map<uint16_t,uint8_t> slist = fdata.value<std::map<uint16_t,uint8_t>>();
                            data.service_list =slist;
                            qDebug() << " slist length " << slist.size();
                        }else{
                            qDebug() << " error for key " << key;
                        }
                        break;
                    case logical_channel_number:
                    {
                        if(fdata.canConvert<std::map<uint16_t,uint16_t>>()){
                            std::map<uint16_t,uint16_t> lcn = fdata.value<std::map<uint16_t,uint16_t>>();
                            data.logiacal_channel=lcn;
                            qDebug() << " lcn size " << lcn.size();
                        }else {
                            qDebug() << " error for key " << key;
                        }
                    }
                        break;
                    default:
                        break;
                    }

                    transport_descriptors_length -= 2+dlen;
                    i+=dlen+2;

                }
            }
        }
    }else {
        // qDebug() << "alredy processed"<< /*nithdr<<*/"\n";
    }
    return retval;
}


QVariant f_default_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a)
{
    qDebug() << __FUNCTION__<<"(0x"
             <<std::hex<<(uint32_t)descriptor<<":"
            <<(uint32_t)length<< ")"<<"\n"
              ;
    a.Skip(length);
    return QVariant();
}
//  descriptor_tag TS PS Identification
//0 n/a n/a Reserved
//1 n/a n/a Reserved

QVariant f_reserved_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a)
{
    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    a.Skip(length);
    return QVariant();
}
//2 X X

QVariant f_video_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a  ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//3 X X

QVariant f_audio_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//4 X X

QVariant f_hierarchy_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//5 X X

QVariant f_registration_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//6 X X

QVariant f_data_stream_alignment_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                            ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//7 X X

void target_background_grid_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                       ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return ;
}
//8 X X

QVariant f_target_background_grid_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}

QVariant f_Video_window_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//9 X X

QVariant f_CA_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                         ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//10 X X

QVariant f_ISO_639_language_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor
             <<":"<<(uint32_t)length<< ")"<<"\n";
    std::map<uint8_t,ISO_639_language> langmap;
    uint8_t idx=0;
    if(length%4 ==0){
        while(length !=0 ){
            //std::string ISO_639_language_code{};
            langmap[idx].ISO_639_language_code.append(1,a.Byte());
            langmap[idx].ISO_639_language_code.append(1,a.Byte());
            langmap[idx].ISO_639_language_code.append(1,a.Byte());
            langmap[idx].audio_type = a.Byte();
            qDebug() << "audio_type : " <<(uint32_t) langmap[idx].audio_type
                     <<" ISO_639_language_code :" << langmap[idx].ISO_639_language_code.c_str()
                    <<"\n";
            length -=4;
            idx++;
        }
    }else{
        qDebug() << "error f_ISO_639_language_descriptor()";
        a.Skip(length);
    }
    return QVariant::fromValue(langmap);;
}
//11 X X

QVariant f_System_clock_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//12 X X

QVariant f_Multiplex_buffer_utilization_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//13 X X

QVariant f_Copyright_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//14 X

QVariant f_Maximum_bitrate_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//15 X X

QVariant f_Private_data_indicator_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//16 X X

QVariant f_Smoothing_buffer_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                       ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//17 X

QVariant f_STD_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
// 18 X X

QVariant f_IBP_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//19-26 X Defined in ISO/IEC 13818-6 DSM_CC extension
//27 X X

QVariant f_MPEG_4_video_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//28 X X

QVariant f_MPEG_4_audio_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//29 X X

QVariant f_IOD_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//30 X

QVariant f_SL_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                         ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//31 X X

QVariant f_FMC_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//32 X X

QVariant f_External_ES_ID_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//33 X X

QVariant f_MuxCode_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                              ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//34 X X

QVariant f_FmxBufferSize_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                    ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//35 X

QVariant f_MultiplexBuffer_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//36-63 n/a n/a ITU-T Rec. H.222.0 | ISO/IEC 13818-1 Reserved
//64-255 n/a n/a User Private

//0x40

QVariant f_network_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    Name name{};
    for (uint8_t i=0;i<length;i++){
        uint8_t chr = a.Byte();
        if (std::isprint(chr)) {
            if (std::isspace(chr)) {
                chr = ' ';

            } else if (chr == ',') {
                chr = ' ';
            }

            name.name.append(1,chr);
        }
    }
    //a.Skip(length);
    qDebug() << "network name : " <<name.name.c_str();
    return QVariant::fromValue(name);
}
//0x41

QVariant f_service_list_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {
    std::map <uint16_t,uint8_t> slist;
    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor
             <<":"<<(uint32_t)length<< ")"<<"\n";
    if (length %3 == 0){
        while (length!=0){
            uint16_t service_id = a.Byte2();
            uint8_t service_type = a.Byte();
            slist[service_id] = service_type;
            length-=3;
            qDebug() << "service_id : " << service_id
                     <<" service_type : "<< (uint32_t)service_type;
        }
    }else{
        qDebug() << " unexpected length " << length;
        a.Skip(length);
    }
    return QVariant::fromValue(slist);
}
//0x42

QVariant f_stuffing_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x43

QVariant f_satellite_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a)
{
    satellite_delivery_system sds{};
    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    if (length == 11){
        std::vector<uint8_t> frequency;
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        sds.frequency = ValueFromByteStream<double>(frequency,3);
        std::vector<uint8_t> orbital_position;
        orbital_position.push_back(a.Byte());
        orbital_position.push_back(a.Byte());
        sds.orbital_position = ValueFromByteStream<double>(orbital_position,3);
        sds.west_east_flag = a.Byte(0x80,false) >>7;
        sds.polarization = a.Byte(0x60,false)>>5;
        sds.roll_off = a.Byte(0x18,false)>>3;
        sds.modulation_system = a.Byte(0x04,false)>>2;
        if (sds.modulation_system != 1) {
            sds.roll_off=0;
        }

        sds.modulation_type = a.Byte(0x03);
        //sds.symbol_rate = a.Byte4(0xffffff00,false);
        std::vector<uint8_t> symbol_rate{};
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte(0xf0,false));
        sds.symbol_rate = ValueFromByteStream<double>(symbol_rate,3);
        sds.FEC_inner =(uint8_t)a.Byte(0x0f);
    }else{
        qDebug()<<"Error parsing satellite_delivery_system_descriptor" ;
        a.Skip(length);
    }
    return QVariant::fromValue(sds);
}
//0x44
QVariant f_cable_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                            ) {
    cable_delivery_system cds{};
    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    if(length == 11){
        std::vector<uint8_t> frequency;
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        cds.frequency = ValueFromByteStream<double>(frequency,4);
        uint16_t reserved_future_use = a.Byte2(0xfff0,false);
        cds.FEC_outer = (uint8_t)a.Byte2(0x000f);
        uint8_t modulation = a.Byte();
        cds.modulation = (uint32_t) std::pow(2.0,modulation + 3);
        std::vector<uint8_t> symbol_rate{};
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte(0xf0,false));
        cds.symbol_rate = ValueFromByteStream<double>(symbol_rate,3);
        cds.FEC_inner = a.Byte(0x0f);
        qDebug() << " frequency : " /*<< std::fixed << std::setprecision(4)*/
                 << cds.frequency
                 << " MHz FEC_outer : " << (uint32_t) cds.FEC_outer
                 << " modulation : " << (uint32_t)cds.modulation/*(uint32_t) std::pow(2.0, cds.modulation + 3)*/
                 << " QAM symbol_rate : " /*<< std::fixed << std::setprecision(3)*/
                 << cds.symbol_rate
                 << " Msymbol/s FEC_inner : " << (uint32_t) cds.FEC_inner
                 <<"\n";
    }else {
        qDebug() << " unexpected length " << length<<"\n";
        a.Skip(length);
    }

    return QVariant::fromValue(cds);
}

QVariant gf_cable_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {
    cable_delivery_system cds{};
    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    if(length == 11){
        std::vector<uint8_t> frequency;
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        frequency.push_back(a.Byte());
        cds.frequency = ValueFromByteStream<double>(frequency,4);
        uint16_t reserved_future_use = a.Byte2(0xfff0,false);
        cds.FEC_outer = (uint8_t)a.Byte2(0x000f);
        cds.modulation = a.Byte();
        std::vector<uint8_t> symbol_rate;
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte());
        symbol_rate.push_back(a.Byte(0xf0,false));
        cds.symbol_rate = ValueFromByteStream<double>(symbol_rate,3);
        cds.FEC_inner = a.Byte(0x0f);
        qDebug() << " frequency : " /*<< std::fixed << std::setprecision(4)*/
                 << cds.frequency
                 << " MHz FEC_outer : " << (uint32_t) cds.FEC_outer
                 << " modulation : " << (uint32_t) std::pow(2.0, cds.modulation + 3)
                 << " QAM symbol_rate : " /*<< std::fixed << std::setprecision(3)*/
                 << cds.symbol_rate
                 << " Msymbol/s FEC_inner : " << (uint32_t) cds.FEC_inner
                 <<"\n";
    }else {
        qDebug() << " unexpected length " << length<<"\n";
        a.Skip(length);
    }

    return QVariant();
}
//0x45

QVariant f_VBI_data_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                               ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x45

QVariant f_VBI_teletext_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    std::string ISO_639_language_code{};
    uint8_t teletext_type;
    uint8_t teletext_magazine_number;
    uint8_t teletext_page_number;
    for (uint8_t i=0;i<length;i++) {
        ISO_639_language_code.append(1,a.Byte());
        ISO_639_language_code.append(1,a.Byte());
        ISO_639_language_code.append(1,a.Byte());
        teletext_type = a.Byte(0xf1,false)>>3;
        teletext_magazine_number = a.Byte(0x07);
        teletext_page_number = a.Byte();
    }

    //a.Skip(length);
    return QVariant();
}
//0x46

QVariant f_bouquet_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {
    Name name{};
    qDebug() << __FUNCTION__
             <<"("<<(uint32_t)descriptor
            <<":"<<(uint32_t)length<< ")"<<"\n"
              ;
    //std::string name{};
    for(uint8_t i=0;i<length;i++){
        name.name.append(1,a.Byte());
    }
    qDebug() <<"name : "<<name.name.c_str();
    //a.Skip(length);
    return QVariant::fromValue(name);
}
//0x47

QVariant f_service_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a)
{
    qDebug() << __FUNCTION__
             <<"("<<(uint32_t)descriptor
            <<":"<<(uint32_t)length<< ")"<<"\n"
              ;
    service sdesc{};
    sdesc.service_type = a.Byte();
    uint8_t service_provider_name_length = a.Byte();

    qDebug() << " service_type : "<< (uint32_t) sdesc.service_type
             << " service_provider_name_length : "<<(uint32_t) service_provider_name_length
             << "\n";
    for (uint8_t i=0;i<service_provider_name_length;i++){
        uint8_t chr = a.Byte();
        if (std::isprint(chr)) {
            if (std::isspace(chr)) {
                chr = ' ';
            } else if (chr == ',') {
                chr = ' ';
            }
            sdesc.service_provider_name.append(1,chr);
        }
    }
    uint8_t service_name_length = a.Byte();
    qDebug() << "service_name_length : " <<service_name_length<<"\n";
    for (uint8_t i=0;i<service_name_length;i++){
        uint8_t chr = a.Byte();
        if (std::isprint(chr)) {
            if (std::isspace(chr)) {
                chr = ' ';
            } else if (chr == ',') {
                chr = ' ';
            }
            sdesc.service_name.append(1,chr);
        }
    }
    qDebug() << "spname : "<<sdesc.service_provider_name.c_str()
             <<" sname : "<<sdesc.service_name.c_str();
    //a.Skip(length);
    return QVariant::fromValue(sdesc);
}
//0x48

QVariant f_country_availability_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    uint8_t  country_availability_flag = a.Byte(0x80,false)>>7;
    uint8_t reserved_future_use = a.Byte(0x7f);
    std::string country_code{};
    for (uint8_t i=0;i<length-2;i++){
        country_code.append(1,a.Byte());
        country_code.append(1,a.Byte());
        country_code.append(1,a.Byte());
        country_code.append(1,',');
    }

    // a.Skip(length);
    return QVariant();
}
//0x49

QVariant f_linkage_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                              ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x4A

QVariant f_NVOD_reference_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    for (uint32_t i=0;i<length;i++) {
        uint16_t transport_stream_id =a.Byte2();
        uint16_t original_network_id =a.Byte2();
        uint16_t service_id = a.Byte2();
    }

    //a.Skip(length);
    return QVariant();
}
//0x4B

QVariant f_time_shifted_service_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                           ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    uint16_t reference_service_id = a.Byte2();
    //a.Skip(length);
    return QVariant();
}
//0x4C

QVariant f_short_event_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                  ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    std::string ISO_639_language_code{};
    ISO_639_language_code.append(1,a.Byte());
    ISO_639_language_code.append(1,a.Byte());
    ISO_639_language_code.append(1,a.Byte());
    uint8_t event_name_length = a.Byte();
    std::string event_name_char{};
    for (uint8_t i=0;i<event_name_length;i++){
        event_name_char.append(1,a.Byte());
    }
    uint8_t text_length = a.Byte();
    std::string text_char{};
    for (uint8_t i=0;i<text_length;i++){
        text_char.append(1,a.Byte());
    }

    //a.Skip(length);
    return QVariant();
}
//0x4D

QVariant f_extended_event_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    uint8_t descriptor_number = a.Byte(0xf0,false)>>4;
    uint8_t last_descriptor_number = a.Byte(0x0f);
    std::string ISO_639_language_code{};
    ISO_639_language_code.append(1,a.Byte());
    ISO_639_language_code.append(1,a.Byte());
    ISO_639_language_code.append(1,a.Byte());
    uint8_t length_of_items = a.Byte();

    for ( uint8_t i=0;i<length_of_items;i++){
        uint8_t item_description_length = a.Byte();
        std::string item_description_char{};
        for (uint8_t j=0;j<item_description_length;j++){
            item_description_char.append(1,a.Byte());
        }
        uint8_t item_length = a.Byte();
        std::string item_char{};
        for (uint8_t j=0;j<item_length;j++){
            item_char.append(1,a.Byte());
        }
    }
    uint8_t text_length = a.Byte();
    std::string text_char;
    for (uint8_t i=0;i<text_length;i++){
        text_char.append(1,a.Byte());
    }

    // a.Skip(length);
    return QVariant();
}
//0x4E

QVariant f_time_shifted_event_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                         ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    uint16_t reference_service_id = a.Byte();
    uint16_t reference_event_id = a.Byte();

    //a.Skip(length);
    return QVariant();
}
//0x4f

QVariant f_component_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    uint8_t stream_content_ext = a.Byte(0xf0,false)>>4;
    uint8_t stream_content = a.Byte(0x0f);
    uint8_t component_type = a.Byte();
    uint8_t component_tag = a.Byte();
    std::string ISO_639_language_code{};
    ISO_639_language_code.append(1,a.Byte());
    ISO_639_language_code.append(1,a.Byte());
    ISO_639_language_code.append(1,a.Byte());
    std::string text_char{};
    for (uint8_t i=0;i<length-6;i++){
        text_char.append(1,a.Byte());
    }

    //a.Skip(length);
    return QVariant();
}
//0x50

QVariant f_mosaic_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x51

QVariant f_stream_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    uint8_t component_tag = a.Byte();
    // a.Skip(length);
    return QVariant();
}
//0x52

QVariant f_CA_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    for (uint8_t i=0;i<length;i++){
        uint16_t CA_system_id =a.Byte2();
    }
    // a.Skip(length);
    return QVariant();
}
//0x53

QVariant f_content_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    for (uint8_t i=0;i<length;i++) {
        uint8_t content_nibble_level_1 =a.Byte(0xf0,false)>>4;
        uint8_t content_nibble_level_2 = a.Byte(0x0f);
        uint8_t user_byte = a.Byte();
    }
    // a.Skip(length);
    return QVariant();
}
//0x54

QVariant f_parental_rating_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    for (uint8_t i=0;i<length;i++){
        std::string country_code{};
        country_code.append(1,a.Byte());
        country_code.append(1,a.Byte());
        country_code.append(1,a.Byte());
        uint8_t rating =a.Byte();
    }

    // a.Skip(length);
    return QVariant();
}
//0x55

QVariant f_teletext_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                               ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    std::string ISO_639_language_code{};
    uint8_t teletext_type;
    uint8_t teletext_magazine_number;
    uint8_t teletext_page_number;
    for (uint8_t i=0;i<length;i++) {
        ISO_639_language_code.append(1,a.Byte());
        ISO_639_language_code.append(1,a.Byte());
        ISO_639_language_code.append(1,a.Byte());
        teletext_type = a.Byte(0xf1,false)>>3;
        teletext_magazine_number = a.Byte(0x07);
        teletext_page_number = a.Byte();
    }


    //a.Skip(length);
    return QVariant();
}
//0x56

QVariant f_telephone_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x57

QVariant f_local_time_offset_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x58

QVariant f_subtitling_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                 ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x59

QVariant f_terrestrial_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    terrestrial_delivery_system tsd{};
    if (length == 11){
        tsd.centre_frequency = a.Byte4();
        tsd.bandwidth = a.Byte(0xe0,false)>>5;
        tsd.priority = a.Byte(0x10,false)>>4;
        tsd.Time_Slicing_indicator = a.Byte(0x08,false)>>3;
        tsd.MPE_FEC_indicator = a.Byte(0x04,false)>>2;
        tsd.reserved_future_use1 = a.Byte(0x03);
        tsd.constellation = a.Byte(0xc0,false)>>6;
        tsd.hierarchy_information = a.Byte(0x38,false)>>3;
        tsd.code_rate_HP_stream = a.Byte(0x07);
        tsd.code_rate_LP_stream = a.Byte(0xe0,false)>>5;
        tsd.guard_interval = a.Byte(0x18,false)>>3;
        tsd.transmission_mode = a.Byte(0x06,false)>>1;
        tsd.other_frequency_flag = a.Byte(0x01);
        tsd.reserved_future_use2 = a.Byte4();
    }else{
        qDebug() << " Error terrestrial_delivery_system_descriptor";
        a.Skip(length);
    }
    return QVariant::fromValue(tsd);
}
//0x5A

QVariant f_multilingual_network_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x5B

QVariant f_multilingual_bouquet_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x5C

QVariant f_multilingual_service_name_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x5D

QVariant f_multilingual_component_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x5E

QVariant f_private_data_specifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    if (length == 4){
        switch (sections.currentTableIdInUse) {
        case NIT_TABLEID_ACTUAL:
            sections.nitActual.private_data_specifier = a.Byte4();
            qDebug() << "NIT Actual private_data_specifier : 0x"  << sections.nitActual.private_data_specifier;
            break;
        case NIT_TABLEID_OTHER:
            sections.nitOther.private_data_specifier = a.Byte4();
            qDebug() << "NIT Other private_data_specifier : 0x"  << sections.nitOther.private_data_specifier;
            break;
        case PAT_TABLEID:
            sections.pat.private_data_specifier = a.Byte4();
            qDebug() << "PAT Other private_data_specifier : 0x"  << sections.pat.private_data_specifier;
            break;
        case PMT_TABLEID:
            sections.pmt.private_data_specifier = a.Byte4();
            qDebug() << "PMT Other private_data_specifier : 0x"  << sections.pmt.private_data_specifier;
            break;
        case BAT_TABLEID:
            sections.bat.private_data_specifier = a.Byte4();
            qDebug() << "BAT Other private_data_specifier : 0x"  << sections.bat.private_data_specifier;
            break;
        case SDT_TABLEID_ACTUAL:
            sections.sdtActual.private_data_specifier = a.Byte4();
            qDebug() << "NIT Other private_data_specifier : 0x"  << sections.sdtActual.private_data_specifier;
            break;
        case SDT_TABLEID_OTHER:
            sections.sdtOther.private_data_specifier = a.Byte4();
            qDebug() << "NIT Other private_data_specifier : 0x"  << sections.sdtOther.private_data_specifier;

            break;
        default:
            qDebug() << "not handled \n";
            a.Skip(length);
            break;
        }
    }else{
        qDebug() << " unexpected length " << length<<"\n";
        a.Skip(length);
    }
    return QVariant();
}
//0x5f

QVariant f_service_move_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a )
{
    qDebug() << __FUNCTION__<<"(0x"
             <<std::hex<<(uint32_t)descriptor
            <<":"<<std::dec<<(uint32_t)length
           << ")";
    if(length == 6){
        uint16_t  new_original_network_id = a.Byte2();
        uint16_t  new_transport_stream_id = a.Byte2();
        uint16_t  new_service_id = a.Byte2();
        qDebug() << " new_original_network_id : " <<new_original_network_id <<
                    " new_transport_stream_id :" <<new_transport_stream_id <<
                    " new_service_id : " <<  new_service_id ;
    }else{
        qDebug() << " unexpected length " << length<<"\n";
        a.Skip(length);
    }
    return QVariant();
}
//0x60

QVariant f_short_smoothing_buffer_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x61

QVariant f_frequency_list_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x62

QVariant f_partial_transport_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                               ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x63

QVariant f_data_broadcast_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x64

QVariant f_scrambling_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";

    if(length ==1){
        uint8_t scrambling_mode = a.Byte();
    }else{
        qDebug() << " unexpected length " << length<<"\n";
        a.Skip(length);
    }
    return QVariant();
}
//0x65

QVariant f_data_broadcast_id_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x66

QVariant f_transport_stream_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                       ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x67

QVariant f_DSNG_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                           ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x68

QVariant f_PDC_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x69

QVariant f_AC_3_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                           ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x6A

QVariant f_ancillary_data_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                     ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x6B

QVariant f_cell_list_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x6C

QVariant f_cell_frequency_link_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x6D

QVariant f_announcement_support_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                           ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x6E

QVariant f_application_signalling_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x6f

QVariant f_adaptation_field_data_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                            ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x70

QVariant f_service_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                         ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x71

QVariant f_service_availability_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                           ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    uint8_t availability_flag = a.Byte(0x80,false)>>7;
    uint8_t reserved = a.Byte(0x7f);
    for (uint8_t i=0;i<length-1;i++) {
        uint16_t cell_id = a.Byte();
    }

    // a.Skip(length);
    return QVariant();
}
//0x72

QVariant f_default_authority_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                        ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x73

QVariant f_related_content_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x74

QVariant f_TVA_id_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x75

QVariant f_content_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                         ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x76

QVariant f_time_slice_fec_identifier_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x77

QVariant f_ECM_repetition_rate_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x78

QVariant f_S2_satellite_delivery_system_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                                   ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    uint8_t scrambling_sequence_selector = (uint8_t)(a.Byte(0x80,false) >>7);
    uint8_t multiple_input_stream_flag = (uint8_t)(a.Byte(0x40,false) >>6);
    uint8_t backwards_compatibility_indicator = (uint8_t)(a.Byte(0x20,false) >>5);
    uint8_t reserved_future_use = a.Byte(0x1f);
    if (scrambling_sequence_selector == 1){
        uint8_t Reserved = (uint8_t)(a.Byte(0xfc,false) >>2);
        uint32_t scrambling_sequence_index = (a.Byte2(0x3fff)<<8)&0x00fffc00;
        scrambling_sequence_index |= (a.Byte()&0x000000ff);
    }
    if (multiple_input_stream_flag == 1){
        uint8_t input_stream_identifier = a.Byte();
    }

    //a.Skip(length);
    return QVariant();
}
//0x79

QVariant f_enhanced_AC_3_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                    ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x7A

QVariant f_DTS_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x7B

QVariant f_AAC_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                          ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x7C

QVariant f_XAIT_location_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                    ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x7D

QVariant f_FTA_content_management_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                             ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";


    a.Skip(length);
    return QVariant();
}
//0x7E

QVariant f_extension_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<
                ":"<<(uint32_t)length<< ")"<<"\n"
                ;
    uint8_t descriptor_tag_extension = a.Byte();
    for (uint8_t i=0;i<descriptor_tag_extension;i++){
        uint8_t selector_byte = a.Byte();
    }

    //a.Skip(length);
    return QVariant();
}
// 0x83

QVariant f_logical_channel_descriptor(uint8_t descriptor, uint32_t length, SectionContaniner& sections,ByteContainer&a
                                      ) {

    qDebug() << __FUNCTION__<<"("<<(uint32_t)descriptor<<":"<<(uint32_t)length<< ")"<<"\n";
    std::map<uint16_t,uint16_t> lcn;
    if(length%4==0){
        while(length !=0) {
            uint16_t service_id = a.Byte2();
            uint8_t visible_service_flag = a.Byte2(0x8000,false);
            uint8_t reserved= (uint8_t)a.Byte2(0x7c00,false)>>9;
            uint16_t Logical_Channel_Number = a.Byte2(0x03ff);
            qDebug() << "service_id : "<<service_id
                     <<" visible_service_flag : " <<(uint32_t) visible_service_flag
                    <<" Logical_Channel_Number : "<< Logical_Channel_Number
                      ;
            length -=4;
            lcn[service_id] = Logical_Channel_Number;
        }
    }else{
        qDebug() << "error f_logical_channel_descriptor()";
        a.Skip(length);
    }
    return QVariant::fromValue(lcn);
}

std::string running_status(uint8_t val) {
    std::string name;
    switch (val) {
    case 0:
        name = "undefined";
        break;
    case 1:
        name = "not running";
        break;
    case 2:
        name = "starts in a few seconds";
        break;
    case 3:
        name = "pausing";
        break;
    case 4:
        name = "running";
        break;
    case 5:
        name = "off-air";
        break;
    default:
        name = "reserved for future use";
        break;
    }
    return name;
}

std::string service_type(uint8_t val) {
    std::string name;
    switch (val) {
    case 0x01: name = "digital television service";
        break;
    case 0x02: name = "digital radio sound service";
        break;
    case 0x03: name = "Teletext service";
        break;
    case 0x04: name = "NVOD reference service";
        break;
    case 0x05: name = "NVOD time - shifted service";
        break;
    case 0x06: name = "mosaic service";
        break;
    case 0x07: name = "FM radio service";
        break;
    case 0x08: name = "DVB SRM service";
        break;
    case 0x0A: name = "advanced codec digital radio sound service";
        break;
    case 0x0B: name = "H.264 / AVC mosaic service";
        break;
    case 0x0C: name = "data broadcast service";
        break;
    case 0x0D: name = "reserved for Common Interface Usage(CENELEC EN 50221 [37])";
        break;
    case 0x0E: name = "RCS Map(see ETSI EN 301 790 [7])";
        break;
    case 0x0F: name = "RCS FLS(see ETSI EN 301 790 [7])";
        break;
    case 0x10: name = "DVB MHP service";
        break;
    case 0x11: name = "MPEG - 2 HD digital television service";
        break;
    case 0x16:name = "H.264 / AVC SD digital television service";
        break;
    case 0x17:name = "H.264 / AVC SD NVOD time - shifted service";
        break;
    case 0x18:name = " H.264 / AVC SD NVOD reference service";
        break;
    case 0x19:name = " H.264 / AVC HD digital television service";
        break;
    case 0x1A:name = " H.264 / AVC HD NVOD time - shifted service";
        break;
    case 0x1B:name = " H.264 / AVC HD NVOD reference service";
        break;
    case 0x1C:name = " H.264 / AVC frame compatible plano - stereoscopic HD digital television service";
        break;
    case 0x1D:name = " H.264 / AVC frame compatible plano - stereoscopic HD NVOD time - shifted";
        break;
    case 0x1E:name = " H.264 / AVC frame compatible plano - stereoscopic HD NVOD reference service";
        break;
    case 0x1F:name = " HEVC digital television service";
        break;
    default:
        if ((val == 0x00) || (val == 0x09)
                || ((val >= 0x12) || (val <= 0x15))
                || ((val >= 0x20) || (val <= 0x7F))
                || (val == 0xFF)) {
            name = "reserved for future use";
        } else if ((val >= 0x80) || (val <= 0xFE)) {
            name = "user defined";
        } else {
            name = "reserved for future use";
        }
        break;

    }
    return name;
}

std::string private_data_specifier_name(uint32_t private_data_specifier) {
    std::string name;
    if (private_data_specifier == 0x00000001) {
        name = "SES";
    } else if (private_data_specifier >= 0x00000002 && private_data_specifier <= 0x00000004) {
        name = "BskyB 1 - 3";
    } else if (private_data_specifier == 0x00000005) {
        name = "ARD, ZDF, ORF";
    } else if (private_data_specifier == 0x00000006) {
        name = "Nokia Multimedia Network Terminals";
    } else if (private_data_specifier == 0x00000007) {
        name = "AT Entertainment Ltd.";
    } else if (private_data_specifier == 0x00000008) {
        name = "TV Cabo Portugal";
    } else if (private_data_specifier >= 0x00000009 && private_data_specifier <= 0x0000000D) {
        name = "Nagravision SA – Kudelski 1 - 5";
    } else if (private_data_specifier == 0x0000000E) {
        name = "Valvision SA";
    } else if (private_data_specifier == 0x0000000F) {
        name = "Quiero Televisión";
    } else if (private_data_specifier == 0x00000010) {
        name = "La Télévision Par Satellite (TPS)";
    } else if (private_data_specifier == 0x00000011) {
        name = "Echostar Communications";
    } else if (private_data_specifier == 0x00000012) {
        name = "Telia AB";
    } else if (private_data_specifier == 0x00000013) {
        name = "Viasat";
    } else if (private_data_specifier == 0x00000014) {
        name = "Boxer TV Access";
    } else if (private_data_specifier == 0x00000015) {
        name = "MediaKabel";
    } else if (private_data_specifier == 0x00000016) {
        name = "Casema";
    } else if (private_data_specifier == 0x00000017) {
        name = "Humax Electronics Co. Ltd .";
    } else if (private_data_specifier == 0x00000018) {
        name = "Neotion SA";
    } else if (private_data_specifier == 0x00000019) {
        name = "Singapore Digital Terrestrial Television";
    } else if (private_data_specifier == 0x0000001A) {
        name = "Télédiffusion de France (TDF)";
    } else if (private_data_specifier == 0x0000001B) {
        name = "Intellibyte Inc.";
    } else if (private_data_specifier == 0x0000001C) {
        name = "Digital Theater Systems Ltd";
    } else if (private_data_specifier == 0x0000001D) {
        name = "Finlux Ltd.";
    } else if (private_data_specifier == 0x0000001E) {
        name = "Sagem SA";
    } else if (private_data_specifier == 0x0000001F) {
        name = "Beijing Compunicate Technology Inc";
    } else if (private_data_specifier >= 0x00000020 && private_data_specifier <= 0x00000023) {
        name = "Lyonnaise Cable 1 - 4";
    } else if (private_data_specifier == 0x00000024) {
        name = "Metronic";
    } else if (private_data_specifier == 0x00000025) {
        name = "MTV Europe ";
    } else if (private_data_specifier == 0x00000026) {
        name = "Pansonic";
    } else if (private_data_specifier == 0x00000027) {
        name = "Mentor Data System, Inc .";
    } else if (private_data_specifier == 0x00000028) {
        name = "EACEM";
    } else if (private_data_specifier == 0x00000029) {
        name = "NorDig";
    } else if (private_data_specifier == 0x0000002A) {
        name = "Intelsis Sistemas Inteligentes S.A .";
    } else if (private_data_specifier == 0x0000002B) {
        name = "DTV haber ve Gorsel yayýncilik";
    } else if (private_data_specifier == 0x0000002D) {
        name = "Alpha Digital Synthesis S.A.";
    } else if (private_data_specifier == 0x0000002E) {
        name = "THOMSON";
    } else if (private_data_specifier == 0x0000002F) {
        name = "Conax A.S.";
    } else if (private_data_specifier == 0x00000030) {
        name = "Telenor";
    } else if (private_data_specifier == 0x00000031) {
        name = "TeleDenmark";
    } else if (private_data_specifier == 0x00000032) {
        name = "Foxtel Management";
    } else if (private_data_specifier == 0x00000033) {
        name = "InOutTV";
    } else if (private_data_specifier == 0x00000034) {
        name = "InOutTV SA (2)";
    } else if (private_data_specifier == 0x00000035) {
        name = "Europe Online Networks S.A .";
    } else if (private_data_specifier == 0x00000036) {
        name = "Groupe Canal+";
    } else if (private_data_specifier == 0x00000037) {
        name = "FreeView (NZ)";
    } else if (private_data_specifier == 0x00000038) {
        name = "OTE";
    } else if (private_data_specifier == 0x00000039) {
        name = "Telewizja Polsat";
    } else if (private_data_specifier == 0x0000003A) {
        name = "arena Sport Rechte und Marketing GmbH";
    } else if (private_data_specifier == 0x0000003B) {
        name = "Wyplay SAS";
    } else if (private_data_specifier == 0x0000003D) {
        name = "Interactive Technologies AD";
    } else if (private_data_specifier == 0x0000003E) {
        name = "T-Kábel Magyarország Kft.";
    } else if (private_data_specifier == 0x0000003F) {
        name = "ITI Neovision";
    } else if (private_data_specifier == 0x00000040) {
        name = "CI Plus LLP";
    } else if (private_data_specifier == 0x00000041) {
        name = "France Telecom Orange";
    } else if (private_data_specifier == 0x00000050) {
        name = "Com Hem ab";
    } else if (private_data_specifier == 0x000000A0) {
        name = "Sentech";
    } else if (private_data_specifier == 0x000000A1) {
        name = "TechniSat Digital GmbH";
    } else if (private_data_specifier == 0x000000A2) {
        name = "LogiWays";
    } else if (private_data_specifier == 0x000000A3) {
        name = "EFG";
    } else if (private_data_specifier == 0x000000A4) {
        name = "CANAL+ INTERNATIONAL";
    } else if (private_data_specifier == 0x000000A5) {
        name = "Canal+ Cyfrowy";
    } else if (private_data_specifier == 0x000000B0) {
        name = "ITI Neovision Sp. z.o.o.";
    } else if (private_data_specifier == 0x000000BE) {
        name = "BetaTechnik";
    } else if (private_data_specifier == 0x000000C0) {
        name = "NDS France";
    } else if (private_data_specifier == 0x000000D0) {
        name = "Dolby Laboratories Inc.";
    } else if (private_data_specifier == 0x000000E0) {
        name = "ExpressVu Inc.";
    } else if (private_data_specifier == 0x000000F0) {
        name = "France Telecom, CNES and DGA (STENTOR)";
    } else if (private_data_specifier == 0x00000100) {
        name = "OpenTV";
    } else if (private_data_specifier == 0x00000110) {
        name = "Media Broadcast GmbH";
    } else if (private_data_specifier == 0x0000013F) {
        name = "Eutelsat S.A. (1)";
    } else if (private_data_specifier == 0x00000140) {
        name = "Eltrona-Interdiffusion S.A.";
    } else if (private_data_specifier == 0x00000150) {
        name = "Loewe Opta GmbH";
    } else if (private_data_specifier == 0x00000160) {
        name = "Triax A/S";
    } else if (private_data_specifier == 0x00000170) {
        name = "Deutsche Telekom AG";
    } else if (private_data_specifier == 0x00000180) {
        name = "EAB - Ericsson AB";
    } else if (private_data_specifier == 0x00000190) {
        name = "Samsung Electronics (UK) Ltd";
    } else if (private_data_specifier == 0x000001A0) {
        name = "RCS&RDS";
    } else if (private_data_specifier == 0x000001B0) {
        name = "ORS comm GmbH & Co KG";
    } else if (private_data_specifier == 0x0000055F) {
        name = "Eutelsat S.A. (2)";
    } else if (private_data_specifier >= 0x00000600 && private_data_specifier <= 0x00000601) {
        name = "UPC 1 - 2";
    } else if (private_data_specifier >= 0x00000602 && private_data_specifier <= 0x00000603) {
        name = "UPC Broadband Holding Services BV";
    } else if (private_data_specifier >= 0x00000604 && private_data_specifier <= 0x00000605) {
        name = "Liberty Global Operations B.V.";
    } else if (private_data_specifier == 0x00000A2B) {
        name = "WISI";
    } else if (private_data_specifier == 0x00000ACE) {
        name = "Ortikon Interactive Oy";
    } else if (private_data_specifier == 0x00000AD0) {
        name = "Zenterio AB";
    } else if (private_data_specifier == 0x00000AE0) {
        name = "Mobistar";
    } else if (private_data_specifier == 0x00000AF0) {
        name = "Inview Technology Ltd";
    } else if (private_data_specifier == 0x00000B00) {
        name = "Slovak Telecom, a.s";
    } else if (private_data_specifier == 0x00001000) {
        name = "La Télévision Par Satellite (TPS )";
    } else if (private_data_specifier == 0x000010F0) {
        name = "TP S.A.";
    } else if (private_data_specifier == 0x00002000) {
        name = "UC-Connect";
    } else if (private_data_specifier == 0x00002004) {
        name = "DTT Afghanistan";
    } else if (private_data_specifier == 0x00002046) {
        name = "DTT Bosnia and Herzegovina";
    } else if (private_data_specifier == 0x00002060) {
        name = "DTT Brunei";
    } else if (private_data_specifier == 0x00002068) {
        name = "DTT Myanmar";
    } else if (private_data_specifier == 0x00002084) {
        name = "DTT Cape Verde";
    } else if (private_data_specifier == 0x000020AA) {
        name = "Comision Nacional de Television de Colombia";
    } else if (private_data_specifier == 0x0000210C) {
        name = "Georgian DTT";
    } else if (private_data_specifier == 0x0000212C) {
        name = "DTT Greece";
    } else if (private_data_specifier == 0x00002160) {
        name = "Vodafone Iceland";
    } else if (private_data_specifier == 0x00002168) {
        name = "Ministry of Communication and Information Technology of the Republic of Indonesia";
    } else if (private_data_specifier == 0x00002180) {
        name = "DTT Cote D\'Ivoire";
    } else if (private_data_specifier == 0x000021CA) {
        name = "MYTV";
    } else if (private_data_specifier == 0x000021EC) {
        name = "DTT Monaco";
    } else if (private_data_specifier == 0x00002213) {
        name = "DTT for Country of Curacao";
    } else if (private_data_specifier == 0x0000224F) {
        name = "Autorida Nacional de los Servicios Publicos";
    } else if (private_data_specifier == 0x00002256) {
        name = "DTT Papua New Guinea";
    } else if (private_data_specifier == 0x00002268) {
        name = "Office of Electronic Communications";
    } else if (private_data_specifier == 0x00002283) {
        name = "DTT - Russian Federation";
    } else if (private_data_specifier == 0x000022AE) {
        name = "DTT Senegal";
    } else if (private_data_specifier == 0x000022B0) {
        name = "DTT Serbia - JP Emisiona Tehnika i Veze";
    } else if (private_data_specifier == 0x000022B2) {
        name = "DTT Seychelles";
    } else if (private_data_specifier == 0x000022BF) {
        name = "DTT Slovak Digital Terrestrial Television";
    } else if (private_data_specifier == 0x000022C1) {
        name = "DTT - Slovenia Digital Terrestrial Television";
    } else if (private_data_specifier == 0x000022C6) {
        name = "DTT - South African Digital Terrestrial Television";
    } else if (private_data_specifier == 0x000022C7) {
        name = "DTT- Hungarian Digital Terrestrial Television";
    } else if (private_data_specifier == 0x000022C8) {
        name = "SIA Lattelecom";
    } else if (private_data_specifier == 0x000022CE) {
        name = "DTT - Irish Digital Terrestrial Television";
    } else if (private_data_specifier == 0x000022CF) {
        name = "DTT- Portugal Digital Terrestrial Television";
    } else if (private_data_specifier == 0x000022D4) {
        name = "“Spanish Broadcasting Regulator";
    } else if (private_data_specifier == 0x000022EC) {
        name = "DTT Swaziland";
    } else if (private_data_specifier == 0x000022F1) {
        name = "Swedish Broadcasting Regulator";
    } else if (private_data_specifier == 0x000022FC) {
        name = "Office of National Broadcasting and Telecommunications Commission";
    } else if (private_data_specifier == 0x00002310) {
        name = "Emirates Digital Terrestrial Television";
    } else if (private_data_specifier == 0x00002320) {
        name = "DTT Uganda";
    } else if (private_data_specifier == 0x0000233A) {
        name = "Independent Television Commission ";
    } else if (private_data_specifier == 0x00002372) {
        name = "DTT Samoa";
    } else if (private_data_specifier == 0x00002B00) {
        name = "DTT – Sky New Zealand";
    } else if (private_data_specifier >= 0x00003200 && private_data_specifier <= 0x0000320F) {
        name = "(Australian Terrestrial Television Networks)";
    } else if (private_data_specifier == 0x0000333A) {
        name = "Digital TV Group";
    } else if (private_data_specifier == 0x00006000) {
        name = "News Datacom";
    } else if (private_data_specifier >= 0x00006001 && private_data_specifier <= 0x00006006) {
        name = "NDC 1 - 6";
    } else if (private_data_specifier == 0x00362275) {
        name = "Irdeto";
    } else if (private_data_specifier == 0x004E544C) {
        name = "NTL";
    } else if (private_data_specifier == 0x00532D41) {
        name = "Scientific Atlanta";
    } else if (private_data_specifier == 0x00564F4F) {
        name = "VOO (Tecteo)";
    } else if (private_data_specifier == 0x00600000) {
        name = "Rhône Vision Cable";
    } else if (private_data_specifier == 0x41555300) {
        name = "Foxtel Management";
    } else if (private_data_specifier == 0x44414E59) {
        name = "News Datacom (IL) 1";
    } else if (private_data_specifier == 0x46524549) {
        name = "News Datacom (IL) 1";
    } else if (private_data_specifier == 0x46534154) {
        name = "BBC";
    } else if (private_data_specifier == 0x46536174) {
        name = "BBC";
    } else if (private_data_specifier >= 0x46545600 && private_data_specifier <= 0x46545620) {
        name = "FreeTV 1 - 33";
    } else if (private_data_specifier >= 0x46585431 && private_data_specifier <= 0x46585433) {
        name = "FOXTEL Management Pty Ltd";
    } else if (private_data_specifier == 0x4658544C) {
        name = "FOXTEL Management Pty Ltd";
    } else if (private_data_specifier == 0x4A4F4A4F) {
        name = "Kabel Deutschland";
    } else if (private_data_specifier >= 0x4F545600 && private_data_specifier <= 0x4F5456FF) {
        name = "(OpenTV 1 - 256)";
    } else if (private_data_specifier >= 0x50484900 && private_data_specifier <= 0x504849FF) {
        name = "(Philips DVS 1 - 256)";
    } else if (private_data_specifier == 0x53415053) {
        name = "Scientific Atlanta";
    } else if (private_data_specifier == 0x5347444E) {
        name = "StarGuide Digital Networks ";
    } else if (private_data_specifier == 0x53475255) {
        name = "GkWare e.K.";
    } else if (private_data_specifier == 0x56444700) {
        name = "Vía Digital";
    } else if (private_data_specifier == 0x564F564F) {
        name = "TechnoTrend AG";
    } else if (private_data_specifier == 0xBBBBBBBB) {
        name = "Bertelsmann Broadband Group";
    } else if (private_data_specifier == 0xE0E0E0E0) {
        name = "eventIS";
    } else if (private_data_specifier == 0xECCA0001) {
        name = "ECCA (European Cable Communications Association )";
    } else if (private_data_specifier == 0xFCFCFCFC) {
        name = "France Telecom";
    } else {
        name = "Not specified";
    }
    return name;
}

uint32_t PAT_Container::Parse(unsigned char *buff, uint32_t sectionNo, dvb_sections_discriptor &dtable, SectionContaniner &container)
{
    if (buff == nullptr) {
        qDebug() << "pat timeout .....\n";
        return -1;
    }
    uint32_t retval = 0;
    ByteContainer a(buff);

    TSTableHeader pathdr("PAT", a);

    if (sectionNo - pathdr.section_length != 3) {
        qDebug() << " section_length out of bound ... \n"
                 << pathdr;
        return -1;
    }
    if (pathdr.current_next_indicator != 1) {
        qDebug() << " current_next_indicator should be 1 got \n"
                 << pathdr;
        return -1;
    } else if (pathdr.section_length < 11 || pathdr.section_length > 1021) {
        qDebug() << " section_length out of bound  \n"
                 << pathdr;
        return -1;
    } else if (pathdr.section_number > pathdr.last_section_number) {
        qDebug() << " section_number invalid  \n"
                 << pathdr;
        return -1;
    }
    container.pat.transport_stream_id = pathdr.bouquet_id;

    auto& verinfo = container.pat.version[pathdr.bouquet_id];

    if (TableSectionVersionCheck(verinfo, pathdr)) {

        qDebug() << pathdr<<"\n";

        uint16_t section_length = pathdr.section_length - 9;

        while (section_length >= 4) {

            uint16_t program_number = a.Byte2();
            uint16_t program_map_PID = a.Byte2(0x1fff);

            section_length -= 4;

            if (program_number != 0) {

                qDebug() << " program_number : " << program_number
                         << " program_map_PID : " << program_map_PID<<"\n";

                container.pat.pat[program_number] = program_map_PID;

            } else {

                container.pat.network_PID = program_map_PID;
                qDebug() << " network_PID : " << container.pat.network_PID<<"\n";

            }
        }
    } else {
        //qDebug() << " PAT alredy parsed\n";
        retval = 1;
    }
    return retval;
}

uint32_t PMT_Container::Parse(unsigned char *buff, uint32_t sectionNo, dvb_sections_discriptor &dtable, SectionContaniner &container)
{

    if (buff == nullptr) {
        qDebug() << "pmt timeout .....\n";
        return -1;
    }
    uint32_t retval = 0;

    ByteContainer a(buff);
    TSTableHeader pmthdr("PMT", a);

    if (sectionNo - pmthdr.section_length != 3) {
        qDebug() << " section_length out of bound ... \n"
                 << pmthdr;
        return -1;
    }
    if (pmthdr.current_next_indicator != 1) {
        qDebug() << " current_next_indicator should be 1 got \n"
                 << pmthdr;
        return -1;
    } else if (pmthdr.section_length < 13 || pmthdr.section_length > 1021) {
        qDebug() << " section_length out of bound  \n"
                 << pmthdr;
        return -1;
    } else if (pmthdr.section_number > pmthdr.last_section_number) {
        qDebug() << " section_number invalid  \n"
                 << pmthdr;
        return -1;
    }
    //TODO:- use map of pmt with programme number as each progame has it own pmt
    container.pmt.program_number = pmthdr.bouquet_id;

    auto& verinfo = container.pmt.version[pmthdr.bouquet_id];
    if (TableSectionVersionCheck(verinfo, pmthdr)) {
        // repate_cnt.store(0, std::memory_order_acquire);

        qDebug() << pmthdr <<"\n";

        int16_t section_length = pmthdr.section_length - 5;

        container.pmt.PCR_PID = a.Byte2(0x1fff);
        int16_t program_info_length = a.Byte2(0x0fff);

        qDebug() << " program_number : " << container.pmt.program_number
                 << " PCR_PID : " << container.pmt.PCR_PID
                 << " program_info_length : " << program_info_length;
        //remove header
        section_length -= 4;
        // remove crc
        section_length -= 4;

        if (program_info_length) {
            if (program_info_length > section_length) {
                qDebug() << " program_info_length : " << program_info_length
                         << " is larger than section_length " << section_length ;
                return -1;
            }
            while (program_info_length > 0) {

                uint8_t des = a.Byte();
                uint8_t dlen = a.Byte();

                qDebug() << "----> program descriptor : 0x "  << (uint32_t) des
                         << " desc len : " << (uint32_t) dlen
                         << "<----\n"
                            ;
                if (dlen > program_info_length) {
                    qDebug() << " PAT descriptor length : "
                             << (uint32_t) dlen
                             << " is larger than program_info_length : "
                             << program_info_length<<"\n";
                    section_length -= 2;
                    retval = -1;
                    break;
                } else {
                    QVariant fdata = dtable.get(des)(des,dlen,container,a);
                    // a.Skip(dlen);

                    section_length -= 2 + dlen;
                    program_info_length -= 2 + dlen;
                }
            }
        }

        while (section_length >= 4) {
            uint8_t stream_type = a.Byte();
            uint16_t elementary_PID = a.Byte2(0x1fff);
            PrgInfo& in = container.pmt.Info[elementary_PID];
            in.stream_type = stream_type;

            int16_t ES_info_length = a.Byte2(0x03ff);

            qDebug() << " stream_type : " << (uint16_t) stream_type
                     << " elementary_PID : " << elementary_PID
                     << " ES_info_length : " << ES_info_length
                     << " remaining section_length : " << section_length<<"\n";

            section_length -= 5;

            if (ES_info_length) {
                if (ES_info_length > section_length) {
                    qDebug() << " ES_info_length : " << ES_info_length
                             << " is larger than section_length " << section_length<<"\n";
                    return -1;
                }
                while (ES_info_length > 0) {
                    uint8_t des = a.Byte();
                    uint8_t dlen = a.Byte();
                    qDebug() << " ----> ES descriptor : 0x"
                             << (int) des
                             << " desc len : " << (int) dlen
                             << "<----"
                             << " ES_info_length : " << ES_info_length
                             <<"\n" ;
                    if (dlen > ES_info_length) {
                        qDebug() << " desc len " << (uint32_t) dlen
                                 << " is grater than ES_info_length "
                                 << ES_info_length <<"\n";
                        ES_info_length -= 2;
                        section_length -= 2;
                        retval = -1;
                        break;
                    }
                    QVariant fdata = dtable.get(des)(des,dlen,container,a);
                    switch (des) {
                    case ISO_639_language_descriptor:

                        if (fdata.canConvert<std::map<uint8_t,ISO_639_language>>()) {
                            std::map<uint8_t,ISO_639_language> lang = fdata.value<std::map<uint8_t,ISO_639_language>>();
                            in.lang = lang[0].ISO_639_language_code.c_str();
                            in.langType = lang[0].audio_type;
                        }
                        break;
                    default:
                        break;
                    }

                    ES_info_length -= 2 + dlen;
                    section_length -= 2 + dlen;

                    // in following condition ES_info_length > section_length
                    if (section_length <= 0) {
                        if (section_length != 0)
                            qDebug() << "---------> end of section breaking out section_length : " << section_length<<"\n";
                        ES_info_length = 0;
                    }
                }
            }

        }
    } else {
        retval = 1;
        //qDebug() << "PMT/TS_program_map_section alredy parsed \n";
    }
    return retval;

}

uint32_t SDT_Container::Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor &dtable, SectionContaniner &container)
{

    if (buff == nullptr) {
        qDebug() << "sdt timeout .....";
        return -1;
    }
    uint32_t retval = 0;

    ByteContainer a(buff);
    TSTableHeader sdthdr("SDT", a);
    if (sectionno - sdthdr.section_length != 3) {
        qDebug() << " section_length out of bound ... \n"
                 << sdthdr;
        return -1;
    }
    if (sdthdr.current_next_indicator != 1) {
        qDebug() << " current_next_indicator should be 1 got \n"
                 << sdthdr;
        return -1;
    } else if (sdthdr.section_length < 12 || sdthdr.section_length > 1021) {
        qDebug() << " section_length out of bound  \n"
                 << sdthdr;
        return -1;
    } else if (sdthdr.section_number > sdthdr.last_section_number) {
        qDebug() << " section_number invalid  \n"
                 << sdthdr;
        return -1;
    }
    SDT_Container* pContainer = (sdthdr.table_id == SDT_TABLEID_ACTUAL)?&container.sdtActual:&container.sdtOther;
    //pContainer->transport_stream_id = sdthdr.bouquet_id;

    auto& verinfo = pContainer->version[sdthdr.bouquet_id];
    if (TableSectionVersionCheck(verinfo, sdthdr)) {
        //repate_cnt.store(0, std::memory_order_acquire);

        qDebug() << sdthdr;

        uint16_t network_id = a.Byte2();
        a.Skip(1);

        int16_t section_length = (sdthdr.section_length & 0x03ff) - 11;

        while (section_length >= 6) {

            uint16_t ServiceID = a.Byte2();
            SDT_Pirmary_Key key {sdthdr.bouquet_id,network_id,ServiceID};
            SDT_Descriptor &desc = pContainer->sdt[key];

            qDebug() << " SDT network_id :" << network_id
                     << " transport_stream_id : " << sdthdr.bouquet_id
                     << " ServiceID : " << ServiceID ;

            desc.service_id = ServiceID;
            desc.EIT_schedule_flag = a.Byte(0x02, false) ? true : false;
            desc.EIT_present_following_flag = a.Byte(0x01) ? true : false;
            desc.running_status = (a.Byte(0xE0, false) >> 5);
            desc.free_CA_mode = a.Byte(0x10, false) ? true : false;

            int16_t dlen = a.Byte2(0x0fff);

            if (dlen) {
                section_length -= 5;
                while (dlen > 0) {
                    uint8_t id = a.Byte();
                    uint8_t ddlen = a.Byte();

                    QVariant fdata = dtable.get(id)(id,ddlen,container,a);
                    switch (id) {
                    case service_descriptor:
                    {
                        if (fdata.canConvert<service>()){
                            service data = fdata.value<service>();
                            desc.service_description = data;
                        }
                    }
                        break;
                    default:
                        break;
                    }

                    dlen -= 2 + ddlen;
                    section_length -= 2 + ddlen;

                }

            } else {
                break;
            }
        }
    } else {
        retval = 1;
    }
    return retval;
}

uint32_t BAT_Container::Parse(unsigned char *buff, uint32_t sectionno, dvb_sections_discriptor &dtable, SectionContaniner &container)
{

    if (buff == nullptr) {
        qDebug() << "bat timeout ..... \n";
        return -1;
    }
    uint32_t retval = 0;

    ByteContainer a(buff);
    TSTableHeader batsdthdr("BAT", a);

    if (sectionno - batsdthdr.section_length != 3) {
        qDebug() << " section_length out of bound ... \n"
                 << batsdthdr <<"\n";
        return -1;
    }

    if (batsdthdr.current_next_indicator != 1) {
        qDebug() << " current_next_indicator should be 1 got \n"
                 << batsdthdr <<"\n";
        return -1;
    } else if (batsdthdr.section_length < 11 || batsdthdr.section_length > 1021) {
        qDebug() << " section_length out of bound  \n"
                 << batsdthdr<<"\n";
        return -1;
    } else if (batsdthdr.section_number > batsdthdr.last_section_number) {
        qDebug() << " section_number invalid  \n"
                 << batsdthdr<<"\n";
        return -1;
    }

    auto& verinfo = container.bat.version[batsdthdr.bouquet_id];

    if (TableSectionVersionCheck(verinfo, batsdthdr)) {

        batsdthdr.section_length = (batsdthdr.section_length & 0x03ff);

        qDebug() << batsdthdr<<"\n";
        TableHexDump(buff,sectionno);
        int16_t bouquet_descriptors_length = a.Byte2(0x0fff);
        int16_t section_length = batsdthdr.section_length;

        if (bouquet_descriptors_length) {
            if (bouquet_descriptors_length > section_length) {
                qDebug() << " ERROR: bouquet_descriptors_length : "
                         << bouquet_descriptors_length
                         << " is gretor than section_length len : "
                         << (uint32_t) section_length
                         <<"\n";
                return -1;
            }

            section_length -= bouquet_descriptors_length;
            while (bouquet_descriptors_length > 0) {
                uint8_t des = a.Byte();
                uint8_t dlen = a.Byte();
                qDebug() << " bat des type : 0x"  << (uint32_t) des
                         <<" des len : " << (uint32_t) dlen
                        <<" bouquet_descriptors_length remaining : "
                       << bouquet_descriptors_length
                       <<"\n";
                if (bouquet_descriptors_length > section_length) {
                    qDebug() << "bouquet_descriptors_length : " << bouquet_descriptors_length
                             << " is grator than section_len" << section_length
                             <<"\n";
                    return -1;
                }
                if (dlen > bouquet_descriptors_length) {
                    qDebug() << "BAT " << batsdthdr.bouquet_id
                             << " (" << (uint32_t) des << "-" << (uint32_t) dlen
                             << ") :descriptor length is inappropriate : "
                             << (int32_t) dlen
                             << " as compared to remaining bouquet_descriptors_length\n";
                    return -1;
                }


                fnptr fn = dtable.get(des);
                if(fn)
                    fn(des,dlen,container,a);
                bouquet_descriptors_length -= dlen + 2;
            }

        }
        uint16_t tslooplen = a.Byte2(0x0fff);
        //qDebug() << "ts loop len : " << tslooplen;
        if (tslooplen > section_length) {
            qDebug() << " ERROR: tslooplen : " << tslooplen
                     << " is gretor than section_length len : "
                     << (uint32_t) section_length<<"\n";
            //verinfo.version = -1;
            return -1;
        }
        for (int i = 0; i < tslooplen;) {
            //trancport_descriptor tsd;
            int16_t transport_descriptors_length = 0;
            uint16_t original_network_id = 0, transport_stream_id = 0;
            transport_stream_id = a.Byte2();
            original_network_id = a.Byte2();
            transport_descriptors_length = a.Byte2(0x0fff);
            //            qDebug() << " transport_stream_id : " << tsd.transport_stream_id <<
            //                        " original_network_id : " << tsd.original_network_id <<
            //                         " transport_descriptors_length : " << transport_descriptors_length <<
            //                         std::endl;
            if (transport_descriptors_length > section_length) {
                qDebug() << " ERROR: transport_descriptors_length : "
                         << transport_descriptors_length
                         << " is gretor than section_length len : "
                         << (uint32_t) section_length<<"\n";
                //verinfo.version = -1;
                return -1;
            }
            if (transport_descriptors_length) {
                i += 6;
                while (transport_descriptors_length > 0) {
                    uint8_t dsc = a.Byte();
                    uint8_t dlen = a.Byte();
                    //qDebug() << " got ts descriptor :0x"  << (int) dsc << " of len : " <<
                    //        std::dec << (int) dlen;
#if 0
                    switch (dsc) {
                    case cable_delivery_system_descriptor:
                    {
                        freq_table ftb;
                        //ftb.original_network_id = original_network_id;
                        //ftb.transport_stream_id = transport_stream_id;
                        std::vector<uint8_t> data;
                        data.push_back(a.Byte());
                        data.push_back(a.Byte());
                        data.push_back(a.Byte());
                        data.push_back(a.Byte());

                        ftb.frequency = ValueFromByteStream<double>(data, 4); //a.Byte4();
                        a.Skip(1);
                        ftb.FEC_outer = a.Byte(0x0f);
                        ftb.modulation = a.Byte();

                        data.clear();
                        data.push_back(a.Byte());
                        data.push_back(a.Byte());
                        data.push_back(a.Byte());
                        data.push_back(a.Byte(0xf0, false));

                        ftb.symbol_rate = ValueFromByteStream<double>(data, 3); //a.Byte4();
                        ftb.FEC_inner = a.Byte(0xf);

                        //ftb.FEC_inner = (uint8_t)(ftb.symbol_rate & 0x0000000f);
                        //ftb.symbol_rate = ftb.symbol_rate >> 4;

                        qDebug() << " frequency : " << std::fixed << std::setprecision(4) << ftb.frequency
                                 << " MHz FEC_outer : " << (uint32_t) ftb.FEC_outer
                                 << " modulation : " << (uint32_t) std::pow(2.0, ftb.modulation + 3)
                                 << " QAM symbol_rate : " << std::fixed << std::setprecision(3) << ftb.symbol_rate
                                 << " Msymbol/s FEC_inner : " << (uint32_t) ftb.FEC_inner
                                    ;
                        tsd.ftable.push_back(ftb);
                    }
                        break;
#if 0
                    case 0x83:
                        //                                break;
                    case 0xe2:
                    case 0x82:
                    case 0x81:
                    case 0x93:
                    {
                        int8_t loop = dlen;
                        if (g_lcnid == dsc) {
                            while (loop > 0) {
                                uint16_t service_id = a.Byte2();
                                uint8_t visible_service_flag = (uint8_t) (a.Byte(0x80, false) >> 0x7);
                                uint16_t lcn = a.Byte2(0x3ff);
                                if (lcn)
                                    tsd.lcnmap[service_id] = lcn;
                                loop -= 4;
                                qDebug() << "\t\t visible_service_flag : " << (uint32_t) visible_service_flag
                                         << " service_id : " << service_id
                                         << " logical_channel_number : " << lcn
                                            ;

                            }
                        } else {
                            qDebug() << " skipping as lcn desc 0x"  << (uint32_t) dsc
                                     << " != "  << (uint32_t) g_lcnid;
                            a.Skip(loop);
                        }
                    }
                        break;
#endif
                    case service_list_descriptor:
                    {
                        uint8_t loopcnt = dlen;
                        while (loopcnt) {
                            uint32_t service_id = a.Byte2();
                            uint8_t service_type = a.Byte();
                            loopcnt -= 3;
                            //qDebug() << "\t\tservice_list_descriptor service_id :  " << service_id << " service_type : " << (int) service_type;
                        }
                    }
                        break;
                    default:
                    {
                        // qDebug() << "skipping not supported table : 0x"  << (uint32_t) dsc;
                        if (dsc >= 0x80 && dsc <= 0xfe) {
                            //possible LCN
                            // qDebug() << "  reminder  " << (dlen % 4) << " result " << ((dlen % 4) == 0);
                            if ((dlen % 4) == 0) {
                                auto& lcndata = binfo.lcnmap[dsc];

                                qDebug() << "desriptor tag 0x"  << (uint32_t) dsc << " of len : " << (uint32_t) dlen << " may have lcn data";
                                uint8_t loop = dlen;
                                while (loop != 0) {

                                    uint16_t service_id = a.Byte2();
                                    uint8_t visible_service_flag = (uint8_t) (a.Byte(0x80, false) >> 0x7);
                                    uint16_t lcn = a.Byte2(0x3ff);
                                    //if (lcn)
                                    //  tsd.lcnmap[service_id] = lcn;
                                    if (lcn)
                                        lcndata[service_id] = lcn;
                                    loop -= 4;
                                    // qDebug() << "\t\t 0x"  << (uint32_t) dsc << ": visible_service_flag : " << (uint32_t) visible_service_flag
                                    //       << " service_id : " << service_id
                                    //      << " logical_channel_number : " << lcn
                                    //    ;
                                }
                            } else {
                                qDebug() << "skipping user defined tag 0x:"  << (uint32_t) dsc << " of len : " << (uint32_t) dlen;
                                a.Skip(dlen);
                            }
                        } else {
                            qDebug() << "skipping tag 0x:"  << (uint32_t) dsc << " of len : " << (uint32_t) dlen;
                            a.Skip(dlen);
                        }
                    }
                        break;
                    }
#else
                    // a.Skip(dlen);
                    dtable.get(dsc)(dsc,dlen,container,a);
                    i += 2 + dlen;
                    transport_descriptors_length -= dlen + 2;
                }


#endif
            } else {
                i += 6;
            }
            //Info.tsd.push_back(tsd);

        }

    } else {
        retval = 1;
    }
    return retval;
}



void TableHexDump(unsigned char* pbuff ,uint32_t len)
{
    ByteContainer a(pbuff);
    std::stringstream ssHex;
    uint32_t toskip = len;
    if (len) {
        do {
            uint32_t lnsize = (toskip > 10) ? 10 : toskip;
            std::vector<uint8_t> data;
            for (unsigned int j = 0; j < lnsize; j++) {
                data.push_back(a.Byte());
            }
            std::string ssStr;
            for (unsigned int j = 0; j < lnsize; j++) {
                ssStr.append(1, (data.at(j) < 32 ? '.' : data.at(j)));
            }
            ssStr.append("  ");
            ssHex << ssStr;
            for (unsigned int j = 0; j < lnsize; j++) {
                ssHex.width(2);
                ssHex.fill('0');
                ssHex  << std::uppercase << std::hex<<int(data.at(j)) << " ";
            }
            ssHex << "\n";
            toskip -= lnsize;
        } while (toskip > 0);
        qDebug() << "HEX DUMP: \n"
                 << ssHex.str().c_str() <<"\n";
        //a.Skip(dlen);
    } else {
        qDebug() << "HEX DUMP: 00"
                 << " len 0 \n";
    }

}

uint32_t TableSectionVersionCheck(versions& verinfo, TSTableHeader& tstblhdr) {

    //if version number is gretor than exesting version
    if (verinfo.version < tstblhdr.version_number) {
        qDebug() << tstblhdr.name.c_str()
                 << " ---> transport_stream_id : " << tstblhdr.bouquet_id
                 << " current version : " << (int) verinfo.version
                 << " new version : " << (int) tstblhdr.version_number
                    ;

        //resize
        verinfo.ResizeSectionMap(tstblhdr.last_section_number);
        //set version no
        verinfo.version = tstblhdr.version_number;
        //set section map
        verinfo.SetSectionMAp(tstblhdr.section_number);
        return 1;
    } else if ((verinfo.version == tstblhdr.version_number)) {
        if (verinfo.isSectionMapFull(tstblhdr.section_number, tstblhdr.last_section_number)) {
            //                qDebug() << "PAT ---> transport_stream_id : " << bouquet_id
            //                        << " of  version : " << (int) version_number
            //                        << " already present ";
            return 0;
        } else if (verinfo.isSectionFull(tstblhdr.section_number)) {
            //                qDebug() << "PAT ---> transport_stream_id : " << bouquet_id
            //                        << " of  version : " << (int) version_number
            //                        << " and section_number  " << (int) section_number
            //                        << " already present ";
            return 0;
        } else {
            //set section map as version number is same
            qDebug() << "TableSectionVersionCheck() --> program_no : " << tstblhdr.bouquet_id
                     << " of  version : " << (uint32_t) tstblhdr.version_number
                     << " and section_number  " << (uint32_t) tstblhdr.section_number
                     << " processing ";
            verinfo.SetSectionMAp(tstblhdr.section_number);
            return 1;
        }
    } else {
        return 0;
    }
    return 0;
}
};
