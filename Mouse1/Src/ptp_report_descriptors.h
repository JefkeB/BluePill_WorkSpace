#ifndef PTP_REPORT_DESCRIPTORS_H_
#define PTP_REPORT_DESCRIPTORS_H_


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


//extern const uint16_t HID_PTP_REPORT_DESC_SIZE;
#define HID_PTP_REPORT_DESC_SIZE 		(738)
extern const uint8_t HID_PTP_ReportDesc[];

#endif
