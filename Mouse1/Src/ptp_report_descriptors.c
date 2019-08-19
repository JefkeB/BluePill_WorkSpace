//
//
//
#include <stdint.h>
#include "stm32f1xx_hal.h"
#include "ptp_report_descriptors.h"



// Descriptor to use
// Touchpad
//#define TOUCHPAD
// Precision TouchPad
//#define PTP
// or Mouse
//#define MOUSE
// ZenBook
//#define ZENBOOK
#define _T



#ifdef PTP
//#define HID_MOUSE_REPORT_DESC_SIZE 28
#define HID_MOUSE_REPORT_DESC_SIZE (258)
#endif

#ifdef MOUSE
#define HID_MOUSE_REPORT_DESC_SIZE (74)
#endif

#ifdef TOUCHPAD
//#define HID_MOUSE_REPORT_DESC_SIZE (532)
#define HID_MOUSE_REPORT_DESC_SIZE (97 + 87)
#endif

#ifdef ZENBOOK
#define HID_MOUSE_REPORT_DESC_SIZE (356 - 8)
#endif

#ifdef _T
//const uint16_t HID_PTP_REPORT_DESC_SIZE = (738);
//#define HID_PTP_REPORT_DESC_SIZE (738) (HID_PTP_REPORT_DESC_SIZE)
#endif




