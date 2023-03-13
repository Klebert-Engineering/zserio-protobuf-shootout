# zserio-protobuf-shootout

## Conversion

### General Transit Feed Specification (GTFS) 

Use as follows (currently only works with vehicle position message):

- Build executable (target `gtfs_app`)
- Run `./gtfs_app create <file>`
- run the python script `convert_gtfs.py` to solve the uint64 Json issue
- run `./gtfs_app convert` to create a zserio binary matching the proto input
- run `./gtfs_app decodepb|decodezs` to decode either protobuf or zs binaries and compare performance

### Baidu Apollo HD map

Works in the same way as above, but does not need a conversion step

- Build executable (target `apollo_app`)
- After creation of input.json in step `./apollo_app create`, simply rename to output.json to continue

### Mapbox VectorTile format

Works the same way as above.

- Build executable (target `vtile_app`)
- Run `./vtile_app create <file>`
- run the python script `convert_vector.py` to solve the uint64 Json issue
- run `./vtile_app convert` to create a zserio binary matching the proto input
- run `./vtile_app decodepb|decodezs` to decode either protobuf or zs binaries and compare performance


## Cross compilation to Raspberry Pi

Currently only working in interactive mode (yet):

- Build Docker image from the `Dockerfile`
- Run docker in interactive mode: `docker run --rm -it  -v $PWD:/work crossdock-zserioproto:latest bash`

Execute the following commands inside the docker:
```
rm -rf build_armv7
mkdir build_armv7
cd build_armv7
cmake .. -DCMAKE_BUILD_TYPE:STRING=Release
cmake --build . --config Release --target vtile_app -j 18
```

Copy the executable to the raspberry.

## Running CodeQL

To compare how zserio and protobuf compare with respect to AUTOSAR complience, we you can run CodeQL with the AUTOSAR rules provided by https://github.com/github/codeql-coding-standards

To get comparable stats you have to adapt for example the vtile.cpp app so that it only uses protobuf libs or zserio libs, by outcommenting all the code/includes/cmake. If this is not done properly the following analysis will simply run on top of proto and zserio which makes it hard to compare.

Prerequisite: 

- Install the CodeQL CLI (check out https://github.com/github/codeql-coding-standards/blob/main/docs/user_manual.md for a good start)
- https://github.com/github/codeql-coding-standards has been cloned in same workspace as this repo
- Cmake configure has been successfully run.

```
cd build

codeql database create --language cpp --command "cmake --build . -t vtile_app" ../codeqldb --overwrite

codeql database analyze --format=sarifv2.1.0 --output=../results.sarif ../codeqldb ../../codeql-coding-standards/cpp/autosar/src/codeql-suites/autosar-default.qls
```

Check results with SARIF viewer (e.g. VSCode plugin) or have additional report generated:

```
python3.11 ../codeql-coding-standards/scripts/reports/analysis_report.py codeqldb results.sarif reports
```

The generated reports can be found here:

- VectorTile App with Protobuf libs only: [CodeQL report](reports-pb/guideline_compliance_summary.md)
- VectorTile App with zserio libs only: [CodeQL report](reports-zs/guideline_compliance_summary.md)


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
