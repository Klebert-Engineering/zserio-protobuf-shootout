/**
 * Automatically generated by Zserio C++ extension version 2.9.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef GTFSREALTIME_POSITION_H
#define GTFSREALTIME_POSITION_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <memory>
#include <zserio/PackingContext.h>
#include <zserio/OptionalHolder.h>
#include <zserio/ArrayTraits.h>

namespace gtfsrealtime
{

class Position
{
public:
    using allocator_type = ::std::allocator<uint8_t>;

    explicit Position(const allocator_type& allocator = allocator_type()) noexcept;

    template <typename ZSERIO_T_bearing,
            typename ZSERIO_T_odometer,
            typename ZSERIO_T_speed>
    Position(
            float latitude_,
            float longitude_,
            ZSERIO_T_bearing&& bearing_,
            ZSERIO_T_odometer&& odometer_,
            ZSERIO_T_speed&& speed_,
            const allocator_type& allocator = allocator_type()) :
            Position(allocator)
    {
        m_latitude_ = latitude_;
        m_longitude_ = longitude_;
        m_bearing_ = ::std::forward<ZSERIO_T_bearing>(bearing_);
        m_odometer_ = ::std::forward<ZSERIO_T_odometer>(odometer_);
        m_speed_ = ::std::forward<ZSERIO_T_speed>(speed_);
    }

    explicit Position(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit Position(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~Position() = default;

    Position(const Position&) = default;
    Position& operator=(const Position&) = default;

    Position(Position&&) = default;
    Position& operator=(Position&&) = default;

    Position(::zserio::PropagateAllocatorT,
            const Position& other, const allocator_type& allocator);

    float getLatitude() const;
    void setLatitude(float latitude_);

    float getLongitude() const;
    void setLongitude(float longitude_);

    float getBearing() const;
    void setBearing(float bearing_);
    bool isBearingUsed() const;
    bool isBearingSet() const;
    void resetBearing();

    double getOdometer() const;
    void setOdometer(double odometer_);
    bool isOdometerUsed() const;
    bool isOdometerSet() const;
    void resetOdometer();

    float getSpeed() const;
    void setSpeed(float speed_);
    bool isSpeedUsed() const;
    bool isSpeedSet() const;
    void resetSpeed();

    static void createPackingContext(::zserio::PackingContextNode& contextNode);
    void initPackingContext(::zserio::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const Position& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    float readLatitude(::zserio::BitStreamReader& in);
    float readLongitude(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<float> readBearing(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<double> readOdometer(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<float> readSpeed(::zserio::BitStreamReader& in);

    float m_latitude_;
    float m_longitude_;
    ::zserio::InplaceOptionalHolder<float> m_bearing_;
    ::zserio::InplaceOptionalHolder<double> m_odometer_;
    ::zserio::InplaceOptionalHolder<float> m_speed_;
};

} // namespace gtfsrealtime

#endif // GTFSREALTIME_POSITION_H
