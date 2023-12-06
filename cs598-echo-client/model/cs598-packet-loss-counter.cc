/*
 *  Copyright (c) 2009 INRIA, UDCAST
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Amine Ismail <amine.ismail@sophia.inria.fr>
 *                      <amine.ismail@udcast.com>
 */

#include "cs598-packet-loss-counter.h"

#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/uinteger.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("CS598PacketLossCounter");

CS598PacketLossCounter::CS598PacketLossCounter(uint8_t bitmapSize)
    : m_lost(0),
      m_bitMapSize(0),
      m_lastMaxSeqNum(0),
      m_receiveBitMap(nullptr)
{
    NS_LOG_FUNCTION(this << bitmapSize);
    SetBitMapSize(bitmapSize);
}

CS598PacketLossCounter::~CS598PacketLossCounter()
{
    NS_LOG_FUNCTION(this);
    delete[] m_receiveBitMap;
}

uint16_t
CS598PacketLossCounter::GetBitMapSize() const
{
    NS_LOG_FUNCTION(this);
    return m_bitMapSize * 8;
}

void
CS598PacketLossCounter::SetBitMapSize(uint16_t winSize)
{
    NS_LOG_FUNCTION(this << winSize);

    NS_ASSERT_MSG(winSize % 8 == 0, "The packet window size should be a multiple of 8");
    m_bitMapSize = winSize / 8;
    if (m_receiveBitMap != nullptr)
    {
        delete[] m_receiveBitMap;
    }
    m_receiveBitMap = new uint8_t[m_bitMapSize]();
    memset(m_receiveBitMap, 0xFF, m_bitMapSize);
}

uint32_t
CS598PacketLossCounter::GetLost() const
{
    NS_LOG_FUNCTION(this);
    return ceil(m_lost / 64.0);
    // return m_lost;
}

bool
CS598PacketLossCounter::GetBit(uint32_t seqNum)
{
    NS_LOG_FUNCTION(this << seqNum);
    return ((m_receiveBitMap[(seqNum % (m_bitMapSize * 8)) / 8] >> (7 - (seqNum % 8))) & 0x01);
}

void
CS598PacketLossCounter::SetBit(uint32_t seqNum, bool val)
{
    NS_LOG_FUNCTION(this << seqNum << val);
    if (val)
    {
        m_receiveBitMap[(seqNum % (m_bitMapSize * 8)) / 8] |= 0x80 >> (seqNum % 8);
    }
    else
    {
        m_receiveBitMap[(seqNum % (m_bitMapSize * 8)) / 8] &= ~(0x80 >> (seqNum % 8));
    }
}

/*
 * This algo works as follows:
 * When a packet is received:
 * 1) From the last received packet to the current one:
 *    1.1) check the corresponding bit in the bitMAP.
 *    This bit indicates if the packet with (SeqNum-bitMapSizeInBit) is
 *    received (1) or not (0)
 *    1.2) Mark the packet as lost (0) in the bitMap
 * 2) Mark the current packet as received (1) in the bitMap
 * 3) Update the value of the last received packet
 */

void
CS598PacketLossCounter::NotifyReceived(uint32_t seqNum)
{
    NS_LOG_FUNCTION(this << seqNum);
    std::cout << seqNum << std::endl;
    for (uint32_t i = m_lastMaxSeqNum + 1; i <= seqNum; i++)
    {
        if (!GetBit(i))
        {
            NS_LOG_INFO("Packet lost: " << i - (m_bitMapSize * 8));
            m_lost += 64;
        } else {
            m_lost -= (m_lost > 0)*ceil(m_lost / 64.0);
        }
        SetBit(i, false);
    }
    SetBit(seqNum, true);
    if (seqNum > m_lastMaxSeqNum)
    {
        m_lastMaxSeqNum = seqNum;
    }
}

} // namespace ns3
