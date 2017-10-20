/* COPYRIGHT (c) 2016-2017 Nova Labs SRL
 *
 * All rights reserved. All use of this software and documentation is
 * subject to the License Agreement located in the file LICENSE.
 */

#include <core/DRV8801_driver/DRV8801.hpp>
#include <Module.hpp>

namespace core {
namespace DRV8801_driver {
DRV8801::DRV8801(
        core::hw::PWMMaster&   pwm,
        core::hw::PWMChannel&  enable,
        core::hw::Pad&         phase,
        core::hw::Pad&         mode1,
        core::hw::Pad&         sleep,
        core::hw::Pad&         fault
) : _pwm(pwm), _enable(enable), _phase(phase), _mode1(mode1), _sleep(sleep), _fault(fault) {}

DRV8801_SignMagnitude::DRV8801_SignMagnitude(
    const char* name,
    DRV8801&    device
) : _device(device) {}

DRV8801::~DRV8801()
{}

DRV8801_SignMagnitude::~DRV8801_SignMagnitude()
{}

bool
DRV8801::probe()
{
    return true;
}

bool
DRV8801_SignMagnitude::init()
{
    _device._sleep.clear();
    _device._mode1.set();

    return true;
}

bool
DRV8801_SignMagnitude::configure()
{
    return true;
}

bool
DRV8801_SignMagnitude::start()
{
    _device._sleep.set();

    return true;
}

bool
DRV8801_SignMagnitude::stop()
{
    _device._sleep.clear();

    return true;
}

bool
DRV8801_SignMagnitude::set(
    const DataType& data
)
{
    int32_t PWM_MAX = _device._pwm.getPeriod();

    int32_t pwm = data * PWM_MAX;

    if (pwm > PWM_MAX) {
        pwm = PWM_MAX;
    } else if (pwm <= -PWM_MAX) {
        pwm = -PWM_MAX;
    }

    if (pwm >= 0) {
        _device._phase.set();
        _device._enable.set(pwm);
    } else {
        _device._phase.clear();
        _device._enable.set(-pwm);
    }

    return true;
}

bool
DRV8801_SignMagnitude::setI(
    const DataType& data
)
{
    int32_t PWM_MAX = _device._pwm.getPeriod();

    int32_t pwm = data * PWM_MAX;

    if (pwm > PWM_MAX) {
        pwm = PWM_MAX;
    } else if (pwm <= -PWM_MAX) {
        pwm = -PWM_MAX;
    }

    if (pwm >= 0) {
        _device._phase.set();
        _device._enable.setI(pwm);
    } else {
        _device._phase.clear();
        _device._enable.setI(-pwm);
    }

    return true;
}

bool
DRV8801_SignMagnitude::waitUntilReady()
{
    return true;
}
}
}
