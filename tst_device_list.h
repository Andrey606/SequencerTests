#ifndef TST_DEVICE_LIST_H
#define TST_DEVICE_LIST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "device_manager/devices.h"

using namespace testing;

TEST(Device_list, DeviceListInitialization)
{
    Device_list *obj = new Device_list();

    ASSERT_THAT(0, obj->add_new_device(0x5555));
    ASSERT_THAT(1, obj->add_new_device(0x5555));
    ASSERT_THAT(0, obj->add_new_device(0x6666));
    ASSERT_THAT(2, obj->get_list_size());
}

TEST(Device_list, DeviceListInfo)
{
    Device_list *obj = new Device_list();

    ASSERT_THAT(0, obj->add_new_device(0x5555));
    ASSERT_THAT(1, obj->get_list_size());
    ASSERT_THAT(false, obj->isValidDevice(0x5555));
    ASSERT_THAT(1, obj->confirm_device(0x5555));
}

TEST(Device_list, DeviceListDeletion)
{
    Device_list *obj = new Device_list();

    ASSERT_THAT(0, obj->add_new_device(0x5555));
    ASSERT_THAT(0, obj->delete_device(0x5555));
    ASSERT_THAT(1, obj->delete_device(0x5555));
}

#endif // TST_DEVICE_LIST_H