#ifdef _T
__ALIGN_BEGIN const uint8_t HID_PTP_ReportDesc[] __ALIGN_END = {
	0x05, 0x01,                     /*  Usage Page (Desktop),                   */
	0x09, 0x02,                     /*  Usage (Mouse),                          */
	0xA1, 0x01,                     /*  Collection (Application),               */

	0x85, REPORT_ID_MOUSE,          /*      Report ID (1),                      */
	0x09, 0x01,                     /*      Usage (Pointer),                    */
	0xA1, 0x00,                     /*      Collection (Physical),              */
	0x05, 0x09,                     /*          Usage Page (Button),            */
	0x19, 0x01,                     /*          Usage Minimum (01h),            */
	0x29, 0x02,                     /*          Usage Maximum (02h),            */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x01,                     /*          Logical Maximum (1),            */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x95, 0x06,                     /*          Report Count (6),               */
	0x81, 0x03,                     /*          Input (Constant, Variable),     */

	0x05, 0x01,                     /*          Usage Page (Desktop),           */
	0x09, 0x30,                     /*          Usage (X),                      */
	0x09, 0x31,                     /*          Usage (Y),                      */
	0x15, 0x81,                     /*          Logical Minimum (-127),         */
	0x25, 0x7F,                     /*          Logical Maximum (127),          */
	0x75, 0x08,                     /*          Report Size (8),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x81, 0x06,                     /*          Input (Variable, Relative),     */

	0x75, 0x08,                     /*          Report Size (8),                */
	0x95, 0x05,                     /*          Report Count (5),               */
	0x81, 0x03,                     /*          Input (Constant, Variable),     */
	0xC0,                           /*      End Collection,                     */

	0x06, 0x00, 0xFF,               /*      Usage Page (FF00h),                 */
	0x09, 0x01,                     /*      Usage (01h),                        */

	0x85, 0x0E,			            /*      Report ID (14),                     */
	0x09, 0xC5,                     /*      Usage (C5h), PTPHQA                 */
	0x15, 0x00,                     /*      Logical Minimum (0),                */
	0x26, 0xFF, 0x00,               /*      Logical Maximum (255),              */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0x95, 0x04,                     /*      Report Count (4),                   */
	0xB1, 0x02,                     /*      Feature (Variable),                 */
	0xC0,                           /*  End Collection,                         */

	0x06, 0x00, 0xFF,               /*  Usage Page (FF00h),                     */
	0x09, 0x01,                     /*  Usage (01h),                            */

	0xA1, 0x01,                     /*  Collection (Application),               */

	0x85, 0x5C,                     /*      Report ID (92),                     */
	0x09, 0x01,                     /*      Usage (01h),                        */
	0x95, 0x0B,                     /*      Report Count (11),                  */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0x81, 0x06,                     /*      Input (Variable, Relative),         */

	0x85, 0x0D,                     /*      Report ID (13),                     */
	0x09, 0xC5,                     /*      Usage (C5h),                        */
	0x15, 0x00,                     /*      Logical Minimum (0),                */
	0x26, 0xFF, 0x00,               /*      Logical Maximum (255),              */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0x95, 0x04,                     /*      Report Count (4),                   */
	0xB1, 0x02,                     /*      Feature (Variable),                 */

	0x85, 0x0C,                     /*      Report ID (12),                     */
	0x09, 0xC6,                     /*      Usage (C6h),                        */
	0x96, 0x20, 0x03,               /*      Report Count (800),                 */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0xB1, 0x02,                     /*      Feature (Variable),                 */

	0x85, 0x0B,                     /*      Report ID (11),                     */
	0x09, 0xC7,                     /*      Usage (C7h),                        */
	0x95, 0x42,                     /*      Report Count (66),                  */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0xB1, 0x02,                     /*      Feature (Variable),                 */
	0xC0,                           /*  End Collection,                         */

	0x05, 0x0D,                     /*  Usage Page (Digitizer),                 */
	0x09, 0x05,                     /*  Usage (Touchpad),                       */
	0xA1, 0x01,                     /*  Collection (Application),               */

	0x85, REPORTID_TOUCHPAD,        /*      Report ID (4),                      */
	0x09, 0x22,                     /*      Usage (Finger),                     */

	// FINGER 1
	0xA1, 0x02,                     /*      Collection (Logical),               */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x01,                     /*          Logical Maximum (1),            */
	0x09, 0x47,                     /*          Usage (Touch Valid),            */
	0x09, 0x42,                     /*          Usage (Tip Switch),             */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x81, 0x03,                     /*          Input (Constant, Variable),     */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x75, 0x04,                     /*          Report Size (4),                */
	0x25, 0x0F,                     /*          Logical Maximum (15),           */
	0x09, 0x51,                     /*          Usage (Contact Identifier),     */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x01,                     /*          Usage Page (Desktop),           */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x75, 0x10,                     /*          Report Size (16),               */
	0x09, 0x30,                     /*          Usage (X),                      */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x09, 0x31,                     /*          Usage (Y),                      */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x0D,                     /*          Usage Page (Digitizer),         */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x64,                     /*          Logical Maximum (100),          */
	0x95, 0x03,                     /*          Report Count (3),               */
	0xC0,                           /*      End Collection,                     */

	// FINGER 2
	0xA1, 0x02,                     /*      Collection (Logical),               */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x01,                     /*          Logical Maximum (1),            */
	0x09, 0x47,                     /*          Usage (Touch Valid),            */
	0x09, 0x42,                     /*          Usage (Tip Switch),             */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x81, 0x03,                     /*          Input (Constant, Variable),     */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x75, 0x04,                     /*          Report Size (4),                */
	0x25, 0x0F,                     /*          Logical Maximum (15),           */
	0x09, 0x51,                     /*          Usage (Contact Identifier),     */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x01,                     /*          Usage Page (Desktop),           */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x75, 0x10,                     /*          Report Size (16),               */
	0x09, 0x30,                     /*          Usage (X),                      */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x09, 0x31,                     /*          Usage (Y),                      */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x0D,                     /*          Usage Page (Digitizer),         */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x64,                     /*          Logical Maximum (100),          */
	0x95, 0x03,                     /*          Report Count (3),               */
	0xC0,                           /*      End Collection,                     */

	// FINGER 3
	0xA1, 0x02,                     /*      Collection (Logical),               */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x01,                     /*          Logical Maximum (1),            */
	0x09, 0x47,                     /*          Usage (Touch Valid),            */
	0x09, 0x42,                     /*          Usage (Tip Switch),             */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x81, 0x03,                     /*          Input (Constant, Variable),     */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x75, 0x04,                     /*          Report Size (4),                */
	0x25, 0x0F,                     /*          Logical Maximum (15),           */
	0x09, 0x51,                     /*          Usage (Contact Identifier),     */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x01,                     /*          Usage Page (Desktop),           */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x75, 0x10,                     /*          Report Size (16),               */
	0x09, 0x30,                     /*          Usage (X),                      */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x09, 0x31,                     /*          Usage (Y),                      */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x0D,                     /*          Usage Page (Digitizer),         */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x64,                     /*          Logical Maximum (100),          */
	0x95, 0x03,                     /*          Report Count (3),               */
	0xC0,                           /*      End Collection,                     */

	// FINGER 4
	0xA1, 0x02,                     /*      Collection (Logical),               */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x01,                     /*          Logical Maximum (1),            */
	0x09, 0x47,                     /*          Usage (Touch Valid),            */
	0x09, 0x42,                     /*          Usage (Tip Switch),             */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x81, 0x03,                     /*          Input (Constant, Variable),     */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x75, 0x04,                     /*          Report Size (4),                */
	0x25, 0x0F,                     /*          Logical Maximum (15),           */
	0x09, 0x51,                     /*          Usage (Contact Identifier),     */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x01,                     /*          Usage Page (Desktop),           */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x75, 0x10,                     /*          Report Size (16),               */
	0x09, 0x30,                     /*          Usage (X),                      */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x09, 0x31,                     /*          Usage (Y),                      */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x0D,                     /*          Usage Page (Digitizer),         */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x64,                     /*          Logical Maximum (100),          */
	0x95, 0x03,                     /*          Report Count (3),               */
	0xC0,                           /*      End Collection,                     */

	// FINGER 5
	0xA1, 0x02,                     /*      Collection (Logical),               */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x01,                     /*          Logical Maximum (1),            */
	0x09, 0x47,                     /*          Usage (Touch Valid),            */
	0x09, 0x42,                     /*          Usage (Tip Switch),             */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x81, 0x03,                     /*          Input (Constant, Variable),     */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x75, 0x04,                     /*          Report Size (4),                */
	0x25, 0x0F,                     /*          Logical Maximum (15),           */
	0x09, 0x51,                     /*          Usage (Contact Identifier),     */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x01,                     /*          Usage Page (Desktop),           */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x75, 0x10,                     /*          Report Size (16),               */
	0x09, 0x30,                     /*          Usage (X),                      */
	0x95, 0x01,                     /*          Report Count (1),               */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
	0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
	0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
	0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
	0x55, 0x0E,                     /*          Unit Exponent (14),             */
	0x65, 0x11,                     /*          Unit (Centimeter),              */
	0x09, 0x31,                     /*          Usage (Y),                      */
	0x81, 0x02,                     /*          Input (Variable),               */
	0x05, 0x0D,                     /*          Usage Page (Digitizer),         */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x64,                     /*          Logical Maximum (100),          */
	0x95, 0x03,                     /*          Report Count (3),               */
	0xC0,                           /*      End Collection,                     */

	0x55, 0x0C,                     /*      Unit Exponent (12),                 */
	0x66, 0x01, 0x10,               /*      Unit (Seconds),                     */
	0x47, 0xFF, 0xFF, 0x00, 0x00,   /*      Physical Maximum (65535),           */
	0x27, 0xFF, 0xFF, 0x00, 0x00,   /*      Logical Maximum (65535),            */
	0x75, 0x10,                     /*      Report Size (16),                   */
	0x95, 0x01,                     /*      Report Count (1),                   */
	0x09, 0x56,                     /*      Usage (Scan Time),                  */
	0x81, 0x02,                     /*      Input (Variable),                   */
	0x09, 0x54,                     /*      Usage (Contact Count),              */
	0x25, 0x7F,                     /*      Logical Maximum (127),              */
	0x95, 0x01,                     /*      Report Count (1),                   */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0x81, 0x02,                     /*      Input (Variable),                   */
	0x05, 0x09,                     /*      Usage Page (Button),                */
	0x09, 0x01,                     /*      Usage (01h),                        */
	0x25, 0x01,                     /*      Logical Maximum (1),                */
	0x75, 0x01,                     /*      Report Size (1),                    */
	0x95, 0x01,                     /*      Report Count (1),                   */
	0x81, 0x02,                     /*      Input (Variable),                   */
	0x95, 0x07,                     /*      Report Count (7),                   */
	0x81, 0x03,                     /*      Input (Constant, Variable),         */
	0x09, 0xC5,                     /*      Usage (C5h),                        */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0x95, 0x02,                     /*      Report Count (2),                   */
	0x81, 0x03,                     /*      Input (Constant, Variable),         */
	0x05, 0x0D,                     /*      Usage Page (Digitizer),             */

	0x85, REPORTID_MAX_COUNT,       /*      Report ID (2),                      */
	0x09, 0x55,                     /*      Usage (Contact Count Maximum),      */
	0x09, 0x59,                     /*      Usage (Pad Type),                   */
	0x75, 0x04,                     /*      Report Size (4),                    */
	0x95, 0x02,                     /*      Report Count (2),                   */
	0x25, 0x0F,                     /*      Logical Maximum (15),               */
	0xB1, 0x02,                     /*      Feature (Variable),                 */

	0x85, REPORTID_LATENCY,         /*      Report ID (7),                      */
	0x09, 0x60,                     /*      Usage (Latency Mode),               */
	0x75, 0x01,                     /*      Report Size (1),                    */
	0x95, 0x01,                     /*      Report Count (1),                   */
	0x15, 0x00,                     /*      Logical Minimum (0),                */
	0x25, 0x01,                     /*      Logical Maximum (1),                */
	0xB1, 0x02,                     /*      Feature (Variable),                 */
	0x95, 0x0F,                     /*      Report Count (15),                  */
	0xB1, 0x03,                     /*      Feature (Constant, Variable),       */

	0x06, 0x00, 0xFF,               /*      Usage Page (Vendor Defined 0xFF00), */
	0x06, 0x00, 0xFF,               /*      Usage Page (Vendor Defined 0xFF00), */

	0x85, REPORTID_PTPHQA,          /*      Report ID (6),                      */
	0x09, 0xC5,                     /*      Usage (Vendor Usage 0xC5),           */
	0x15, 0x00,                     /*      Logical Minimum (0),                */
	0x26, 0xFF, 0x00,               /*      Logical Maximum (255),              */
	0x75, 0x08,                     /*      Report Size (8),                    */
	0x96, 0x00, 0x01,               /*      Report Count (256),                 */
	0xB1, 0x02,                     /*      Feature (Variable),                 */

	0xC0,                           /*  End Collection,                         */

	0x05, 0x0D,                     /*  Usage Page (Digitizer),                 */
	0x09, 0x0E,                     /*  Usage (Configuration),                  */

	0xA1, 0x01,                     /*  Collection (Application),               */
	0x85, REPORTID_REPORTINGMODE,   /*      Report ID (3),                      */
	0x09, 0x22,                     /*      Usage (Finger),                     */
	0xA1, 0x00,                     /*      Collection (Physical),              */
	0x09, 0x52,                     /*          Usage (Device Mode),            */
	0x15, 0x00,                     /*          Logical Minimum (0),            */
	0x25, 0x0A,                     /*          Logical Maximum (10),           */
	0x75, 0x10,                     /*          Report Size (16),               */
	0x95, 0x01,                     /*          Report Count (1),               */
	0xB1, 0x02,                     /*          Feature (Variable),             */
	0xC0,                           /*      End Collection,                     */

	0x09, 0x22,                     /*      Usage (Finger),                     */
	0xA1, 0x00,                     /*      Collection (Physical),              */
	0x85, REPORTID_FUNCTION_SWITCH, /*          Report ID (5),                  */
	0x09, 0x57,                     /*          Usage (Surface switch)          */
	0x09, 0x58,                     /*          Usage (Button switch),          */
	0x75, 0x01,                     /*          Report Size (1),                */
	0x95, 0x02,                     /*          Report Count (2),               */
	0x25, 0x01,                     /*          Logical Maximum (1),            */
	0xB1, 0x02,                     /*          Feature (Variable),             */
	0x95, 0x0E,                     /*          Report Count (14),              */
	0xB1, 0x03,                     /*          Feature (Constant, Variable),   */
	0xC0,                           /*      End Collection,                     */

	0xC0                            /*  End Collection                          */
};
#endif


