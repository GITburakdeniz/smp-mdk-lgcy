//
// Title:
//      SimpleTypes.h
//
// Project:
//      Simulation Model Portability (SMP) Standard 2.0
//      C++ Model Development Kit (MDK)
//      Version 1.2 from October 28th, 2005
//
// Origin:
//      Simulation Model Portability (SMP) Configuration Control Board (CCB)
//
// Purpose:
//      This file defines convenience methods for SMP 2.0 base types.
//      This includes wrappers for Duration, DateTime, AnySimple and Uuid.
//
// Author:
//      Peter Ellsiepen, Peter Fritzen
//

#ifndef MDK_SIMPLETYPES_H_
#define MDK_SIMPLETYPES_H_

// ----------------------------------------------------------------------------
// ---------------------------- Include files ---------------------------------
// ----------------------------------------------------------------------------

#include "Smp/Exceptions.h"
#include "Smp/SimpleTypes.h"

// ----------------------------------------------------------------------------
// ---------------------------- Duration type ---------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        /// Duration wrapper for Smp::Duration type.
        /// This wrapper provides convenience methods to convert a Duration.
        /// It supports strings, seconds, and days/hours/minutes/seconds.
        struct Duration
        {
            static const Smp::Duration   TicksPerSecond = 1000*1000*1000;
            Smp::Duration                ticks;    // 64 bits

            // ----------------------------------------------------------------
            // ------------------------- Constructors -------------------------
            // ----------------------------------------------------------------

            /// Default constructor.
            Duration();

            /// Copy constructor from Smp Duration.
            /// @param source Source Smp Duration to copy.
            Duration(const Smp::Duration& source);

            /// Constructor for the given time elements.
            /// @param days Number of full days of duration.
            /// @param hours Number of additional hours of duration.
            /// @param minutes Number of additional minutes of duration.
            /// @param seconds Number of additional seconds of duration.
            /// @param nanoseconds Number of additional nanoseconds of duration.
            Duration(const Smp::Int32 days, 
                     const Smp::Int16 hours, 
                     const Smp::Int16 minutes, 
                     const Smp::Int16 seconds, 
                     const Smp::Int32 nanoseconds = 0);

            /// Constructor for the given time in seconds.
            /// @param seconds Duration in seconds
            Duration(const Smp::Float64 seconds);

            /// Constructor taking a string.
            /// @param string Duration string (Format: [+|-]dd.hh:mm:ss[.ns]).
            Duration(const char* string);

            // ----------------------------------------------------------------
            // ------------------------- Operators ----------------------------
            // ----------------------------------------------------------------

            /// Assignment operator for Smp Duration.
            /// @param source Source Smp Duration to assign.
            Smp::Mdk::Duration& operator = (const Smp::Duration& source);

            /// Assignment operator from seconds.
            /// @param seconds Duration in seconds
            Smp::Mdk::Duration& operator = (const Smp::Float64 seconds);

            /// Returns negative of duration.
            /// @return Negative duration.
            Smp::Mdk::Duration operator - (void) const;

            /// Returns a new Duration as a sum of instance and a given Duration.
            /// @param  duration Duration to add to instance.
            /// @return New Duration as a sum of instance and the given Duration.
            Smp::Mdk::Duration operator + (Smp::Mdk::Duration duration) const;

            /// Returns duration between instance and another Duration value.
            /// @param  duration Duration value to calculate difference for.
            /// @return Duration between instance and given Duration value.
            Smp::Mdk::Duration operator - (Smp::Mdk::Duration duration) const;

            /// Adds a given Duration to the instance.
            /// @param duration Duration to add to instance.
            void operator += (Smp::Mdk::Duration duration);

            /// Subtracts a given Duration from the instance.
            /// @param duration Duration to subtract from instance.
            void operator -= (Smp::Mdk::Duration duration);

            /// Compare whether instance is greater than another Duration.
            /// @param duration Duration to compare with.
            /// @return True if instance is later than given Duration.
            bool operator > (Smp::Mdk::Duration duration) const;

            /// Compare whether instance is earlier than another Duration.
            /// @param duration Duration to compare with.
            /// @return True if given instance is earlier than given Duration.
            bool operator < (Smp::Mdk::Duration duration) const;

            /// Compare whether instance equals another Duration.
            /// @param duration Duration to compare with.
            /// @return True if given instance is equal to the given Duration.
            bool operator == (Smp::Mdk::Duration duration) const;

            /// Compare whether instance differs from another Duration.
            /// @param duration Duration to compare with.
            /// @return True if given instance is different from given Duration.
            bool operator != (Smp::Mdk::Duration duration) const;

            // ----------------------------------------------------------------
            // ------------------------- Setter & Getter ----------------------
            // ----------------------------------------------------------------

            /// Set Duration by the given time elements.
            /// @param days Number of full days of duration.
            /// @param hours Number of additional hours of duration.
            /// @param minutes Number of additional minutes of duration.
            /// @param seconds Number of additional seconds of duration.
            /// @param nanoseconds Number of additional nanoseconds of duration.
            bool Set(const Smp::Int32 days, 
                     const Smp::Int16 hours, 
                     const Smp::Int16 minutes, 
                     const Smp::Int16 seconds, 
                     const Smp::Int32 nanoseconds = 0);

            /// Get the given time elements from a Duration.
            /// @param days Number of days of duration.
            /// @param hours Number of hours of duration.
            /// @param minutes Number of minutes of duration.
            /// @param seconds Number of seconds of duration.
            /// @param nanoseconds Number of nanoseconds of duration.
            void Get(Smp::Int32& days, 
                     Smp::Int16& hours, 
                     Smp::Int16& minutes, 
                     Smp::Int16& seconds, 
                     Smp::Int32& nanoseconds) const;

            /// Set Duration in seconds.
            /// @param seconds Duration in seconds
            bool Set(const Smp::Float64 seconds);

            /// Get Duration in seconds.
            /// @return Duration in seconds
            Smp::Float64 Get() const;

            /// Set Duration with the Format ([+|-]dd.hh:mm:ss[.ns]).
            /// @param string Duration string (input buffer)
            /// @return <code>true</code> on success, <code>false</code> otherwise.
            /// @remarks When no sign is given, a positive sign is assumed.
            ///          When no nanoseconds are given, a value of 0 is assumed.
            bool Set(const char* string);

            /// Get Duration in the Format (dd:hh:mm:ss:ns).
            /// @param string Duration string (output buffer, to be provided by caller)
            void Get(char* string) const;
        };
    }
}

