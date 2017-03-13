/**
@file	 RewindLogic.h
@brief
@author  Tobias Blomberg / SM0SVX & Adi Bier / DL1HRC
@date	 2017-03-12

\verbatim
SvxLink - A Multi Purpose Voice Services System for Ham Radio Use
Copyright (C) 2003-2017 Tobias Blomberg / SM0SVX

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

#ifndef REWIND_LOGIC_INCLUDED
#define REWIND_LOGIC_INCLUDED


/****************************************************************************
 *
 * System Includes
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Project Includes
 *
 ****************************************************************************/


#include <AsyncDnsLookup.h>
#include <AsyncTimer.h>
#include <AsyncAudioFifo.h>
#include <AsyncAudioRecoder.h>


/****************************************************************************
 *
 * Local Includes
 *
 ****************************************************************************/

#include "LogicBase.h"


/****************************************************************************
 *
 * Forward declarations
 *
 ****************************************************************************/

namespace Async
{
  class UdpSocket;
  class DnsLookup;
};



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

#define REWIND_KEEP_ALIVE_INTERVAL   5
#define REWIND_SIGN_LENGTH           8
#define REWIND_PROTOCOL_SIGN         "REWIND01"
#define REWIND_CLASS_REWIND_CONTROL  0x0000
#define REWIND_CLASS_SYSTEM_CONSOLE  0x0100
#define REWIND_CLASS_SERVER_NOTICE   0x0200
#define REWIND_CLASS_DEVICE_DATA     0x0800
#define REWIND_CLASS_APPLICATION     0x0900
#define REWIND_CLASS_KAIROS_DATA     (REWIND_CLASS_DEVICE_DATA + 0x00)
#define REWIND_CLASS_HYTERA_DATA     (REWIND_CLASS_DEVICE_DATA + 0x10)
#define REWIND_TYPE_KEEP_ALIVE       (REWIND_CLASS_REWIND_CONTROL + 0)
#define REWIND_TYPE_CLOSE            (REWIND_CLASS_REWIND_CONTROL + 1)
#define REWIND_TYPE_CHALLENGE        (REWIND_CLASS_REWIND_CONTROL + 2)
#define REWIND_TYPE_AUTHENTICATION   (REWIND_CLASS_REWIND_CONTROL + 3)
#define REWIND_TYPE_REPORT           (REWIND_CLASS_SYSTEM_CONSOLE + 0)
#define REWIND_TYPE_BUSY_NOTICE      (REWIND_CLASS_SERVER_NOTICE + 0)
#define REWIND_TYPE_ADDRESS_NOTICE   (REWIND_CLASS_SERVER_NOTICE + 1)
#define REWIND_TYPE_BINDING_NOTICE   (REWIND_CLASS_SERVER_NOTICE + 2)
#define REWIND_TYPE_EXTERNAL_SERVER  (REWIND_CLASS_KAIROS_DATA + 0)
#define REWIND_TYPE_REMOTE_CONTROL   (REWIND_CLASS_KAIROS_DATA + 1)
#define REWIND_TYPE_SNMP_TRAP        (REWIND_CLASS_KAIROS_DATA + 2)
#define REWIND_TYPE_PEER_DATA        (REWIND_CLASS_HYTERA_DATA + 0)
#define REWIND_TYPE_RDAC_DATA        (REWIND_CLASS_HYTERA_DATA + 1)
#define REWIND_TYPE_MEDIA_DATA       (REWIND_CLASS_HYTERA_DATA + 2)
#define REWIND_TYPE_SUBSCRIPTION     (REWIND_CLASS_APPLICATION + 0x00)
#define REWIND_TYPE_DMR_DATA_BASE    (REWIND_CLASS_APPLICATION + 0x10)
#define REWIND_TYPE_DMR_AUDIO_FRAME  (REWIND_CLASS_APPLICATION + 0x20)
#define REWIND_TYPE_DMR_EMBEDDED_DATA (REWIND_CLASS_APPLICATION + 0x27)
#define REWIND_TYPE_SUPER_HEADER      (REWIND_CLASS_APPLICATION + 0x28)
#define REWIND_TYPE_FAILURE_CODE      (REWIND_CLASS_APPLICATION + 0x29)
#define REWIND_FLAG_NONE             0
#define REWIND_FLAG_REAL_TIME_1      (1 << 0)
#define REWIND_FLAG_REAL_TIME_2      (1 << 1)
#define REWIND_FLAG_DEFAULT_SET      REWIND_FLAG_NONE
#define REWIND_ROLE_REPEATER_AGENT   0x10
#define REWIND_ROLE_APPLICATION      0x20
#define REWIND_SERVICE_CRONOS_AGENT        (REWIND_ROLE_REPEATER_AGENT + 0)
#define REWIND_SERVICE_TELLUS_AGENT        (REWIND_ROLE_REPEATER_AGENT + 1)
#define REWIND_SERVICE_SIMPLE_APPLICATION  (REWIND_ROLE_APPLICATION    + 0)
#define SHA256_DIGEST_LENGTH    32

