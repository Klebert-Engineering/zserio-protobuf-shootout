/**
 * Automatically generated by Zserio C++ extension version 2.9.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef GTFSREALTIME_VEHICLE_POSITION_H
#define GTFSREALTIME_VEHICLE_POSITION_H

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

#include <gtfsrealtime/CongestionLevel.h>
#include <gtfsrealtime/OccupancyStatus.h>
#include <gtfsrealtime/Position.h>
#include <gtfsrealtime/TripDescriptor.h>
#include <gtfsrealtime/VehicleDescriptor.h>
#include <gtfsrealtime/VehicleStopStatus.h>

namespace gtfsrealtime
{

class VehiclePosition
{
public:
    using allocator_type = ::std::allocator<uint8_t>;

    explicit VehiclePosition(const allocator_type& allocator = allocator_type()) noexcept;

    template <typename ZSERIO_T_trip,
            typename ZSERIO_T_vehicle,
            typename ZSERIO_T_position,
            typename ZSERIO_T_current_stop_sequence,
            typename ZSERIO_T_stop_id,
            typename ZSERIO_T_timestamp,
            typename ZSERIO_T_congestion_level,
            typename ZSERIO_T_occupancy_status,
            ::zserio::is_field_constructor_enabled_t<ZSERIO_T_trip, VehiclePosition, allocator_type> = 0>
    VehiclePosition(
            ZSERIO_T_trip&& trip_,
            ZSERIO_T_vehicle&& vehicle_,
            ZSERIO_T_position&& position_,
            ZSERIO_T_current_stop_sequence&& current_stop_sequence_,
            ZSERIO_T_stop_id&& stop_id_,
            ::gtfsrealtime::VehicleStopStatus current_status_,
            ZSERIO_T_timestamp&& timestamp_,
            ZSERIO_T_congestion_level&& congestion_level_,
            ZSERIO_T_occupancy_status&& occupancy_status_,
            const allocator_type& allocator = allocator_type()) :
            VehiclePosition(allocator)
    {
        m_trip_ = ::std::forward<ZSERIO_T_trip>(trip_);
        m_vehicle_ = ::std::forward<ZSERIO_T_vehicle>(vehicle_);
        m_position_ = ::std::forward<ZSERIO_T_position>(position_);
        m_current_stop_sequence_ = ::std::forward<ZSERIO_T_current_stop_sequence>(current_stop_sequence_);
        m_stop_id_ = ::std::forward<ZSERIO_T_stop_id>(stop_id_);
        m_current_status_ = current_status_;
        m_timestamp_ = ::std::forward<ZSERIO_T_timestamp>(timestamp_);
        m_congestion_level_ = ::std::forward<ZSERIO_T_congestion_level>(congestion_level_);
        m_occupancy_status_ = ::std::forward<ZSERIO_T_occupancy_status>(occupancy_status_);
    }

    explicit VehiclePosition(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit VehiclePosition(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~VehiclePosition() = default;

    VehiclePosition(const VehiclePosition&) = default;
    VehiclePosition& operator=(const VehiclePosition&) = default;

    VehiclePosition(VehiclePosition&&) = default;
    VehiclePosition& operator=(VehiclePosition&&) = default;

    VehiclePosition(::zserio::PropagateAllocatorT,
            const VehiclePosition& other, const allocator_type& allocator);

    const ::gtfsrealtime::TripDescriptor& getTrip() const;
    ::gtfsrealtime::TripDescriptor& getTrip();
    void setTrip(const ::gtfsrealtime::TripDescriptor& trip_);
    void setTrip(::gtfsrealtime::TripDescriptor&& trip_);
    bool isTripUsed() const;
    bool isTripSet() const;
    void resetTrip();

    const ::gtfsrealtime::VehicleDescriptor& getVehicle() const;
    ::gtfsrealtime::VehicleDescriptor& getVehicle();
    void setVehicle(const ::gtfsrealtime::VehicleDescriptor& vehicle_);
    void setVehicle(::gtfsrealtime::VehicleDescriptor&& vehicle_);
    bool isVehicleUsed() const;
    bool isVehicleSet() const;
    void resetVehicle();

    const ::gtfsrealtime::Position& getPosition() const;
    ::gtfsrealtime::Position& getPosition();
    void setPosition(const ::gtfsrealtime::Position& position_);
    void setPosition(::gtfsrealtime::Position&& position_);
    bool isPositionUsed() const;
    bool isPositionSet() const;
    void resetPosition();

    uint32_t getCurrent_stop_sequence() const;
    void setCurrent_stop_sequence(uint32_t current_stop_sequence_);
    bool isCurrent_stop_sequenceUsed() const;
    bool isCurrent_stop_sequenceSet() const;
    void resetCurrent_stop_sequence();

    const ::zserio::string<>& getStop_id() const;
    ::zserio::string<>& getStop_id();
    void setStop_id(const ::zserio::string<>& stop_id_);
    void setStop_id(::zserio::string<>&& stop_id_);
    bool isStop_idUsed() const;
    bool isStop_idSet() const;
    void resetStop_id();

    ::gtfsrealtime::VehicleStopStatus getCurrent_status() const;
    void setCurrent_status(::gtfsrealtime::VehicleStopStatus current_status_);

    uint64_t getTimestamp() const;
    void setTimestamp(uint64_t timestamp_);
    bool isTimestampUsed() const;
    bool isTimestampSet() const;
    void resetTimestamp();

    ::gtfsrealtime::CongestionLevel getCongestion_level() const;
    void setCongestion_level(::gtfsrealtime::CongestionLevel congestion_level_);
    bool isCongestion_levelUsed() const;
    bool isCongestion_levelSet() const;
    void resetCongestion_level();

    ::gtfsrealtime::OccupancyStatus getOccupancy_status() const;
    void setOccupancy_status(::gtfsrealtime::OccupancyStatus occupancy_status_);
    bool isOccupancy_statusUsed() const;
    bool isOccupancy_statusSet() const;
    void resetOccupancy_status();

    static void createPackingContext(::zserio::PackingContextNode& contextNode);
    void initPackingContext(::zserio::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const VehiclePosition& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TripDescriptor> readTrip(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TripDescriptor> readTrip(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::VehicleDescriptor> readVehicle(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::VehicleDescriptor> readVehicle(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::Position> readPosition(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::Position> readPosition(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<uint32_t> readCurrent_stop_sequence(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint32_t> readCurrent_stop_sequence(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::zserio::string<>> readStop_id(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::gtfsrealtime::VehicleStopStatus readCurrent_status(::zserio::BitStreamReader& in);
    ::gtfsrealtime::VehicleStopStatus readCurrent_status(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint64_t> readTimestamp(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint64_t> readTimestamp(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::CongestionLevel> readCongestion_level(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::CongestionLevel> readCongestion_level(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::OccupancyStatus> readOccupancy_status(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::OccupancyStatus> readOccupancy_status(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);

    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TripDescriptor> m_trip_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::VehicleDescriptor> m_vehicle_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::Position> m_position_;
    ::zserio::InplaceOptionalHolder<uint32_t> m_current_stop_sequence_;
    ::zserio::InplaceOptionalHolder<::zserio::string<>> m_stop_id_;
    ::gtfsrealtime::VehicleStopStatus m_current_status_;
    ::zserio::InplaceOptionalHolder<uint64_t> m_timestamp_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::CongestionLevel> m_congestion_level_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::OccupancyStatus> m_occupancy_status_;
};

} // namespace gtfsrealtime

#endif // GTFSREALTIME_VEHICLE_POSITION_H
