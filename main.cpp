#include "tst_device.h"
#include "tst_message.h"
#include "tst_device_intercom.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
