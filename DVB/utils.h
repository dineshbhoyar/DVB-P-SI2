/*
 * File:   utils.h
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



#ifndef UTILS_H
#define UTILS_H
#include <string>

std::string west_east_flag_to_string(uint8_t west_east_flag);

std::string polarization_to_string(uint8_t polarization);

std::string roll_off_to_string(uint8_t roll_off);

std::string modulation_system_to_string(uint8_t modulation_system);

std::string modulation_type_to_string(uint8_t modulation_type);

std::string FEC_inner_to_string(uint8_t FCE_inner);

std::string FEC_outer_to_string(uint8_t FCE_outer);

std::string bandwidth_to_string(uint8_t bandwidth);

std::string priority_to_string(uint8_t priority);

std::string used_unsued_to_string(uint8_t used);

std::string constellation_to_string(uint8_t constellation);

std::string hierarchy_information_to_string(uint8_t hierarchy_information);

std::string code_rate_to_string(uint8_t code_rate);

std::string guard_interval_to_string(uint8_t guard_interval);

std::string transmission_mode_to_string(uint8_t transmission_mode);

#endif // UTILS_H
