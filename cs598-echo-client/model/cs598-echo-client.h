#ifndef CS598_MODULE_H
#define CS598_MODULE_H

// Add a doxygen group for this module.
// If you have more than one file, this should be in only one of them.
/**
 * \defgroup cs598-module Description of the cs598-module
 */

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ipv4-address.h"
#include "ns3/ptr.h"
#include <ns3/traced-callback.h>


namespace ns3
{

// Each class should be documented using Doxygen,
// and have an \ingroup cs598-module directive
class Socket;
class Packet;

class cs598EchoClient : public Application
{
  public:
    static TypeId GetTypeId();

    cs598EchoClient();

    ~cs598EchoClient() override;

    void SetRemote(Address ip, uint16_t port);

    void SetRemote(Address addr);

    void SetDataSize(uint32_t dataSize);

    uint32_t GetDataSize() const;

    void SetFill(std::string fill);
    void SetFill(uint8_t fill, uint32_t dataSize);
    void SetFill(uint8_t* fill, uint32_t fillSize, uint32_t dataSize);

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

    uint32_t m_count; //!< Maximum number of packets the application will send
    Time m_interval;  //!< Packet inter-send time
    uint32_t m_size;  //!< Size of the sent packet (including the SeqTsHeader)

    uint32_t m_dataSize; //!< packet payload size (must be equal to m_size)
    uint8_t* m_data;     //!< packet payload data

    uint32_t m_sent;       //!< Counter for sent packets
    Ptr<Socket> m_socket;  //!< Socket
    Address m_peerAddress; //!< Remote peer address
    uint16_t m_peerPort;   //!< Remote peer port
    EventId m_sendEvent;   //!< Event to send the next packet

#ifdef NS3_LOG_ENABLE
    std::string m_peerAddressString; //!< Remote peer address string
#endif                               // NS3_LOG_ENABLE

};

}

#endif /* CS598_MODULE_H */
