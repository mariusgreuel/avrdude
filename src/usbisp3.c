#include "ac_cfg.h"

#include <windows.h>
#include <Setupapi.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>

#include "avrdude.h"
#include "libavrdude.h"

#include "usbisp3.h"

#include "winusb.h"

const char usbisp3_desc[] = "USB ISP 3.0 by Ngo Hung Cuong";

// winusb support
static WINUSB_INTERFACE_HANDLE hWinUsb;
static uint8_t buff[64 * 1024];
static OVERLAPPED ov;
static HANDLE hUsb;
static uint32_t connected = 0;

static uint32_t KT_WinUSB_OpenVidPid(uint32_t vid, uint32_t pid);
static void KT_WinUSB_Close(void);
static uint32_t KT_WinUSB_Read(uint8_t ep, uint8_t* p_data, uint32_t length);
static uint32_t KT_WinUSB_Write(uint8_t ep, uint8_t* p_data, uint32_t length);

// usbisp3
static char szFirmwareVer[] = "USB ISP 3.0 version 230726";
static char szSerialVer[] = "ICVN.VN-230722";

static uint32_t usbisp3_spi_exch(const PROGRAMMER* pgm, const uint8_t* pu8Send, uint8_t* pu8Recv, int u8Length)
{
    uint8_t u8Buff[64];

    u8Buff[0] = 0x24;
    u8Buff[1] = u8Length;
    memmove(&u8Buff[4], pu8Send, u8Length);
    if (!KT_WinUSB_Write(0x01, u8Buff, 64))
    {
        return -1;
    }
    if (!KT_WinUSB_Read(0x81, u8Buff, 64))
    {
        return -1;
    }
    memmove(pu8Recv, u8Buff, u8Length);

    return 0;
}

static uint32_t usbisp3_avr_setup(const PROGRAMMER* pgm, uint8_t u8Speed, uint8_t u8Type, uint8_t u8Time)
{
    uint8_t u8Buff[64];

    u8Buff[0] = 0x10;
    u8Buff[1] = u8Type;
    u8Buff[2] = u8Speed;
    u8Buff[3] = u8Time;

    return KT_WinUSB_Write(0x01, u8Buff, 64);
}

static uint32_t usbisp3_avr_exit(const PROGRAMMER* pgm, uint8_t u8RstType, uint8_t u8RstVal)
{
    uint8_t u8Buff[64];

    u8Buff[0] = 0x11;
    u8Buff[1] = u8RstType;
    u8Buff[2] = u8RstVal;

    return KT_WinUSB_Write(0x01, u8Buff, 64);
}

static int usbisp3_initialize(const PROGRAMMER* pgm, const AVRPART* p)
{
    uint8_t i;

    for (i = 0; i < 8; ++i) {
        if (!usbisp3_avr_setup(pgm, i, 1, 0))
        {
            usbisp3_avr_exit(pgm, 0, 0);
            return -1;
        }

        if (pgm->program_enable(pgm, p) == 0x00)
        {
            return 0;
        }
    }
    
    return -1;
}

static void usbisp3_display(const PROGRAMMER* pgm, const char* p)
{

    return;
}

static void usbisp3_enable(PROGRAMMER* pgm, const AVRPART* p)
{

    return;
}

static void usbisp3_disable(const PROGRAMMER* pgm)
{
    
    usbisp3_avr_exit(pgm, 0, 0);
}

static void usbisp3_powerdown(const PROGRAMMER* pgm)
{
    
    pgm->disable(pgm);
}

