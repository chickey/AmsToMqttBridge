#ifndef _AMSDATA_H
#define _AMSDATA_H

#include "Arduino.h"
#include <Timezone.h>

enum AmsType {
    AmsTypeAutodetect = 0x00,
    AmsTypeAidon = 0x01,
    AmsTypeKaifa = 0x02,
    AmsTypeKamstrup = 0x03,
    AmsTypeIskra = 0x08,
    AmsTypeLandis = 0x09,
    AmsTypeSagemcom = 0x0A,
    AmsTypeCustom = 0x88,
    AmsTypeUnknown = 0xFF
};

class AmsData {
public:
    AmsData();

    void apply(AmsData& other);

    unsigned long getLastUpdateMillis();

    time_t getPackageTimestamp();

    uint8_t getListType();

    String getListId();
    String getMeterId();
    uint8_t getMeterType();
    String getMeterModel();

    time_t getMeterTimestamp();

    uint16_t getActiveImportPower();
    uint16_t getReactiveImportPower();
    uint16_t getActiveExportPower();
    uint16_t getReactiveExportPower();

    float getL1Voltage();
    float getL2Voltage();
    float getL3Voltage();

    float getL1Current();
    float getL2Current();
    float getL3Current();

    float getPowerFactor();
    float getL1PowerFactor();
    float getL2PowerFactor();
    float getL3PowerFactor();

    double getActiveImportCounter();
    double getReactiveImportCounter();
    double getActiveExportCounter();
    double getReactiveExportCounter();

    bool isThreePhase();
    bool isTwoPhase();

protected:
    unsigned long lastUpdateMillis = 0;
    unsigned long lastList2 = 0;
    uint8_t listType = 0, meterType = AmsTypeUnknown;
    time_t packageTimestamp = 0;
    String listId, meterId, meterModel;
    time_t meterTimestamp = 0;
    uint16_t activeImportPower = 0, reactiveImportPower = 0, activeExportPower = 0, reactiveExportPower = 0;
    float l1voltage = 0, l2voltage = 0, l3voltage = 0, l1current = 0, l2current = 0, l3current = 0;
    float powerFactor = 0, l1PowerFactor = 0, l2PowerFactor = 0, l3PowerFactor = 0;
    double activeImportCounter = 0, reactiveImportCounter = 0, activeExportCounter = 0, reactiveExportCounter = 0;
    bool threePhase = false, twoPhase = false, counterEstimated = false;
};

#endif
