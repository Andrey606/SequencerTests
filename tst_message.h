#ifndef TST_DEVICE_LIST_H
#define TST_DEVICE_LIST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "message.h"
#include <QDebug>
#include <QJsonDocument>

using namespace testing;

TEST(Message, MessageInitialization)
{
    ::Message obj;

    ASSERT_THAT(::Message::eFrom::UNDEFINED, obj.from());
    ASSERT_THAT(::Message::eTo::UNDEFINED, obj.to());
    ASSERT_THAT(::Message::eMsgId::UNDEFINED, obj.msgId());
    ASSERT_THAT("", obj.data());
    ASSERT_THAT("", obj.topicName());
}

TEST(Message, MessageInitialization2)
{
    ::Message obj(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QByteArray("test"), QString("topic"));

    ASSERT_THAT(::Message::eFrom::HOST, obj.from());
    ASSERT_THAT(::Message::eTo::DEVICE, obj.to());
    ASSERT_THAT(::Message::eMsgId::JSON, obj.msgId());
    ASSERT_THAT("test", obj.data());
    ASSERT_THAT("topic", obj.topicName());
}

TEST(Message, MessageInitialization3)
{
    ::Message obj(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QByteArray("test"), QString("topic"));
    ::Message obj2(obj);

    ASSERT_THAT(::Message::eFrom::HOST, obj2.from());
    ASSERT_THAT(::Message::eTo::DEVICE, obj2.to());
    ASSERT_THAT(::Message::eMsgId::JSON, obj2.msgId());
    ASSERT_THAT("test", obj2.data());
    ASSERT_THAT("topic", obj2.topicName());
}

TEST(Message, MessageInitialization4)
{
    ::Message obj(::Message::eFrom::HOST, ::Message::eTo::DEVICE, QJsonObject());;

    ASSERT_THAT(::Message::eFrom::HOST, obj.from());
    ASSERT_THAT(::Message::eTo::DEVICE, obj.to());
    ASSERT_THAT(::Message::eMsgId::JSON, obj.msgId());
    ASSERT_THAT("", obj.data());
    ASSERT_THAT("", obj.topicName());
}

TEST(Message, tesData)
{
    QJsonObject json{
        {"_commandType", "DeviceStateUpdateCommand"},
        {"hubId", "omo-sl-embed-ua-kiev-andrey"},
        {"_id", "ccccccfffed82fdf"},
        {"desired", QJsonObject{ {"unlock", 4000 }}}
    };

    ::Message obj(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QJsonDocument(json).toJson());
    ASSERT_THAT(QJsonDocument(json).toJson(), obj.data());


    QJsonObject json2{
        {"_commandType", "000000000000"},
        {"hubId", "000000000000"},
        {"_id", "000000000000"},
        {"desired", QJsonObject{ {"unlock", 4000 }}}
    };

    ::Message obj2(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QJsonDocument(json).toJson());
    ASSERT_NE(QJsonDocument(json2).toJson(), obj2.data());
}

TEST(Message, tesTopic)
{
    ::Message obj(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QByteArray("test"));
    ASSERT_THAT("", obj.topicName());

    ::Message obj2(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QByteArray("test"), "hubCommands");
    ASSERT_THAT("hubCommands", obj2.topicName());
}

TEST(Message, testIsEmpty)
{
    ::Message obj(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QByteArray(), QString("topic"));
    EXPECT_TRUE(obj.isEmpty());

    ::Message obj2(::Message::eFrom::HOST, ::Message::eTo::DEVICE, ::Message::eMsgId::JSON, QByteArray("test"), QString("topic"));
    EXPECT_FALSE(obj2.isEmpty());
}

#endif // TST_DEVICE_LIST_H