static int  usbisp3_program_enable(const PROGRAMMER* pgm, const AVRPART* p)
{
    uint8_t cmd[4];
    uint8_t res[4];

    if (p->op[AVR_OP_PGM_ENABLE] == NULL)
    {
        pmsg_error("program enable instruction not defined for part %s\n", p->desc);
        return -1;
    }

    memset(cmd, 0, sizeof(cmd));
    avr_set_bits(p->op[AVR_OP_PGM_ENABLE], cmd);

    pgm->cmd(pgm, cmd, res);

    {
        int i;
        msg_debug("program_enable(): sending command. Resp = ");

        for (i = 0; i < 4; i++)
        {
            msg_debug("%02x ", res[i]);
        }
        msg_debug("\n");
    }

    // check for sync character
    if (res[2] != cmd[1])
        return -2;

    return 0;
}

static int  usbisp3_chip_erase(const PROGRAMMER* pgm, const AVRPART* p)
{

    unsigned char cmd[4];
    unsigned char res[4];

    if (p->op[AVR_OP_CHIP_ERASE] == NULL)
    {
        pmsg_error("chip erase instruction not defined for part %s\n", p->desc);
        return -1;
    }

    pgm->pgm_led(pgm, ON);

    memset(cmd, 0, sizeof(cmd));

    avr_set_bits(p->op[AVR_OP_CHIP_ERASE], cmd);
    pgm->cmd(pgm, cmd, res);
    usleep(p->chip_erase_delay);

    pgm->initialize(pgm, p);

    pgm->pgm_led(pgm, OFF);

    return 0;
}

static int usbisp3_open(PROGRAMMER* pgm, const char* port)
{
    uint8_t u8Buff[64];

    if (KT_WinUSB_OpenVidPid(0x03eb, 0xc8b4))
    {
        uint8_t ser[100];
        char szSer[100];
        uint32_t len;

        if (WinUsb_GetDescriptor(hWinUsb, USB_STRING_DESCRIPTOR_TYPE, 3, 3, ser, 100, (PULONG)&len))
        {
            if (len > 64)
            {
                KT_WinUSB_Close();
                return -1;
            }
            if (len != ser[0])
            {
                KT_WinUSB_Close();
                return -1;
            }
            uint32_t i;
            for (i = 0; i < (len / 2 - 1); ++i)
            {
                szSer[i] = ser[2 + i * 2];
            }
            szSer[i] = 0;
            if (strcmpi(szSer, szSerialVer))
            {
                pmsg_error("Wrong firmware version\n");
                KT_WinUSB_Close();
                return -1;
            }
            u8Buff[0] = 0x00;
            if (!KT_WinUSB_Write(0x01, u8Buff, 64))
            {
                pmsg_error("USB IO: FAILED\n");
                return -1;
            }
            if (!KT_WinUSB_Read(0x81, u8Buff, 64)) {
                pmsg_error("USB IO: FAILED\n");
                return -1;
            }
            if (strcmpi((char *)u8Buff, szFirmwareVer))
            {
                pmsg_error("Wrong firmware version\n");
                KT_WinUSB_Close();
                return -1;
            }

            return 0;
        }
        else
        {
            KT_WinUSB_Close();
            return -1;
        }

        return -1;
    }

    return -1;
}

static void usbisp3_close(PROGRAMMER* pgm)
{

    KT_WinUSB_Close();
}

static int usbisp3_cmd(const PROGRAMMER* pgm, const unsigned char* cmd,
    unsigned char* res)
{

    return pgm->spi(pgm, cmd, res, 4);
}

static uint32_t usbisp3_spi_exch_n(const PROGRAMMER* pgm, uint32_t u32Length, uint8_t* pu8Send, uint8_t* pu8Recv)
{
    uint8_t u8Buff[64];

    u8Buff[0] = 0x03;
    u8Buff[1] = (u32Length);
    u8Buff[2] = (u32Length >> 8);
    u8Buff[3] = (0);
    u8Buff[4] = (0);

    if (!KT_WinUSB_Write(0x01, u8Buff, 64)) {
        return 0;
    }

    if (!KT_WinUSB_Write(0x01, pu8Send, u32Length)) {
        return 0;
    }

    u8Buff[0] = 0x25;
    u8Buff[1] = (u32Length);
    u8Buff[2] = (u32Length >> 8);
    u8Buff[3] = (0);
    u8Buff[4] = (0);

    if (!KT_WinUSB_Write(0x01, u8Buff, 64)) {
        return 0;
    }

    u8Buff[0] = 0x04;
    u8Buff[1] = (u32Length);
    u8Buff[2] = (u32Length >> 8);
    u8Buff[3] = (u32Length >> 16);
    u8Buff[4] = (u32Length >> 24);

    if (!KT_WinUSB_Write(0x01, u8Buff, 64)) {
        return 0;
    }

    return KT_WinUSB_Read(0x81, pu8Recv, u32Length);
}

