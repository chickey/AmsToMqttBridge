#ifndef _HDLC_H
#define _HDLC_H

#include "Arduino.h"
#include <stdint.h>
#include "lwip/def.h"

#define HDLC_FLAG 0x7E
#define HDLC_BOUNDRY_FLAG_MISSING -1
#define HDLC_FCS_ERROR -2
#define HDLC_HCS_ERROR -3
#define HDLC_FRAME_INCOMPLETE -4
#define HDLC_UNKNOWN_DATA -9
#define HDLC_ENCRYPTION_CONFIG_MISSING -90
#define HDLC_ENCRYPTION_AUTH_FAILED -91
#define HDLC_ENCRYPTION_KEY_FAILED -92
#define HDLC_ENCRYPTION_DECRYPT_FAILED -93
#define HDLC_TIMESTAMP_UNKNOWN -99

#define MBUS_START 0x68
#define MBUS_END 0x16
#define MBUS_BOUNDRY_FLAG_MISSING -1
#define MBUS_FRAME_LENGTH_NOT_EQUAL -40
#define MBUS_FRAME_INTERMEDIATE_SEGMENT -41
#define MBUS_FRAME_LAST_SEGMENT -42
#define MBUS_CHECKSUM_ERROR -2

struct HDLCConfig {
    uint8_t encryption_key[32];
	uint8_t authentication_key[32];
	uint8_t system_title[8];
	uint8_t initialization_vector[12];
    uint8_t additional_authenticated_data[17];
    uint8_t authentication_tag[12];
};

typedef struct HDLCHeader {
	uint8_t  flag;
	uint16_t format;
} __attribute__((packed)) HDLCHeader;

typedef struct HDLCFooter {
	uint16_t fcs;
	uint8_t flag;
} __attribute__((packed)) HDLCFooter;

typedef struct HDLC3CtrlHcs {
    uint8_t control;
    uint16_t hcs;
} __attribute__((packed)) HDLC3CtrlHcs;

typedef struct HDLCLLC {
    uint8_t dst;
    uint8_t src;
    uint8_t control;
} __attribute__((packed)) HDLCLLC;

typedef struct HDLCADPU {
    uint8_t flag;
    uint32_t id;
} __attribute__((packed)) HDLCADPU;

typedef struct MbusHeader {
	uint8_t flag1;
	uint8_t len1;
	uint8_t len2;
	uint8_t flag2;
} __attribute__((packed)) MbusHeader;

typedef struct MbusFooter {
	uint8_t fcs;
	uint8_t flag;
} __attribute__((packed)) MbusFooter;


// Blue book, Table 2
enum CosemType {
    CosemTypeNull = 0x00,
    CosemTypeArray = 0x01,
    CosemTypeStructure = 0x02,
    CosemTypeOctetString = 0x09,
    CosemTypeString = 0x0A,
    CosemTypeDLongSigned = 0x05,
    CosemTypeDLongUnsigned = 0x06,
    CosemTypeLongSigned = 0x10,
    CosemTypeLongUnsigned = 0x12,
    CosemTypeLong64Signed = 0x14,
    CosemTypeLong64Unsigned = 0x15,
    CosemTypeDateTime = 0x19
};

struct CosemBasic {
    uint8_t type;
    uint8_t length;
} __attribute__((packed));

struct CosemString {
    uint8_t type;
    uint8_t length;
    uint8_t data[];
} __attribute__((packed));

struct CosemLongSigned {
    uint8_t type;
	int16_t data;
} __attribute__((packed));

struct CosemLongUnsigned {
    uint8_t type;
    uint16_t data;
} __attribute__((packed));

struct CosemDLongSigned {
    uint8_t type;
    int32_t data;
} __attribute__((packed));

struct CosemDLongUnsigned {
    uint8_t type;
    uint32_t data;
} __attribute__((packed));

struct CosemLong64Signed {
    uint8_t type;
    int64_t data;
} __attribute__((packed));

struct CosemLong64Unsigned {
    uint8_t type;
    uint64_t data;
} __attribute__((packed));

struct CosemDateTime {
    uint8_t type;
    uint16_t year;
    uint8_t month;
    uint8_t dayOfMonth;
    uint8_t dayOfWeek;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t hundredths;
    int16_t deviation;
    uint8_t status;
} __attribute__((packed));

typedef union {
    struct CosemBasic base;
	struct CosemString str;
	struct CosemString oct;
    struct CosemLongSigned ls;
	struct CosemLongUnsigned lu;
    struct CosemDLongSigned dls;
    struct CosemDLongUnsigned dlu;
    struct CosemLong64Signed l64s;
    struct CosemLong64Unsigned l64u;
    struct CosemDateTime dt;
} CosemData; 

void mbus_hexdump(const uint8_t* buf, int len);
int HDLC_validate(const uint8_t* d, int len, HDLCConfig* config, CosemDateTime* timestamp);

uint8_t mbusChecksum(const uint8_t* p, int len);

uint64_t ntohll(uint64_t x);

#endif