/****************************************************************************
 *
 * Exported Global Variables
 *
 ****************************************************************************/



/****************************************************************************
 *
 * Class definitions
 *
 ****************************************************************************/

/**
@brief
@author Tobias Blomberg / SM0SVX
@date   2017-02-12
*/
class RewindLogic : public LogicBase
{
  public:
    /**
     * @brief 	Constructor
     * @param   cfg A previously initialized configuration object
     * @param   name The name of the logic core
     */
    RewindLogic(Async::Config& cfg, const std::string& name);

    /**
     * @brief 	Destructor
     */
    ~RewindLogic(void);

    /**
     * @brief 	Initialize the logic core
     * @return	Returns \em true on success or \em false on failure
     */
    virtual bool initialize(void);

    /**
     * @brief 	Get the audio pipe sink used for writing audio into this logic
     * @return	Returns an audio pipe sink object
     */
    virtual Async::AudioSink *logicConIn(void) { return m_logic_con; }

    /**
     * @brief 	Get the audio pipe source used for reading audio from this logic
     * @return	Returns an audio pipe source object
     */
    virtual Async::AudioSource *logicConOut(void) { return m_logic_con; }

  protected:


  private:
    static const unsigned UDP_HEARTBEAT_TX_CNT_RESET = 60;

    struct RewindVersionData
    {
      uint32_t number;
      uint8_t service;
      char description[0];
    };

    struct RewindAddressData
    {
      struct in_addr address;
      uint16_t port;
    };

    struct RewindBindingData
    {
      uint16_t port;
    };

    struct RewindSubscriptionData
    {
      uint32_t type;
      uint32_t number;
    };

    struct RewindData
    {
      char sign[REWIND_SIGN_LENGTH];
      uint16_t type;
      uint16_t flags;
      uint32_t number;
      uint16_t length;
      uint8_t data[0];
    };

    enum STATUS {
      DISCONNECTED,
      CONNECTING,
      WAITING_PASS_ACK,
      AUTHENTICATED
    };

    STATUS m_state;


    unsigned              m_msg_type;
    Async::UdpSocket*     m_udp_sock;
    Async::IpAddress	  ip_addr;
    Async::DnsLookup	  *dns;
    uint32_t              m_client_id;
    std::string           m_auth_key;
    std::string           rewind_host;
    uint16_t              rewind_port;
    std::string           m_callsign;
    std::string           m_id;
    Async::Timer          m_reconnect_timer;
    Async::Timer          m_ping_timer;

    Async::AudioRecoder*  m_logic_con;

    std::string           m_rxfreq;
    std::string           m_txfreq;
    std::string           m_power;
    std::string           m_color;
    std::string           m_lat;
    std::string           m_lon;
    std::string           m_height;
    std::string           m_location;
    std::string           m_description;
    std::string           m_swid;
    std::string           m_tg;

    int                   sequenceNumber;
    bool                  m_slot1;
    bool                  m_slot2;

    RewindLogic(const RewindLogic&);
    RewindLogic& operator=(const RewindLogic&);

    void handleMsgServerInfo(std::istream& is);
    void sendEncodedAudio(const void *buf, int count);
    void flushEncodedAudio(void);
    void onDataReceived(const Async::IpAddress& addr, uint16_t port,
                             void *buf, int count);
    void sendMsg(RewindData *rd, size_t len);
    void connect(void);
    void reconnect(Async::Timer *t);
    void dnsResultsReady(Async::DnsLookup& dns_lookup);
    void disconnect(void);
    void allEncodedSamplesFlushed(void);
    void flushTimeout(Async::Timer *t);
    void pingHandler(Async::Timer *t);
    void authenticate(const std::string pass);
    void sendKeepAlive(void);
    void sendServiceData(void);
    void sendCloseMessage(void);
    void sendConfiguration(void);
    void mkSHA256(std::string pass, int len, uint8_t hash[]);
    void handleDataMessage(std::string datamessage);

};  /* class RewindLogic */


//} /* namespace */

#endif /* REWIND_LOGIC_INCLUDED */


/*
 * This file has not been truncated
 */