static uint32_t usbisp3_avr_read_flash(const PROGRAMMER* pgm, uint16_t u16Address, uint16_t u16Length, uint8_t* pu8Data)
{
    uint8_t u8SendBuff[8 * 1024];
    u16Length >>= 1;
    u16Address >>= 1;
    uint32_t i;
    uint8_t* p;
    p = u8SendBuff;

    for (i = 0; i < u16Length; ++i) {
        *p = 0x20;
        ++p;
        *p = (u16Address >> 8);
        ++p;
        *p = (u16Address);
        ++p;
        *p = 0x00;
        ++p;

        *p = 0x28;
        ++p;
        *p = (u16Address >> 8);
        ++p;
        *p = (u16Address);
        ++p;
        *p = 0x00;
        ++p;

        ++u16Address;
    }

    if (usbisp3_spi_exch_n(pgm, u16Length * 8, u8SendBuff, u8SendBuff)) {
        p = pu8Data;
        for (i = 0; i < u16Length; ++i) {
            *p = u8SendBuff[i * 8 + 3];
            ++p;
            *p = u8SendBuff[i * 8 + 7];
            ++p;
        }
        return 1;
    }
    else {
        return 0;
    }
}

static uint32_t usbisp3_avr_read_eeprom(const PROGRAMMER* pgm, uint16_t u16Address, uint16_t u16Length, uint8_t* pu8Data)
{
    uint8_t u8SendBuff[8 * 1024];

    uint32_t i;
    uint8_t* p;
    p = u8SendBuff;

    for (i = 0; i < u16Length; ++i) {
        *p = 0xA0;
        ++p;
        *p = (u16Address >> 8);
        ++p;
        *p = (u16Address);
        ++p;
        *p = 0x00;
        ++p;

        ++u16Address;
    }

    if (usbisp3_spi_exch_n(pgm, u16Length * 4, u8SendBuff, u8SendBuff)) {
        p = pu8Data;
        for (i = 0; i < u16Length; ++i) {
            *p = u8SendBuff[i * 4 + 3];
            ++p;
        }
        return 1;
    }
    else {
        return 0;
    }
}

