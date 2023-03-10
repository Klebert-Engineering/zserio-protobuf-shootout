/**
 * Automatically generated by Zserio C++ extension version 2.9.0.
 * Generator setup: writerCode, pubsubCode, serviceCode, sqlCode, sourcesAmalgamation, stdAllocator.
 */

#ifndef GTFSREALTIME_ALERT_H
#define GTFSREALTIME_ALERT_H

#include <zserio/Traits.h>
#include <zserio/BitStreamReader.h>
#include <zserio/BitStreamWriter.h>
#include <zserio/AllocatorPropagatingCopy.h>
#include <memory>
#include <zserio/PackingContext.h>
#include <zserio/OptionalHolder.h>
#include <zserio/Array.h>
#include <zserio/ArrayTraits.h>
#include <zserio/Vector.h>

#include <gtfsrealtime/Cause.h>
#include <gtfsrealtime/Effect.h>
#include <gtfsrealtime/EntitySelector.h>
#include <gtfsrealtime/TimeRange.h>
#include <gtfsrealtime/TranslatedString.h>

namespace gtfsrealtime
{

class Alert
{
private:
    class ZserioElementFactory_active_period
    {
    public:
        explicit ZserioElementFactory_active_period(Alert& owner);

        void create(::zserio::vector<::gtfsrealtime::TimeRange>& array,
                ::zserio::BitStreamReader& in, size_t index) const;

        void create(::zserio::PackingContextNode& contextNode,
                ::zserio::vector<::gtfsrealtime::TimeRange>& array,
                ::zserio::BitStreamReader& in, size_t index) const;

    private:
        std::reference_wrapper<Alert> m_ownerRef;
    };

    class ZserioElementFactory_informed_entity
    {
    public:
        explicit ZserioElementFactory_informed_entity(Alert& owner);

        void create(::zserio::vector<::gtfsrealtime::EntitySelector>& array,
                ::zserio::BitStreamReader& in, size_t index) const;

        void create(::zserio::PackingContextNode& contextNode,
                ::zserio::vector<::gtfsrealtime::EntitySelector>& array,
                ::zserio::BitStreamReader& in, size_t index) const;

    private:
        std::reference_wrapper<Alert> m_ownerRef;
    };

    using ZserioArrayType_active_period = ::zserio::Array<::zserio::vector<::gtfsrealtime::TimeRange>, ::zserio::ObjectArrayTraits<::gtfsrealtime::TimeRange, ZserioElementFactory_active_period>, ::zserio::ArrayType::AUTO>;
    using ZserioArrayType_informed_entity = ::zserio::Array<::zserio::vector<::gtfsrealtime::EntitySelector>, ::zserio::ObjectArrayTraits<::gtfsrealtime::EntitySelector, ZserioElementFactory_informed_entity>, ::zserio::ArrayType::AUTO>;

public:
    using allocator_type = ::std::allocator<uint8_t>;

    explicit Alert(const allocator_type& allocator = allocator_type()) noexcept;

    template <typename ZSERIO_T_active_period,
            typename ZSERIO_T_informed_entity,
            typename ZSERIO_T_url,
            typename ZSERIO_T_header_text,
            typename ZSERIO_T_description_text,
            ::zserio::is_field_constructor_enabled_t<ZSERIO_T_active_period, Alert, allocator_type> = 0>
    Alert(
            ZSERIO_T_active_period&& active_period_,
            ZSERIO_T_informed_entity&& informed_entity_,
            ::gtfsrealtime::Cause cause_,
            ::gtfsrealtime::Effect effect_,
            ZSERIO_T_url&& url_,
            ZSERIO_T_header_text&& header_text_,
            ZSERIO_T_description_text&& description_text_,
            const allocator_type& allocator = allocator_type()) :
            Alert(allocator)
    {
        m_active_period_ = ZserioArrayType_active_period(::std::forward<ZSERIO_T_active_period>(active_period_), ::zserio::ObjectArrayTraits<::gtfsrealtime::TimeRange, ZserioElementFactory_active_period>());
        m_informed_entity_ = ZserioArrayType_informed_entity(::std::forward<ZSERIO_T_informed_entity>(informed_entity_), ::zserio::ObjectArrayTraits<::gtfsrealtime::EntitySelector, ZserioElementFactory_informed_entity>());
        m_cause_ = cause_;
        m_effect_ = effect_;
        m_url_ = ::std::forward<ZSERIO_T_url>(url_);
        m_header_text_ = ::std::forward<ZSERIO_T_header_text>(header_text_);
        m_description_text_ = ::std::forward<ZSERIO_T_description_text>(description_text_);
    }

