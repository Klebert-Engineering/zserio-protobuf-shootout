#include <iostream>
#include <fstream>
#include <string>
#include "gtfs-realtime.pb.h"
#include <google/protobuf/util/json_util.h>
#include <gtfs/gtfsrealtime/FeedMessage.h>
#include <zserio/DebugStringUtil.h>
#include <zserio/FileUtil.h>
#include <zserio/SerializeUtil.h>
using namespace std;


int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc < 2) {
    cerr << "Usage:  " << argv[0] << " <create|convert> GTFS_FILE" << endl;
    return -1;
  }

  if(std::string(argv[1]) == "create") {

    cout << "creating..." << endl;

    transit_realtime::FeedMessage feedMsg;

  // Read the existing GTFS file.
    fstream input(argv[2], ios::in | ios::binary);
    if (!feedMsg.ParseFromIstream(&input)) {
      cerr << "Failed to parse feed message." << endl;
      return -1;
    }

    std::string json;
    google::protobuf::util::MessageToJsonString(feedMsg, &json);

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

    gtfs::gtfsrealtime::FeedMessage zs_feed = zserio::fromJsonString<gtfs::gtfsrealtime::FeedMessage>(json);

    zserio::serializeToFile(zs_feed, "gtfs.zsbin");
  }

  
  

  return 0;
}