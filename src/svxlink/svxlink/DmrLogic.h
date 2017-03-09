/**
@file	 DmrLogic.h
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

#ifndef DMR_LOGIC_INCLUDED
#define DMR_LOGIC_INCLUDED


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
#include <AsyncAudioEncoder.h>
#include <AsyncAudioDecoder.h>


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
class DmrLogic : public LogicBase
{
  public:
    /**
     * @brief 	Constructor
     * @param   cfg A previously initialized configuration object
     * @param   name The name of the logic core
     */
    DmrLogic(Async::Config& cfg, const std::string& name);

    /**
     * @brief 	Destructor
     */
    ~DmrLogic(void);

    /**
     * @brief 	Initialize the logic core
     * @return	Returns \em true on success or \em false on failure
     */
    virtual bool initialize(void);

    /**
     * @brief 	Get the audio pipe sink used for writing audio into this logic
     * @return	Returns an audio pipe sink object
     */
    virtual Async::AudioSink *logicConIn(void) { return m_logic_con_in; }

    /**
     * @brief 	Get the audio pipe source used for reading audio from this logic
     * @return	Returns an audio pipe source object
     */
    virtual Async::AudioSource *logicConOut(void) { return m_logic_con_out; }

  protected:

  private:
    static const unsigned UDP_HEARTBEAT_TX_CNT_RESET = 60;


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
    std::string           dmr_host;
    uint16_t              dmr_port;
    std::string           m_callsign;
    std::string           m_id;
    Async::Timer          m_reconnect_timer;
    Async::Timer          m_ping_timer;

    Async::AudioEncoder*  m_logic_con_in;
    Async::AudioFifo*     m_logic_con_out;
    Async::AudioDecoder*  m_dec;
    std::string           m_rxfreq;
    std::string           m_txfreq;
    std::string           m_power;
    std::string           m_color;
    std::string           m_lat;
    std::string           m_lon;    
    std::string           m_height;
    std::string           m_location;
    std::string           m_description;
    std::string           m_url;
    std::string           m_swid;
    std::string           m_pack;
    int                  seqId;
    bool                 m_slot1;
    bool                 m_slot2;

    DmrLogic(const DmrLogic&);
    DmrLogic& operator=(const DmrLogic&);

    void handleMsgServerInfo(std::istream& is);
    void sendEncodedAudio(const void *buf, int count);
    void flushEncodedAudio(void);
    void onDataReceived(const Async::IpAddress& addr, uint16_t port,
                             void *buf, int count);
    void sendMsg(std::string msg);
    void connect(void);
    void reconnect(Async::Timer *t);
    void dnsResultsReady(Async::DnsLookup& dns_lookup);
    void disconnect(void);
    void allEncodedSamplesFlushed(void);
    void flushTimeout(Async::Timer *t);
    void pingHandler(Async::Timer *t);
    void authPassphrase(const char *t);
    void sendPing(void);
    void sendPong(void);
    void sendCloseMessage(void);
    void sendConfiguration(void);
    void handleDataMessage(std::string datamessage);

};  /* class DmrLogic */


//} /* namespace */

#endif /* DMR_LOGIC_INCLUDED */


/*
 * This file has not been truncated
 */