static uint32_t usbisp3_avr_write_flash(const PROGRAMMER* pgm, uint32_t u16Address, uint16_t u16Length, uint8_t* pu8Data)
{
    uint8_t u8SendBuff[1024];
    uint32_t i;
    uint8_t* p;
    p = u8SendBuff;
    uint8_t* pS;
    pS = pu8Data;
    uint16_t u16TmpAddress;
    uint16_t u16Pos = 0;
    uint8_t u8Poll;

    if (u16Length < 16) {
        u16TmpAddress = 0;
        p = u8SendBuff;
        pS = pu8Data;
        for (i = 0; i < (u16Length / 2); ++i) {
            *p = 0x40;
            ++p;
            *p = (u16TmpAddress >> 8);
            ++p;
            *p = (u16TmpAddress);
            ++p;
            *p = *pS;
            ++pS;
            ++p;

            *p = 0x48;
            ++p;
            *p = (u16TmpAddress >> 8);
            ++p;
            *p = (u16TmpAddress);
            ++p;
            *p = *pS;
            ++pS;
            ++p;

            ++u16TmpAddress;
        }
        if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, u16Length * 4)) {
            return 0;
        }
        
        u8SendBuff[0] = 0x4c;
        u8SendBuff[1] = (u16Address >> 9);
        u8SendBuff[2] = (u16Address >> 1);
        u8SendBuff[3] = 0x00;
        if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
            return 0;
        }
        
        for (i = 0; i < u16Length; ++i) {
            if (pu8Data[i] != 0xff) {
                u16Pos = i;
                break;
            }
        }
        if (u16Pos != u16Length) {
            if (u16Pos % 2) {
                u16TmpAddress = u16Address + u16Pos;
                u16TmpAddress >>= 1;
                u8Poll = 0;
                for (i = 0; i < 1000; ++i) {
                    u8SendBuff[0] = 0x28;
                    u8SendBuff[1] = (u16TmpAddress >> 8);
                    u8SendBuff[2] = (u16TmpAddress);
                    u8SendBuff[3] = 0x00;
                    if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
                        return 0;
                    }
                    if (u8SendBuff[3] == pu8Data[u16Pos]) {
                        u8Poll = 1;
                        break;
                    }
                }
                if (u8Poll) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                u16TmpAddress = u16Address + u16Pos;
                u16TmpAddress >>= 1;
                u8Poll = 0;
                for (i = 0; i < 1000; ++i) {
                    u8SendBuff[0] = 0x20;
                    u8SendBuff[1] = (u16TmpAddress >> 8);
                    u8SendBuff[2] = (u16TmpAddress);
                    u8SendBuff[3] = 0x00;
                    if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
                        return 0;
                    }
                    if (u8SendBuff[3] == pu8Data[u16Pos]) {
                        u8Poll = 1;
                        break;
                    }
                }
                if (u8Poll) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
        }
        else {
            Sleep(10);
            return 1;
        }
    }
    else {
        u16TmpAddress = 0;
        p = u8SendBuff;
        pS = pu8Data;
        for (i = 0; i < (u16Length / 2); ++i) {
            *p = 0x40;
            ++p;
            *p = (u16TmpAddress >> 8);
            ++p;
            *p = (u16TmpAddress);
            ++p;
            *p = *pS;
            ++pS;
            ++p;

            *p = 0x48;
            ++p;
            *p = (u16TmpAddress >> 8);
            ++p;
            *p = (u16TmpAddress);
            ++p;
            *p = *pS;
            ++pS;
            ++p;

            ++u16TmpAddress;
        }
        if (!usbisp3_spi_exch_n(pgm, u16Length * 4, u8SendBuff, u8SendBuff)) {
            return 0;
        }

        u8SendBuff[0] = 0x4c;
        u8SendBuff[1] = (u16Address >> 9);
        u8SendBuff[2] = (u16Address >> 1);
        u8SendBuff[3] = 0x00;
        if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
            return 0;
        }

        for (i = 0; i < u16Length; ++i) {
            if (pu8Data[i] != 0xff) {
                u16Pos = i;
                break;
            }
        }
        if (u16Pos != u16Length) {

            if (u16Pos % 2) {

                u16TmpAddress = u16Address + u16Pos;
                u16TmpAddress >>= 1;
                u8Poll = 0;
                for (i = 0; i < 1000; ++i) {
                    u8SendBuff[0] = 0x28;
                    u8SendBuff[1] = (u16TmpAddress >> 8);
                    u8SendBuff[2] = (u16TmpAddress);
                    u8SendBuff[3] = 0x00;
                    if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
                        return 0;
                    }
                    if (u8SendBuff[3] == pu8Data[u16Pos]) {
                        u8Poll = 1;
                        break;
                    }
                }
                if (u8Poll) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
            else {
                u16TmpAddress = u16Address + u16Pos;
                u16TmpAddress >>= 1;
                u8Poll = 0;
                for (i = 0; i < 1000; ++i) {
                    u8SendBuff[0] = 0x20;
                    u8SendBuff[1] = (u16TmpAddress >> 8);
                    u8SendBuff[2] = (u16TmpAddress);
                    u8SendBuff[3] = 0x00;
                    if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
                        return 0;
                    }
                    if (u8SendBuff[3] == pu8Data[u16Pos]) {
                        u8Poll = 1;
                        break;
                    }
                }
                if (u8Poll) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
        }
        else {
            Sleep(10);
            return 1;
        }
    }

    return 0;
}

