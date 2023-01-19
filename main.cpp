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


// Main function:  Reads the entire address book from a file and prints all
//   the information inside.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  if (argc != 2) {
    cerr << "Usage:  " << argv[0] << " GTFS_FILE" << endl;
    return -1;
  }

  transit_realtime::FeedMessage feedMsg;

  // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!feedMsg.ParseFromIstream(&input)) {
      cerr << "Failed to parse feed message." << endl;
      return -1;
    }

  std::string json;
  google::protobuf::util::MessageToJsonString(feedMsg, &json);

  //std::cout << json;
  
  gtfs::gtfsrealtime::FeedMessage zs_feed = zserio::fromJsonString<gtfs::gtfsrealtime::FeedMessage>(json);

  zserio::serializeToFile(zs_feed, "gtfs.zsbin");

  return 0;
}