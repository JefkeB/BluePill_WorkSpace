/**
  ******************************************************************************
  * @file    usbd_hid.c
  * @author  MCD Application Team
  * @version V2.4.2
  * @date    11-December-2015
  * @brief   This file provides the HID core functions.
  *
  * @verbatim
  *      
  *          ===================================================================      
  *                                HID Class  Description
  *          =================================================================== 
  *           This module manages the HID class V1.11 following the "Device Class Definition
  *           for Human Interface Devices (HID) Version 1.11 Jun 27, 2001".
  *           This driver implements the following aspects of the specification:
  *             - The Boot Interface Subclass
  *             - The Mouse protocol
  *             - Usage Page : Generic Desktop
  *             - Usage : Joystick
  *             - Collection : Application 
  *      
  * @note     In HS mode and when the DMA is used, all variables and data structures
  *           dealing with the DMA during the transaction process should be 32-bit aligned.
  *           
  *      
  *  @endverbatim
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "usbd_hid_ptp.h"

#include "usbd_desc.h"
#include "usbd_ctlreq.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup USBD_HID 
  * @brief usbd core module
  * @{
  */ 

/** @defgroup USBD_HID_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Defines
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup USBD_HID_Private_FunctionPrototypes
  * @{
  */


static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx);

static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx);

static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req);

static uint8_t  *USBD_HID_GetCfgDesc (uint16_t *length);

static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length);

static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, uint8_t epnum);
/**
  * @}
  */ 



/** @defgroup USBD_HID_Private_Variables
  * @{
  */

USBD_ClassTypeDef  USBD_HID =
{
  USBD_HID_Init,
  USBD_HID_DeInit,
  USBD_HID_Setup,
  NULL, /*EP0_TxSent*/
  NULL, /*EP0_RxReady*/
  USBD_HID_DataIn, /*DataIn*/
  NULL, /*DataOut*/
  NULL, /*SOF */
  NULL,
  NULL,
  USBD_HID_GetCfgDesc,
  USBD_HID_GetCfgDesc,
  USBD_HID_GetCfgDesc,
  USBD_HID_GetDeviceQualifierDesc,
};


// values for the Report id's in the report descriptor
#define REPORT_ID_MOUSE					1
#define REPORTID_MAX_COUNT				2
#define REPORTID_REPORTINGMODE			3
#define REPORTID_TOUCHPAD				4
#define REPORTID_FUNCTION_SWITCH		5
#define REPORTID_PTPHQA					6
#define REPORTID_LATENCY				7
//#define REPORT_ID_
//#define REPORT_ID_
//#define REPORT_ID_
#define REPORTID_VENDOR_C7				11
#define	REPORTID_VENDOR_USAGE_SEGMENT	12
#define	REPORTID_VENDOR_C4				13

#define FEATURE_BUILD(x)				(0x0300 + x)


