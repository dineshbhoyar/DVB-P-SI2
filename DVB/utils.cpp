/*
 * File:   utils.cpp
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



#include "utils.h"
std::string west_east_flag_to_string(uint8_t west_east_flag)
{
    return (west_east_flag)?"eastern position":"western position";
}

std::string polarization_to_string(uint8_t polarization)
{
    std::string result;
    switch (polarization) {
    case 0:
        result="linear - horizontal";
        break;
    case 1:
        result = "linear - vertical";
        break;
    case 2:
        result = "Circular - left";
        break;
    case 3:
        result ="Circular - right";
        break;
    default:
        result = "N/A";
        break;
    }
    return result;
}

std::string roll_off_to_string(uint8_t roll_off)
{
    std::string result;
    switch (roll_off) {
    case 0:
        result="α = 0.35";
        break;
    case 1:
        result = "α = 0.25";
        break;
    case 2:
        result = "α = 0.20";
        break;
    case 3:
        result ="reserved";
        break;
    default:
        result = "N/A";
        break;
    }
    return result;
}


std::string modulation_system_to_string(uint8_t modulation_system)
{
    return (modulation_system)?"DVB-S2":"DVB-S";
}

std::string modulation_type_to_string(uint8_t modulation_type)
{

    std::string result;
    switch (modulation_type) {
    case 0:
        result="Auto";
        break;
    case 1:
        result = "QPSK";
        break;
    case 2:
        result = "8PSK";
        break;
    case 3:
        result ="16-QAM (n/a for DVB-S2)";
        break;
    default:
        result = "N/A";
        break;
    }
    return result;
}


std::string FEC_inner_to_string(uint8_t FCE_inner)
{
    std::string result;
    switch (FCE_inner) {
    case 0:
        result="not defined";
        break;
    case 1:
        result = "1/2 conv. code rate";
        break;
    case 2:
        result = "2/3 conv. code rate";
        break;
    case 3:
        result ="3/4 conv. code rate";
        break;
    case 4:
        result = "5/6 conv. code rate";
        break;
    case 5:
        result ="7/8 conv. code rate";
        break;
    case 6:
        result ="8/9 conv. code rate";
        break;
    case 7:
        result ="3/5 conv. code rate";
        break;
    case 8:
        result ="4/5 conv. code rate";
        break;
    case 9:
        result ="9/10 conv. code rate";
        break;
    case 0x0f:
        result ="no conv. Coding";
        break;
    default:
        result = "reserved for future use";
        break;
    }
    return result;
}

std::string FEC_outer_to_string(uint8_t FCE_outer)
{

    std::string result;
    switch (FCE_outer) {
    case 0:
        result="not defined";
        break;
    case 1:
        result = "no outer FEC coding";
        break;
    case 2:
        result = "RS(204/188)";
        break;
    default:
        result = "reserved for future use";
        break;
    }
    return result;
}


std::string bandwidth_to_string(uint8_t bandwidth)
{
    std::string result;
    switch (bandwidth) {
    case 0:
        result="8 MHz";
        break;
    case 1:
        result = "7 MHz";
        break;
    case 2:
        result = "6 MHz";
        break;
    case 3:
        result = " 5 MHz";
        break;
    default:
        result = "Reserved for future use";
        break;
    }
    return result;
}

std::string priority_to_string(uint8_t priority)
{
    return (priority)?"HP (high priority)":"LP (low priority)";
}

std::string used_unsued_to_string(uint8_t used)
{
    return (used)?"used":"not used";
}

std::string constellation_to_string(uint8_t constellation)
{
    std::string result;
    switch (constellation) {
    case 0:
        result="QPSK";
        break;
    case 1:
        result = "16-QAM";
        break;
    case 2:
        result = "64-QAM";
        break;
    default:
        result = "reserved for future use";
        break;
    }
    return result;
}

std::string hierarchy_information_to_string(uint8_t hierarchy_information)
{
    std::string result;
    switch (hierarchy_information) {
    case 0:
        result="non-hierarchical, native interleaver";
        break;
    case 1:
        result = "α = 1, native interleaver";
        break;
    case 2:
        result = "α = 2, native interleaver";
        break;
    case 3:
        result = "α = 4, native interleaver";
        break;
    case 4:
        result="non-hierarchical, in-depth interleaver";
        break;
    case 5:
        result ="α = 1, in-depth interleaver";
        break;

    case 6:
        result ="α = 2, in-depth interleaver";
        break;

    case 7:
        result ="α = 4, in-depth interleaver";
        break;
    default:
        result = "N/A";
        break;
    }
    return result;
}

std::string code_rate_to_string(uint8_t code_rate)
{
    std::string result;
    switch (code_rate) {
    case 0:
        result="1/2";
        break;
    case 1:
        result = "2/3";
        break;
    case 2:
        result = "3/4";
        break;
    case 3:
        result = "5/6";
        break;
    case 4:
        result="7/8";
        break;
    default:
        result = "reserved for future use";
        break;
    }
    return result;
}

std::string guard_interval_to_string(uint8_t guard_interval)
{
    std::string result;
    switch (guard_interval) {
    case 0:
        result="1/32";
        break;
    case 1:
        result = "1/16";
        break;
    case 2:
        result = "1/8";
        break;
    case 3:
        result = "1/4";
        break;
    default:
        result = "N/A";
        break;
    }
    return result;
}

std::string transmission_mode_to_string(uint8_t transmission_mode)
{
    std::string result;
    switch (transmission_mode) {
    case 0:
        result="2k mode";
        break;
    case 1:
        result = "8k mode";
        break;
    case 2:
        result = "4k mode";
        break;
    default:
        result = "reserved for future use";
        break;
    }
    return result;
}
