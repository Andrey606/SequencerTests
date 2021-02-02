#ifndef TST_DEVICE_LIST_H
#define TST_DEVICE_LIST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "message.h"
#include <QDebug>

using namespace testing;

TEST(Message, MessageInitialization)
{
    //Message obj;
    ::Message obj;

    ASSERT_THAT(::Message::eFrom::UNDEFINED, obj.from());
    ASSERT_THAT(::Message::eTo::UNDEFINED, obj.to());
    ASSERT_THAT(::Message::eMsgId::UNDEFINED, obj.msgId());
    ASSERT_THAT("", obj.data());
    ASSERT_THAT("", obj.topicName());
}

#endif // TST_DEVICE_LIST_H