// ----------------------------------------------------------------------------
// ---------------------------- DateTime type ---------------------------------
// ----------------------------------------------------------------------------

namespace Smp
{ 
    namespace Mdk
    {
        /// DateTime wrapper for Smp::DateTime type.
        /// This wrapper provides convenience methods to convert a DateTime.
        /// It supports strings, days, and day/month/year/hours/minutes/seconds.
        struct DateTime
        {
            static const Smp::UInt8 DaysInMonth[12];
            static const Smp::Int64 TicksPerSecond  = 1000*1000*1000;
            static const Smp::Int64 TicksPerDay     = 24*60*60*TicksPerSecond;
            static const Smp::Int64 TicksPerCentury = 36524*TicksPerDay;

            Smp::DateTime           ticks;      // 64 bits

            // ----------------------------------------------------------------
            // ------------------------- Constructors -------------------------
            // ----------------------------------------------------------------

            /// Default constructor.
            DateTime();

            /// Copy constructor from Smp DateTime.
            /// @param source Source Smp DateTime to copy.
            DateTime(const Smp::DateTime& source);

            /// Copy constructor from days.
            /// @param days Number of days relative to MJD2000+0.5.
            DateTime(const Smp::Float64 days);

            /// Constructor for given date and time elements.
            /// @param year Year of date part.
            /// @param month Month of date part.
            /// @param day Day of date part.
            /// @param hours Hours of time part.
            /// @param minutes Minutes of time part.
            /// @param seconds Seconds of time part.
            /// @param nanoseconds Nanoseconds of time part.
            DateTime(const Smp::Int16 year, 
                     const Smp::Int16 month, 
                     const Smp::Int16 day, 
                     const Smp::Int16 hours, 
                     const Smp::Int16 minutes, 
                     const Smp::Int16 seconds, 
                     const Smp::Int32 nanoseconds = 0);

            /// Constructor taking a string.
            /// @param string DateTime string (Format: dd.mm.yyyy hh:mm:ss[.ns]).
            DateTime(const char* string);

            // ----------------------------------------------------------------
            // ------------------------- Operators ----------------------------
            // ----------------------------------------------------------------

            /// Assignment operator from Smp DateTime.
            /// @param source Source Smp DateTime to assign.
            Smp::Mdk::DateTime& operator = (const Smp::DateTime& source);

            /// Assignment operator from days.
            /// @param days Number of days relative to MJD2000+0.5.
            Smp::Mdk::DateTime& operator = (const Smp::Float64 days);

            /// Returns duration between instance and another DateTime value.
            /// @param  dateTime DateTime value to calculate duration for.
            /// @return Duration between instance and given DateTime value.
            Smp::Mdk::Duration operator - (Smp::Mdk::DateTime dateTime) const;

