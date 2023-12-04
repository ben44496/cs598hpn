#ifndef CS598_MODULE_HELPER_H
#define CS598_MODULE_HELPER_H

#include "ns3/cs598-echo-client.h"
#include "ns3/application-container.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv6-address.h"
#include "ns3/node-container.h"
#include "ns3/object-factory.h"
#include <stdint.h>

namespace ns3
{

// Each class should be documented using Doxygen,
// and have an \ingroup cs598-module directive

class cs598EchoClientHelper
{
  public:
    cs598EchoClientHelper(Address ip, uint16_t port);
    cs598EchoClientHelper(Address addr);

    void SetAttribute(std::string name, const AttributeValue& value);

    void SetFill(Ptr<Application> app, std::string fill);
    void SetFill(Ptr<Application> app, uint8_t fill, uint32_t dataLength);
    void SetFill(Ptr<Application> app, uint8_t* fill, uint32_t fillLength, uint32_t dataLength);

    ApplicationContainer Install(Ptr<Node> node) const;

    ApplicationContainer Install(std::string nodeName) const;

    ApplicationContainer Install(NodeContainer c) const;

  private:
    Ptr<Application> InstallPriv(Ptr<Node> node) const;

    ObjectFactory m_factory;
};

} // namespace ns3


#endif /* CS598_MODULE_HELPER_H */
