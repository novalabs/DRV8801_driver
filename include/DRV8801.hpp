/* COPYRIGHT (c) 2016-2018 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#pragma once

#include <ModuleConfiguration.hpp>

#include <core/hw/PWM.hpp>
#include <core/hw/GPIO.hpp>
#include <core/utils/BasicActuator.hpp>

#include <core/common_msgs/Float32.hpp>

namespace core {
namespace DRV8801_driver {
class DRV8801
{
public:
    DRV8801(
            core::hw::PWMMaster&   pwm,
            core::hw::PWMChannel&  enable,
            core::hw::Pad&         phase,
            core::hw::Pad&         mode1,
            core::hw::Pad&         sleep,
            core::hw::Pad&         fault
    );

    virtual
    ~DRV8801();

public:
    bool
    probe();


public:
    core::hw::PWMMaster&   _pwm;
    core::hw::PWMChannel&  _enable;
    core::hw::Pad&        _phase;
    core::hw::Pad&        _mode1;
    core::hw::Pad&        _sleep;
    core::hw::Pad&        _fault;
};


class DRV8801_SignMagnitude:
    public core::utils::BasicActuator<float>
{
public:
    DRV8801_SignMagnitude(
        const char* name,
        DRV8801&    device
    );

    virtual
    ~DRV8801_SignMagnitude();

public:
    bool
    init();

    bool
    configure();

    bool
    start();

    bool
    stop();

    bool
    waitUntilReady();

    bool
    set(
        const DataType& data
    );

    bool
    setI(
        const DataType& data
    );


protected:
    core::os::Time _set_timestamp;

private:
    DRV8801& _device;

public:
    struct Converter {
        using TO   = float;
        using FROM = core::common_msgs::Float32;

        static inline TO
        _(
            const FROM& from
        )
        {
            return from.value;
        }
    };
};
}
}
