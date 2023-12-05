#include "cs598-echo-client.h"

#include "ns3/seq-ts-header.h"

#include "ns3/inet-socket-address.h"
#include "ns3/inet6-socket-address.h"
#include "ns3/ipv4-address.h"
#include "ns3/log.h"
#include "ns3/nstime.h"
#include "ns3/packet.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/socket.h"
#include "ns3/uinteger.h"
// #include <string.h>
#include "ns3/core-module.h"
#include <cstdio>
#include <cstdlib>


namespace ns3
{

NS_LOG_COMPONENT_DEFINE("cs598EchoClientApplication");

NS_OBJECT_ENSURE_REGISTERED(cs598EchoClient);

TypeId
cs598EchoClient::GetTypeId()
{
    static TypeId tid =
        TypeId("ns3::cs598EchoClient")
            .SetParent<Application>()
            .SetGroupName("Applications")
            .AddConstructor<cs598EchoClient>()
            .AddAttribute(
                "MaxPackets",
                "The maximum number of packets the application will send (zero means infinite)",
                UintegerValue(100),
                MakeUintegerAccessor(&cs598EchoClient::m_count),
                MakeUintegerChecker<uint32_t>())
            .AddAttribute("Interval",
                          "The time to wait between packets",
                          TimeValue(Seconds(1.0)),
                          MakeTimeAccessor(&cs598EchoClient::m_interval),
                          MakeTimeChecker())
            .AddAttribute("RemoteAddressFast",
                          "The destination Address of the outbound packets",
                          AddressValue(),
                          MakeAddressAccessor(&cs598EchoClient::m_peerAddressFast),
                          MakeAddressChecker())
            .AddAttribute("RemotePortFast",
                          "The destination port of the outbound packets",
                          UintegerValue(0),
                          MakeUintegerAccessor(&cs598EchoClient::m_peerPortFast),
                          MakeUintegerChecker<uint16_t>())
            .AddAttribute("RemoteAddressSlow",
                          "The destination Address of the outbound packets",
                          AddressValue(),
                          MakeAddressAccessor(&cs598EchoClient::m_peerAddressSlow),
                          MakeAddressChecker())
            .AddAttribute("RemotePortSlow",
                          "The destination port of the outbound packets",
                          UintegerValue(0),
                          MakeUintegerAccessor(&cs598EchoClient::m_peerPortSlow),
                          MakeUintegerChecker<uint16_t>())
            .AddAttribute(
                "PacketSize",
                "Size of echo data in outbound packets",
                UintegerValue(100),
                MakeUintegerAccessor(&cs598EchoClient::SetDataSize, &cs598EchoClient::GetDataSize),
                MakeUintegerChecker<uint32_t>())
            .AddAttribute(
                "Always",
                "Always send on fast or slow path",
                StringValue(""),
                MakeStringAccessor(&cs598EchoClient::SetAlways),
                MakeStringChecker());

    return tid;
}

cs598EchoClient::cs598EchoClient() : m_packetLossCounterFast(0), m_packetLossCounterSlow(0)
{
    NS_LOG_FUNCTION(this);
    m_sent = 0;
    m_socketFast = nullptr;
    m_socketSlow = nullptr;
    m_sendEvent = EventId();
    m_data = nullptr;
    m_dataSize = 0;
    m_bufferFast.seq = 0;
    m_bufferSlow.seq = 0;
}

cs598EchoClient::~cs598EchoClient()
{
    NS_LOG_FUNCTION(this);
    m_socketFast = nullptr;
    m_socketSlow = nullptr;

    delete[] m_data;
    m_data = nullptr;
    m_dataSize = 0;
}

void
cs598EchoClient::SetRemote(Address ip, uint16_t port, bool isFast)
{
    NS_LOG_FUNCTION(this << ip << port);
    if (isFast) {
        m_peerAddressFast = ip;
        m_peerPortFast = port;
    } else {
        m_peerAddressSlow = ip;
        m_peerPortSlow = port;
    }
}

void
cs598EchoClient::SetRemote(Address addr, bool isFast)
{
    NS_LOG_FUNCTION(this << addr);
    if (isFast) {
        m_peerAddressFast = addr;
    } else {
        m_peerAddressSlow = addr;
    }
}

void
cs598EchoClient::DoDispose()
{
    NS_LOG_FUNCTION(this);
    Application::DoDispose();
}

void
cs598EchoClient::StartApplication()
{
    NS_LOG_FUNCTION(this);
    // m_packetLossCounterFast.SetBitMapSize(sizeof(SequenceNumber)*8);
    // m_packetLossCounterSlow.SetBitMapSize(sizeof(SequenceNumber)*8);
    m_packetLossCounterFast.SetBitMapSize(64);
    m_packetLossCounterSlow.SetBitMapSize(64);
    if (!m_socketFast)
    {
        TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");
        m_socketFast = Socket::CreateSocket(GetNode(), tid);
        if (Ipv4Address::IsMatchingType(m_peerAddressFast))
        {
            if (m_socketFast->Bind() == -1)
            {
                NS_FATAL_ERROR("Failed to bind socket");
            }
            m_socketFast->Connect(
                InetSocketAddress(Ipv4Address::ConvertFrom(m_peerAddressFast), m_peerPortFast));
        }
        else if (InetSocketAddress::IsMatchingType(m_peerAddressFast))
        {
            if (m_socketFast->Bind() == -1)
            {
                NS_FATAL_ERROR("Failed to bind socket");
            }
            m_socketFast->Connect(m_peerAddressFast);
        }
        else
        {
            NS_ASSERT_MSG(false, "Incompatible address type: " << m_peerAddressFast);
        }
    }

    m_socketFast->SetRecvCallback(MakeCallback(&cs598EchoClient::HandleRead, this));
    m_socketFast->SetAllowBroadcast(true);

    if (!m_socketSlow)
    {
        TypeId tid = TypeId::LookupByName("ns3::UdpSocketFactory");
        m_socketSlow = Socket::CreateSocket(GetNode(), tid);
        if (Ipv4Address::IsMatchingType(m_peerAddressSlow))
        {
            if (m_socketSlow->Bind() == -1)
            {
                NS_FATAL_ERROR("Failed to bind socket");
            }
            m_socketSlow->Connect(
                InetSocketAddress(Ipv4Address::ConvertFrom(m_peerAddressSlow), m_peerPortSlow));
        }
        else if (InetSocketAddress::IsMatchingType(m_peerAddressSlow))
        {
            if (m_socketSlow->Bind() == -1)
            {
                NS_FATAL_ERROR("Failed to bind socket");
            }
            m_socketSlow->Connect(m_peerAddressSlow);
        }
        else
        {
            NS_ASSERT_MSG(false, "Incompatible address type: " << m_peerAddressSlow);
        }
    }

    m_socketSlow->SetRecvCallback(MakeCallback(&cs598EchoClient::HandleRead, this));
    m_socketSlow->SetAllowBroadcast(true);

    ScheduleTransmit(Seconds(0.));
}

void
cs598EchoClient::StopApplication()
{
    NS_LOG_FUNCTION(this);

    if (m_socketFast) {
        m_socketFast->Close();
        m_socketFast->SetRecvCallback(MakeNullCallback<void, Ptr<Socket>>());
        m_socketFast = nullptr;
    }

    if (m_socketSlow) {
        m_socketSlow->Close();
        m_socketSlow->SetRecvCallback(MakeNullCallback<void, Ptr<Socket>>());
        m_socketSlow = nullptr;
    }

    Simulator::Cancel(m_sendEvent);
}

void
cs598EchoClient::SetDataSize(uint32_t dataSize)
{
    NS_LOG_FUNCTION(this << dataSize);

    //
    // If the client is setting the echo packet data size this way, we infer
    // that she doesn't care about the contents of the packet at all, so
    // neither will we.
    //
    delete[] m_data;
    m_data = nullptr;
    m_dataSize = 0;
    m_size = dataSize;
}

uint32_t
cs598EchoClient::GetDataSize() const
{
    NS_LOG_FUNCTION(this);
    return m_size;
}

void
cs598EchoClient::ScheduleTransmit(Time dt)
{
    NS_LOG_FUNCTION(this << dt);
    m_sendEvent = Simulator::Schedule(dt, &cs598EchoClient::Send, this);
}

void
cs598EchoClient::Send()
{
    NS_LOG_FUNCTION(this);

    NS_ASSERT(m_sendEvent.IsExpired());

    Ptr<Packet> p;
    // if (m_dataSize)
    // {
    //     //
    //     // If m_dataSize is non-zero, we have a data buffer of the same size that we
    //     // are expected to copy and send.  This state of affairs is created if one of
    //     // the Fill functions is called.  In this case, m_size must have been set
    //     // to agree with m_dataSize
    //     //
    //     NS_ASSERT_MSG(m_dataSize == m_size,
    //                   "CS598UdpEchoClient::Send(): m_size and m_dataSize inconsistent");
    //     NS_ASSERT_MSG(m_data, "CS598UdpEchoClient::Send(): m_dataSize but no m_data");
    //     p = Create<Packet>(m_data, m_dataSize);
    // }
    // else
    // {
    //     //
    //     // If m_dataSize is zero, the client has indicated that it doesn't care
    //     // about the data itself either by specifying the data size by setting
    //     // the corresponding attribute or by not calling a SetFill function.  In
    //     // this case, we don't worry about it either.  But we do allow m_size
    //     // to have a value different from the (zero) m_dataSize.
    //     //
    //     p = Create<Packet>(m_size);
    // }

    Address localAddress;

    Ptr<Socket>& socket = m_socketFast;
    Address& peerAddress = m_peerAddressFast;
    uint16_t& peerPort = m_peerPortFast;
    bool isFast = true;
    // TODO: LOGIC TO FIGURE OUT WHICH SOCKET

    isFast = calculateWhichSocket();

    // std::cout << m_always << std::endl;
    if ((isFast && m_always == "") || m_always == "fast") {
    // if (isFast) {
        socket = m_socketFast;
        peerAddress = m_peerAddressFast;
        peerPort = m_peerPortFast;
        p = Create<Packet>((uint8_t*)&m_bufferFast, sizeof(SequenceNumber));
        m_bufferFast.seq++;
        NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": Sent fast path.");
    } else if ((!isFast && m_always == "") || m_always == "slow") {
    // } else if (!isFast) {
        socket = m_socketSlow;
        peerAddress = m_peerAddressSlow;
        peerPort = m_peerPortSlow;
        p = Create<Packet>((uint8_t*)&m_bufferSlow, sizeof(SequenceNumber));
        m_bufferSlow.seq++;
        NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": Sent slow path.");
    }


    socket->GetSockName(localAddress);
    // call to the trace sinks before the packet is actually sent,
    // so that tags added to the packet can be sent as well
    m_txTrace(p);
    if (Ipv4Address::IsMatchingType(peerAddress))
    {
        m_txTraceWithAddresses(
            p,
            localAddress,
            InetSocketAddress(Ipv4Address::ConvertFrom(peerAddress), peerPort));
    }
    socket->Send(p);
    ++m_sent;

    // if (Ipv4Address::IsMatchingType(peerAddress))
    // {
    //     NS_LOG_INFO("At time " << Simulator::Now().As(Time::S) << " client sent " << m_size
    //                            << " bytes to " << Ipv4Address::ConvertFrom(peerAddress)
    //                            << " port " << peerPort);
    // }
    // else if (InetSocketAddress::IsMatchingType(peerAddress))
    // {
    //     NS_LOG_INFO(
    //         "At time " << Simulator::Now().As(Time::S) << " client sent " << m_size << " bytes to "
    //                    << InetSocketAddress::ConvertFrom(peerAddress).GetIpv4() << " port "
    //                    << InetSocketAddress::ConvertFrom(peerAddress).GetPort());
    // }

    if (m_sent < m_count || m_count == 0)
    {
        ScheduleTransmit(m_interval);
    }
}

