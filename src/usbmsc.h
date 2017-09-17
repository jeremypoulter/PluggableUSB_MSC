//================================================================================
//================================================================================

/**
  MSC USB class
*/
#ifndef USBMSC_h
#define USBMSC_h

#undef min
#undef max

#include <functional>
#include <stdint.h>
#include <Arduino.h>

#include "usb.h"
#include "usb_protocol_msc.h"

// Total number of endpoint is 3 control endpoint -1, BULK OUT Endpoint -2
#define TOTAL_EP                        3
// Default Control Endpoint is 0 
#define CTRL_EP                         0

#define MSC_FIRST_ENDPOINT              pluggedEndpoint
#define MSC_IN_INDEX                    0
#define MSC_OUT_INDEX                   1

// BULK IN Endpoint
#define MSC_BULK_IN_EP                  ((uint8_t)(MSC_FIRST_ENDPOINT+MSC_IN_INDEX))
// BULK OUT Endpoint 
#define MSC_BULK_OUT_EP                 ((uint8_t)(MSC_FIRST_ENDPOINT+MSC_OUT_INDEX))
// Control Endpoint size - 64 bytes 
#define CTRL_EP_SIZE                    64
// BULK IN/OUT Endpoint size - 64 bytes 
#define MSC_BULK_IN_EP_SIZE             64
#define MSC_BULK_OUT_EP_SIZE            64
#define MSC_MAX_EP_SIZE            			64


// MSC class specific request
#define GET_MAX_LUN                     0xA1
#define MASS_STORAGE_RESET              0x21

#define D_MSC_EP(_addr, _packetSize) \
  D_ENDPOINT(_addr, 0x02, _packetSize, 0)

#ifndef DOXYGEN_ARD
// the following would confuse doxygen documentation tool, so skip in that case for autodoc build
_Pragma("pack()")

#define WEAK __attribute__ ((weak))

#endif

typedef std::function<void(size_t bytes)> DataEventHandlerFunction;

/**
    Concrete MSC implementation of a PluggableUSBModule
 */
class MSC_ : public PluggableUSBModule
{
private:
  uint32_t epType[2];
  DataEventHandlerFunction _onDataWrite;
  DataEventHandlerFunction _onDataRead;

protected:
  // Implementation of the PUSBListNode

  /// Creates a MSCDescriptor interface and sollicit USBDevice to send control to it.
  ///   \see USBDevice::SendControl()
  int getInterface(uint8_t* interfaceNum);
  /// Current implementation just returns 0
  int getDescriptor(USBSetup& setup);
  /// Optional interface usb setup callback, current implementation returns false
  bool setup(USBSetup& setup);
  /// MSC Device short name, defaults to "MSC" and returns a length of 4 chars
  uint8_t getShortName(char* name);

  void processMscCwb(struct usb_msc_cbw *udi_msc_cbw);
public:
  /// Creates a MSC USB device with 2 endpoints
  MSC_(void);

  /// Poll to see if there is stuff to do
  void poll();

  /// NIY
  operator bool();

  // USB events
  void onDataWrite(DataEventHandlerFunction fnHandler) {
    _onDataWrite = fnHandler;
  }
  void onDataRead(DataEventHandlerFunction fnHandler) {
    _onDataRead = fnHandler;
  }
};
extern MSC_ MassStorage;

#endif	/* USBMSC_h */
