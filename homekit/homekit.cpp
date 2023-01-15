#include "homekit.hpp"
#include <esp_log.h>
#include <qrcode.hpp>

static const char *TAG = "HomeKit";

using namespace qrcode;

namespace HomeKit {

HomeKit::HomeKit(const char *setupCode, const char *setupId)
    : _setupCode(setupCode),
      _setupId(setupId) {}

HomeKit::~HomeKit() {
    hap_stop();
    hap_deinit();
}

void HomeKit::init() {
    hap_init(HAP_TRANSPORT_WIFI);

    hap_set_setup_code(_setupCode.data());
    hap_set_setup_id(_setupId.data());
}

void HomeKit::start() {
    for (const auto& accessory : accessories) {
        accessory->start();
    }

    hap_start();
    ESP_LOGI(TAG, "Started HomeKit module.");
}

bool HomeKit::isProbablyPaired() const {
    return hap_get_paired_controller_count() > 0;
}

void HomeKit::printQRCode() {
    if (accessories.empty()) {
        ESP_LOGE(TAG, "Cannot print QR code. No registered accessories");
        return;
    }

    auto &acc = accessories.front();

    char *setup_payload = esp_hap_get_setup_payload(
            _setupCode.data(), _setupId.data(), false, acc->_cid);
    QrCode setup_qrcode = QrCode::encodeText(setup_payload, QrCode::Ecc::LOW);
    setup_qrcode.print();
}

}