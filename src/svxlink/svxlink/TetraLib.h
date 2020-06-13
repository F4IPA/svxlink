/**
@file	 TetraLib.h
@brief   Contains methods for Pei communication
@author  Adi Bier / DL1HRC
@date	 2020-05-28

\verbatim
SvxLink - A Multi Purpose Voice Services System for Ham Radio Use
Copyright (C) 2003-2020 Tobias Blomberg / SM0SVX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
\endverbatim
*/


#ifndef TETRA_LIB_INCLUDED
#define TETRA_LIB_INCLUDED


/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/

#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>


/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/




/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/




/****************************************************************************
 *
 * Forward declarations
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Namespace
 *
 ****************************************************************************/

//namespace MyNameSpace
//{


/****************************************************************************
 *
 * Forward declarations of classes inside of the declared namespace
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Defines & typedefs
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/

std::string TxGrant[] = { 
   "0 - Transmission granted",
   "1 - Transmission not granted",
   "2 - Transmission queued",
   "3 - Transmission granted to another"
};

std::string CallStatus[] = {
  "0 - Call progressing",
  "1 - Call queued",
  "2 - Called party paged",
  "3 - Call continue",
  "4 - Hang time expired"
};

std::string CalledPartyIdentityType[] = {
  "0 - SSI",
  "1 - TSI",
  "2 - SNA (V+D only)",
  "3 - PABX external subscriber number (V+D or DMO if via a gateway)",
  "4 - PSTN external subscriber number (V+D or DMO if via a gateway)",
  "5 - Extended TSI"
};

std::string OpMode[] =  {
   "0 - V+D (trunked mode operation)", 
   "1 - DMO", 
   "2 - V+D with dual watch of DMO",
   "3 - DMO with dual watch of V+D", 
   "4 - V+D and DMO (used in conjunction CTSP command)", 
   "5 - NN", 
   "6 - DMO Repeater mode"
};

std::string TxDemandPriority[] = {
   "0 - Low", 
   "1 - High", 
   "2 - Pre-emptive", 
   "3 - Emergency"
};

std::string TransientComType[] = {
   "0 - Voice + Data",
   "1 - DMO-Direct MS-MS",
   "2 - DMO-Via DM-REP",
   "3 - DMO-Via DM-GATE",
   "4 - DMO-Via DM-REP/GATE" 
};

std::string RegStat[] = {
   "0 - Registering or searching a network, one or more networks are available",
   "1 - Registered, home network",
   "2 - Not registered, no network currently available",
   "3 - System reject, no other network available",
   "4 - Unknown",
   "5 - Registered, visited network"
};

std::string AiService[] = {
   "0 - TETRA speech",
   "1 - 7,2 kbit/s unprotected data",
   "2 - Low protection 4,8 kbit/s short interleaving depth = 1",
   "3 - Low protection 4,8 kbit/s medium interleaving depth = 4",
   "4 - Low protection 4,8 kbit/s long interleaving depth = 8",
   "5 - High protection 2,4 kbit/s short interleaving depth = 1",
   "6 - High protection 2,4 kbit/s medium interleaving depth = 4",
   "7 - High protection 2,4 kbit/s high interleaving depth = 8",
   "8 - Packet Data (V+D only)",
   "9 - SDS type 1 (16 bits)",
   "10 - SDS type 2 (32 bits)",
   "11 - SDS type 3 (64 bits)",
   "12 - SDS type 4 (0 - 2 047 bits)",
   "13 - Status (16 bits, some values are reserved in EN 300 392-2 [3])"
};

std::string AiMode[] = {
   "0 - V+D (trunked mode operation)",
   "1 - DMO",
   "2 - V+D with dual watch of DMO",
   "3 - DMO with dual watch of V+D",
   "4 - V+D and DMO (used in conjunction CTSP command)"
};

std::string DisconnectCause[] = {
   "0 - Not defined or unknown",
   "1 - User request",
   "2 - Called party busy",
   "3 - Called party not reachable",
   "4 - Called party does not support encryption",
   "5 - Network congestion",
   "6 - Not allowed traffic",
   "7 - Incompatible traffic",
   "8 - Service not available",
   "9 - Pre-emption",
   "10 - Invalid call identifier",
   "11 - Called party rejection",
   "12 - No idle CC entity",
   "13 - Timer expiry",
   "14 - SwMI disconnect",
   "15 - No acknowledgement",
   "16 - Unknown TETRA identity",
   "17 - Supplementary Service dependent",
   "18 - Unknown external subscriber number",
   "19 - Call restoration failed",
   "20 - Called party requires encryption",
   "21 - Concurrent set-up not supported",
   "22 - Called party is under the same DM-GATE as the calling party",
   "23 - Reserved",
   "24 - Reserved",
   "25 - Reserved",
   "26 - Reserved",
   "27 - Reserved",
   "28 - Reserved",
   "29 - Reserved",
   "30 - Reserved",
   "31 - Called party offered unacceptable service",
   "32 - Pre-emption by late entering gateway",
   "33 - Link to DM-REP not established or failed",
   "34 - Link to gateway failed",
   "35 - Call rejected by gateway",
   "36 - V+D call set-up failure",
   "37 - V+D resource lost or call timer expired",
   "38 - Transmit authorization lost",
   "39 - Channel has become occupied by other users",
   "40 - Security parameter mismatch"
};

std::string DmCommunicationType[] = {
   "0 - Any, MT decides",
   "1 - Direct MS-MS",
   "2 - Via DM-REP",
   "3 - Via DM-GATE",
   "4 - Via DM-REP/GATE",
   "5 - Reserved",
   "6 - Direct MS-MS, but maintain gateway registration"
};

std::string NumType[] = {
   "0 - Individual (ISSI or ITSI)",
   "1 - Group (GSSI or GTSI)",
   "2 - PSTN Gateway (ISSI or ITSI)",
   "3 - PABX Gateway (ISSI or ITSI)",
   "4 - Service Centre (ISSI or ITSI)",
   "5 - Service Centre (E.164 number)",
   "6 - Individual (extended TSI)",
   "7 - Group (extended TSI)"
};

/****************************************************************************
 *
 * Class definitions
 *
 ****************************************************************************/

