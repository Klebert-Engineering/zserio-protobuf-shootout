# zserio-protobuf-shootout

First Hack at converting GTFS realtime data encoded in protobuf to an equivalent zserio schema.

Use as follows (currently only works with vehicle position message):

- Build executable
- Run `./zs_pb_shootout create <file>`
- run the python script `convert.py` to solve the uint64 Json issue
- run `./zs_pb_shootout convert`

