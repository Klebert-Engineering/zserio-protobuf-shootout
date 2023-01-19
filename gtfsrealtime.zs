package gtfsrealtime;

struct FeedMessage
{
  // Metadata about this feed and feed message.
  FeedHeader header;

  // Contents of the feed.
  FeedEntity entity[];
};

// Metadata about a feed, included in feed messages.
struct FeedHeader 
{
  // Version of the feed specification.
  // The current version is 2.0.
  string gtfsRealtimeVersion;
          
  Incrementality incrementality = Incrementality.FULL_DATASET;

  // This timestamp identifies the moment when the content of this feed has been
  // created (in server time). In POSIX time (i.e., number of seconds since
  // January 1st 1970 00:00:00 UTC).
  optional varuint64 timestamp;
};

// Determines whether the current fetch is incremental.  Currently,
  // DIFFERENTIAL mode is unsupported and behavior is unspecified for feeds
  // that use this mode.  There are discussions on the GTFS Realtime mailing
  // list around fully specifying the behavior of DIFFERENTIAL mode and the
  // documentation will be updated when those discussions are finalized.
enum bit:4 Incrementality 
{
  FULL_DATASET = 0,
  DIFFERENTIAL = 1,
};

// A definition (or update) of an entity in the transit feed.
struct FeedEntity {
  // The ids are used only to provide incrementality support. The id should be
  // unique within a FeedMessage. Consequent FeedMessages may contain
  // FeedEntities with the same id. In case of a DIFFERENTIAL update the new
  // FeedEntity with some id will replace the old FeedEntity with the same id
  // (or delete it - see is_deleted below).
  // The actual GTFS entities (e.g. stations, routes, trips) referenced by the
  // feed must be specified by explicit selectors (see EntitySelector below for
  // more info).
  string id;

  // Whether this entity is to be deleted. Relevant only for incremental
  // fetches.
  bool is_deleted = false;

  // Data about the entity itself. Exactly one of the following fields must be
  // present (unless the entity is being deleted).
  optional TripUpdate trip_update;
  optional VehiclePosition vehicle;
  optional Alert alert;
};

struct TripUpdate 
{
  // The Trip that this message applies to. There can be at most one
  // TripUpdate entity for each actual trip instance.
  // If there is none, that means there is no prediction information available.
  // It does *not* mean that the trip is progressing according to schedule.
  TripDescriptor trip;

  // Additional information on the vehicle that is serving this trip.
  optional VehicleDescriptor vehicle;

  // Updates to StopTimes for the trip (both future, i.e., predictions, and in
  // some cases, past ones, i.e., those that already happened).
  // The updates must be sorted by stop_sequence, and apply for all the
  // following stops of the trip up to the next specified one.
  //
  // Example 1:
  // For a trip with 20 stops, a StopTimeUpdate with arrival delay and departure
  // delay of 0 for stop_sequence of the current stop means that the trip is
  // exactly on time.
  //
  // Example 2:
  // For the same trip instance, 3 StopTimeUpdates are provided:
  // - delay of 5 min for stop_sequence 3
  // - delay of 1 min for stop_sequence 8
  // - delay of unspecified duration for stop_sequence 10
  // This will be interpreted as:
  // - stop_sequences 3,4,5,6,7 have delay of 5 min.
  // - stop_sequences 8,9 have delay of 1 min.
  // - stop_sequences 10,... have unknown delay.
  StopTimeUpdate stop_time_update[];

  // Moment at which the vehicle's real-time progress was measured. In POSIX
  // time (i.e., the number of seconds since January 1st 1970 00:00:00 UTC).
  optional varuint64 timestamp;

  // The current schedule deviation for the trip.  Delay should only be
  // specified when the prediction is given relative to some existing schedule
  // in GTFS.
  //
  // Delay (in seconds) can be positive (meaning that the vehicle is late) or
  // negative (meaning that the vehicle is ahead of schedule). Delay of 0
  // means that the vehicle is exactly on time.
  //
  // Delay information in StopTimeUpdates take precedent of trip-level delay
  // information, such that trip-level delay is only propagated until the next
  // stop along the trip with a StopTimeUpdate delay value specified.
  //
  // Feed providers are strongly encouraged to provide a TripUpdate.timestamp
  // value indicating when the delay value was last updated, in order to
  // evaluate the freshness of the data.
  //
  // NOTE: This field is still experimental, and subject to change. It may be
  // formally adopted in the future.
  optional varint32 delay;
};

