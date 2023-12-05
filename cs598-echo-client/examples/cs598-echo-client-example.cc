#include "ns3/core-module.h"
#include "ns3/cs598-echo-client-helper.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

/**
 *
 *       10.1.1.x (fast)
 *  --------------------
 *  |                  |
 * Node 0            Node 1
 *  |                  |
 *  --------------------
 *       10.1.2.x (slow)
 *
 */

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("CS598EchoClientExample");

typedef struct Info {
    uint32_t total_packets;
    uint32_t dropped_packets;
} Info;
Info info;

// Callbacks Start
static void
RxDrop(Ptr<const Packet> p)
{
    NS_LOG_UNCOND("RxDrop at " << Simulator::Now().GetSeconds());
    info.dropped_packets++;
}

static void
PacketSent(Ptr<const Packet> p)
{
    NS_LOG_UNCOND("Packet sent at " << Simulator::Now().GetSeconds());
    info.total_packets++;
}
// Callbacks End

int
main(int argc, char* argv[])
{
    uint32_t nPackets = 10;

    CommandLine cmd(__FILE__);
    cmd.AddValue("num_packets", "Number of packets to echo", nPackets);
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    // LogComponentEnable("cs598EchoClientApplication", LOG_LEVEL_ALL);
    // LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_ALL);
    LogComponentEnable("cs598EchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    NS_LOG_INFO("Creating Topology");
    NodeContainer nodesFast;
    nodesFast.Create(2);

    NodeContainer nodesSlow;
    nodesSlow.Add(nodesFast.Get(1));
    nodesSlow.Add(nodesFast.Get(0));

    PointToPointHelper pointToPointFast;
    pointToPointFast.SetDeviceAttribute("DataRate", StringValue("50Mbps"));
    pointToPointFast.SetChannelAttribute("Delay", StringValue("20ms")); // NY to London
    Ptr<RateErrorModel> em = CreateObject<RateErrorModel>();
    em->SetAttribute("ErrorRate", DoubleValue(0.25));
    em->SetAttribute("ErrorUnit", StringValue("ERROR_UNIT_PACKET"));
    pointToPointFast.SetDeviceAttribute("ReceiveErrorModel", PointerValue(em));

    PointToPointHelper pointToPointSlow;
    pointToPointSlow.SetDeviceAttribute("DataRate", StringValue("1Gbps"));
    pointToPointSlow.SetChannelAttribute("Delay", StringValue("60ms"));

    AsciiTraceHelper ascii;
    pointToPointFast.EnableAsciiAll(ascii.CreateFileStream("myfirst.tr"));
    pointToPointSlow.EnableAsciiAll(ascii.CreateFileStream("mysecond.tr"));

    NetDeviceContainer devicesFast;
    devicesFast = pointToPointFast.Install(nodesFast);
    NetDeviceContainer devicesSlow;
    devicesSlow = pointToPointSlow.Install(nodesSlow);

    InternetStackHelper stack;
    stack.Install(nodesFast);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfacesFast = address.Assign(devicesFast);
    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfacesSlow = address.Assign(devicesSlow);

    int flags = 1;
    if (flags == 0) {
        // Node 0 is client, node 1 is server
        UdpEchoClientHelper echoClientFast(interfacesFast.GetAddress(1), 9);
        echoClientFast.SetAttribute("MaxPackets", UintegerValue(nPackets));
        echoClientFast.SetAttribute("Interval", TimeValue(Seconds(0.25)));
        echoClientFast.SetAttribute("PacketSize", UintegerValue(1024));

        UdpEchoClientHelper echoClientSlow(interfacesSlow.GetAddress(1), 9);
        echoClientSlow.SetAttribute("MaxPackets", UintegerValue(nPackets));
        echoClientSlow.SetAttribute("Interval", TimeValue(Seconds(0.25)));
        echoClientSlow.SetAttribute("PacketSize", UintegerValue(1024));

        ApplicationContainer clientAppsFast = echoClientFast.Install(nodesFast.Get(0));
        clientAppsFast.Start(Seconds(2.0));
        clientAppsFast.Stop(Seconds(20.0));

        ApplicationContainer clientAppsSlow = echoClientSlow.Install(nodesSlow.Get(0));
        clientAppsSlow.Start(Seconds(2.0));
        clientAppsSlow.Stop(Seconds(20.0));

        UdpEchoServerHelper echoServerFast(9);
        UdpEchoServerHelper echoServerSlow(9);

        ApplicationContainer serverApps = echoServerFast.Install(nodesFast.Get(1));
        serverApps.Start(Seconds(1.0));
        serverApps.Stop(Seconds(20.0));

        serverApps = echoServerSlow.Install(nodesSlow.Get(1));
        serverApps.Start(Seconds(1.0));
        serverApps.Stop(Seconds(20.0));

        // Callbacks Start
        devicesFast.Get(0)->TraceConnectWithoutContext("PhyTxBegin", MakeCallback(&PacketSent));
        devicesSlow.Get(0)->TraceConnectWithoutContext("PhyTxBegin", MakeCallback(&PacketSent));
        devicesFast.Get(1)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));
        devicesSlow.Get(1)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));
    } else if (flags == 1) {
        // Using cs598EchoClientHelper
        cs598EchoClientHelper echoClientHelperFast(interfacesFast.GetAddress(1), 9, interfacesSlow.GetAddress(1), 9);
        echoClientHelperFast.SetAttribute("MaxPackets", UintegerValue(nPackets));
        echoClientHelperFast.SetAttribute("Interval", TimeValue(Seconds(0.25)));
        echoClientHelperFast.SetAttribute("PacketSize", UintegerValue(1024));

        ApplicationContainer clientApps = echoClientHelperFast.Install(nodesFast.Get(0));
        clientApps.Start(Seconds(2.0));
        clientApps.Stop(Seconds(20.0));

        UdpEchoServerHelper echoServerFast(9);
        UdpEchoServerHelper echoServerSlow(9);

        ApplicationContainer serverApps = echoServerFast.Install(nodesFast.Get(1));
        serverApps.Start(Seconds(1.0));
        serverApps.Stop(Seconds(20.0));

        serverApps = echoServerSlow.Install(nodesSlow.Get(1));
        serverApps.Start(Seconds(1.0));
        serverApps.Stop(Seconds(20.0));

        devicesFast.Get(0)->TraceConnectWithoutContext("PhyTxBegin", MakeCallback(&PacketSent));
        devicesSlow.Get(0)->TraceConnectWithoutContext("PhyTxBegin", MakeCallback(&PacketSent));
        devicesFast.Get(1)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));
        devicesSlow.Get(1)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));
    }

    Simulator::Run();
    std::cout << "Total packets sent: " << info.total_packets << std::endl;
    std::cout << "Total packets dropped: " << info.dropped_packets << std::endl;
    Simulator::Destroy();


    return 0;
}