//
//
//
#define HID_PTP_REPORT_DESC_SIZE 		(738)
__ALIGN_BEGIN static uint8_t HID_PTP_ReportDesc[HID_PTP_REPORT_DESC_SIZE]  __ALIGN_END =
{
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


// https://docs.microsoft.com/en-us/windows-hardware/design/component-guidelines/touch-and-pen-support
//
//
const uint8_t touchQualityKey[] = {
    REPORTID_PTPHQA,
	0xfc, 0x28, 0xfe, 0x84, 0x40, 0xcb, 0x9a, 0x87, 0x0d, 0xbe, 0x57, 0x3c, 0xb6, 0x70, 0x09, 0x88,
	0x07, 0x97, 0x2d, 0x2b, 0xe3, 0x38, 0x34, 0xb6, 0x6c, 0xed, 0xb0, 0xf7, 0xe5, 0x9c, 0xf6, 0xc2,
	0x2e, 0x84, 0x1b, 0xe8, 0xb4, 0x51, 0x78, 0x43, 0x1f, 0x28, 0x4b, 0x7c, 0x2d, 0x53, 0xaf, 0xfc,
	0x47, 0x70, 0x1b, 0x59, 0x6f, 0x74, 0x43, 0xc4, 0xf3, 0x47, 0x18, 0x53, 0x1a, 0xa2, 0xa1, 0x71,
	0xc7, 0x95, 0x0e, 0x31, 0x55, 0x21, 0xd3, 0xb5, 0x1e, 0xe9, 0x0c, 0xba, 0xec, 0xb8, 0x89, 0x19,
	0x3e, 0xb3, 0xaf, 0x75, 0x81, 0x9d, 0x53, 0xb9, 0x41, 0x57, 0xf4, 0x6d, 0x39, 0x25, 0x29, 0x7c,
	0x87, 0xd9, 0xb4, 0x98, 0x45, 0x7d, 0xa7, 0x26, 0x9c, 0x65, 0x3b, 0x85, 0x68, 0x89, 0xd7, 0x3b,
	0xbd, 0xff, 0x14, 0x67, 0xf2, 0x2b, 0xf0, 0x2a, 0x41, 0x54, 0xf0, 0xfd, 0x2c, 0x66, 0x7c, 0xf8,
	0xc0, 0x8f, 0x33, 0x13, 0x03, 0xf1, 0xd3, 0xc1, 0x0b, 0x89, 0xd9, 0x1b, 0x62, 0xcd, 0x51, 0xb7,
	0x80, 0xb8, 0xaf, 0x3a, 0x10, 0xc1, 0x8a, 0x5b, 0xe8, 0x8a, 0x56, 0xf0, 0x8c, 0xaa, 0xfa, 0x35,
	0xe9, 0x42, 0xc4, 0xd8, 0x55, 0xc3, 0x38, 0xcc, 0x2b, 0x53, 0x5c, 0x69, 0x52, 0xd5, 0xc8, 0x73,
	0x02, 0x38, 0x7c, 0x73, 0xb6, 0x41, 0xe7, 0xff, 0x05, 0xd8, 0x2b, 0x79, 0x9a, 0xe2, 0x34, 0x60,
	0x8f, 0xa3, 0x32, 0x1f, 0x09, 0x78, 0x62, 0xbc, 0x80, 0xe3, 0x0f, 0xbd, 0x65, 0x20, 0x08, 0x13,
	0xc1, 0xe2, 0xee, 0x53, 0x2d, 0x86, 0x7e, 0xa7, 0x5a, 0xc5, 0xd3, 0x7d, 0x98, 0xbe, 0x31, 0x48,
	0x1f, 0xfb, 0xda, 0xaf, 0xa2, 0xa8, 0x6a, 0x89, 0xd6, 0xbf, 0xf2, 0xd3, 0x32, 0x2a, 0x9a, 0xe4,
	0xcf, 0x17, 0xb7, 0xb8, 0xf4, 0xe1, 0x33, 0x08, 0x24, 0x8b, 0xc4, 0x43, 0xa5, 0xe5, 0x24, 0xc2
};

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_CfgDesc[USB_HID_CONFIG_DESC_SIZ]  __ALIGN_END =
{
  0x09, /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION, /* bDescriptorType: Configuration */
  USB_HID_CONFIG_DESC_SIZ,
  /* wTotalLength: Bytes returned */
  0x00,
  0x01,         /*bNumInterfaces: 1 interface*/
  0x01,         /*bConfigurationValue: Configuration value*/
  0x00,         /*iConfiguration: Index of string descriptor describing
  the configuration*/
  0xE0,         /*bmAttributes: bus powered and Support Remote Wake-up */
  0x32,         /*MaxPower 100 mA: this current is used for detecting Vbus*/
  
  /************** Descriptor of Joystick Mouse interface ****************/
  /* 09 */
  0x09,         /*bLength: Interface Descriptor size*/
  USB_DESC_TYPE_INTERFACE,/*bDescriptorType: Interface descriptor type*/
  0x00,         /*bInterfaceNumber: Number of Interface*/
  0x00,         /*bAlternateSetting: Alternate setting*/
  0x01,         /*bNumEndpoints*/
  0x03,         /*bInterfaceClass: HID*/
  0x01,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
  0x02,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
  0,            /*iInterface: Index of string descriptor*/
  /******************** Descriptor of Joystick Mouse HID ********************/
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  (HID_PTP_REPORT_DESC_SIZE & 0xFF),		/*wItemLength: Total length of Report descriptor*/
  (HID_PTP_REPORT_DESC_SIZE >> 8) & 0xFF,
  /******************** Descriptor of Mouse endpoint ********************/
  /* 27 */
  0x07,          /*bLength: Endpoint Descriptor size*/
  USB_DESC_TYPE_ENDPOINT, /*bDescriptorType:*/
  
  HID_EPIN_ADDR,     /*bEndpointAddress: Endpoint Address (IN)*/
  0x03,          /*bmAttributes: Interrupt endpoint*/
  HID_EPIN_SIZE, /*wMaxPacketSize: 4 Byte max */
  0x00,
  HID_FS_BINTERVAL,          /*bInterval: Polling Interval (10 ms)*/
  /* 34 */
} ;

/* USB HID device Configuration Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_Desc[USB_HID_DESC_SIZ]  __ALIGN_END  =
{
  /* 18 */
  0x09,         /*bLength: HID Descriptor size*/
  HID_DESCRIPTOR_TYPE, /*bDescriptorType: HID*/
  0x11,         /*bcdHID: HID Class Spec release number*/
  0x01,
  0x00,         /*bCountryCode: Hardware target country*/
  0x01,         /*bNumDescriptors: Number of HID class descriptors to follow*/
  0x22,         /*bDescriptorType*/
  (HID_PTP_REPORT_DESC_SIZE & 0xFF),/*wItemLength: Total length of Report descriptor*/
  (HID_PTP_REPORT_DESC_SIZE >> 8) & 0xFF,
};