void
cs598EchoClient::HandleRead(Ptr<Socket> socket)
{
    NS_LOG_FUNCTION(this << socket);
    Ptr<Packet> packet;
    Address from;
    Address localAddress;
    while ((packet = socket->RecvFrom(from)))
    {
        if (InetSocketAddress::IsMatchingType(from))
        {
        //     NS_LOG_INFO("At time " << Simulator::Now().As(Time::S) << " client received "
        //                            << packet->GetSize() << " bytes from "
        //                            << InetSocketAddress::ConvertFrom(from).GetIpv4() << " port "
        //                            << InetSocketAddress::ConvertFrom(from).GetPort());
            if (InetSocketAddress::ConvertFrom(from).GetIpv4() == m_peerAddressFast) {
                NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": Received from fast");
                SequenceNumber seq;
                packet->CopyData(seq.seqBytes, (uint32_t)sizeof(SequenceNumber));
                // std::cout << seq.seq << std::endl;
                m_packetLossCounterFast.NotifyReceived(seq.seq);
                NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": Sequence Number: " << seq.seq);
            } else {
                NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": Received from slow");
                SequenceNumber seq;
                packet->CopyData(seq.seqBytes, (uint32_t)sizeof(SequenceNumber));
                // std::cout << seq.seq << std::endl;
                m_packetLossCounterSlow.NotifyReceived(seq.seq);
                NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": Sequence Number: " << seq.seq);
            }
        }
        socket->GetSockName(localAddress);
        m_rxTrace(packet);
        m_rxTraceWithAddresses(packet, from, localAddress);
    }
}

bool
cs598EchoClient::calculateWhichSocket()
{
    NS_LOG_FUNCTION(this);
    NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": Packet loss fast: " << m_packetLossCounterFast.GetLost() << ", slow: " << m_packetLossCounterSlow.GetLost());

    double pA = m_packetLossCounterFast.GetLost() / 64.0;
    double pB = m_packetLossCounterSlow.GetLost() / 64.0;
    double Tfast = 0.04*(1+pA)/(1-2*pA); // in seconds, 20ms
    double Tslow = 0.06*(1+pB)/(1-2*pB); // in seconds, 60ms, from example

    NS_LOG_INFO("T" << Simulator::Now().As(Time::S) << ": pA: " << pA << ", pB: " << pB << ", Tfast: " << Tfast << ", Tslow: " << Tslow);
    if (Tfast <= Tslow) {
        return true;
    }
    return false;
}


void
cs598EchoClient::SetAlways(const std::string& always)
{
    NS_LOG_FUNCTION(this);
    m_always = always;
}
}
