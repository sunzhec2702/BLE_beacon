#include "simpleBLENFCUtility.h"
#include "simpleble.h"

//Check ACK
//Build Frame
//Destruct Frame

const uint8 ack_frame[] = {0x00, 0x00, 0xff, 0x00, 0xff, 0x00};
const uint8 nack_frame[] = {0x00, 0x00, 0xff, 0xff, 0x00, 0x00};
static const uint8 error_frame[] = {0x00, 0x00, 0xff, 0x01, 0xff, 0x7f, 0x81, 0x00};

bool check_ack(uint8 *content, uint16 content_num)
{
    if (sizeof(ack_frame) > content_num)
    {
        return false;
    }
    if (memcpy(content, ack_frame, sizeof(ack_frame)) != 0)
    {
        return false;
    }
    return true;
}

void build_send_frame(uint8 *pbtFrame, size_t *pszFrame, const uint8 *pbtData, const size_t szData)
{
   if (szData <= PN53x_NORMAL_FRAME__DATA_MAX_LEN)
    {
        // LEN - Packet length = data length (len) + checksum (1) + end of stream marker (1)
        pbtFrame[3] = szData + 1;
        // LCS - Packet length checksum
        pbtFrame[4] = 256 - (szData + 1);
        // TFI
        pbtFrame[5] = 0xD4;
        // DATA - Copy the PN53X command into the packet buffer
        memcpy(pbtFrame + 6, pbtData, szData);

        // DCS - Calculate data payload checksum
        uint8 btDCS = (256 - 0xD4);
        for (size_t szPos = 0; szPos < szData; szPos++)
        {
            btDCS -= pbtData[szPos];
        }
        pbtFrame[6 + szData] = btDCS;

        // 0x00 - End of stream marker
        pbtFrame[szData + 7] = 0x00;

        (*pszFrame) = szData + PN53x_NORMAL_FRAME__OVERHEAD;
    }
    else if (szData <= PN53x_EXTENDED_FRAME__DATA_MAX_LEN)
    {
        // Extended frame marker
        pbtFrame[3] = 0xff;
        pbtFrame[4] = 0xff;
        // LENm
        pbtFrame[5] = (szData + 1) >> 8;
        // LENl
        pbtFrame[6] = (szData + 1) & 0xff;
        // LCS
        pbtFrame[7] = 256 - ((pbtFrame[5] + pbtFrame[6]) & 0xff);
        // TFI
        pbtFrame[8] = 0xD4;
        // DATA - Copy the PN53X command into the packet buffer
        memcpy(pbtFrame + 9, pbtData, szData);

        // DCS - Calculate data payload checksum
        uint8 btDCS = (256 - 0xD4);
        for (size_t szPos = 0; szPos < szData; szPos++)
        {
            btDCS -= pbtData[szPos];
        }
        pbtFrame[9 + szData] = btDCS;

        // 0x00 - End of stream marker
        pbtFrame[szData + 10] = 0x00;

        (*pszFrame) = szData + PN53x_EXTENDED_FRAME__OVERHEAD;
    }
    else
    {
        return NFC_ECHIP;
    }
    return NFC_SUCCESS;
}