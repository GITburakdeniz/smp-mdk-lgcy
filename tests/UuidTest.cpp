#include "UuidTest.h"

#include "Mdk/SimpleTypes.h"

using namespace ::Smp::Mdk;

void UuidTest::setUp(void)
{
}

void UuidTest::tearDown(void)
{
}

void UuidTest::testConstructors(void)
{
    {
        Uuid uuid;
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt32(0), uuid.Data1);
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt16(0), uuid.Data2);
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt16(0), uuid.Data3);
        for (::Smp::UInt32 i(0); i != 8; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(::Smp::UInt8(0), uuid.Data4[i]);
        }
    }

    {
        Uuid uuid(NullUuid);
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt32(0), uuid.Data1);
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt16(0), uuid.Data2);
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt16(0), uuid.Data3);
        for (::Smp::UInt32 i(0); i != 8; ++i)
        {
            CPPUNIT_ASSERT_EQUAL(::Smp::UInt8(0), uuid.Data4[i]);
        }
    }

    {
	Uuid uuid("00112233-4455-6677-8899-AABBCCDDEEFF");
	CPPUNIT_ASSERT_EQUAL(::Smp::UInt32(0x00112233), uuid.Data1);
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt16(0x4455), uuid.Data2);
        CPPUNIT_ASSERT_EQUAL(::Smp::UInt16(0x6677), uuid.Data3);
    }
}