/* USB Standard Device Descriptor */
__ALIGN_BEGIN static uint8_t USBD_HID_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC]  __ALIGN_END =
{
  USB_LEN_DEV_QUALIFIER_DESC,
  USB_DESC_TYPE_DEVICE_QUALIFIER,
  0x00,
  0x02,
  0x00,
  0x00,
  0x00,
  0x40,
  0x01,
  0x00,
};


/**
  * @}
  */ 

/** @defgroup USBD_HID_Private_Functions
  * @{
  */ 

/**
  * @brief  USBD_HID_Init
  *         Initialize the HID interface
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_Init (USBD_HandleTypeDef *pdev, 
                               uint8_t cfgidx)
{
  uint8_t ret = 0;
  
  /* Open EP IN */
  USBD_LL_OpenEP(pdev,
                 HID_EPIN_ADDR,
                 USBD_EP_TYPE_INTR,
                 HID_EPIN_SIZE);  
  
  pdev->pClassData = USBD_malloc(sizeof (USBD_HID_HandleTypeDef));
  
  if(pdev->pClassData == NULL)
  {
    ret = 1; 
  }
  else
  {
    ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  }
  return ret;
}

/**
  * @brief  USBD_HID_Init
  *         DeInitialize the HID layer
  * @param  pdev: device instance
  * @param  cfgidx: Configuration index
  * @retval status
  */
static uint8_t  USBD_HID_DeInit (USBD_HandleTypeDef *pdev, 
                                 uint8_t cfgidx)
{
  /* Close HID EPs */
  USBD_LL_CloseEP(pdev,
                  HID_EPIN_ADDR);
  
  /* FRee allocated memory */
  if(pdev->pClassData != NULL)
  {
    USBD_free(pdev->pClassData);
    pdev->pClassData = NULL;
  } 
  
  return USBD_OK;
}

/**
  * @brief  USBD_HID_Setup
  *         Handle the HID specific requests
  * @param  pdev: instance
  * @param  req: usb requests
  * @retval status
  */
