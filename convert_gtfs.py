import json

# open the input file
with open("input.json", "r") as f:
    # load JSON data from file
    data = json.load(f)

# iterate through the entities
for entity in data["entity"]:
    # convert "timestamp" field to int
    entity["vehicle"]["timestamp"] = int(entity["vehicle"]["timestamp"])

# open the output file
with open("output.json", "w") as f:
    # write the updated JSON data to file
    json.dump(data, f)
