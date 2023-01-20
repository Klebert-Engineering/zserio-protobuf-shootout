/**
 * Automatically generated by Zserio C++ extension version 2.9.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef GTFSREALTIME_STOP_TIME_SCHEDULE_RELATIONSHIP_H
#define GTFSREALTIME_STOP_TIME_SCHEDULE_RELATIONSHIP_H

#include <array>

#include <zserio/Enums.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/PackingContext.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

namespace gtfsrealtime
{

enum class StopTimeScheduleRelationship : uint8_t
{
    SCHEDULED = UINT8_C(0),
    SKIPPED = UINT8_C(1),
    NO_DATA = UINT8_C(2)
};

} // namespace gtfsrealtime

namespace zserio
{

// This is full specialization of enumeration traits and methods for StopTimeScheduleRelationship enumeration.
template <>
struct EnumTraits<::gtfsrealtime::StopTimeScheduleRelationship>
{
    static constexpr ::std::array<const char*, 3> names =
    {{
        "SCHEDULED",
        "SKIPPED",
        "NO_DATA"
    }};

    static constexpr ::std::array<::gtfsrealtime::StopTimeScheduleRelationship, 3> values =
    {{
        ::gtfsrealtime::StopTimeScheduleRelationship::SCHEDULED,
        ::gtfsrealtime::StopTimeScheduleRelationship::SKIPPED,
        ::gtfsrealtime::StopTimeScheduleRelationship::NO_DATA
    }};
};

template <>
size_t enumToOrdinal<::gtfsrealtime::StopTimeScheduleRelationship>(::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
::gtfsrealtime::StopTimeScheduleRelationship valueToEnum<::gtfsrealtime::StopTimeScheduleRelationship>(
        typename ::std::underlying_type<::gtfsrealtime::StopTimeScheduleRelationship>::type rawValue);

template <>
uint32_t enumHashCode<::gtfsrealtime::StopTimeScheduleRelationship>(::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
void initPackingContext<::zserio::PackingContextNode, ::gtfsrealtime::StopTimeScheduleRelationship>(
        ::zserio::PackingContextNode& contextNode, ::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
size_t bitSizeOf<::gtfsrealtime::StopTimeScheduleRelationship>(::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
size_t bitSizeOf<::zserio::PackingContextNode, ::gtfsrealtime::StopTimeScheduleRelationship>(
        ::zserio::PackingContextNode& contextNode, ::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
size_t initializeOffsets<::gtfsrealtime::StopTimeScheduleRelationship>(size_t bitPosition, ::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
size_t initializeOffsets<::zserio::PackingContextNode, ::gtfsrealtime::StopTimeScheduleRelationship>(
        ::zserio::PackingContextNode& contextNode, size_t bitPosition, ::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
::gtfsrealtime::StopTimeScheduleRelationship read<::gtfsrealtime::StopTimeScheduleRelationship>(::zserio::BitStreamReader& in);

template <>
::gtfsrealtime::StopTimeScheduleRelationship read<::gtfsrealtime::StopTimeScheduleRelationship, ::zserio::PackingContextNode>(
        ::zserio::PackingContextNode& contextNode, ::zserio::BitStreamReader& in);

template <>
void write<::gtfsrealtime::StopTimeScheduleRelationship>(::zserio::BitStreamWriter& out, ::gtfsrealtime::StopTimeScheduleRelationship value);

template <>
void write<::zserio::PackingContextNode, ::gtfsrealtime::StopTimeScheduleRelationship>(
        ::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out, ::gtfsrealtime::StopTimeScheduleRelationship value);

} // namespace zserio

#endif // GTFSREALTIME_STOP_TIME_SCHEDULE_RELATIONSHIP_H