#ifdef _Taap
static uint8_t hid_report_descriptor[1024];

static const uint8_t hid_report_descriptor_prefix[] = {
		0x05, 0x01,                     /*  Usage Page (Desktop),                   */
		0x09, 0x02,                     /*  Usage (Mouse),                          */
		0xA1, 0x01,                     /*  Collection (Application),               */

		0x85, REPORT_ID_MOUSE,          /*      Report ID (1),                      */
		0x09, 0x01,                     /*      Usage (Pointer),                    */
		0xA1, 0x00,                     /*      Collection (Physical),              */
		0x05, 0x09,                     /*          Usage Page (Button),            */
		0x19, 0x01,                     /*          Usage Minimum (01h),            */
		0x29, 0x02,                     /*          Usage Maximum (02h),            */
		0x15, 0x00,                     /*          Logical Minimum (0),            */
		0x25, 0x01,                     /*          Logical Maximum (1),            */
		0x75, 0x01,                     /*          Report Size (1),                */
		0x95, 0x02,                     /*          Report Count (2),               */
		0x81, 0x02,                     /*          Input (Variable),               */
		0x95, 0x06,                     /*          Report Count (6),               */
		0x81, 0x03,                     /*          Input (Constant, Variable),     */

		0x05, 0x01,                     /*          Usage Page (Desktop),           */
		0x09, 0x30,                     /*          Usage (X),                      */
		0x09, 0x31,                     /*          Usage (Y),                      */
		0x15, 0x81,                     /*          Logical Minimum (-127),         */
		0x25, 0x7F,                     /*          Logical Maximum (127),          */
		0x75, 0x08,                     /*          Report Size (8),                */
		0x95, 0x02,                     /*          Report Count (2),               */
		0x81, 0x06,                     /*          Input (Variable, Relative),     */

		0x75, 0x08,                     /*          Report Size (8),                */
		0x95, 0x05,                     /*          Report Count (5),               */
		0x81, 0x03,                     /*          Input (Constant, Variable),     */
		0xC0,                           /*      End Collection,                     */

		0x06, 0x00, 0xFF,               /*      Usage Page (FF00h),                 */
		0x09, 0x01,                     /*      Usage (01h),                        */

		0x85, 0x0E,			            /*      Report ID (14),                     */
		0x09, 0xC5,                     /*      Usage (C5h), PTPHQA                 */
		0x15, 0x00,                     /*      Logical Minimum (0),                */
		0x26, 0xFF, 0x00,               /*      Logical Maximum (255),              */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0x95, 0x04,                     /*      Report Count (4),                   */
		0xB1, 0x02,                     /*      Feature (Variable),                 */
		0xC0,                           /*  End Collection,                         */

		0x06, 0x00, 0xFF,               /*  Usage Page (FF00h),                     */
		0x09, 0x01,                     /*  Usage (01h),                            */

		0xA1, 0x01,                     /*  Collection (Application),               */

		0x85, 0x5C,                     /*      Report ID (92),                     */
		0x09, 0x01,                     /*      Usage (01h),                        */
		0x95, 0x0B,                     /*      Report Count (11),                  */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0x81, 0x06,                     /*      Input (Variable, Relative),         */

		0x85, 0x0D,                     /*      Report ID (13),                     */
		0x09, 0xC5,                     /*      Usage (C5h),                        */
		0x15, 0x00,                     /*      Logical Minimum (0),                */
		0x26, 0xFF, 0x00,               /*      Logical Maximum (255),              */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0x95, 0x04,                     /*      Report Count (4),                   */
		0xB1, 0x02,                     /*      Feature (Variable),                 */

		0x85, 0x0C,                     /*      Report ID (12),                     */
		0x09, 0xC6,                     /*      Usage (C6h),                        */
		0x96, 0x20, 0x03,               /*      Report Count (800),                 */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0xB1, 0x02,                     /*      Feature (Variable),                 */

		0x85, 0x0B,                     /*      Report ID (11),                     */
		0x09, 0xC7,                     /*      Usage (C7h),                        */
		0x95, 0x42,                     /*      Report Count (66),                  */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0xB1, 0x02,                     /*      Feature (Variable),                 */
		0xC0,                           /*  End Collection,                         */

		0x05, 0x0D,                     /*  Usage Page (Digitizer),                 */
		0x09, 0x05,                     /*  Usage (Touchpad),                       */
		0xA1, 0x01,                     /*  Collection (Application),               */

		0x85, REPORTID_TOUCHPAD,        /*      Report ID (4),                      */
		0x09, 0x22,                     /*      Usage (Finger),                     */
};

static uint8_t hid_report_descriptor_finger[] = {
		0xA1, 0x02,                     /*      Collection (Logical),               */
		0x15, 0x00,                     /*          Logical Minimum (0),            */
		0x25, 0x01,                     /*          Logical Maximum (1),            */
		0x09, 0x47,                     /*          Usage (Touch Valid),            */
		0x09, 0x42,                     /*          Usage (Tip Switch),             */
		0x95, 0x02,                     /*          Report Count (2),               */
		0x75, 0x01,                     /*          Report Size (1),                */
		0x81, 0x02,                     /*          Input (Variable),               */
		0x75, 0x01,                     /*          Report Size (1),                */
		0x95, 0x02,                     /*          Report Count (2),               */
		0x81, 0x03,                     /*          Input (Constant, Variable),     */
		0x95, 0x01,                     /*          Report Count (1),               */
		0x75, 0x04,                     /*          Report Size (4),                */
		0x25, 0x0F,                     /*          Logical Maximum (15),           */
		0x09, 0x51,                     /*          Usage (Contact Identifier),     */
		0x81, 0x02,                     /*          Input (Variable),               */
		0x05, 0x01,                     /*          Usage Page (Desktop),           */
		0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
		0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
		0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
		0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
		0x55, 0x0E,                     /*          Unit Exponent (14),             */
		0x65, 0x11,                     /*          Unit (Centimeter),              */
		0x75, 0x10,                     /*          Report Size (16),               */
		0x09, 0x30,                     /*          Usage (X),                      */
		0x95, 0x01,                     /*          Report Count (1),               */
		0x81, 0x02,                     /*          Input (Variable),               */
		0x16, 0x00, 0x00,               /*          Logical Minimum (0),            */
		0x26, 0xCC, 0x04,               /*          Logical Maximum (1228),         */
		0x36, 0x00, 0x00,               /*          Physical Minimum (0),           */
		0x46, 0x00, 0x04,               /*          Physical Maximum (1024),        */
		0x55, 0x0E,                     /*          Unit Exponent (14),             */
		0x65, 0x11,                     /*          Unit (Centimeter),              */
		0x09, 0x31,                     /*          Usage (Y),                      */
		0x81, 0x02,                     /*          Input (Variable),               */
		0x05, 0x0D,                     /*          Usage Page (Digitizer),         */
		0x15, 0x00,                     /*          Logical Minimum (0),            */
		0x25, 0x64,                     /*          Logical Maximum (100),          */
		0x95, 0x03,                     /*          Report Count (3),               */
		0xC0,                           /*      End Collection,                     */
};

