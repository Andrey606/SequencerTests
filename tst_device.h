#ifndef TST_DEVICE_H
#define TST_DEVICE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "device_manager/devices.h"

using namespace testing;

TEST(Device, DeviceInitialization)
{
    ASSERT_THAT(0, Device().get_device_mac());
    ASSERT_THAT(0, Device().get_device_short());
    ASSERT_THAT("", Device().get_device_name());
    ASSERT_THAT("", Device().get_device_type());
    ASSERT_THAT("", Device().get_device_second_type());
    ASSERT_THAT(0, Device().get_device_endpoint());
    // ASSERT_THAT(Device::eCommands::NO_ACTION, Device().get_device_command_general()); -> fixed (not critical)
}

TEST(Device, DeviceMyltiTypeDetection)
{
    Device *obj = new Device();
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    obj->set_device_endpoint(1);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    obj->set_device_short(0x5555);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());

    ASSERT_THAT(0, obj->set_device_name("omo.r.lampBro"));
    ASSERT_THAT("multiTypeDevice", obj->get_device_type());
    ASSERT_THAT(1, obj->multiDevice.endpoint.size());
    ASSERT_THAT(2, obj->multiDevice.endpoint[0]);
    ASSERT_THAT("Alarm", obj->multiDevice.DevicesArray[0]);
}

TEST(Device, changeDeviceTypeByName)
{
    Device *obj = new Device();
    ASSERT_THAT("", obj->get_device_type());
    ASSERT_THAT(0, obj->set_device_name("lumi.sensor_motion.aq2"));
    ASSERT_THAT("IMS", obj->get_device_type());
    ASSERT_THAT(0, obj->set_device_name("lumi.sensor_smoke"));
    ASSERT_THAT("IMS", obj->get_device_type());
}

TEST(Device, DETECTED)
{
    Device *obj = new Device();
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    obj->set_device_endpoint(1);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    obj->set_device_short(0x5555);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
}

TEST(Device, changeDeviceConfirmStatus)
{
    Device *obj = new Device();
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    obj->set_device_endpoint(1);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    obj->set_device_short(0x5555);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj->get_device_status());
    ASSERT_THAT(0, obj->set_device_name("lumi.sensor_motion.aq2"));
    ASSERT_THAT((int)Device::eConfirmedStatus::JOINED, obj->get_device_status());
    obj->set_device_status(Device::eConfirmedStatus::READY_FOR_SENDING);
    ASSERT_THAT((int)Device::eConfirmedStatus::JOINED, obj->get_device_status());
    obj->set_device_status(Device::eConfirmedStatus::CONFIRMED);
    ASSERT_THAT((int)Device::eConfirmedStatus::JOINED, obj->get_device_status());
    obj->set_device_status(Device::eConfirmedStatus::HAVE_SENT_TO_SERVER);
    ASSERT_THAT((int)Device::eConfirmedStatus::JOINED, obj->get_device_status());

    Device *obj2 = new Device(0x4444);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj2->get_device_status());
    obj2->set_device_endpoint(1);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj2->get_device_status());
    obj2->set_device_short(0x5555);
    ASSERT_THAT(Device::eConfirmedStatus::DETECTED, obj2->get_device_status());
    ASSERT_THAT(0, obj2->set_device_name("lumi.sensor_motion.aq2"));
    ASSERT_THAT((int)Device::eConfirmedStatus::READY_FOR_SENDING, obj2->get_device_status());
    obj2->set_device_status(Device::eConfirmedStatus::HAVE_SENT_TO_SERVER);
    ASSERT_THAT((int)Device::eConfirmedStatus::HAVE_SENT_TO_SERVER, obj2->get_device_status());
    obj2->set_device_status(Device::eConfirmedStatus::CONFIRMED);
    ASSERT_THAT((int)Device::eConfirmedStatus::CONFIRMED, obj2->get_device_status());

    obj2->set_device_status(Device::eConfirmedStatus::DEVICE_ADDING_ERROR);
    ASSERT_THAT((int)Device::eConfirmedStatus::CONFIRMED, obj2->get_device_status());
}

#endif // TST_DEVICE_H
