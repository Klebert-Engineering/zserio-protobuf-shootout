#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include "apollo.pb.h"
#include <google/protobuf/util/json_util.h>
#include <apollozs/apollozs/Map.h>
#include <zserio/DebugStringUtil.h>
#include <zserio/FileUtil.h>
#include <zserio/SerializeUtil.h>

using namespace std;


void decodePb(const std::string& filename) {
  using clock = std::chrono::system_clock;
  std::chrono::time_point<clock> start_tp_;

  start_tp_ = clock::now();

  apollo::hdmap::Map map;

  // Read the existing GTFS file.
  std::fstream input(filename, std::ios::in | std::ios::binary);
  if (!map.ParseFromIstream(&input)) {
    std::cerr << "Failed to parse feed message." << std::endl;
    return;
  }

  auto duration = clock::now() - start_tp_;

  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration - seconds);
  auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration - seconds - milliseconds);

  std::cout << "Duration: " << seconds.count() << " seconds, "
            << milliseconds.count() << " milliseconds, "
            << microseconds.count() << " microseconds." << std::endl;
}


int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc < 2) {
    cerr << "Usage:  " << argv[0] << " <create|convert|decodepb|decodezs> FILE" << endl;
    return -1;
  }

  if(std::string(argv[1]) == "create") {

    cout << "creating..." << endl;

    apollo::hdmap::Map map;

  // Read the existing Apollo map file.
    fstream input(argv[2], ios::in | ios::binary);
    if (!map.ParseFromIstream(&input)) {
      cerr << "Failed to parse feed message." << endl;
      return -1;
    }

    std::string json;
    google::protobuf::util::MessageToJsonString(map, &json);

    // Write the json string to a file which we then need to transform using the python script
    ofstream outfile ("input.json");
    outfile << json;
    outfile.close();
    
  }
  
  else if(std::string(argv[1]) == "convert")
  {
    cout << "converting..." << endl;
    // Open the file
    ifstream infile("output.json");

    // Check if the file is open
    if(!infile.is_open()) {
        cerr << "Error opening file" << endl;
        return -1;
    }

    // Create a string to store the json
    std::string json;

    // Read the contents of the file into the string
    getline(infile, json, '\0');

    // Close the file
    infile.close();

    apollozs::apollozs::Map zsMap = 
            zserio::fromJsonString<apollozs::apollozs::Map>(json);

    zserio::serializeToFile(zsMap, "apollo.zsbin");
  }
  else if (std::string(argv[1]) == "decodepb") {
    decodePb(argv[2]);
  }

  else if(std::string(argv[1]) == "decodezs")
  {
    using clock = std::chrono::steady_clock;
    std::chrono::time_point<clock> start_tp_;

    start_tp_ = clock::now();

    std::cout << "Timestamp: " << start_tp_.time_since_epoch().count() << std::endl;

    apollozs::apollozs::Map zsMap = 
          zserio::deserializeFromFile<apollozs::apollozs::Map>(std::string(argv[2]));

    auto duration = clock::now() - start_tp_;

    std::cout << "ZS decode duration: " << duration.count() / 1000000.0 << " milliseconds." << std::endl;
  }
  
  return 0;
}