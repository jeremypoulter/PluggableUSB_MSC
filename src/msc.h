#ifndef _MSC_H
#define _MSC_H

#include "usb_protocol_msc.h"

void msc_config(uint8_t in, uint8_t out);
void msc_process_cbw(struct usb_msc_cbw *cbw, uint32_t recv);

#endif // !_MSC_H