            /// Returns a new DateTime as a sum of instance and a given Duration.
            /// @param  duration Duration to add to instance.
            /// @return New DateTime as a sum of instance and the given Duration.
            Smp::Mdk::DateTime operator + (Smp::Mdk::Duration duration) const;

            /// Returns a new DateTime as a difference of instance and a given Duration.
            /// @param  duration Duration to subtract from instance.
            /// @return New DateTime as a difference of instance and the given Duration.
            Smp::Mdk::DateTime operator - (Smp::Mdk::Duration duration) const;

            /// Adds a given Duration to the instance.
            /// @param duration Duration to add to instance.
            void operator += (Smp::Mdk::Duration duration);

            /// Subtracts a given Duration from the instance.
            /// @param duration Duration to subtract from instance.
            void operator -= (Smp::Mdk::Duration duration);

            /// Compare whether instance is later than another DateTime.
            /// @param dateTime DateTime to compare with.
            /// @return True if instance is later than given DateTime.
            bool operator > (Smp::Mdk::DateTime dateTime) const;

            /// Compare whether instance is earlier than another DateTime.
            /// @param dateTime DateTime to compare with.
            /// @return True if given instance is earlier than given DateTime.
            bool operator < (Smp::Mdk::DateTime dateTime) const;

            /// Compare whether instance equals another DateTime.
            /// @param dateTime DateTime to compare with.
            /// @return True if given instance is equal to the given DateTime.
            bool operator == (Smp::Mdk::DateTime dateTime) const;

            /// Compare whether instance differs from another DateTime.
            /// @param dateTime DateTime to compare with.
            /// @return True if given instance is different from given DateTime.
            bool operator != (Smp::Mdk::DateTime dateTime) const;

            // ----------------------------------------------------------------
            // ------------------------- Setter & Getter ----------------------
            // ----------------------------------------------------------------

            /// Set DateTime by the given date and time elements.
            /// @param year Year of date part.
            /// @param month Month of date part.
            /// @param day Day of date part.
            /// @param hours Hours of time part.
            /// @param minutes Minutes of time part.
            /// @param seconds Seconds of time part.
            /// @param nanoseconds Nanoseconds of time part.
            bool Set(const Smp::Int16 year, 
                     const Smp::Int16 month, 
                     const Smp::Int16 day, 
                     const Smp::Int16 hours, 
                     const Smp::Int16 minutes, 
                     const Smp::Int16 seconds, 
                     const Smp::Int32 nanoseconds = 0);

            /// Get date and time elements from DateTime.
            /// @param year Year of date part.
            /// @param month Month of date part.
            /// @param day Day of date part.
            /// @param hours Hours of time part.
            /// @param minutes Minutes of time part.
            /// @param seconds Seconds of time part.
            /// @param nanoseconds Nanoseconds of time part.
            void Get(Smp::Int16& year, 
                     Smp::Int16& month, 
                     Smp::Int16& day, 
                     Smp::Int16& hours, 
                     Smp::Int16& minutes, 
                     Smp::Int16& seconds, 
                     Smp::Int32& nanoseconds) const;

            /// Set DateTime by number of days, relative to MJD2000+0.5.
            /// @param days Number of days relative to MJD2000+0.5.
            bool Set(const Smp::Float64 days);

            /// Get DateTime in number of days, relative to MJD2000+0.5.
            /// @return Number of days relative to MJD2000+0.5.
            Smp::Float64 Get() const;
            
            /// Set DateTime from string (Format: dd.mm.yyyy hh:mm:ss[.ns]).
            /// @param string DateTime string (input buffer).
            /// @return <code>true</code> on success, <code>false</code> otherwise.
            bool Set(const char* string);

            /// Get DateTime as string (Format: dd.mm.yyyy hh:mm:ss[.ns]).
            /// @param string DateTime string (output buffer, to be provided by caller).
            void Get(char* string) const;

            // ----------------------------------------------------------------
            // ------------------------- Static Functions ---------------------
            // ----------------------------------------------------------------

            /// Check for leap year.
            /// @param year Year to check.
            /// @return <code>true</code> if the given year is a leap year, 
            ///         <code>false</code> otherwise. 
            static bool IsLeapYear(int year);
        };
    }
}

