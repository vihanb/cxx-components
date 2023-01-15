#pragma once

#include <hap.h>
#include <string>
#include <vector>
#include <memory>

#include "homekit_service.hpp"

namespace HomeKit {

class HomeKit;

class Accessory {
private:
    hap_acc_t *accessory;
    std::string debugIdentifier;
    hap_cid_t _cid;

    std::vector<std::unique_ptr<Service>> services;

    static int identifyRoutine(hap_acc_t *acc);

    friend class HomeKit;
public:
    /**
     * @brief Construct a new Accessory object
     * 
     * @param name 
     * @param model 
     * @param serial 
     * @param fwRev Firmware Revision
     * @param hwRev Hardware Revision
     * @param cid Accessory type ID.
     */
    explicit Accessory(
        const std::string &name,
        const std::string &model,
        const std::string &serial,
        const std::string &fwRev,
        const std::string &hwRev,
        hap_cid_t cid
    );
    
    Accessory(Accessory&&);

    Accessory() = delete;
    Accessory(const Accessory&) = delete;

    ~Accessory();

    void addService(Service *service);

    /**
     * Adds the accessory to HomeKit.
     */
    void start();
};

}