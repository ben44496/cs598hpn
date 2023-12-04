#include "cs598-echo-client-helper.h"

#include "ns3/names.h"
#include "ns3/cs598-echo-client.h"
#include "ns3/uinteger.h"
#include "ns3/application-container.h"
#include "ns3/node-container.h"

namespace ns3
{

cs598EchoClientHelper::cs598EchoClientHelper(Address address, uint16_t port)
{
    m_factory.SetTypeId(cs598EchoClient::GetTypeId());
    SetAttribute("RemoteAddress", AddressValue(address));
    SetAttribute("RemotePort", UintegerValue(port));
}

cs598EchoClientHelper::cs598EchoClientHelper(Address address)
{
    m_factory.SetTypeId(cs598EchoClient::GetTypeId());
    SetAttribute("RemoteAddress", AddressValue(address));
}

void
cs598EchoClientHelper::SetAttribute(std::string name, const AttributeValue& value)
{
    m_factory.Set(name, value);
}

void
cs598EchoClientHelper::SetFill(Ptr<Application> app, std::string fill)
{
    app->GetObject<cs598EchoClient>()->SetFill(fill);
}

void
cs598EchoClientHelper::SetFill(Ptr<Application> app, uint8_t fill, uint32_t dataLength)
{
    app->GetObject<cs598EchoClient>()->SetFill(fill, dataLength);
}

void
cs598EchoClientHelper::SetFill(Ptr<Application> app,
                             uint8_t* fill,
                             uint32_t fillLength,
                             uint32_t dataLength)
{
    app->GetObject<cs598EchoClient>()->SetFill(fill, fillLength, dataLength);
}

ApplicationContainer
cs598EchoClientHelper::Install(Ptr<Node> node) const
{
    return ApplicationContainer(InstallPriv(node));
}

ApplicationContainer
cs598EchoClientHelper::Install(std::string nodeName) const
{
    Ptr<Node> node = Names::Find<Node>(nodeName);
    return ApplicationContainer(InstallPriv(node));
}

ApplicationContainer
cs598EchoClientHelper::Install(NodeContainer c) const
{
    ApplicationContainer apps;
    for (auto i = c.Begin(); i != c.End(); ++i)
    {
        apps.Add(InstallPriv(*i));
    }

    return apps;
}

Ptr<Application>
cs598EchoClientHelper::InstallPriv(Ptr<Node> node) const
{
    Ptr<Application> app = m_factory.Create<cs598EchoClient>();
    node->AddApplication(app);

    return app;
}


}