// ----------------------------------------------------------------------------
// ---------------------------- Uuid type -------------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        /// Uuid wrapper for Smp::Uuid type.
        /// This wrapper provides convenience methods to convert a Uuid.
        /// It supports conversion to and from string.
        struct Uuid : public Smp::Uuid
        {
            /// Minimum size of a buffer that can store a Uuid as string.
            static const int BUFFER_SIZE = 37;

            // ----------------------------------------------------------------
            // ------------------------- Constructors -------------------------
            // ----------------------------------------------------------------

            /// Default constructor.
            Uuid();

            /// Copy constructor from Smp Uuid.
            /// @param source Source Uuid to copy.
            Uuid(const Smp::Uuid& source);

            /// Constructor given a string.
            /// @param string Uuid string in the Format (8-4-4-4-12).
            Uuid(const char* string);

            // ----------------------------------------------------------------
            // ------------------------- Operators ----------------------------
            // ----------------------------------------------------------------

            /// Assignment operator for Smp Uuid.
            /// @param source Source Uuid to copy.
            Uuid& operator = (const Smp::Uuid& source);

            /// Assignment operator for Smp Uuid.
            /// @param string Uuid string.
            Uuid& operator = (const char* string);

            /// Compare whether instance equals another Uuid.
            /// @param uuid Uuid to compare with.
            /// @return True if given instance is equal to the given Uuid.
            bool operator == (const Smp::Uuid uuid) const;

            /// Compare whether instance not equals another Uuid.
            /// @param uuid Uuid to compare with.
            /// @return True if given instance is unequal to the given Uuid.
            bool operator != (const Smp::Uuid uuid) const;

            // ----------------------------------------------------------------
            // ------------------------- Setter & Getter ----------------------
            // ----------------------------------------------------------------

            /// Assign Uuid from string (in hexadecimal 8-4-4-4-12 format).
            /// @param string Uuid string (input buffer).
            /// @return <code>true</code> on success, <code>false</code> otherwise.
            bool Set(const char* string);

            /// Retrieve Uuid as string (in hexadecimal 8-4-4-4-12 format).
            /// @param string Uuid string (output buffer, to be provided by caller).
            void Get(char* string) const;
        };

        /// Uuid that does not specify a type, but stands for "no type".
        static const Uuid NullUuid = Uuid("00000000-0000-0000-0000-000000000000");
    }
}

// ----------------------------------------------------------------------------
// ---------------------------- AnySimple type --------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{ 
    namespace Mdk
    {
        /// AnySimple wrapper for Smp::AnySimple type.
        /// This wrapper provides convenience methods to convert an AnySimple.
        /// It supports setter and getter methods, and assignment operators.
        struct AnySimple : public Smp::AnySimple
        {
            // ----------------------------------------------------------------
            // ---------------------- Operators -------------------------------
            // ----------------------------------------------------------------

            /// Assignment operator
            AnySimple& operator = (const Smp::AnySimple& source);

            // ----------------------------------------------------------------
            // ---------------------- Setter methods --------------------------
            // ----------------------------------------------------------------

            /// Int64, Duration, or DateTime setter.
            /// @param v Value to assign to any.
            /// @param t Type  to assign to any.
            /// @remarks This method cannot be replaced by overloaded methods,
            /// as both Duration and DateTime are mapped to Int64 internally.
            void Set(const Smp::Int64 v, Smp::SimpleTypeKind t) throw 
                (Smp::InvalidAnyType);

            /// Set value to Bool.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Bool automatically.
            void Set(const Smp::Bool v);

            /// Set value to Char8.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Char8 automatically.
            void Set(const Smp::Char8 v);

            /// Set value to Int8.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Int8 automatically.
            void Set(const Smp::Int8 v);

            /// Set value to UInt8.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_UInt8 automatically.
            void Set(const Smp::UInt8 v);

            /// Set value to Int16.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Int16 automatically.
            void Set(const Smp::Int16 v);

            /// Set value to UInt16.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_UInt16 automatically.
            void Set(const Smp::UInt16 v);

            /// Set value to Int32.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Int32 automatically.
            void Set(const Smp::Int32 v);

            /// Set value to UInt32.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_UInt32 automatically.
            void Set(const Smp::UInt32 v);

            /// Set value to Int64.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Int64 automatically.
            void Set(const Smp::Int64 v);

            /// Set value to UInt64.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_UInt64 automatically.
            void Set(const Smp::UInt64 v);

            /// Set value to Float32.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set Float32 automatically.
            void Set(const Smp::Float32 v);

            /// Set value to Float64.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Float64 automatically.
            void Set(const Smp::Float64 v);

            /// Set value to Mdk DateTime.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_DateTime automatically.
            void Set(const Smp::Mdk::DateTime& v);

            /// Set value to Mdk Duration.
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_Duration automatically.
            void Set(const Smp::Mdk::Duration& v);

            /// Set value to 8 bit character string (String8).
            /// @param v Value to assign to any.
            /// @remarks The type of the any is set ST_String8 automatically.
            void Set(Smp::String8 const v);

            /// Get value from another AnySimple.
            /// @param source Source AnySimple to get value from.
            /// @remarks This only works when source has the same type.
            void Set(const Smp::AnySimple& source) throw (Smp::InvalidAnyType);

            // ----------------------------------------------------------------
            // ---------------------- Getter methods --------------------------
            // ----------------------------------------------------------------

            /// Get Char8 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Char8.
            void Get(Smp::Char8& v) throw (Smp::InvalidAnyType);

            /// Get Bool value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Bool.
            void Get(Smp::Bool& v) throw (Smp::InvalidAnyType);

            /// Get Int8 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Int8.
            void Get(Smp::Int8& v) throw (Smp::InvalidAnyType);

            /// Get Int16 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Int16.
            void Get(Smp::Int16& v) throw (Smp::InvalidAnyType);

            /// Get Int32 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Int32.
            void Get(Smp::Int32& v) throw (Smp::InvalidAnyType);

            /// Get Int64 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Int64.
            void Get(Smp::Int64& v) throw (Smp::InvalidAnyType);

            /// Get UInt8 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_UInt8.
            void Get(Smp::UInt8& v) throw (Smp::InvalidAnyType);

            /// Get UInt16 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_UInt16.
            void Get(Smp::UInt16& v) throw (Smp::InvalidAnyType);

            /// Get UInt32 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_UInt32.
            void Get(Smp::UInt32& v) throw (Smp::InvalidAnyType);

            /// Get UInt64 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_UInt64.
            void Get(Smp::UInt64& v) throw (Smp::InvalidAnyType);

            /// Get Float32 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Float32.
            void Get(Smp::Float32& v) throw (Smp::InvalidAnyType);

            /// Get Float64 value.
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_Float64.
            void Get(Smp::Float64& v) throw (Smp::InvalidAnyType);

            /// Get 8 bit character string (String8).
            /// @param v Value of any.
            /// @remarks This method throws an exception of type Smp::InvalidAnyType
            ///          if the AnySimple is not of type ST_String8.
            void Get(Smp::String8& v) throw (Smp::InvalidAnyType);            
        };
    }
}