static const uint8_t hid_report_descriptor_suffix[] = {
		0x55, 0x0C,                     /*      Unit Exponent (12),                 */
		0x66, 0x01, 0x10,               /*      Unit (Seconds),                     */
		0x47, 0xFF, 0xFF, 0x00, 0x00,   /*      Physical Maximum (65535),           */
		0x27, 0xFF, 0xFF, 0x00, 0x00,   /*      Logical Maximum (65535),            */
		0x75, 0x10,                     /*      Report Size (16),                   */
		0x95, 0x01,                     /*      Report Count (1),                   */
		0x09, 0x56,                     /*      Usage (Scan Time),                  */
		0x81, 0x02,                     /*      Input (Variable),                   */
		0x09, 0x54,                     /*      Usage (Contact Count),              */
		0x25, 0x7F,                     /*      Logical Maximum (127),              */
		0x95, 0x01,                     /*      Report Count (1),                   */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0x81, 0x02,                     /*      Input (Variable),                   */
		0x05, 0x09,                     /*      Usage Page (Button),                */
		0x09, 0x01,                     /*      Usage (01h),                        */
		0x25, 0x01,                     /*      Logical Maximum (1),                */
		0x75, 0x01,                     /*      Report Size (1),                    */
		0x95, 0x01,                     /*      Report Count (1),                   */
		0x81, 0x02,                     /*      Input (Variable),                   */
		0x95, 0x07,                     /*      Report Count (7),                   */
		0x81, 0x03,                     /*      Input (Constant, Variable),         */
		0x09, 0xC5,                     /*      Usage (C5h),                        */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0x95, 0x02,                     /*      Report Count (2),                   */
		0x81, 0x03,                     /*      Input (Constant, Variable),         */
		0x05, 0x0D,                     /*      Usage Page (Digitizer),             */

		0x85, REPORTID_MAX_COUNT,       /*      Report ID (2),                      */
		0x09, 0x55,                     /*      Usage (Contact Count Maximum),      */
		0x09, 0x59,                     /*      Usage (Pad Type),                   */
		0x75, 0x04,                     /*      Report Size (4),                    */
		0x95, 0x02,                     /*      Report Count (2),                   */
		0x25, 0x0F,                     /*      Logical Maximum (15),               */
		0xB1, 0x02,                     /*      Feature (Variable),                 */

		0x85, REPORTID_LATENCY,         /*      Report ID (7),                      */
		0x09, 0x60,                     /*      Usage (Latency Mode),               */
		0x75, 0x01,                     /*      Report Size (1),                    */
		0x95, 0x01,                     /*      Report Count (1),                   */
		0x15, 0x00,                     /*      Logical Minimum (0),                */
		0x25, 0x01,                     /*      Logical Maximum (1),                */
		0xB1, 0x02,                     /*      Feature (Variable),                 */
		0x95, 0x0F,                     /*      Report Count (15),                  */
		0xB1, 0x03,                     /*      Feature (Constant, Variable),       */

		0x06, 0x00, 0xFF,               /*      Usage Page (Vendor Defined 0xFF00), */
		0x06, 0x00, 0xFF,               /*      Usage Page (Vendor Defined 0xFF00), */

		0x85, REPORTID_PTPHQA,          /*      Report ID (6),                      */
		0x09, 0xC5,                     /*      Usage (Vendor Usage 0xC5),           */
		0x15, 0x00,                     /*      Logical Minimum (0),                */
		0x26, 0xFF, 0x00,               /*      Logical Maximum (255),              */
		0x75, 0x08,                     /*      Report Size (8),                    */
		0x96, 0x00, 0x01,               /*      Report Count (256),                 */
		0xB1, 0x02,                     /*      Feature (Variable),                 */

		0xC0,                           /*  End Collection,                         */

		0x05, 0x0D,                     /*  Usage Page (Digitizer),                 */
		0x09, 0x0E,                     /*  Usage (Configuration),                  */

		0xA1, 0x01,                     /*  Collection (Application),               */
		0x85, REPORTID_REPORTINGMODE,   /*      Report ID (3),                      */
		0x09, 0x22,                     /*      Usage (Finger),                     */
		0xA1, 0x00,                     /*      Collection (Physical),              */
		0x09, 0x52,                     /*          Usage (Device Mode),            */
		0x15, 0x00,                     /*          Logical Minimum (0),            */
		0x25, 0x0A,                     /*          Logical Maximum (10),           */
		0x75, 0x10,                     /*          Report Size (16),               */
		0x95, 0x01,                     /*          Report Count (1),               */
		0xB1, 0x02,                     /*          Feature (Variable),             */
		0xC0,                           /*      End Collection,                     */

		0x09, 0x22,                     /*      Usage (Finger),                     */
		0xA1, 0x00,                     /*      Collection (Physical),              */
		0x85, REPORTID_FUNCTION_SWITCH, /*          Report ID (5),                  */
		0x09, 0x57,                     /*          Usage (Surface switch)          */
		0x09, 0x58,                     /*          Usage (Button switch),          */
		0x75, 0x01,                     /*          Report Size (1),                */
		0x95, 0x02,                     /*          Report Count (2),               */
		0x25, 0x01,                     /*          Logical Maximum (1),            */
		0xB1, 0x02,                     /*          Feature (Variable),             */
		0x95, 0x0E,                     /*          Report Count (14),              */
		0xB1, 0x03,                     /*          Feature (Constant, Variable),   */
		0xC0,                           /*      End Collection,                     */

		0xC0                            /*  End Collection                          */
};
#endif

#ifdef ZENBOOK

