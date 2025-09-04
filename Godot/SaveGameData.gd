extends RefCounted
class_name SaveGameData

var integer_one:int
var integer_two:int
var integer_three:int
var integer_four:int
var float_one:float
var float_two:float
var float_three:float
var vector_one:Vector3
var vector_two:Vector3

static var current:SaveGameData

static func load_from_file(path:String) -> void:
    if not FileAccess.file_exists(path):
        return
    var file = FileAccess.open(path, FileAccess.READ)
    if file:
        var data = JSON.parse_string(file.get_as_text())
        file.close()
        if typeof(data) == TYPE_DICTIONARY:
            var d:Dictionary = data
            current = SaveGameData.new()
            current.integer_one = d.get("integer_one", 0)
            current.integer_two = d.get("integer_two", 0)
            current.integer_three = d.get("integer_three", 0)
            current.integer_four = d.get("integer_four", 0)
            current.float_one = d.get("float_one", 0.0)
            current.float_two = d.get("float_two", 0.0)
            current.float_three = d.get("float_three", 0.0)
            var v1 = d.get("vector_one", {})
            if v1 is Dictionary:
                current.vector_one = Vector3(v1.get("x", 0), v1.get("y", 0), v1.get("z", 0))
            var v2 = d.get("vector_two", {})
            if v2 is Dictionary:
                current.vector_two = Vector3(v2.get("x", 0), v2.get("y", 0), v2.get("z", 0))

static func save_to_file(path:String) -> void:
    if current == null:
        return
    var data = {
        "integer_one": current.integer_one,
        "integer_two": current.integer_two,
        "integer_three": current.integer_three,
        "integer_four": current.integer_four,
        "float_one": current.float_one,
        "float_two": current.float_two,
        "float_three": current.float_three,
        "vector_one": {"x": current.vector_one.x, "y": current.vector_one.y, "z": current.vector_one.z},
        "vector_two": {"x": current.vector_two.x, "y": current.vector_two.y, "z": current.vector_two.z},
    }
    var file = FileAccess.open(path, FileAccess.WRITE)
    if file:
        file.store_string(JSON.stringify(data))
        file.close()

static func try_load_from_args() -> bool:
    var args = OS.get_cmdline_args()
    for i in range(args.size() - 1):
        if args[i].to_lower() == "-load":
            var file_path = args[i + 1]
            if file_path.get_extension().to_lower() == "mgdf" and FileAccess.file_exists(file_path):
                load_from_file(file_path)
                return true
            break
    return false