std::string dec2nmea_lat(float latitude)
{
  char lat[10];
  float minute = (latitude - int(latitude)) * 60;
  float second = (minute - int(minute)) * 100;
  sprintf(lat, "%02d%02.0f.%02.0f", int(latitude), minute, second);
  std::string s = std::string(lat);
  s += (latitude > 0 ? "N": "S");
  return s;
} /* dec2nmea_lat */


std::string dec2nmea_lon(float longitude)
{
  char lon[10];
  float minute = (longitude - int(longitude)) * 60;
  float second = (minute - int(minute)) * 100;
  sprintf(lon, "%03d%02.0f.%02.0f", int(longitude), minute, second);
  std::string s = std::string(lon);
  s += (longitude > 0 ? "E": "W");
  return s;
} /* dec2nmea_lon */


bool handle_LIP_compact(std::string lip, float & lat, float & lon)
{
  if (lip.length() < 18) return false;
  std::stringstream ss;
  long mlatl, mlonl;

  // calculate latitude
  std::string m_lat = lip.substr(7,6);
  ss << std::hex << m_lat;
  ss >> mlatl;
  mlatl *= 180;
  lat = mlatl / 16777216;
  ss.clear();

  // calculate longitude
  std::string m_lon = lip.substr(13,6);
  ss << std::hex << m_lon;
  ss >> mlonl;
  mlonl *= 360;
  lon = mlonl / 16777216;

 // lt1 = sprintf("%06.3fN",($lat - int($lat))*60);
 // lat = int($lat).$lt1;
  return true;
} /* handle_LIP_compact */


void handle_LIP_short(std::string in, float &lat, float &lon)
{
  lat = 0;
  lon = 0;
  double tla;
  double tlo;

  /* Protocol identifier
     0x03 = simple GPS
     0x0A = LIP
     0x83 = Complex SDS-TL GPS message transfer
  */
  if (in.substr(0,2) == "0A")
  {
    tlo = std::stol(in.substr(2,1),nullptr,16) << 25;
    tlo +=std::stol(in.substr(3,1),nullptr,16) << 21;
    tlo +=std::stol(in.substr(4,1),nullptr,16) << 17;
    tlo +=std::stol(in.substr(5,1),nullptr,16) << 13;
    tlo +=std::stol(in.substr(6,1),nullptr,16) << 9;
    tlo +=std::stol(in.substr(7,1),nullptr,16) << 5;
    tlo +=(std::stol(in.substr(8,1),nullptr,16) & 0x08) << 1;

    tla =  (std::stol(in.substr(9,1),nullptr,16) & 0x7) << 22;
    tla += std::stol(in.substr(10,1),nullptr,16) << 18;
    tla += std::stol(in.substr(11,1),nullptr,16) << 14;
    tla += std::stol(in.substr(12,1),nullptr,16) << 10;
    tla += std::stol(in.substr(13,1),nullptr,16) << 6;
    tla += std::stol(in.substr(14,1),nullptr,16) << 2;
    tla += (std::stol(in.substr(15,1),nullptr,16) & 0x0C) >> 2;

    lat = tla*180/33554432;
    lon = tlo*360/33554432;
  }
} /* handle_LIP_latlon */


