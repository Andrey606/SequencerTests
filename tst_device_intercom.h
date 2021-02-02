#ifndef TST_DEVICE_INTERCOM_H
#define TST_DEVICE_INTERCOM_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "device_manager/devices.h"

using namespace testing;

TEST(Device_intercom, IntercomInitialization)
{
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

    obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_ON);
    ASSERT_THAT(Device::_Intercom::eState::STATE_ON, obj2->Intercom.get_device_event_intercom());
}

TEST(Device_intercom, IntercomEvents)
{
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

    obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_ON);
    ASSERT_THAT(Device::_Intercom::eState::STATE_ON, obj2->Intercom.get_device_event_intercom());
    ASSERT_THAT(true, obj2->Intercom._event);

    obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_OFF);
    ASSERT_THAT(Device::_Intercom::eState::STATE_OFF, obj2->Intercom.get_device_event_intercom());
    ASSERT_THAT(true, obj2->Intercom._event);
}

TEST(Device_intercom, IntercomCommands)
{
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


    // check Intercom comands <-> events handling
    obj2->Intercom.set_device_command_intercom(Device::_Intercom::eCommands2::eCommands::CMD_UNLOCK, 0, "user1", "correl1");
    obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_ON);
    ASSERT_THAT(Device::_Intercom::eState::STATE_ON, obj2->Intercom.get_device_event_intercom());
    for(int j=0; j<obj2->Intercom.command2.size(); j++)
    {
        if(obj2->Intercom.command2[j].answered == false)
        {
            ASSERT_THAT(obj2->Intercom.command2[j].correlationId, "correl1");
            ASSERT_THAT(obj2->Intercom.command2[j].userId, "user1");
            obj2->Intercom.command2[j].answered = true; // -> fixed (not critical)
            break;
        }
    }
    obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_OFF);
    ASSERT_THAT(Device::_Intercom::eState::STATE_OFF, obj2->Intercom.get_device_event_intercom());
    for(int j=0; j<obj2->Intercom.command2.size(); j++)
    {
        if(obj2->Intercom.command2[j].answered == false)
        {
            ASSERT_THAT(obj2->Intercom.command2[j].correlationId, "correl1");
            ASSERT_THAT(obj2->Intercom.command2[j].userId, "user1");
            obj2->Intercom.command2[j].answered = true; // -> fixed (not critical)
            break;
        }
    }
    obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_ON);
    ASSERT_THAT(Device::_Intercom::eState::STATE_ON, obj2->Intercom.get_device_event_intercom());
    for(int j=0; j<obj2->Intercom.command2.size(); j++)
    {
        if(obj2->Intercom.command2[j].answered == false)
        {
            ASSERT_THAT(obj2->Intercom.command2[j].correlationId, "");
            ASSERT_THAT(obj2->Intercom.command2[j].userId, "");
            obj2->Intercom.command2[j].answered = true; // -> fixed (not critical)
            break;
        }
    }
}

TEST(Device_intercom, LotsIntercomCommands)
{
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

    // check Intercom comands <-> events handling
    int size = 5;
    QString userArray[5] = {"user1", "user2", "user3", "user4", "user5"};
    QString correlArray[5] = {"correl1", "correl2", "correl3", "correl4", "correl5"};

    for(int i=0; i<size; i++)
    {
        obj2->Intercom.set_device_command_intercom(Device::_Intercom::eCommands2::eCommands::CMD_UNLOCK, 0, userArray[i], correlArray[i]);
    }

    for(int i=0; i<size; i++)
    {
        obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_ON);
        ASSERT_THAT(Device::_Intercom::eState::STATE_ON, obj2->Intercom.get_device_event_intercom());
        for(int j=0; j<obj2->Intercom.command2.size(); j++)
        {
            if(obj2->Intercom.command2[j].answered == false)
            {
                ASSERT_THAT(obj2->Intercom.command2[j].correlationId, correlArray[i]);
                ASSERT_THAT(obj2->Intercom.command2[j].userId, userArray[i]);
                obj2->Intercom.command2[j].answered = true; // -> fixed (not critical)
                break;
            }
        }
    }

    for(int i=0; i<size; i++)
    {
        obj2->Intercom.set_device_event_intercom(Device::_Intercom::eState::STATE_OFF);
        ASSERT_THAT(Device::_Intercom::eState::STATE_OFF, obj2->Intercom.get_device_event_intercom());
        for(int j=0; j<obj2->Intercom.command2.size(); j++)
        {
            if(obj2->Intercom.command2[j].answered == false)
            {
                ASSERT_THAT(obj2->Intercom.command2[j].correlationId, correlArray[i]);
                ASSERT_THAT(obj2->Intercom.command2[j].userId, userArray[i]);
                obj2->Intercom.command2[j].answered = true; // -> fixed (not critical)
                break;
            }
        }
    }
}

#endif // TST_DEVICE_INTERCOM_H
