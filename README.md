# zserio-protobuf-shootout

First Hack at converting GTFS realtime data encoded in protobuf to an equivalent zserio schema.

Use as follows (currently only works with vehicle position message):

- Build executable
- Run `./zs_pb_shootout create <file>`
- run the python script `convert.py` to solve the uint64 Json issue
- run `./zs_pb_shootout convert`



## Non-benchmark reasons to choose zserio over protobuf

### Handling of default values

Protobuf handles default values defined in the schema in such a case that if there is no data in the bytestream received, the API will generate the value based on the default value in the reader API. This means that if a field is not set, it is not clear at the readers end, whether the value has accidentally not been set, or if the writer intended to save space on the wire and assumed the default value. In protobuf these default values are often used for data compatibility reasons so that newer clients can assume values for data that is sent from older servers.
Protobuf has enforced default values for all scalar fields of a message. In case no default values shall be used, a wrapper is needed around each scalar value (which kind of defeats the idea in general.)

In zserio there are no enforced defaults. A default value is simply an option to a scalar field. The default value is also always written to the stream. It is not a way to save data size. It simply can be used as a fallback/default value.

In case of functional safety relevant data the use of default values has to be handled with care in case the receiving end shall be enabled to validate the integrity of the data. With protobuf this is nearly impossible to do without wrapping each and every scalar value into a compound wrapper.
For wrappers, see [Google Well Known Types](https://developers.google.com/protocol-buffers/docs/reference/google.protobuf) which basically put every scalar into a compound.

The NDS.Live coding guidelines do not forbid the use of defaults, but there is a tendency to not use them at all, since also in case the value is part of the stream it is still unclear whether it was set by intention or simply by the serializing code.

**Technical difference in a nutshell:**

Writer code in protobuf can simply forget to write a field to the stream and everything will be correctly serialized and is a valid protobuf message.

If writer code in zserio forgets to set a field in a struct, the serializing code will throw an exception and no stream will be written.