static uint32_t usbisp3_avr_write_eeprom(const PROGRAMMER* pgm, uint32_t u16Address, uint16_t u16Length, uint8_t* pu8Data)
{
    uint8_t u8SendBuff[1024];
    uint32_t i;
    uint8_t* p;
    p = u8SendBuff;
    uint8_t* pS;
    pS = pu8Data;
    uint16_t u16TmpAddress;
    uint16_t u16Pos = 0;
    uint8_t u8Poll;

    if (u16Length != 0x01) {
        
        u16TmpAddress = 0;
        p = u8SendBuff;
        pS = pu8Data;
        for (i = 0; i < u16Length; ++i) {
            *p = 0xC1;
            ++p;
            *p = (i >> 8);
            ++p;
            *p = (i);
            ++p;
            *p = *pS;
            ++pS;
            ++p;
        }
        if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, u16Length * 4)) {
            return 0;
        }
        for (i = 0; i < u16Length; ++i) {
            if (pu8Data[i] != 0xff) {
                u16Pos = i;
                break;
            }
        }
        if (u16Pos != u16Length) {
            u8Poll = 0;
            for (i = 0; i < 1000; ++i) {
                u8SendBuff[0] = 0xA0;
                u8SendBuff[1] = ((u16Address + u16Pos) >> 8);
                u8SendBuff[2] = (u16Address + u16Pos);
                u8SendBuff[3] = 0x00;
                if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
                    return 0;
                }
                if (u8SendBuff[3] == pu8Data[u16Pos]) {
                    u8Poll = 1;
                    break;
                }
            }
            if (u8Poll) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            Sleep(10);
            return 1;
        }
    }
    else {
        u8SendBuff[0] = 0xC0;
        u8SendBuff[1] = (u16Address >> 8);
        u8SendBuff[2] = (u16Address);
        u8SendBuff[3] = pu8Data[0];
        if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
            return 0;
        }
        u8Poll = 0;
        for (i = 0; i < 1000; ++i) {
            u8SendBuff[0] = 0xA0;
            u8SendBuff[1] = (u16Address >> 8);
            u8SendBuff[2] = (u16Address);
            u8SendBuff[3] = 0x00;
            if (!usbisp3_spi_exch(pgm, u8SendBuff, u8SendBuff, 4)) {
                return 0;
            }
            if (u8SendBuff[3] == pu8Data[0]) {
                u8Poll = 1;
                break;
            }
        }
        if (u8Poll) {
            return 1;
        }
        else {
            return 0;
        }
    }

    return 0;
}

