import json

def convert_to_int(data):
    """
    Recursively scans the input dictionary `data` and converts all fields of name "intValue" to integers.
    """
    if isinstance(data, dict):
        for key in data.keys():
            if key == "intValue" or key == "uintValue" or key == "id":
                try:
                    data[key] = int(data[key])
                except ValueError:
                    pass  # If `data[key]` is not a valid integer, leave it as it is
            else:
                convert_to_int(data[key])
    elif isinstance(data, list):
        for item in data:
            convert_to_int(item)

# open the input file
with open("vtile_input.json", "r") as f:
    # load JSON data from file
    data = json.load(f)

# convert all "intValue" fields to integers
convert_to_int(data)

# open the output file
with open("output.json", "w") as f:
    # write the updated JSON data to file
    json.dump(data, f, ensure_ascii=False)
