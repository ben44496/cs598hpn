#ifndef CS598_MODULE_H
#define CS598_MODULE_H

// Add a doxygen group for this module.
// If you have more than one file, this should be in only one of them.
/**
 * \defgroup cs598-module Description of the cs598-module
 */

#include "ns3/cs598-udp-echo-client.h"
// #include "ns3/cs598-udp-echo-server.h"

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ipv4-address.h"
#include "ns3/ptr.h"
#include "ns3/applications-module.h"
#include "ns3/packet-loss-counter.h"
#include "ns3/cs598-packet-loss-counter.h"
#include <ns3/traced-callback.h>
#include <stdint.h>

namespace ns3
{


// Each class should be documented using Doxygen,
// and have an \ingroup cs598-module directive
class Socket;
class Packet;

class cs598EchoClient : public Application
{
  public:
    typedef union {
      uint32_t seq;
      uint8_t seqBytes[4];
    } SequenceNumber;

    static TypeId GetTypeId();

    cs598EchoClient();

    ~cs598EchoClient() override;

    void SetRemote(Address ip, uint16_t port, bool isFast);

    void SetRemote(Address addr, bool isFast);

    void SetDataSize(uint32_t dataSize);
    uint32_t GetDataSize() const;

  protected:
    void DoDispose() override;

  private:
    void StartApplication() override;

    void StopApplication() override;

    void ScheduleTransmit(Time dt);

    void Send();

    void HandleRead(Ptr<Socket> socket);

    TracedCallback<Ptr<const Packet>> m_txTrace;
    TracedCallback<Ptr<const Packet>> m_rxTrace;
    TracedCallback<Ptr<const Packet>, const Address &, const Address &> m_txTraceWithAddresses;
    TracedCallback<Ptr<const Packet>, const Address &, const Address &> m_rxTraceWithAddresses;

    uint32_t m_count;
    Time m_interval;
    uint32_t m_size;

    uint32_t m_dataSize; //!< packet payload size (must be equal to m_size)
    uint8_t* m_data;     //!< packet payload data

    uint32_t m_sent; //!< Counter for sent packets

    Address m_peerAddressFast; //!< Remote peer address
    uint16_t m_peerPortFast;   //!< Remote peer port
    Ptr<Socket> m_socketFast;

    Address m_peerAddressSlow;
    uint16_t m_peerPortSlow;
    Ptr<Socket> m_socketSlow;


    CS598PacketLossCounter m_packetLossCounterFast;
    SequenceNumber m_bufferFast;
    CS598PacketLossCounter m_packetLossCounterSlow;
    SequenceNumber m_bufferSlow;

    EventId m_sendEvent; //!< Event to send the next packet
#ifdef NS3_LOG_ENABLE
    std::string m_peerAddressString; //!< Remote peer address string
#endif                               // NS3_LOG_ENABLE


  bool calculateWhichSocket(Ptr<Packet> packet, Address from, Address localAddress);
  // return true for fast, false for slow
};

}

#endif /* CS598_MODULE_H */