// Timing information for a single predicted event (either arrival or
  // departure).
  // Timing consists of delay and/or estimated time, and uncertainty.
  // - delay should be used when the prediction is given relative to some
  //   existing schedule in GTFS.
  // - time should be given whether there is a predicted schedule or not. If
  //   both time and delay are specified, time will take precedence
  //   (although normally, time, if given for a scheduled trip, should be
  //   equal to scheduled time in GTFS + delay).
  //
  // Uncertainty applies equally to both time and delay.
  // The uncertainty roughly specifies the expected error in true delay (but
  // note, we don't yet define its precise statistical meaning). It's possible
  // for the uncertainty to be 0, for example for trains that are driven under
  // computer timing control.
struct StopTimeEvent {
    // Delay (in seconds) can be positive (meaning that the vehicle is late) or
    // negative (meaning that the vehicle is ahead of schedule). Delay of 0
    // means that the vehicle is exactly on time.
    optional varint32 delay;

    // Event as absolute time.
    // In Unix time (i.e., number of seconds since January 1st 1970 00:00:00
    // UTC).
    optional varint64 time;

    // If uncertainty is omitted, it is interpreted as unknown.
    // If the prediction is unknown or too uncertain, the delay (or time) field
    // should be empty. In such case, the uncertainty field is ignored.
    // To specify a completely certain prediction, set its uncertainty to 0.
    optional varint32 uncertainty;
};

// Realtime update for arrival and/or departure events for a given stop on a
  // trip. Updates can be supplied for both past and future events.
  // The producer is allowed, although not required, to drop past events.
struct StopTimeUpdate {
    // The update is linked to a specific stop either through stop_sequence or
    // stop_id, so one of the fields below must necessarily be set.
    // See the documentation in TripDescriptor for more information.

    // Must be the same as in stop_times.txt in the corresponding GTFS feed.
    optional varuint32 stop_sequence;
    // Must be the same as in stops.txt in the corresponding GTFS feed.
    optional string stop_id;

    optional StopTimeEvent arrival;
    optional StopTimeEvent departure;

    StopTimeScheduleRelationship schedule_relationship = StopTimeScheduleRelationship.SCHEDULED;
  };

// The relation between this StopTime and the static schedule.
    enum bit:4 StopTimeScheduleRelationship 
    {
      // The vehicle is proceeding in accordance with its static schedule of
      // stops, although not necessarily according to the times of the schedule.
      // At least one of arrival and departure must be provided. If the schedule
      // for this stop contains both arrival and departure times then so must
      // this update.
      SCHEDULED = 0,

      // The stop is skipped, i.e., the vehicle will not stop at this stop.
      // Arrival and departure are optional.
      SKIPPED = 1,

      // No data is given for this stop. The main intention for this value is to
      // give the predictions only for part of a trip, i.e., if the last update
      // for a trip has a NO_DATA specifier, then StopTimes for the rest of the
      // stops in the trip are considered to be unspecified as well.
      // Neither arrival nor departure should be supplied.
      NO_DATA = 2,
    };

// Realtime positioning information for a given vehicle.
struct VehiclePosition 
{
  // The Trip that this vehicle is serving.
  // Can be empty or partial if the vehicle can not be identified with a given
  // trip instance.
  optional TripDescriptor trip;

  // Additional information on the vehicle that is serving this trip.
  optional VehicleDescriptor vehicle;

  // Current position of this vehicle.
  optional Position position;

  // The stop sequence index of the current stop. The meaning of
  // current_stop_sequence (i.e., the stop that it refers to) is determined by
  // current_status.
  // If current_status is missing IN_TRANSIT_TO is assumed.
  optional varuint32 current_stop_sequence;
  // Identifies the current stop. The value must be the same as in stops.txt in
  // the corresponding GTFS feed.
  optional string stop_id;

  // The exact status of the vehicle with respect to the current stop.
  // Ignored if current_stop_sequence is missing.
  VehicleStopStatus current_status = VehicleStopStatus.IN_TRANSIT_TO;

  // Moment at which the vehicle's position was measured. In POSIX time
  // (i.e., number of seconds since January 1st 1970 00:00:00 UTC).
  optional varuint64 timestamp;

  optional CongestionLevel congestion_level;

  optional OccupancyStatus occupancy_status;
};

enum bit:4 VehicleStopStatus 
{
    // The vehicle is just about to arrive at the stop (on a stop
    // display, the vehicle symbol typically flashes).
    INCOMING_AT = 0,

    // The vehicle is standing at the stop.
    STOPPED_AT = 1,

    // The vehicle has departed and is in transit to the next stop.
    IN_TRANSIT_TO = 2,
};

// Congestion level that is affecting this vehicle.
enum bit:4 CongestionLevel {
    UNKNOWN_CONGESTION_LEVEL = 0,
    RUNNING_SMOOTHLY = 1,
    STOP_AND_GO = 2,
    CONGESTION = 3,
    SEVERE_CONGESTION = 4,  // People leaving their cars.
};

