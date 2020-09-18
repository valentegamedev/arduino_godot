extends Sprite


const serial_res = preload("res://bin/gdserial.gdns")
onready var serial_port = serial_res.new()
var started = false
var intext = ""
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


func _process(delta):
	if started:
		var t = serial_port.read_text()
		if t.length() > 0:
			for c in t:
				if c == "\n":
					trigger_text_received(intext)
					intext = ""
				else:
					intext+=c

func trigger_text_received(text):
	print(text)

func _on_Button_pressed():
	print(serial_port.open_port("COM7", 9600))
	started = true

func _on_Close_pressed():
	serial_port.close_port()

func _on_Write_pressed():
	serial_port.write_text("Hello Arduino!\n")
