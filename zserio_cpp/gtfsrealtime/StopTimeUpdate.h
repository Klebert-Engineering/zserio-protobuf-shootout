/**
 * Automatically generated by Zserio C++ extension version 2.9.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef GTFSREALTIME_STOP_TIME_UPDATE_H
#define GTFSREALTIME_STOP_TIME_UPDATE_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <memory>
#include <zserio/PackingContext.h>
#include <zserio/OptionalHolder.h>
#include <zserio/ArrayTraits.h>
#include <zserio/String.h>
#include <zserio/Types.h>

#include <gtfsrealtime/StopTimeEvent.h>
#include <gtfsrealtime/StopTimeScheduleRelationship.h>

namespace gtfsrealtime
{

class StopTimeUpdate
{
public:
    using allocator_type = ::std::allocator<uint8_t>;

    explicit StopTimeUpdate(const allocator_type& allocator = allocator_type()) noexcept;

    template <typename ZSERIO_T_stop_sequence,
            typename ZSERIO_T_stop_id,
            typename ZSERIO_T_arrival,
            typename ZSERIO_T_departure,
            ::zserio::is_field_constructor_enabled_t<ZSERIO_T_stop_sequence, StopTimeUpdate, allocator_type> = 0>
    StopTimeUpdate(
            ZSERIO_T_stop_sequence&& stop_sequence_,
            ZSERIO_T_stop_id&& stop_id_,
            ZSERIO_T_arrival&& arrival_,
            ZSERIO_T_departure&& departure_,
            ::gtfsrealtime::StopTimeScheduleRelationship schedule_relationship_,
            const allocator_type& allocator = allocator_type()) :
            StopTimeUpdate(allocator)
    {
        m_stop_sequence_ = ::std::forward<ZSERIO_T_stop_sequence>(stop_sequence_);
        m_stop_id_ = ::std::forward<ZSERIO_T_stop_id>(stop_id_);
        m_arrival_ = ::std::forward<ZSERIO_T_arrival>(arrival_);
        m_departure_ = ::std::forward<ZSERIO_T_departure>(departure_);
        m_schedule_relationship_ = schedule_relationship_;
    }

    explicit StopTimeUpdate(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit StopTimeUpdate(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~StopTimeUpdate() = default;

    StopTimeUpdate(const StopTimeUpdate&) = default;
    StopTimeUpdate& operator=(const StopTimeUpdate&) = default;

    StopTimeUpdate(StopTimeUpdate&&) = default;
    StopTimeUpdate& operator=(StopTimeUpdate&&) = default;

    StopTimeUpdate(::zserio::PropagateAllocatorT,
            const StopTimeUpdate& other, const allocator_type& allocator);

    uint32_t getStop_sequence() const;
    void setStop_sequence(uint32_t stop_sequence_);
    bool isStop_sequenceUsed() const;
    bool isStop_sequenceSet() const;
    void resetStop_sequence();

    const ::zserio::string<>& getStop_id() const;
    ::zserio::string<>& getStop_id();
    void setStop_id(const ::zserio::string<>& stop_id_);
    void setStop_id(::zserio::string<>&& stop_id_);
    bool isStop_idUsed() const;
    bool isStop_idSet() const;
    void resetStop_id();

    const ::gtfsrealtime::StopTimeEvent& getArrival() const;
    ::gtfsrealtime::StopTimeEvent& getArrival();
    void setArrival(const ::gtfsrealtime::StopTimeEvent& arrival_);
    void setArrival(::gtfsrealtime::StopTimeEvent&& arrival_);
    bool isArrivalUsed() const;
    bool isArrivalSet() const;
    void resetArrival();

    const ::gtfsrealtime::StopTimeEvent& getDeparture() const;
    ::gtfsrealtime::StopTimeEvent& getDeparture();
    void setDeparture(const ::gtfsrealtime::StopTimeEvent& departure_);
    void setDeparture(::gtfsrealtime::StopTimeEvent&& departure_);
    bool isDepartureUsed() const;
    bool isDepartureSet() const;
    void resetDeparture();

    ::gtfsrealtime::StopTimeScheduleRelationship getSchedule_relationship() const;
    void setSchedule_relationship(::gtfsrealtime::StopTimeScheduleRelationship schedule_relationship_);

    static void createPackingContext(::zserio::PackingContextNode& contextNode);
    void initPackingContext(::zserio::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const StopTimeUpdate& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    ::zserio::InplaceOptionalHolder<uint32_t> readStop_sequence(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint32_t> readStop_sequence(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::zserio::string<>> readStop_id(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::StopTimeEvent> readArrival(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::StopTimeEvent> readArrival(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::StopTimeEvent> readDeparture(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::StopTimeEvent> readDeparture(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::gtfsrealtime::StopTimeScheduleRelationship readSchedule_relationship(::zserio::BitStreamReader& in);
    ::gtfsrealtime::StopTimeScheduleRelationship readSchedule_relationship(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);

    ::zserio::InplaceOptionalHolder<uint32_t> m_stop_sequence_;
    ::zserio::InplaceOptionalHolder<::zserio::string<>> m_stop_id_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::StopTimeEvent> m_arrival_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::StopTimeEvent> m_departure_;
    ::gtfsrealtime::StopTimeScheduleRelationship m_schedule_relationship_;
};

} // namespace gtfsrealtime

#endif // GTFSREALTIME_STOP_TIME_UPDATE_H