static const uint8_t HID_MOUSE_ReportDesc[] = {
		0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)

		0x09, 0x02,        // Usage (Mouse)
		0xA1, 0x01,        // Collection (Application)
		0x85, REPORT_ID_MOUSE,  //   Report ID (1)
		0x09, 0x01,        //   Usage (Pointer)
		0xA1, 0x00,        //   Collection (Physical)

		0x05, 0x09,        //     Usage Page (Button)
		0x19, 0x01,        //     Usage Minimum (0x01)
		0x29, 0x02,        //     Usage Maximum (0x02)
		0x15, 0x00,        //     Logical Minimum (0)
		0x25, 0x01,        //     Logical Maximum (1)
		0x75, 0x01,        //     Report Size (1)
		0x95, 0x02,        //     Report Count (2)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x95, 0x06,        //     Report Count (6)
		0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

		0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
		0x09, 0x30,        //     Usage (X)
		0x09, 0x31,        //     Usage (Y)
		0x09, 0x38,        //     Usage (Wheel)
		0x15, 0x81,        //     Logical Minimum (-127)
		0x25, 0x7F,        //     Logical Maximum (127)
		0x75, 0x08,        //     Report Size (8)
		0x95, 0x03,        //     Report Count (3)
		0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
		0x05, 0x0C,        //     Usage Page (Consumer)

		0x0A, 0x38, 0x02,  //     Usage (AC Pan)
		0x95, 0x01,        //     Report Count (1)
		0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
		0x75, 0x08,        //     Report Size (8)
		0x95, 0x03,        //     Report Count (3)
		0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0xC0,              //   End Collection
		0xC0,              // End Collection

		0x05, 0x0D,        // Usage Page (Digitizer)
		0x09, 0x05,        // Usage (Touch Pad)

		0xA1, 0x01,        // Collection (Application)
		0x85, REPORTID_TOUCHPAD,        //   Report ID (4)
		0x09, 0x22,        //   Usage (Finger)
		0xA1, 0x02,        //   Collection (Logical)
		0x15, 0x00,        //     Logical Minimum (0)
		0x25, 0x01,        //     Logical Maximum (1)
		0x09, 0x47,        //     Usage (Confidence)
		0x09, 0x42,        //     Usage (Tip Switch)
		0x95, 0x02,        //     Report Count (2)
		0x75, 0x01,        //     Report Size (1)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x75, 0x01,        //     Report Size (1)
		0x95, 0x02,        //     Report Count (2)
		0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x95, 0x01,        //     Report Count (1)
		0x75, 0x04,        //     Report Size (4)
		0x25, 0x0F,        //     Logical Maximum (15)
		0x09, 0x51,        //     Usage (Contact Identifier)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
		0x15, 0x00,        //     Logical Minimum (0)
		0x26, 0x80, 0x0C,  //     Logical Maximum (3200)
		0x75, 0x10,        //     Report Size (16)
		0x55, 0x0E,        //     Unit Exponent (-2)
		0x65, 0x13,        //     Unit (System: English Linear, Length: Centimeter)
		0x09, 0x30,        //     Usage (X)
		0x35, 0x00,        //     Physical Minimum (0)
		0x46, 0x90, 0x01,  //     Physical Maximum (400)
		0x95, 0x01,        //     Report Count (1)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x46, 0x13, 0x01,  //     Physical Maximum (275)
		0x26, 0x96, 0x08,  //     Logical Maximum (2198)
		0x26, 0x96, 0x08,  //     Logical Maximum (2198)
		0x09, 0x31,        //     Usage (Y)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x05, 0x0D,        //     Usage Page (Digitizer)
		0x15, 0x00,        //     Logical Minimum (0)
		0x25, 0x64,        //     Logical Maximum (100)
		0x95, 0x03,        //     Report Count (3)
		0xC0,              //   End Collection

		0x55, 0x0C,        //   Unit Exponent (-4)
		0x66, 0x01, 0x10,  //   Unit (System: SI Linear, Time: Seconds)
		0x47, 0xFF, 0xFF, 0x00, 0x00,  //   Physical Maximum (65534)
		0x27, 0xFF, 0xFF, 0x00, 0x00,  //   Logical Maximum (65534)
		0x75, 0x10,        //   Report Size (16)
		0x95, 0x01,        //   Report Count (1)
		0x09, 0x56,        //   Usage (Scan Time)
		0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

		0x09, 0x54,        //   Usage (Contact Count)
		0x25, 0x7F,        //   Logical Maximum (127)
		0x95, 0x01,        //   Report Count (1)
		0x75, 0x08,        //   Report Size (8)
		0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

		0x05, 0x09,        //   Usage Page (Button)
		0x09, 0x01,        //   Usage (Pointer)
		0x25, 0x01,        //   Logical Maximum (1)
		0x75, 0x01,        //   Report Size (1)
		0x95, 0x01,        //   Report Count (1)
		0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x95, 0x07,        //   Report Count (7)
		0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
/*
		0x09, 0xC5,        //   Usage (Vendor Usage 0xC5)
		0x75, 0x08,        //   Report Size (8)
		0x95, 0x04,        //   Report Count (4)
		0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
*/

		0x05, 0x0D,        //   Usage Page (Digitizer)
		0x85, REPORTID_MAX_COUNT,        //   Report ID (2)
		0x09, 0x55,        //   Usage (Contact Count Maximum)
		0x09, 0x59,        //   Usage (Pad Type)
		0x75, 0x04,        //   Report Size (4)
		0x95, 0x02,        //   Report Count (2)
		0x25, 0x0F,        //   Logical Maximum (15)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0x85, REPORTID_LATENCY,        //   Report ID (7)
		0x09, 0x60,        //   Usage (Latency Mode)
		0x75, 0x01,        //   Report Size (1)
		0x95, 0x01,        //   Report Count (1)
		0x15, 0x00,        //   Logical Minimum (0)
		0x25, 0x01,        //   Logical Maximum (1)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
		0x95, 0x0F,        //   Report Count (15)
		0xB1, 0x03,        //   Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
		0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)

		0x85, REPORTID_PTPHQA,        //   Report ID (6)
		0x09, 0xC5,        //   Usage (Vendor Usage 0xC5)
		0x15, 0x00,        //   Logical Minimum (0)
		0x26, 0xFF, 0x00,  //   Logical Maximum (255)
		0x75, 0x08,        //   Report Size (8)
		0x96, 0x00, 0x01,  //   Report Count (256)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0x85, REPORTID_VENDOR_C4,        //   Report ID (13)
		0x09, 0xC4,        //   Usage (0xC4)
		0x15, 0x00,        //   Logical Minimum (0)
		0x26, 0xFF, 0x00,  //   Logical Maximum (255)
		0x75, 0x08,        //   Report Size (8)
		0x95, 0x04,        //   Report Count (4)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0x85, REPORTID_VENDOR_USAGE_SEGMENT,        //   Report ID (12)
		0x09, 0xC6,        //   Usage (Vendor usage for segment #)
		0x96, 0x8A, 0x02,  //   Report Count (650)
		0x75, 0x08,        //   Report Size (8)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0x85, REPORTID_VENDOR_C7,        //   Report ID (11)
		0x09, 0xC7,        //   Usage (Vendor Usage)
		0x95, 0x80,        //   Report Count (-128)
		0x75, 0x08,        //   Report Size (8)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0xC0,              // End Collection


		0x05, 0x0D,        // Usage Page (Digitizer)
		0x09, 0x0E,        // Usage (Configuration)

		0xA1, 0x01,        // Collection (Application)


		/*
		     feature reporting
		 	 0 	Mouse Collection
			 3 	Windows Precision Touchpad Collection
		 */
		0x85, REPORTID_REPORTINGMODE,        //   Report ID (3)
		0x09, 0x22,        //   Usage (Finger)
		0xA1, 0x00,        //   Collection (Physical)
		0x09, 0x52,        //     Usage (Input Mode)
		0x15, 0x00,        //     Logical Minimum (0)
		0x25, 0x0A,        //     Logical Maximum (10)
		0x75, 0x10,        //     Report Size (16)
		0x95, 0x01,        //     Report Count (1)
		0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
		0xC0,              //   End Collection

		0x09, 0x22,        //   Usage (Finger)
		0xA1, 0x00,        //   Collection (Physical)
		0x85, REPORTID_FUNCTION_SWITCH,        //     Report ID (5)
		0x09, 0x57,        //     Usage (Surface switch)
		0x09, 0x58,        //     Usage (Button switch)
		0x15, 0x00,        //     Logical Minimum (0)
		0x75, 0x01,        //     Report Size (1)
		0x95, 0x02,        //     Report Count (2)
		0x25, 0x03,        //     Logical Maximum (3)
		0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
		0x95, 0x0E,        //     Report Count (14)
		0xB1, 0x03,        //     Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
		0xC0,              //   End Collection

		0xC0,              // End Collection
};