static int  usbisp3_paged_write(const PROGRAMMER* pgm, const AVRPART* p, const AVRMEM* mem,
    unsigned int page_size, unsigned int addr, unsigned int n_bytes)
{
    if ((!mem->paged || page_size <= 1) || (strcmp(mem->desc, "flash") != 0 && strcmp(mem->desc, "eeprom") != 0))
    {
        return -1;
    }

    if (strcmp(mem->desc, "flash") == 0)
    {
        OPCODE* readop = 0, * lext = mem->op[AVR_OP_LOAD_EXT_ADDR];
        uint8_t data = 0, cmd[64], res[64];

        if (lext) {
            memset(cmd, 0, sizeof(cmd));
            avr_set_bits(lext, cmd);
            avr_set_addr(lext, cmd, addr / 2);
            pgm->cmd(pgm, cmd, res);
        }

        if (usbisp3_avr_write_flash(pgm, addr, n_bytes, &mem->buf[addr]))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    if (usbisp3_avr_write_eeprom(pgm, addr, n_bytes, &mem->buf[addr]))
    {
        return 0;
    }
    else
    {
        return -1;
    }

    return -1;
}

static int usbisp3_paged_load(const PROGRAMMER* pgm, const AVRPART* p, const AVRMEM* mem,
    unsigned int page_size, unsigned int addr, unsigned int n_bytes)
{

    // only supporting flash & eeprom page reads
    if ((!mem->paged || page_size <= 1) || (strcmp(mem->desc, "flash") != 0 && strcmp(mem->desc, "eeprom") != 0))
    {
        return -1;
    }

    if (strcmp(mem->desc, "flash") == 0)
    {
        OPCODE* readop = 0, * lext = mem->op[AVR_OP_LOAD_EXT_ADDR];
        uint8_t data = 0, cmd[64], res[64];

        if (lext) {
            memset(cmd, 0, sizeof(cmd));
            avr_set_bits(lext, cmd);
            avr_set_addr(lext, cmd, addr / 2);
            pgm->cmd(pgm, cmd, res);
        }

        if (usbisp3_avr_read_flash(pgm, addr, n_bytes, &mem->buf[addr]))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }

    if (usbisp3_avr_read_eeprom(pgm, addr, n_bytes, &mem->buf[addr]))
    {
        return 0;
    }
    else
    {
        return -1;
    }

    return -1;
}

static int  usbisp3_parseextparams(const PROGRAMMER* pgm, const LISTID extparms)
{

    return 0;
}

void usbisp3_initpgm(PROGRAMMER* pgm)
{
    pgm->initialize = usbisp3_initialize;
    pgm->display = usbisp3_display;
    pgm->enable = usbisp3_enable;
    pgm->disable = usbisp3_disable;
    pgm->powerdown = usbisp3_powerdown;
    pgm->program_enable = usbisp3_program_enable;
    pgm->chip_erase = usbisp3_chip_erase;
    pgm->open = usbisp3_open;
    pgm->close = usbisp3_close;
    pgm->spi = usbisp3_spi_exch;

    pgm->read_byte = avr_read_byte_default;
    pgm->write_byte = avr_write_byte_default;

    pgm->cmd = usbisp3_cmd;
    pgm->paged_write = usbisp3_paged_write;
    pgm->paged_load = usbisp3_paged_load;

    pgm->parseextparams = usbisp3_parseextparams;

    strncpy(pgm->type, "usbisp3", sizeof(pgm->type));
}

uint32_t KT_WinUSB_OpenVidPid(uint32_t vid, uint32_t pid)
{
    connected = 0;
    HANDLE hDevInfoSet;

    GUID hidGuid = { 0xdee824ef, 0x729b, 0x4a0e, 0x9c, 0x14, 0xb7, 0x11, 0x7d, 0x33, 0xa8,  0x17 };

    hDevInfoSet = SetupDiGetClassDevsA(&hidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
    if (!hDevInfoSet) {
        return 0;
    }
    DWORD dwRes;
    DWORD dwStatus;
    DWORD dwInterfaceIndex = 0;
    SP_DEVICE_INTERFACE_DATA devInterfaceData;
    SP_DEVICE_INTERFACE_DETAIL_DATA detail;
    devInterfaceData.cbSize = sizeof(devInterfaceData);
    char* pBuff;
    SP_DEVINFO_DATA devInfoData;
    DWORD dwRegType, dwRegSize;
    DWORD dwFound = 0;
    while (1) {
        dwRes = SetupDiEnumDeviceInterfaces(hDevInfoSet, NULL, &hidGuid, dwInterfaceIndex, &devInterfaceData);
        if (dwRes) {
            dwStatus = GetLastError();
        }
        else {
            return 0;
        }
        
        if (dwStatus == ERROR_NO_MORE_ITEMS) {
            return 0;
        }
        
        devInfoData.cbSize = sizeof(devInfoData);
        SetupDiEnumDeviceInfo(hDevInfoSet, dwInterfaceIndex, &devInfoData);

        SetupDiGetDeviceRegistryPropertyA(hDevInfoSet, &devInfoData, SPDRP_HARDWAREID, &dwRegType, NULL, 0, &dwRegSize);

        pBuff = (char*)malloc(dwRegSize);
        if (!pBuff) {
            return 0;
        }
        
        SetupDiGetDeviceRegistryPropertyA(hDevInfoSet, &devInfoData, SPDRP_HARDWAREID, &dwRegType, (unsigned char*)pBuff, dwRegSize, NULL);
        
        char szVid[100];
        char szPid[100];
        char* p;
        wsprintfA(szPid, "pid_%04x", pid);
        wsprintfA(szVid, "vid_%04x&", vid);
        lstrcatA(szVid, szPid);
        DWORD dwLen, dwJ;
        dwLen = lstrlenA(pBuff);
        for (dwJ = 0; dwJ < dwLen; ++dwJ) {
            if (pBuff[dwJ] >= 'A' && pBuff[dwJ] <= 'Z')
                pBuff[dwJ] += 0x20;
        }
        p = strstr(pBuff, szVid);
        if (p) {
            dwFound = 1;
            break;
        }
        ++dwInterfaceIndex;
    }

    if (dwFound) {
    }
    else {
        return 0;
    }

    memset(&detail, 0, sizeof(detail));
    detail.cbSize = sizeof(detail);
    DWORD dwSize = 0;
    SetupDiGetDeviceInterfaceDetail(hDevInfoSet, &devInterfaceData, NULL, 0, &dwSize, NULL);
    PSP_DEVICE_INTERFACE_DETAIL_DATA ktNew;
    ktNew = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(dwSize);
    if (!ktNew) {
        return 0;
    }
    ktNew->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
    SetupDiGetDeviceInterfaceDetail(hDevInfoSet, &devInterfaceData, ktNew, dwSize, NULL, NULL);

    hUsb = CreateFile(ktNew->DevicePath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
    if (!hUsb) {
        return 0;
    }
    if (!WinUsb_Initialize(hUsb, &hWinUsb)) {
        return 0;
    }
    
    connected = 1;
    return 1;
}

void KT_WinUSB_Close(void)
{

    if (connected)
    {
        connected = 0;
        CloseHandle(hUsb);
        WinUsb_Free(hWinUsb);
    }
}

uint32_t KT_WinUSB_Read(uint8_t ep, uint8_t* p_data, uint32_t length)
{
    DWORD len;

    ov.hEvent = CreateEventA(NULL, TRUE, FALSE, "KT_WinUsb");
    if (ov.hEvent == NULL)
    {
        return 0;
    }
    DWORD dwTimeOut = 5000;

    WinUsb_SetPipePolicy(hWinUsb, 0x81, PIPE_TRANSFER_TIMEOUT, sizeof(ULONG), &dwTimeOut);

    WinUsb_ReadPipe(hWinUsb, ep | 0x80, buff, length, &len, &ov);
    DWORD dwTrans;

    WinUsb_GetOverlappedResult(hWinUsb, &ov, &dwTrans, TRUE);
    if (dwTrans != length) {
        CloseHandle(ov.hEvent);
        return 0;
    }

    memmove(p_data, buff, length);
    CloseHandle(ov.hEvent);
    return 1;
}

uint32_t KT_WinUSB_Write(uint8_t ep, uint8_t* p_data, uint32_t length)
{
    DWORD len;

    memmove(buff, p_data, length);

    return WinUsb_WritePipe(hWinUsb, ep, buff, length, &len, NULL);
}
