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
    optional varuint64 id;
    packed varuint32 tags[];
    optional GeomType type;
    packed varuint32 geometry[];
    optional extern raster;
};

struct Layer 
{
    string name;
    Feature features[];
    string keys[];
    packed Value values[];
    optional uint32 extent;
    uint32 version;
};

struct Tile 
{
    Layer layers[];
};
    