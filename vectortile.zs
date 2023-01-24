package vectortile;

enum bit:4 GeomType 
{
    UNKNOWN = 0,
    POINT = 1,
    LINESTRING = 2,
    POLYGON = 3,
};

struct Value 
{
    optional string stringValue;
    optional float16 floatValue;
    optional float32 doubleValue;
    optional varint64 intValue;
    optional varuint64 uintValue;
    optional varint64 sintValue;
    optional bool boolValue;
};

struct Feature 
{
    uint64 id;
    packed uint32 tags[];
    GeomType type;
    packed uint32 geometry[];
    optional extern raster;
};

struct Layer 
{
    uint32 version;
    string name;
    packed Feature features[];
    string keys[];
    packed Value values[];
    optional uint32 extent;
};

struct Tile 
{
    packed Layer layers[];
};
    