/*
  Creates a sds from text, format of a command send to the Pei device must be:

  AT+CTSDS=RxISSI,len<0x0D><0x0A>
  message<0x1A>

  Where:
  RxISSI  - the ISSI (not TEI) of the destination MS
  len     - the length of the following message in byte
  message - the message as hex characters
*/
bool createSDS(std::string & sds, std::string issi, std::string message)
{
  if (message.length() > 120 || issi.length() > 8) return false;

  std::stringstream ss;
  ss << "8204FF01";

  for (unsigned int a=0; a<message.length(); a++)
  {
    ss << std::hex << (int)message[a];
  }

  char f[2*message.length()+issi.length()+20];
  sprintf(f, "AT+CMGS=%s,%03d\r\n%s%c",
             std::to_string(std::stoi(issi)).c_str(),
             (int)ss.str().length() * 4,
             ss.str().c_str(), 0x1a);
  sds = f;
  return true;
} /* createSDS */


std::string decodeSDS(std::string hexSDS)
{
  std::string sds_text;
  unsigned int a;
  char byte[2];
  unsigned int x;
  std::stringstream ss;

  for (a=0; a < hexSDS.length(); a+=2)
  {
    ss << std::hex << hexSDS.substr(a,2);
    ss >> x;
    sprintf(byte, "%c", x);
    sds_text += byte;
    ss.clear();
  }
  return sds_text;
} /* decodeSDS */


std::string getPeiError(int errorcode)
{

std::string error[] = {
"0 - The MT was unable to send the data over the air (e.g. to the SwMI)",
"1 - The MT can not establish a reliable communication with the TE",
"2 - The PEI link of the MT is being used already",
"3 - This is a general error report code which indicates that the MT supports \
the command but not in its current state. This code shall be used when no \
other code is more appropriate for the specific context",
"4 - The MT does not support the command",
"5 - The MT can not process any command until the PIN for the SIM is provided",
"6 - Reserved",
"7 - Reserved",
"8 - Reserved",
"9 - Reserved",
"10 - The MT can not process the command due to the absence of a SIM",
"11 - The SIM PIN1 is required for the MT to execute the command",
"12 - MMI unblocking of the SIM PIN1 is required",
"13 - The MT failed to access the SIM",
"14 - The MT can not currently execute the command due to the SIM not being \
ready to proceed",
"15 - The MT does not recognize this SIM",
"16 - The entered PIN for the SIM is incorrect",
"17 - The SIM PIN2 is required for the MT to execute the command",
"18 - MMI unblocking of the SIM PIN2 is required",
"19 - Reserved",
"20 - The MT message stack is full",
"21 -The requested message index in the message stack does not exist",
"22 - The requested message index does not correspond to any message",
"23 - The MT failed to store or access to its message stack",
"24 - The text string associated with a status value is too long",
"25 - The text string associated with a status value contains invalid characters",
"26 - The <dial string> is longer than 25 digits",
"27 - The <dial string> contains invalid characters",
"28 - Reserved",
"29 - Reserved",
"30 - The MS is currently out of service and can not process the command",
"31 - The MT did not receive any Layer 2 acknowledgement from the SwMI",
"32 - <user data> decoding failed",
"33 - At least one of the parameters is of the wrong type e.g. string instead \
of number or vice-versa",
"34 - At least one of the supported parameters in the command is out of range",
"35 - Syntax error. The syntax of the command is incorrect e.g. mandatory \
parameters are missing or are exceeding Data received without command",
"36 - The MT received <user data> without AT+CMGS= ...<CR>",
"37 - AT+CMGS command received, but timeout expired waiting for <userdata>",
"38 - The TE has already registered the Protocol Identifier with the MT",
"39 - Registration table in SDS-TL is full. The MT can no longer register \
a new Protocol Identifier until a registered Protocol identifier is \
deregistered",
"40 - The MT supports the requested service but not while it is in DMO",
"41 - The MT is in Transmit inhibit mode and is not able to process the \
command in this state",
"42 - The MT is involved in a signalling activity and is not able to process \
the available command until the current transaction ends. In V+D, \
the signalling activity could be e.g. group attachment, group report, SDS \
processing, processing of DGNA, registration, authentication or any \
transaction requiring a response from the MS or the SwMI. In DMO, the \
signalling activity could be e.g. Call or SDS processing.",
"43 - The MT supports the requested service but not while it is in V+D",
"44 - The MT supports handling of unknown parameters",
"45 - Reserved" 
};

return error[errorcode];

} /* getPeiError */


//} /* namespace */

#endif /* TETRA_LIB_INCLUDED */



/*
 * This file has not been truncated
 */