    explicit Alert(::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());
    explicit Alert(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator = allocator_type());

    ~Alert() = default;

    Alert(const Alert&) = default;
    Alert& operator=(const Alert&) = default;

    Alert(Alert&&) = default;
    Alert& operator=(Alert&&) = default;

    Alert(::zserio::PropagateAllocatorT,
            const Alert& other, const allocator_type& allocator);

    const ::zserio::vector<::gtfsrealtime::TimeRange>& getActive_period() const;
    ::zserio::vector<::gtfsrealtime::TimeRange>& getActive_period();
    void setActive_period(const ::zserio::vector<::gtfsrealtime::TimeRange>& active_period_);
    void setActive_period(::zserio::vector<::gtfsrealtime::TimeRange>&& active_period_);

    const ::zserio::vector<::gtfsrealtime::EntitySelector>& getInformed_entity() const;
    ::zserio::vector<::gtfsrealtime::EntitySelector>& getInformed_entity();
    void setInformed_entity(const ::zserio::vector<::gtfsrealtime::EntitySelector>& informed_entity_);
    void setInformed_entity(::zserio::vector<::gtfsrealtime::EntitySelector>&& informed_entity_);

    ::gtfsrealtime::Cause getCause() const;
    void setCause(::gtfsrealtime::Cause cause_);

    ::gtfsrealtime::Effect getEffect() const;
    void setEffect(::gtfsrealtime::Effect effect_);

    const ::gtfsrealtime::TranslatedString& getUrl() const;
    ::gtfsrealtime::TranslatedString& getUrl();
    void setUrl(const ::gtfsrealtime::TranslatedString& url_);
    void setUrl(::gtfsrealtime::TranslatedString&& url_);
    bool isUrlUsed() const;
    bool isUrlSet() const;
    void resetUrl();

    const ::gtfsrealtime::TranslatedString& getHeader_text() const;
    ::gtfsrealtime::TranslatedString& getHeader_text();
    void setHeader_text(const ::gtfsrealtime::TranslatedString& header_text_);
    void setHeader_text(::gtfsrealtime::TranslatedString&& header_text_);
    bool isHeader_textUsed() const;
    bool isHeader_textSet() const;
    void resetHeader_text();

    const ::gtfsrealtime::TranslatedString& getDescription_text() const;
    ::gtfsrealtime::TranslatedString& getDescription_text();
    void setDescription_text(const ::gtfsrealtime::TranslatedString& description_text_);
    void setDescription_text(::gtfsrealtime::TranslatedString&& description_text_);
    bool isDescription_textUsed() const;
    bool isDescription_textSet() const;
    void resetDescription_text();

    static void createPackingContext(::zserio::PackingContextNode& contextNode);
    void initPackingContext(::zserio::PackingContextNode& contextNode) const;

    size_t bitSizeOf(size_t bitPosition = 0) const;
    size_t bitSizeOf(::zserio::PackingContextNode& contextNode, size_t bitPosition) const;

    size_t initializeOffsets(size_t bitPosition = 0);
    size_t initializeOffsets(::zserio::PackingContextNode& contextNode, size_t bitPosition);

    bool operator==(const Alert& other) const;
    uint32_t hashCode() const;

    void write(::zserio::BitStreamWriter& out) const;
    void write(::zserio::PackingContextNode& contextNode, ::zserio::BitStreamWriter& out) const;

private:
    ZserioArrayType_active_period readActive_period(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ZserioArrayType_active_period readActive_period(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ZserioArrayType_informed_entity readInformed_entity(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ZserioArrayType_informed_entity readInformed_entity(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::gtfsrealtime::Cause readCause(::zserio::BitStreamReader& in);
    ::gtfsrealtime::Cause readCause(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::gtfsrealtime::Effect readEffect(::zserio::BitStreamReader& in);
    ::gtfsrealtime::Effect readEffect(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> readUrl(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> readUrl(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> readHeader_text(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> readHeader_text(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> readDescription_text(::zserio::BitStreamReader& in,
            const allocator_type& allocator);
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> readDescription_text(::zserio::PackingContextNode& contextNode,
            ::zserio::BitStreamReader& in, const allocator_type& allocator);

    ZserioArrayType_active_period m_active_period_;
    ZserioArrayType_informed_entity m_informed_entity_;
    ::gtfsrealtime::Cause m_cause_;
    ::gtfsrealtime::Effect m_effect_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> m_url_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> m_header_text_;
    ::zserio::InplaceOptionalHolder<::gtfsrealtime::TranslatedString> m_description_text_;
};

} // namespace gtfsrealtime

#endif // GTFSREALTIME_ALERT_H