static uint8_t  USBD_HID_Setup (USBD_HandleTypeDef *pdev, 
                                USBD_SetupReqTypedef *req)
{
  uint16_t len = 0;
  uint8_t  *pbuf = NULL;
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*) pdev->pClassData;
  
  switch (req->bmRequest & USB_REQ_TYPE_MASK)
  {
  case USB_REQ_TYPE_CLASS :  
    switch (req->bRequest)
    {
      
      
    case HID_REQ_SET_PROTOCOL:
      hhid->Protocol = (uint8_t)(req->wValue);
      break;
      
    case HID_REQ_GET_PROTOCOL:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&hhid->Protocol,
                        1);    
      break;
      
    case HID_REQ_SET_IDLE:
      hhid->IdleState = (uint8_t)(req->wValue >> 8);
      break;
      
    case HID_REQ_GET_IDLE:
      USBD_CtlSendData (pdev, 
                        (uint8_t *)&hhid->IdleState,
                        1);        
      break;      
      
    default:
      USBD_CtlError (pdev, req);
      return USBD_FAIL; 
    }
    break;
    
  case USB_REQ_TYPE_STANDARD:
    switch (req->bRequest)
    {
    case USB_REQ_GET_DESCRIPTOR: 
      if( req->wValue >> 8 == HID_REPORT_DESC)
      {
        len = MIN(HID_PTP_REPORT_DESC_SIZE , req->wLength);
        pbuf = HID_PTP_ReportDesc;
      }
      else if( req->wValue >> 8 == HID_DESCRIPTOR_TYPE)
      {
        pbuf = USBD_HID_Desc;   
        len = MIN(USB_HID_DESC_SIZ , req->wLength);
      }
      
      USBD_CtlSendData (pdev, 
                        pbuf,
                        len);
      
      break;
      
    case USB_REQ_GET_INTERFACE :
      USBD_CtlSendData (pdev,
                        (uint8_t *)&hhid->AltSetting,
                        1);
      break;
      
    case USB_REQ_SET_INTERFACE :
      hhid->AltSetting = (uint8_t)(req->wValue);
      break;
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_SendReport 
  *         Send HID Report
  * @param  pdev: device instance
  * @param  buff: pointer to report
  * @retval status
  */
uint8_t USBD_HID_SendReport     (USBD_HandleTypeDef  *pdev, 
                                 uint8_t *report,
                                 uint16_t len)
{
  USBD_HID_HandleTypeDef     *hhid = (USBD_HID_HandleTypeDef*)pdev->pClassData;
  
  if (pdev->dev_state == USBD_STATE_CONFIGURED )
  {
    if(hhid->state == HID_IDLE)
    {
      hhid->state = HID_BUSY;
      USBD_LL_Transmit (pdev, 
                        HID_EPIN_ADDR,                                      
                        report,
                        len);
    }
  }
  return USBD_OK;
}

/**
  * @brief  USBD_HID_GetPollingInterval 
  *         return polling interval from endpoint descriptor
  * @param  pdev: device instance
  * @retval polling interval
  */
uint32_t USBD_HID_GetPollingInterval (USBD_HandleTypeDef *pdev)
{
  uint32_t polling_interval = 0;

  /* HIGH-speed endpoints */
  if(pdev->dev_speed == USBD_SPEED_HIGH)
  {
   /* Sets the data transfer polling interval for high speed transfers. 
    Values between 1..16 are allowed. Values correspond to interval 
    of 2 ^ (bInterval-1). This option (8 ms, corresponds to HID_HS_BINTERVAL */
    polling_interval = (((1 <<(HID_HS_BINTERVAL - 1)))/8);
  }
  else   /* LOW and FULL-speed endpoints */
  {
    /* Sets the data transfer polling interval for low and full 
    speed transfers */
    polling_interval =  HID_FS_BINTERVAL;
  }
  
  return ((uint32_t)(polling_interval));
}

/**
  * @brief  USBD_HID_GetCfgDesc 
  *         return configuration descriptor
  * @param  speed : current device speed
  * @param  length : pointer data length
  * @retval pointer to descriptor buffer
  */
static uint8_t  *USBD_HID_GetCfgDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_CfgDesc);
  return USBD_HID_CfgDesc;
}


/**
  * @brief  USBD_HID_DataIn
  *         handle data IN Stage
  * @param  pdev: device instance
  * @param  epnum: endpoint index
  * @retval status
  */
static uint8_t  USBD_HID_DataIn (USBD_HandleTypeDef *pdev, 
                              uint8_t epnum)
{
  
  /* Ensure that the FIFO is empty before a new transfer, this condition could 
  be caused by  a new transfer before the end of the previous transfer */
  ((USBD_HID_HandleTypeDef *)pdev->pClassData)->state = HID_IDLE;
  return USBD_OK;
}


/**
* @brief  DeviceQualifierDescriptor 
*         return Device Qualifier descriptor
* @param  length : pointer data length
* @retval pointer to descriptor buffer
*/
static uint8_t  *USBD_HID_GetDeviceQualifierDesc (uint16_t *length)
{
  *length = sizeof (USBD_HID_DeviceQualifierDesc);
  return USBD_HID_DeviceQualifierDesc;
}

/**
  * @}
  */ 


/**
  * @}
  */ 


/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