#endif

#ifdef TOUCHPAD

#define CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_X 3207
#define CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_Y 1783
#define CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_PRESSURE 511
#define CONFIG_USB_HID_TOUCHPAD_PHYSICAL_MAX_X 1018 /* tenth of mm */
#define CONFIG_USB_HID_TOUCHPAD_PHYSICAL_MAX_Y 566 /* tenth of mm */
#define CONFIG_TOUCHPAD_VIRTUAL_SIZE (48*1024)


#define REPORT_ID_TOUCHPAD			0x01
#define REPORT_ID_DEVICE_CAPS		0x0A
#define REPORT_ID_DEVICE_CERT		0x0B

#define MAX_FINGERS					2

#define FINGER_USAGE \
	0x05, 0x0D,        /*   Usage Page (Digitizer) */ \
	0x09, 0x22,        /*   Usage (Finger) */ \
	0xA1, 0x02,        /*   Collection (Logical) */ \
	0x09, 0x47,        /*     Usage (Confidence) */ \
	0x09, 0x42,        /*     Usage (Tip Switch) */ \
	0x09, 0x32,        /*     Usage (In Range) */ \
	0x15, 0x00,        /*     Logical Minimum (0) */ \
	0x25, 0x01,        /*     Logical Maximum (1) */ \
	0x75, 0x01,        /*     Report Size (1) */ \
	0x95, 0x03,        /*     Report Count (3) */ \
	0x81, 0x02,        /*     Input (Data,Var,Abs) */ \
	0x09, 0x51,        /*     Usage (0x51) Contact identifier */ \
	0x75, 0x04,        /*     Report Size (4) */ \
	0x95, 0x01,        /*     Report Count (1) */ \
	0x25, 0x0F,        /*     Logical Maximum (15) */ \
	0x81, 0x02,        /*     Input (Data,Var,Abs) */ \
	0x05, 0x0D,        /*     Usage Page (Digitizer) */ \
			   /*     Logical Maximum of Pressure */ \
	0x26, (CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_PRESSURE & 0xFF), \
	      (CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_PRESSURE >> 8), \
	0x75, 0x09,        /*     Report Size (9) */ \
	0x09, 0x30,        /*     Usage (Tip pressure) */ \
	0x81, 0x02,        /*     Input (Data,Var,Abs) */ \
	0x26, 0xFF, 0x0F,  /*     Logical Maximum (4095) */ \
	0x75, 0x0C,        /*     Report Size (12) */ \
	0x09, 0x48,        /*     Usage (WIDTH) */ \
	0x81, 0x02,        /*     Input (Data,Var,Abs) */ \
	0x09, 0x49,        /*     Usage (HEIGHT) */ \
	0x81, 0x02,        /*     Input (Data,Var,Abs) */ \
	0x05, 0x01,        /*     Usage Page (Generic Desktop Ctrls) */ \
	0x75, 0x0C,        /*     Report Size (12) */ \
	0x55, 0x0E,        /*     Unit Exponent (-2) */ \
	0x65, 0x11,        /*     Unit (System: SI Linear, Length: cm) */ \
	0x09, 0x30,        /*     Usage (X) */ \
	0x35, 0x00,        /*     Physical Minimum (0) */ \
	0x26, (CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_X & 0xff), \
	      (CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_X >> 8), \
	                   /*     Logical Maximum */ \
	0x46, (CONFIG_USB_HID_TOUCHPAD_PHYSICAL_MAX_X & 0xff), \
	      (CONFIG_USB_HID_TOUCHPAD_PHYSICAL_MAX_X >> 8), \
	                   /*     Physical Maximum (tenth of mm) */ \
	0x81, 0x02,        /*     Input (Data,Var,Abs) */ \
	0x26, (CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_Y & 0xff), \
	      (CONFIG_USB_HID_TOUCHPAD_LOGICAL_MAX_Y >> 8), \
	                   /*     Logical Maximum */ \
	0x46, (CONFIG_USB_HID_TOUCHPAD_PHYSICAL_MAX_Y & 0xff), \
	      (CONFIG_USB_HID_TOUCHPAD_PHYSICAL_MAX_Y >> 8), \
	                   /*     Physical Maximum (tenth of mm) */ \
	0x09, 0x31,        /*     Usage (Y) */ \
	0x81, 0x02,        /*     Input (Data,Var,Abs) */ \
	0xC0               /*   End Collection */
/*
 * HID: Report Descriptor
 * TODO(b/35582031): There are ways to reduce flash usage, as the
 * Finger Usage is repeated 5 times.
 */
static const uint8_t HID_MOUSE_ReportDesc[] = {
	/* Touchpad Collection */
	0x05, 0x0D,                    /* Usage Page (Digitizer) */
	0x09, 0x05,                    /* Usage (Touch Pad) */
	0xA1, 0x01,                    /* Collection (Application) */
	0x85, REPORT_ID_TOUCHPAD,      /*   Report ID (1, Touch) */
	/* Finger 0 */
	FINGER_USAGE,
#if 0
	/* Finger 1 */
	FINGER_USAGE,
	/* Finger 2 */
	FINGER_USAGE,
	/* Finger 3 */
	FINGER_USAGE,
	/* Finger 4 */
	FINGER_USAGE,
#endif
	/* Contact count */
	0x05, 0x0D,                    /*   Usage Page (Digitizer) */
	0x09, 0x54,                    /*   Usage (Contact count) */
	0x25, MAX_FINGERS,             /*   Logical Maximum (MAX_FINGERS) */
	0x75, 0x07,                    /*   Report Size (7) */
	0x95, 0x01,                    /*   Report Count (1) */
	0x81, 0x02,                    /*   Input (Data,Var,Abs) */
	/* Button */
	0x05, 0x01,                    /*   Usage Page(Generic Desktop Ctrls) */
	0x05, 0x09,                    /*   Usage (Button) */
	0x19, 0x01,                    /*   Usage Minimum (0x01) */
	0x29, 0x01,                    /*   Usage Maximum (0x01) */
	0x15, 0x00,                    /*   Logical Minimum (0) */
	0x25, 0x01,                    /*   Logical Maximum (1) */
	0x75, 0x01,                    /*   Report Size (1) */
	0x95, 0x01,                    /*   Report Count (1) */
	0x81, 0x02,                    /*   Input (Data,Var,Abs) */
	/* Timestamp */
	0x05, 0x0D,                    /*   Usage Page (Digitizer) */
	0x55, 0x0C,                    /*   Unit Exponent (-4) */
	0x66, 0x01, 0x10,              /*   Unit (Seconds) */
	0x47, 0xFF, 0xFF, 0x00, 0x00,  /*   Physical Maximum (65535) */
	0x27, 0xFF, 0xFF, 0x00, 0x00,  /*   Logical Maximum (65535) */
	0x75, 0x10,                    /*   Report Size (16) */
	0x95, 0x01,                    /*   Report Count (1) */
	0x09, 0x56,                    /*   Usage (0x56, Relative Scan Time) */
	0x81, 0x02,                    /*   Input (Data,Var,Abs) */
	0x85, REPORT_ID_DEVICE_CAPS,   /*   Report ID (Device Capabilities) */
	0x09, 0x55,                    /*   Usage (Contact Count Maximum) */
	0x09, 0x59,                    /*   Usage (Pad Type) */
	0x25, 0x0F,                    /*   Logical Maximum (15) */
	0x75, 0x08,                    /*   Report Size (8) */
	0x95, 0x02,                    /*   Report Count (2) */
	0xB1, 0x02,                    /*   Feature (Data,Var,Abs) */
	/* Page 0xFF, usage 0xC5 is device certificate. */
	0x06, 0x00, 0xFF,              /*   Usage Page (Vendor Defined) */
	0x85, REPORT_ID_DEVICE_CERT,   /*   Report ID (Device Certification) */
	0x09, 0xC5,                    /*   Usage (Vendor Usage 0xC5) */
	0x15, 0x00,                    /*   Logical Minimum (0) */
	0x26, 0xFF, 0x00,              /*   Logical Maximum (255) */
	0x75, 0x08,                    /*   Report Size (8) */
	0x96, 0x00, 0x01,              /*   Report Count (256) */
	0xB1, 0x02,                    /*   Feature (Data,Var,Abs) */
	0xC0,                          /* End Collection */
};
#endif

