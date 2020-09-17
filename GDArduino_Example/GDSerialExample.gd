extends Sprite


const serial_res = preload("res://bin/gdserial.gdns")
onready var serial_port = serial_res.new()
var started = false
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


func _process(delta):
	if started:
		var t = serial_port.read_text()
		if t.length() > 0:
			print(t)


func _on_Button_pressed():
	print(serial_port.open_port("/dev/ttyACM0", 9600))
	started = true

func _on_Close_pressed():
	serial_port.close_port()


func _on_Write_pressed():
	serial_port.write_text("Oi")
