/**
 * Automatically generated by Zserio C++ extension version 2.9.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef GTFSREALTIME_TIME_RANGE_H
#define GTFSREALTIME_TIME_RANGE_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <memory>
#include <zserio/PackingContext.h>
#include <zserio/OptionalHolder.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Types.h>

namespace gtfsrealtime
{

class TimeRange
{
public:
    using allocator_type = ::std::allocator<uint8_t>;

    explicit TimeRange(const allocator_type& allocator = allocator_type()) noexcept;

    template <typename ZSERIO_T_start,
            typename ZSERIO_T_end,
            ::zserio::is_field_constructor_enabled_t<ZSERIO_T_start, TimeRange, allocator_type> = 0>
    TimeRange(
            ZSERIO_T_start&& start_,
            ZSERIO_T_end&& end_,
            const allocator_type& allocator = allocator_type()) :
            TimeRange(allocator)
    {
        m_start_ = ::std::forward<ZSERIO_T_start>(start_);
        m_end_ = ::std::forward<ZSERIO_T_end>(end_);
    }

    explicit TimeRange(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit TimeRange(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~TimeRange() = default;

    TimeRange(const TimeRange&) = default;
    TimeRange& operator=(const TimeRange&) = default;

    TimeRange(TimeRange&&) = default;
    TimeRange& operator=(TimeRange&&) = default;

    TimeRange(::zserio::PropagateAllocatorT,
            const TimeRange& other, const allocator_type& allocator);

    uint64_t getStart() const;
    void setStart(uint64_t start_);
    bool isStartUsed() const;
    bool isStartSet() const;
    void resetStart();

    uint64_t getEnd() const;
    void setEnd(uint64_t end_);
    bool isEndUsed() const;
    bool isEndSet() const;
    void resetEnd();

    static void createPackingContext(::zserio::PackingContextNode& contextNode);
    void initPackingContext(::zserio::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const TimeRange& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    ::zserio::InplaceOptionalHolder<uint64_t> readStart(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint64_t> readStart(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint64_t> readEnd(::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<uint64_t> readEnd(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);

    ::zserio::InplaceOptionalHolder<uint64_t> m_start_;
    ::zserio::InplaceOptionalHolder<uint64_t> m_end_;
};

} // namespace gtfsrealtime

#endif // GTFSREALTIME_TIME_RANGE_H
