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
    // NS_LOG_UNCOND("RxDrop at " << Simulator::Now().GetSeconds());
    info.dropped_packets++;
}

static void
PacketSent(Ptr<const Packet> p)
{
    // NS_LOG_UNCOND("Packet sent at " << Simulator::Now().GetSeconds());
    info.total_packets++;
}
// Callbacks End

int
main(int argc, char* argv[])
{
    ns3::RngSeedManager::SetSeed(50);
    uint32_t nPackets = 100;

    CommandLine cmd(__FILE__);
    cmd.AddValue("num_packets", "Number of packets to echo", nPackets);
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    // LogComponentEnable("cs598EchoClientApplication", LOG_LEVEL_ALL);
    // LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_ALL);
    LogComponentEnable("cs598EchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    NS_LOG_INFO("Creating Topology");
    NodeContainer nodes;
    nodes.Create(2);


    // Ptr<UniformRandomVariable> uv = CreateObject<UniformRandomVariable>();
    // uv->SetStream(50);
    // RateErrorModel error_model;
    // error_model.SetRandomVariable(uv);
    // error_model.SetUnit(RateErrorModel::ERROR_UNIT_PACKET);
    // error_model.SetRate(error_p);


    PointToPointHelper pointToPointFast;
    pointToPointFast.SetDeviceAttribute("DataRate", StringValue("50Mbps"));
    pointToPointFast.SetChannelAttribute("Delay", StringValue("40ms")); // NY to London
    Ptr<RateErrorModel> em = CreateObject<RateErrorModel>();
    Ptr<UniformRandomVariable> uv = CreateObject<UniformRandomVariable>();
    uv->SetStream(50);
    uv->SetAttribute("Min", DoubleValue(0.5));
    uv->SetAttribute("Max", DoubleValue(1.0));
    em->SetRandomVariable(uv);
    em->SetUnit(RateErrorModel::ERROR_UNIT_PACKET);
    em->SetRate(0.25);
    pointToPointFast.SetDeviceAttribute("ReceiveErrorModel", PointerValue(em));

    PointToPointHelper pointToPointSlow;
    pointToPointSlow.SetDeviceAttribute("DataRate", StringValue("1Gbps"));
    pointToPointSlow.SetChannelAttribute("Delay", StringValue("60ms"));
    Ptr<RateErrorModel> em2 = CreateObject<RateErrorModel>();
    Ptr<UniformRandomVariable> uv2 = CreateObject<UniformRandomVariable>();
    uv2->SetStream(100);
    uv2->SetAttribute("Min", DoubleValue(0.0));
    uv2->SetAttribute("Max", DoubleValue(0.25));
    em->SetRandomVariable(uv2);
    em2->SetUnit(RateErrorModel::ERROR_UNIT_PACKET);
    em2->SetRate(0.25);
    pointToPointFast.SetDeviceAttribute("ReceiveErrorModel", PointerValue(em2));

    AsciiTraceHelper ascii;
    pointToPointFast.EnableAsciiAll(ascii.CreateFileStream("myfirst.tr"));
    pointToPointSlow.EnableAsciiAll(ascii.CreateFileStream("mysecond.tr"));

    NetDeviceContainer devicesFast;
    devicesFast = pointToPointFast.Install(nodes);
    NetDeviceContainer devicesSlow;
    devicesSlow = pointToPointSlow.Install(nodes);

    InternetStackHelper stack;
    stack.Install(nodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfacesFast = address.Assign(devicesFast);
    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer interfacesSlow = address.Assign(devicesSlow);


    NS_LOG_INFO("Creating Applications");
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(nodes.Get(1));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(300.0));

    //===//
    // UdpEchoClientHelper echoClientFast(interfacesFast.GetAddress(1), 9);
    // echoClientFast.SetAttribute("MaxPackets", UintegerValue(nPackets));
    // echoClientFast.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    // echoClientFast.SetAttribute("PacketSize", UintegerValue(1024));

    // UdpEchoClientHelper echoClientSlow(interfacesSlow.GetAddress(1), 9);
    // echoClientSlow.SetAttribute("MaxPackets", UintegerValue(nPackets));
    // echoClientSlow.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    // echoClientSlow.SetAttribute("PacketSize", UintegerValue(1024));

    // ApplicationContainer clientAppsFast = echoClientFast.Install(nodes.Get(0));
    // clientAppsFast.Start(Seconds(2.0));
    // clientAppsFast.Stop(Seconds(10.0));

    // ApplicationContainer clientAppsSlow = echoClientSlow.Install(nodes.Get(0));
    // clientAppsSlow.Start(Seconds(2.0));
    // clientAppsSlow.Stop(Seconds(10.0));
    //===//


    //
    cs598EchoClientHelper echoClient(interfacesFast.GetAddress(1), 9, interfacesSlow.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(nPackets));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(0.01)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));
    // echoClient.SetAttribute("Always", StringValue("fast"));

    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(300.0));
    //


    // Callbacks Start
    devicesFast.Get(0)->TraceConnectWithoutContext("PhyTxEnd", MakeCallback(&PacketSent));
    devicesSlow.Get(0)->TraceConnectWithoutContext("PhyTxEnd", MakeCallback(&PacketSent));
    devicesFast.Get(1)->TraceConnectWithoutContext("PhyTxDrop", MakeCallback(&RxDrop));
    devicesSlow.Get(1)->TraceConnectWithoutContext("PhyTxDrop", MakeCallback(&RxDrop));
    devicesFast.Get(1)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));
    devicesSlow.Get(1)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));
    devicesFast.Get(0)->TraceConnectWithoutContext("PhyTxDrop", MakeCallback(&RxDrop));
    devicesSlow.Get(0)->TraceConnectWithoutContext("PhyTxDrop", MakeCallback(&RxDrop));
    devicesFast.Get(0)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));
    devicesSlow.Get(0)->TraceConnectWithoutContext("PhyRxDrop", MakeCallback(&RxDrop));



    Simulator::Run();
    std::cout << "Total packets sent: " << info.total_packets << std::endl;
    std::cout << "Total packets dropped: " << info.dropped_packets << std::endl;
    Simulator::Destroy();


    return 0;
}
