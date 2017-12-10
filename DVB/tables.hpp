/*
 * File:   tables.hpp
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




#ifndef TABLES_HPP
#define	TABLES_HPP

#define PAT_PID (0x0000)
#define CAT_PID (0x0001)
#define NIT_PID (0x0010)
#define EIT_PID (0x0012)
#define TOT_PID (0x0014)
#define TDT_PID (0x0014)
#define SDT_PID (0x0011)
#define BAT_PID (0x0011)
#define BAT_PID_EX (217)


#define NULLPACKET_PID (0x1fff)

#define PAT_TABLEID (0x00)
#define CAT_TABLEID (0x01)
#define PMT_TABLEID (0x02)
#define NIT_TABLEID_ACTUAL (0x40)
#define NIT_TABLEID_OTHER (0x41)

#define SDT_TABLEID_ACTUAL (0x42)
#define SDT_TABLEID_OTHER (0x46)

#define BAT_TABLEID (0x4A)
#define EIT_TABLEID_PF_ACTUAL (0x4E)
#define EIT_TABLEID_PF_OTHER (0x4F)
#define EIT_TABLEID_SCHEDULE_ACTUAL_LOW (0x50)
#define EIT_TABLEID_SCHEDULE_ACTUAL_HIGH (0x5F)

#define EIT_TABLEID_SCHEDULE_OTHER_LOW (0x60)
#define EIT_TABLEID_SCHEDULE_OTHER_HIGH (0x6F)

#define TDT_TABLEID (0x70)
#define TOT_TABLEID (0x73)

#define INVALID_TABLEID (0xff)

#define MAX_SECTION_LEN 4096 
#define MAX_SECTION_NUM 256

#define ISO_639_language_descriptor                                     0x0a
#define network_name_descriptor                                         0x40
#define service_list_descriptor                                         0x41
#define stuffing_descriptor                                             0x42
#define satellite_delivery_system_descriptor                            0x43
#define cable_delivery_system_descriptor                                0x44
#define VBI_data_descriptor                                             0x45
#define VBI_teletext_descriptor                                         0x46
#define bouquet_name_descriptor                                         0x47
#define service_descriptor                                              0x48
#define country_availability_descriptor                                 0x49
#define linkage_descriptor                                              0x4A
#define NVOD_reference_descriptor                                       0x4B
#define time_shifted_service_descriptor                                 0x4C
#define short_event_descriptor                                          0x4D
#define extended_event_descriptor                                       0x4E
#define time_shifted_event_descriptor                                   0x4F
#define component_descriptor                                            0x50
#define mosaic_descriptor                                               0x51
#define stream_identifier_descriptor                                    0x52
#define CA_identifier_descriptor                                        0x53
#define content_descriptor                                              0x54
#define parental_rating_descriptor                                      0x55
#define teletext_descriptor                                             0x56
#define telephone_descriptor                                            0x57
#define local_time_offset_descriptor                                    0x58
#define subtitling_descriptor                                           0x59
#define terrestrial_delivery_system_descriptor                          0x5A
#define multilingual_network_name_descriptor                            0x5B
#define multilingual_bouquet_name_descriptor                            0x5C
#define multilingual_service_name_descriptor                            0x5D
#define multilingual_component_descriptor                               0x5E
#define private_data_specifier_descriptor                               0x5F
#define service_move_descriptor                                         0x60
#define short_smoothing_buffer_descriptor                               0x61
#define frequency_list_descriptor                                       0x62
#define partial_transport_stream_descriptor                             0x63
#define data_broadcast_descriptor                                       0x64
#define scrambling_descriptor                                           0x65
#define data_broadcast_id_descriptor                                    0x66
#define transport_stream_descriptor                                     0x67
#define DSNG_descriptor                                    0x68
#define PDC_descriptor                                                  0x69
#define AC_3_descriptor                                   0x6A
#define ancillary_data_descriptor                                       0x6B
#define cell_list_descriptor                                            0x6C
#define cell_frequency_link_descriptor                                  0x6D
#define announcement_support_descriptor                                 0x6E
#define application_signalling_descriptor                               0x6F
#define adaptation_field_data_descriptor                                0x70
#define service_identifier_descriptor                         0x71
#define service_availability_descriptor                                 0x72
#define default_authority_descriptor                                    0x73
#define related_content_descriptor                                      0x74
#define TVA_id_descriptor                                               0x75
#define content_identifier_descriptor                                   0x76
#define time_slice_fec_identifier_descriptor                            0x77
#define ECM_repetition_rate_descriptor                                  0x78
#define S2_satellite_delivery_system_descriptor                         0x79
#define enhanced_AC_3_descriptor                                        0x7A
#define DTS_descriptor                                   0x7B
#define AAC_descriptor      0x7C
#define XAIT_location_descriptor    0x7D
#define FTA_content_management_descriptor 0x7E
#define extension_descriptor 0x7F
#define logical_channel_number 0x83
//user defined 0x80 to 0xFE and forbidden 0xFF
/*
#define program_association_section                                           0x00
#define conditional_access_section                                            0x01
#define program_map_section                                                   0x02
#define transport_stream_description_section                                  0x03
//#define reserved                                                              0x04 to 0x3F
#define network_information_section - actual_network                          0x40
#define network_information_section - other_network                           0x41
#define service_description_section - actual_transport_stream                 0x42
//#define reserved for future use                                               0x43 to 0x45
#define service_description_section - other_transport_stream                  0x46
//#define reserved for future use                                               0x47 to 0x49
#define bouquet_association_section                                           0x4A
//#define reserved for future use                                               0x4B to 0x4D
#define event_information_section - actual_transport_stream, present/following0x4E
#define event_information_section - other_transport_stream, present/following 0x4F
#define event_information_section - actual_transport_stream, schedule         0x50 to 0x5F
#define event_information_section - other_transport_stream, schedule          0x60 to 0x6F
#define time_date_section                                                     0x70
#define running_status_section                                                0x71
#define stuffing_section                                                      0x72
#define time_offset_section                                                   0x73
//#define reserved for future use                                               0x74 to 0x7D
#define discontinuity_information_section                                     0x7E
#define selection_information_section                                         0x7F
#define user defined                                                          0x80 to 0xFE
//#define reserved                                                              0xFF


 */


#endif	/* TABLES_HPP */

