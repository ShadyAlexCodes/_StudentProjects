extends Area2D

var width
var height
var direction
var speed

func _ready():
	position = get_viewport_rect().size / 2
	direction = Vector2()
	speed = 100
	direction.x = rand_range(-1, 1)
	direction.y = rand_range(-1, 1)
	direction = direction.normalized()
	width = get_viewport_rect().size.x
	height = get_viewport_rect().size.y
	
func _process(delta):
	position += direction * speed * delta
	if position.x < 0 or position.x > width:
        direction.x *= -1
	if position.y <0 or position.y > width:
		direction.y *= -1
		
	
	
func _on_UFO_input_event(viewport, event, shape_idx):
	   if event is InputEventMouseButton and event.button_index == BUTTON_LEFT and event.pressed:
		