#ifdef MOUSE
__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END =
{
	0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
	0x09, 0x02,        // Usage (Mouse)

	0xA1, 0x01,        // Collection (Application)

	0x09, 0x01,        //   Usage (Pointer)
	0xA1, 0x00,        //   Collection (Physical)

	0x05, 0x09,        //     Usage Page (Button)
	0x19, 0x01,        //     Usage Minimum (0x01)
	0x29, 0x03,        //     Usage Maximum (0x03)
	0x15, 0x00,        //     Logical Minimum (0)
	0x25, 0x01,        //     Logical Maximum (1)
	0x95, 0x03,        //     Report Count (3)
	0x75, 0x01,        //     Report Size (1)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x01,        //     Report Count (1)
	0x75, 0x05,        //     Report Size (5)
	0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
	0x09, 0x30,        //     Usage (X)
	0x09, 0x31,        //     Usage (Y)
	0x09, 0x38,        //     Usage (Wheel)
	0x15, 0x81,        //     Logical Minimum (-127)
	0x25, 0x7F,        //     Logical Maximum (127)
	0x75, 0x08,        //     Report Size (8)
	0x95, 0x03,        //     Report Count (3)
	0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,              //   End Collection

	0x09, 0x3C,        //   Usage (Motion Wakeup)
	0x05, 0xFF,        //   Usage Page (Reserved 0xFF)
	0x09, 0x01,        //   Usage (0x01)
	0x15, 0x00,        //   Logical Minimum (0)
	0x25, 0x01,        //   Logical Maximum (1)
	0x75, 0x01,        //   Report Size (1)
	0x95, 0x02,        //   Report Count (2)
	0xB1, 0x22,        //   Feature (Data,Var,Abs,No Wrap,Linear,No Preferred State,No Null Position,Non-volatile)
	0x75, 0x06,        //   Report Size (6)
	0x95, 0x01,        //   Report Count (1)
	0xB1, 0x01,        //   Feature (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

	0xC0,              // End Collection
};

#endif

#ifdef PTP
__ALIGN_BEGIN static uint8_t HID_MOUSE_ReportDesc[HID_MOUSE_REPORT_DESC_SIZE]  __ALIGN_END =
{
		0x05, 0x0D,        // Usage Page (Digitizer)
		0x09, 0x05,        // Usage (Touch Pad)
		0xA1, 0x01,        // Collection (Application)

		0x85, 0x01,        //   Report ID (1)
		0x09, 0x22,        //   Usage (Finger)
		0xA1, 0x02,        //   Collection (Logical)
		0x15, 0x00,        //     Logical Minimum (0)
		0x25, 0x01,        //     Logical Maximum (1)

		0x09, 0x47,        //     Usage (Confidence)

		0x09, 0x42,        //     Usage (Tip Switch)
		0x95, 0x02,        //     Report Count (2)
		0x75, 0x01,        //     Report Size (1)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x95, 0x01,        //     Report Count (1)
		0x75, 0x02,        //     Report Size (2)
		0x25, 0x02,        //     Logical Maximum (2)

		0x09, 0x51,        //     Usage (Contact Identifier)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x75, 0x01,        //     Report Size (1)
		0x95, 0x04,        //     Report Count (4)
		0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

		0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
		0x15, 0x00,        //     Logical Minimum (0)
		0x26, 0xFF, 0x0F,  //     Logical Maximum (4095)
		0x75, 0x10,        //     Report Size (16)
		0x55, 0x0E,        //     Unit Exponent (-2)
		0x65, 0x13,        //     Unit (System: English Linear, Length: Centimeter)

		0x09, 0x30,        //     Usage (X)
		0x35, 0x00,        //     Physical Minimum (0)
		0x46, 0x90, 0x01,  //     Physical Maximum (400)
		0x95, 0x01,        //     Report Count (1)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x46, 0x13, 0x01,  //     Physical Maximum (275)

		0x09, 0x31,        //     Usage (Y)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0xC0,              //   End Collection

		0x55, 0x0C,        //   Unit Exponent (-4)
		0x66, 0x01, 0x10,  //   Unit (System: SI Linear, Time: Seconds)
		0x47, 0xFF, 0xFF, 0x00, 0x00,  //   Physical Maximum (65534)
		0x27, 0xFF, 0xFF, 0x00, 0x00,  //   Logical Maximum (65534)
		0x75, 0x10,        //   Report Size (16)
		0x95, 0x01,        //   Report Count (1)

		0x05, 0x0D,        //   Usage Page (Digitizer)
		0x09, 0x56,        //   Usage (Scan Time)
		0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x09, 0x54,        //   Usage (Contact count)
		0x25, 0x7F,        //   Logical Maximum (127)
		0x95, 0x01,        //   Report Count (1)
		0x75, 0x08,        //   Report Size (8)
		0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

		0x05, 0x09,        //   Usage Page (Button)
		0x09, 0x01,        //   Usage (Button 1)
		0x25, 0x01,        //   Logical Maximum (1)
		0x75, 0x01,        //   Report Size (1)
		0x95, 0x01,        //   Report Count (1)
		0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x95, 0x07,        //   Report Count (7)
		0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)

		0x05, 0x0D,        //   Usage Page (Digitizer)
		0x85, 0x02,        //   Report ID (2)	// Feature
		0x09, 0x55,        //   Usage (Contact Count Maximum)
		0x09, 0x59,        //   Usage (Pad TYpe)
		0x75, 0x04,        //   Report Size (4)
		0x95, 0x02,        //   Report Count (2)
		0x25, 0x0F,        //   Logical Maximum (15)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
		0x85, 0x03,        //   Report ID (3)	// PTPHQA
		0x09, 0xC5,        //   Usage (Vendor Usage 0xC5)
		0x15, 0x00,        //   Logical Minimum (0)
		0x26, 0xFF, 0x00,  //   Logical Maximum (255)
		0x75, 0x08,        //   Report Size (8)
		0x96, 0x00, 0x01,  //   Report Count (256)
		0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)

		0xC0,              // End Collection

