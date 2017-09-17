#ifndef _MSC_H
#define _MSC_H

#undef min
#undef max

#include <functional>
#include "usb_protocol_msc.h"

typedef std::function<void(bool write, size_t bytes)> DataEvent;

void msc_config(uint8_t in, uint8_t out, DataEvent onData);
void msc_process_cbw(struct usb_msc_cbw *cbw, uint32_t recv);

#endif // !_MSC_H