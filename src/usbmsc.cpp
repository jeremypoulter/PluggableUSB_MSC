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

/** Endpoint number of the Mass Storage device-to-host data IN endpoint. */
#define MASS_STORAGE_IN_EPNUM          3	

/** Endpoint number of the Mass Storage host-to-device data OUT endpoint. */
#define MASS_STORAGE_OUT_EPNUM         4	

#define MSC_INTERFACE 	pluggedInterface	// MSC Interface
#define MSC_FIRST_ENDPOINT pluggedEndpoint
#define MSC_ENDPOINT_OUT	pluggedEndpoint
#define MSC_ENDPOINT_IN	((uint8_t)(pluggedEndpoint+1))

#define MSC_RX MSC_ENDPOINT_OUT
#define MSC_TX MSC_ENDPOINT_IN

#define MSC_CLASS 0x8

//	DEVICE DESCRIPTOR
//const DeviceDescriptor USB_DeviceDescriptorB = D_DEVICE(0xEF, 0x02, 0x01, 64, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
//const DeviceDescriptor USB_DeviceDescriptor = D_DEVICE(0x00, 0x00, 0x00, 64, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
//const	DeviceDescriptor USB_DeviceDescriptor = D_DEVICE(0x00, 0x00, 0x00, 0x40, 0x03EB, 0x2403, 0x100, 0x00, 0x20, 0x03, 0x1);
const DeviceDescriptor USB_DeviceDescriptorB = D_DEVICE(0xEF, 0x02, 0x01, MSC_MAX_EP_SIZE, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);
const	DeviceDescriptor USB_DeviceDescriptor = D_DEVICE(0x00, 0x00, 0x00, MSC_MAX_EP_SIZE, USB_VID, USB_PID, 0x100, IMANUFACTURER, IPRODUCT, ISERIAL, 1);

MSC_ MassStorage;

int MSC_::getInterface(uint8_t* interfaceNum)
{
	DBUGLN("getInterface");
	DBUGVAR(*interfaceNum);

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
	DBUGLN("setup");
	DBUGVAR(setup.bmRequestType, HEX);
	DBUGVAR(setup.wValueH, HEX);

	//Support requests here if needed. Typically these are optional


	return false;
}

int MSC_::getDescriptor(USBSetup& setup)
{
	DBUGLN("getDescriptor");
	DBUGVAR(setup.bmRequestType, HEX);
	DBUGVAR(setup.wValueH, HEX);

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


MSC_::MSC_(void) : PluggableUSBModule(TOTAL_EP - 1, 1, epType)
{
	epType[0] = EP_TYPE_BULK_OUT_MSC;	// MSC_ENDPOINT_OUT
	epType[1] = EP_TYPE_BULK_IN_MSC;	// MSC_ENDPOINT_IN
	PluggableUSB().plug(this);
}