//**************************************************
		0x05, 0x0D,        // Usage Page (Digitizer)

		0x09, 0x0E,        // Usage (Configuration)
		0xA1, 0x01,        // Collection (Application)
		0x85, 0x04,        //   Report ID (4)	// feature
		0x09, 0x22,        //   Usage (Finger)
		0xA1, 0x02,        //   Collection (Logical)
		0x09, 0x52,        //     Usage (0x52)
		0x15, 0x00,        //     Logical Minimum (0)
		0x25, 0x0A,        //     Logical Maximum (10)
		0x75, 0x08,        //     Report Size (8)
		0x95, 0x01,        //     Report Count (1)
		0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
		0xC0,              //   End Collection

		0x09, 0x22,        //   Usage (Finger)
		0xA1, 0x00,        //   Collection (Physical)
		0x85, 0x05,        //     Report ID (5)	// feature
		0x09, 0x57,        //     Usage (Surface switch)
		0x09, 0x58,        //     Usage (Button switch)
		0x75, 0x01,        //     Report Size (1)
		0x95, 0x02,        //     Report Count (2)
		0x25, 0x01,        //     Logical Maximum (1)
		0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
		0x95, 0x06,        //     Report Count (6)
		0xB1, 0x03,        //     Feature (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
		0xC0,              //   End Collection

		0xC0,              // End Collection

//**************************************************
		0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
		0x09, 0x02,        // Usage (Mouse)
		0xA1, 0x01,        // Collection (Application)

			0x85, 0x06,        //   Report ID (6)
			0x09, 0x01,        //   Usage (Pointer)
			0xA1, 0x00,        //   Collection (Physical)

			0x05, 0x09,        //     Usage Page (Button)
			0x19, 0x01,        //     Usage Minimum (0x01)
			0x29, 0x02,        //     Usage Maximum (0x02)
			0x25, 0x01,        //     Logical Maximum (1)
			0x75, 0x01,        //     Report Size (1)
			0x95, 0x02,        //     Report Count (2)
			0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
			0x95, 0x06,        //     Report Count (6)
			//0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
			0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

			0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
			0x09, 0x30,        //     Usage (X)
			0x09, 0x31,        //     Usage (Y)
			0x75, 0x08,        //     Report Size (8)
			0x95, 0x02,        //     Report Count (2)
			0x15, 0x81,        //     Logical Minimum (-127)
			0x25, 0x7F,        //     Logical Maximum (127)
			0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)

			0xC0,              //   End Collection
		0xC0,              // End Collection

#if 0
		0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
		0x09, 0x02,        // Usage (Mouse)
		0xA1, 0x01,        // Collection (Application)

		0x09, 0x01,        //   Usage (Pointer)
		0xA1, 0x00,        //   Collection (Physical)
#if 0
		0x05, 0x09,        //     Usage Page (Button)
		0x19, 0x01,        //     Usage Minimum (0x01)
		0x29, 0x03,        //     Usage Maximum (0x03)
		0x15, 0x00,        //     Logical Minimum (0)
		0x25, 0x01,        //     Logical Maximum (1)
		0x95, 0x03,        //     Report Count (3)
		0x75, 0x01,        //     Report Size (1)
		0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
		0x95, 0x01,        //     Report Count (1)
		0x75, 0x05,        //     Report Size (5)
		0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
#endif
		0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
		0x09, 0x30,        //     Usage (X)
		0x09, 0x31,        //     Usage (Y)
		//0x09, 0x38,        //     Usage (Wheel)
		0x15, 0x81,        //     Logical Minimum (-127)
		0x25, 0x7F,        //     Logical Maximum (127)
		0x75, 0x10,        //     Report Size (16)
		//0x95, 0x03,        //     Report Count (3)
		0x95, 0x02,        //     Report Count (2)
		0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)

		0xC0,              //   End Collection
#if 0
		0x09, 0x3C,        //   Usage (Motion Wakeup)
		0x05, 0xFF,        //   Usage Page (Reserved 0xFF)
		0x09, 0x01,        //   Usage (0x01)
		0x15, 0x00,        //   Logical Minimum (0)
		0x25, 0x01,        //   Logical Maximum (1)
		0x75, 0x01,        //   Report Size (1)
		0x95, 0x02,        //   Report Count (2)
		0xB1, 0x22,        //   Feature (Data,Var,Abs,No Wrap,Linear,No Preferred State,No Null Position,Non-volatile)
		0x75, 0x06,        //   Report Size (6)
		0x95, 0x01,        //   Report Count (1)
		0xB1, 0x01,        //   Feature (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
#endif
		0xC0,              // End Collection

#if 0
	0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
	0x09, 0x02,        // Usage (Mouse)
	0xA1, 0x01,        // Collection (Application)
	0x09, 0x01,        //   Usage (Pointer)
	0xA1, 0x00,        //   Collection (Physical)

	0x05, 0x09,        //     Usage Page (Button)
	0x19, 0x01,        //     Usage Minimum (0x01)
	0x29, 0x03,        //     Usage Maximum (0x03)
	0x15, 0x00,        //     Logical Minimum (0)
	0x25, 0x01,        //     Logical Maximum (1)
	0x95, 0x03,        //     Report Count (3)
	0x75, 0x01,        //     Report Size (1)
	0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
	0x95, 0x01,        //     Report Count (1)
	0x75, 0x05,        //     Report Size (5)
	0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)

	0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
	0x09, 0x30,        //     Usage (X)
	0x09, 0x31,        //     Usage (Y)
	//0x09, 0x38,        //     Usage (Wheel)
//	0x15, 0x81,        //     Logical Minimum (-127)
//	0x25, 0x7F,        //     Logical Maximum (127)
//	0x75, 0x08,        //     Report Size (8)
	0x75, 0x10,        //     Report Size (16)
//	0x95, 0x03,        //     Report Count (3)
	0x95, 0x02,        //     Report Count (2)
    0x25, 0x0a,        //    LOGICAL_MAXIMUM (10)
	0x81, 0x06,        //     Input (Data,Var,Rel,No Wrap,Linear,Preferred State,No Null Position)
	0xC0,              //   End Collection
/*
	0x09, 0x3C,        //   Usage (Motion Wakeup)
	0x05, 0xFF,        //   Usage Page (Reserved 0xFF)
	0x09, 0x01,        //   Usage (0x01)
	0x15, 0x00,        //   Logical Minimum (0)
	0x25, 0x01,        //   Logical Maximum (1)
	0x75, 0x01,        //   Report Size (1)
	0x95, 0x02,        //   Report Count (2)
	0xB1, 0x22,        //   Feature (Data,Var,Abs,No Wrap,Linear,No Preferred State,No Null Position,Non-volatile)
	0x75, 0x06,        //   Report Size (6)
	0x95, 0x01,        //   Report Count (1)
	0xB1, 0x01,        //   Feature (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
*/
	0xC0              // End Collection
#endif
/*
  0x05,   0x01,
  0x09,   0x02,
  0xA1,   0x01,
  0x09,   0x01,

  0xA1,   0x00,
  0x05,   0x09,
  0x19,   0x01,
  0x29,   0x03,

  0x15,   0x00,
  0x25,   0x01,
  0x95,   0x03,
  0x75,   0x01,

  0x81,   0x02,
  0x95,   0x01,
  0x75,   0x05,
  0x81,   0x01,

  0x05,   0x01,
  0x09,   0x30,
  0x09,   0x31,
  0x09,   0x38,

  0x15,   0x81,
  0x25,   0x7F,
  0x75,   0x08,
  0x95,   0x03,

  0x81,   0x06,
  0xC0,   0x09,
  0x3c,   0x05,
  0xff,   0x09,

  0x01,   0x15,
  0x00,   0x25,
  0x01,   0x75,
  0x01,   0x95,

  0x02,   0xb1,
  0x22,   0x75,
  0x06,   0x95,
  0x01,   0xb1,

  0x01,   0xc0
  */
#endif
};
#endif
