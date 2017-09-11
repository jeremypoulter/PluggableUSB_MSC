/* 
** Copyright (c) 2015, Gary Grewal
** Permission to use, copy, modify, and/or distribute this software for
** any purpose with or without fee is hereby granted, provided that the
** above copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
** SOFTWARE.
*/

#include "usbmsc.h"
#include "debug.h"

#define MSC_INTERFACE       pluggedInterface  // MSC Interface
#define MSC_FIRST_ENDPOINT  pluggedEndpoint

// Endpoint number of the Mass Storage host-to-device data OUT endpoint.
#define MSC_ENDPOINT_OUT	pluggedEndpoint
// Endpoint number of the Mass Storage device-to-host data IN endpoint.
#define MSC_ENDPOINT_IN	((uint8_t)(pluggedEndpoint+1))

#define MSC_RX MSC_ENDPOINT_OUT
#define MSC_TX MSC_ENDPOINT_IN

#define OUT_BANK                           0
#define IN_BANK                            1

#define COMPILER_WORD_ALIGNED         __attribute__((__aligned__(4)))

// DEVICE DESCRIPTOR
//const DeviceDescriptor USB_DeviceDescriptorB = D_DEVICE(0xEF, 0x02, 0x01, 64, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
//const DeviceDescriptor USB_DeviceDescriptor = D_DEVICE(0x00, 0x00, 0x00, 64, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
//const DeviceDescriptor USB_DeviceDescriptor = D_DEVICE(0x00, 0x00, 0x00, 0x40, 0x03EB, 0x2403, 0x100, 0x00, 0x20, 0x03, 0x1);
const DeviceDescriptor USB_DeviceDescriptor = D_DEVICE(0x00, 0x00, 0x00, MSC_MAX_EP_SIZE, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
const DeviceDescriptor USB_DeviceDescriptorB = D_DEVICE(0xEF, 0x02, 0x01, MSC_MAX_EP_SIZE, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);

// From ASF/compiler.h
#define swap32(u32) ((uint32_t)__builtin_bswap32((uint32_t)(u32)))

#define  le32_to_cpu(x) (x)
#define  cpu_to_le32(x) (x)
#define  LE32_TO_CPU(x) (x)
#define  CPU_TO_LE32(x) (x)

#define  be32_to_cpu(x) swap32(x)
#define  cpu_to_be32(x) swap32(x)
#define  BE32_TO_CPU(x) swap32(x)
#define  CPU_TO_BE32(x) swap32(x)

MSC_ MassStorage;

COMPILER_WORD_ALIGNED
uint8_t getmaxlun[] = {
  0x00, // 0 (since one LUN (SPI Flash) is connected )
};

int MSC_::getInterface(uint8_t* interfaceNum)
{
  DBUG("getInterface: ");
  DBUGLN(*interfaceNum);

  interfaceNum[0] += 1;	// uses 1 interfaces
  MSCDescriptor _mscInterface =
  {
    D_INTERFACE(MSC_INTERFACE, 2, MSC_CLASS, MSC_SUBCLASS_SCSI, MSC_PROTOCOL_BULK_ONLY),
    D_MSC_EP(MSC_BULK_IN_EP | 0x80, MSC_BULK_IN_EP_SIZE),
    D_MSC_EP(MSC_BULK_OUT_EP, MSC_BULK_OUT_EP_SIZE)
  };
  return USB_SendControl(0, &_mscInterface, sizeof(_mscInterface));
}

bool MSC_::setup(USBSetup& setup)
{
  DBUG("setup: ");
  DBUG(setup.bmRequestType, HEX);
  DBUG(" ");
  DBUG(setup.wValueH, HEX);
  DBUG(" ");
  DBUG(setup.wIndex, HEX);
  DBUG(" ");
  DBUGLN(setup.wLength, HEX);

  switch(setup.bmRequestType) 
  {
    // MSC class requests
    // Get MaxLUN supported
    case GET_MAX_LUN:
      DBUGLN("GET_MAX_LUN");
      // wIndex should be interface number
      if (setup.wValueH == 0 /* && setup.wIndex == 0 */ && setup.wLength == 1) {
        USB_Send(CTRL_EP, getmaxlun, sizeof(getmaxlun));
      } else {
        //  Stall the request
        USB_Stall(IN_BANK);
      }
      return true;

    case MASS_STORAGE_RESET:
      DBUGLN("MASS_STORAGE_RESET");
      // wIndex should be interface number
      //dir = setup.wIndex & 0x80;
      if (setup.wValueH == 0 && setup.wIndex == 0 && setup.wLength == 0) {
        //epSetStatusReg(MSC_BULK_IN_EP, USB_DEVICE_EPSTATUSSET_DTGLIN);
        //epSetStatusReg(MSC_BULK_OUT_EP, USB_DEVICE_EPSTATUSSET_DTGLOUT);
        USB_SendZLP(CTRL_EP);
      } else {
        //  Stall the request
        USB_Stall(IN_BANK);
      }
      return true;
  }

  return false;
}

int MSC_::getDescriptor(USBSetup& setup)
{
  DBUG("getDescriptor ");
  DBUG(setup.bmRequestType, HEX);
  DBUG(" ");
  DBUGLN(setup.wValueH, HEX);

  // Check if this is a HID Class Descriptor request
  if (setup.bmRequestType != REQUEST_DEVICETOHOST_STANDARD_INTERFACE) { return 0; }
  if (setup.wValueH != 0x100) { return 0; }

  uint8_t desc_length = 0;
  const uint8_t *desc_addr = 0;

  desc_addr = (const uint8_t*)&(8 == setup.wLength ? USB_DeviceDescriptorB : USB_DeviceDescriptor);
  desc_length = *desc_addr;
  if (desc_length > setup.wLength) {
    desc_length = setup.wLength;
  }

  return USB_SendControl(0, desc_addr, desc_length);
}

uint8_t MSC_::getShortName(char* name)
{
  memcpy(name, "MSC", 3);
  return 3;
}

void MSC_::poll()
{
  int ep = MSC_BULK_OUT_EP;
  struct usb_msc_cbw udi_msc_cbw;
  int32_t recv = (int32_t)USB_Recv(ep, &udi_msc_cbw, sizeof(udi_msc_cbw));
  if(recv > 0) {
    DBUG("poll: got ");
    DBUGLN(recv);

    // Check CBW integrity:
    // transfer status/CBW length/CBW signature
    if ((sizeof(udi_msc_cbw) != recv)
    || (udi_msc_cbw.dCBWSignature !=
        CPU_TO_BE32(USB_CBW_SIGNATURE))) 
    {
      // (5.2.1) Devices receiving a CBW with an invalid signature should stall
      // further traffic on the Bulk In pipe, and either stall further traffic
      // or accept and discard further traffic on the Bulk Out pipe, until
      // reset recovery.
/*
      udi_msc_b_cbw_invalid = true;
      udi_msc_cbw_invalid();
      udi_msc_csw_invalid();
*/
      return;
    }

    processMscCwb(&udi_msc_cbw);
  }
}


void MSC_::processMscCwb(struct usb_msc_cbw *udi_msc_cbw)
{
  DBUGVAR(udi_msc_cbw->CDB[0], HEX);

}

MSC_::MSC_(void) : PluggableUSBModule(TOTAL_EP - 1, 1, epType)
{
  epType[0] = EP_TYPE_BULK_IN_MSC;	// MSC_ENDPOINT_IN
  epType[1] = EP_TYPE_BULK_OUT_MSC;	// MSC_ENDPOINT_OUT
  PluggableUSB().plug(this);
}