// The degree of passenger occupancy of the vehicle. This field is still
  // experimental, and subject to change. It may be formally adopted in the
  // future.
enum bit:4 OccupancyStatus {
    // The vehicle is considered empty by most measures, and has few or no
    // passengers onboard, but is still accepting passengers.
    EMPTY = 0,

    // The vehicle has a relatively large percentage of seats available.
    // What percentage of free seats out of the total seats available is to be
    // considered large enough to fall into this category is determined at the
    // discretion of the producer.
    MANY_SEATS_AVAILABLE = 1,

    // The vehicle has a relatively small percentage of seats available.
    // What percentage of free seats out of the total seats available is to be
    // considered small enough to fall into this category is determined at the
    // discretion of the feed producer.
    FEW_SEATS_AVAILABLE = 2,

    // The vehicle can currently accommodate only standing passengers.
    STANDING_ROOM_ONLY = 3,

    // The vehicle can currently accommodate only standing passengers
    // and has limited space for them.
    CRUSHED_STANDING_ROOM_ONLY = 4,

    // The vehicle is considered full by most measures, but may still be
    // allowing passengers to board.
    FULL = 5,

    // The vehicle is not accepting additional passengers.
    NOT_ACCEPTING_PASSENGERS = 6,
};

// An alert, indicating some sort of incident in the public transit network.
struct Alert {
  // Time when the alert should be shown to the user. If missing, the
  // alert will be shown as long as it appears in the feed.
  // If multiple ranges are given, the alert will be shown during all of them.
  TimeRange active_period[];

  // Entities whose users we should notify of this alert.
  EntitySelector informed_entity[];

  Cause cause = Cause.UNKNOWN_CAUSE;
 
  Effect effect = Effect.UNKNOWN_EFFECT;

  // The URL which provides additional information about the alert.
  optional TranslatedString url;

  // Alert header. Contains a short summary of the alert text as plain-text.
  optional TranslatedString header_text;

  // Full description for the alert as plain-text. The information in the
  // description should add to the information of the header.
  optional TranslatedString description_text;
};

// Cause of this alert.
enum varuint16 Cause 
{
    UNKNOWN_CAUSE = 1,
    OTHER_CAUSE = 2,  // Not machine-representable.
    TECHNICAL_PROBLEM = 3,
    STRIKE = 4,         // Public transit agency employees stopped working.
    DEMONSTRATION = 5,  // People are blocking the streets.
    ACCIDENT = 6,
    HOLIDAY = 7,
    WEATHER = 8,
    MAINTENANCE = 9,
    CONSTRUCTION = 10,
    POLICE_ACTIVITY = 11,
    MEDICAL_EMERGENCY = 12,
};

// What is the effect of this problem on the affected entity.
enum varuint16 Effect 
{
    NO_SERVICE = 1,
    REDUCED_SERVICE = 2,

    // We don't care about INsignificant delays: they are hard to detect, have
    // little impact on the user, and would clutter the results as they are too
    // frequent.
    SIGNIFICANT_DELAYS = 3,

    DETOUR = 4,
    ADDITIONAL_SERVICE = 5,
    MODIFIED_SERVICE = 6,
    OTHER_EFFECT = 7,
    UNKNOWN_EFFECT = 8,
    STOP_MOVED = 9,
};


//
// Low level data structures used above.
//

// A time interval. The interval is considered active at time 't' if 't' is
// greater than or equal to the start time and less than the end time.
struct TimeRange {
  // Start time, in POSIX time (i.e., number of seconds since January 1st 1970
  // 00:00:00 UTC).
  // If missing, the interval starts at minus infinity.
  optional varuint64 start;

  // End time, in POSIX time (i.e., number of seconds since January 1st 1970
  // 00:00:00 UTC).
  // If missing, the interval ends at plus infinity.
  optional varuint64 end;
};

// A position.
struct Position {
  // Degrees North, in the WGS-84 coordinate system.
  float32 latitude;

  // Degrees East, in the WGS-84 coordinate system.
  float32 longitude;

  // Bearing, in degrees, clockwise from North, i.e., 0 is North and 90 is East.
  // This can be the compass bearing, or the direction towards the next stop
  // or intermediate location.
  // This should not be direction deduced from the sequence of previous
  // positions, which can be computed from previous data.
  optional float32 bearing;

  // Odometer value, in meters.
  optional float64 odometer;
  // Momentary speed measured by the vehicle, in meters per second.
  optional float32 speed;
};