// ----------------------------------------------------------------------------
// ---------------------------- Array template --------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{
    namespace Mdk
    {
        /// Template that encapsulates an array.
        /// This template allows using arrays as return types of 
        /// operation and property.
        template <class ArrayItemType, int size>
        struct Array
        {
            ArrayItemType internalArray[size];

            // Constructor
            Array()
            {
                memset(internalArray, 0, sizeof(internalArray));
            }

            // index-get operator
            inline const ArrayItemType& operator [] (long index) const 
            {
                return internalArray[index];
            }

            // index-set operator
            inline ArrayItemType& operator [] (long index)
            {
                return internalArray[index];
            }

            // address operator, especially for strings to get a char pointer.
            inline ArrayItemType* operator & (void)
            { 
                return internalArray;
            }
        };
    }
}

// ----------------------------------------------------------------------------
// ---------------------------- String template -------------------------------
// ----------------------------------------------------------------------------

namespace Smp 
{
    namespace Mdk
    {
        /// Template that encapsulates a string.
        /// This template allows using strings as return types of 
        /// operation and property.
        template <int size>
        struct String
        {
            Smp::Char8 internalArray[size+1];

            // Constructor
            String()
            {
                memset(internalArray, 0, sizeof(internalArray));
            }

            // Constructor taking a string
            String(Smp::String8 string)
            {
                strncpy(internalArray, string, size);
            }

            // index-get operator
            inline const Smp::Char8& operator [] (long index) const 
            {
                assert(index < size);
                return internalArray[index];
            }

            // index-set operator
            inline Smp::Char8& operator [] (long index)
            {
                assert(index < size);
                return internalArray[index];
            }

            // address operator, especially for strings to get a char pointer.
            inline Smp::Char8* operator & (void)
            { 
                return internalArray;
            }

            // assignment operator for strings
            inline Smp::Char8* operator = (Smp::String8 string)
            {
                return strncpy(internalArray, string, size);
            }
        };
    }
}

#endif  // MDK_SIMPLETYPES_H_

/***********
 * History *
 ***********/

//$Log: SimpleTypes.h,v $
//Revision 1.5  2007/02/07 23:14:54  nin
//Added support for String8 in AnySimple class.
//
//Revision 1.2  2006/09/27 11:49:45  nin
//SMP2 v1.2
// 