// A descriptor that identifies an instance of a GTFS trip, or all instances of
// a trip along a route.
// - To specify a single trip instance, the trip_id (and if necessary,
//   start_time) is set. If route_id is also set, then it should be same as one
//   that the given trip corresponds to.
// - To specify all the trips along a given route, only the route_id should be
//   set. Note that if the trip_id is not known, then stop sequence ids in
//   TripUpdate are not sufficient, and stop_ids must be provided as well. In
//   addition, absolute arrival/departure times must be provided.
struct TripDescriptor {
  // The trip_id from the GTFS feed that this selector refers to.
  // For non frequency-based trips, this field is enough to uniquely identify
  // the trip. For frequency-based trip, start_time and start_date might also be
  // necessary.
  optional string trip_id;

  // The route_id from the GTFS that this selector refers to.
  optional string route_id;

  // The direction_id from the GTFS feed trips.txt file, indicating the
  // direction of travel for trips this selector refers to. This field is
  // still experimental, and subject to change. It may be formally adopted in
  // the future.
  optional varuint32 direction_id;

  // The initially scheduled start time of this trip instance.
  // When the trip_id corresponds to a non-frequency-based trip, this field
  // should either be omitted or be equal to the value in the GTFS feed. When
  // the trip_id corresponds to a frequency-based trip, the start_time must be
  // specified for trip updates and vehicle positions. If the trip corresponds
  // to exact_times=1 GTFS record, then start_time must be some multiple
  // (including zero) of headway_secs later than frequencies.txt start_time for
  // the corresponding time period. If the trip corresponds to exact_times=0,
  // then its start_time may be arbitrary, and is initially expected to be the
  // first departure of the trip. Once established, the start_time of this
  // frequency-based trip should be considered immutable, even if the first
  // departure time changes -- that time change may instead be reflected in a
  // StopTimeUpdate.
  // Format and semantics of the field is same as that of
  // GTFS/frequencies.txt/start_time, e.g., 11:15:35 or 25:15:35.
  optional string start_time;
  // The scheduled start date of this trip instance.
  // Must be provided to disambiguate trips that are so late as to collide with
  // a scheduled trip on a next day. For example, for a train that departs 8:00
  // and 20:00 every day, and is 12 hours late, there would be two distinct
  // trips on the same time.
  // This field can be provided but is not mandatory for schedules in which such
  // collisions are impossible - for example, a service running on hourly
  // schedule where a vehicle that is one hour late is not considered to be
  // related to schedule anymore.
  // In YYYYMMDD format.
  optional string start_date;

  optional ScheduleRelationship schedule_relationship;
};

// Identification information for the vehicle performing the trip.
struct VehicleDescriptor {
  // Internal system identification of the vehicle. Should be unique per
  // vehicle, and can be used for tracking the vehicle as it proceeds through
  // the system.
  optional string id;

  // User visible label, i.e., something that must be shown to the passenger to
  // help identify the correct vehicle.
  optional string label;

  // The license plate of the vehicle.
  optional string license_plate;
};

// A selector for an entity in a GTFS feed.
struct EntitySelector {
  // The values of the fields should correspond to the appropriate fields in the
  // GTFS feed.
  // At least one specifier must be given. If several are given, then the
  // matching has to apply to all the given specifiers.
  optional string agency_id;
  optional string route_id;
  // corresponds to route_type in GTFS.
  optional varint32 route_type;
  optional TripDescriptor trip;
  optional string stop_id;
};

// An internationalized message containing per-language versions of a snippet of
// text or a URL.
// One of the strings from a message will be picked up. The resolution proceeds
// as follows:
// 1. If the UI language matches the language code of a translation,
//    the first matching translation is picked.
// 2. If a default UI language (e.g., English) matches the language code of a
//    translation, the first matching translation is picked.
// 3. If some translation has an unspecified language code, that translation is
//    picked.
struct TranslatedString {
  
  // At least one translation must be provided.
  Translation translation[];
};

struct Translation {
    // A UTF-8 string containing the message.
    string text;
    // BCP-47 language code. Can be omitted if the language is unknown or if
    // no i18n is done at all for the feed. At most one translation is
    // allowed to have an unspecified language tag.
    optional string language;
  };

// The relation between this trip and the static schedule. If a trip is done
  // in accordance with temporary schedule, not reflected in GTFS, then it
  // shouldn't be marked as SCHEDULED, but likely as ADDED.
enum bit:4 ScheduleRelationship {
    // Trip that is running in accordance with its GTFS schedule, or is close
    // enough to the scheduled trip to be associated with it.
    SCHEDULED = 0,

    // An extra trip that was added in addition to a running schedule, for
    // example, to replace a broken vehicle or to respond to sudden passenger
    // load.
    ADDED = 1,

    // A trip that is running with no schedule associated to it, for example, if
    // there is no schedule at all.
    UNSCHEDULED = 2,

    // A trip that existed in the schedule but was removed.
    CANCELED = 3,
};