extends Node

onready var player:Player = $Player
onready var ScoreTimer:Timer = $ScoreTimer
onready var StartTimer:Timer = $StartTimer
onready var MobTimer:Timer = $MobTimer
onready var Music:AudioStreamPlayer = $Music
onready var DeathSound:AudioStreamPlayer = $DeathSound
onready var HUD:CanvasLayer = $HUD
onready var StartPosition:Position2D = $StartPosition


export(PackedScene) var mob_scene
var score



func _ready():
	randomize()
	new_game()
	player.connect("hit",self,"game_over")

func game_over():
	ScoreTimer.stop()
	MobTimer.stop()
	
	Music.stop()
	DeathSound.play()
	
	HUD.show_game_over()
	
func new_game():
	score = 0
	player.start(StartPosition.position)
	StartTimer.start()
	Music.play()
	
	HUD.update_score(score)
	HUD.show_message("Get Ready")
	
	get_tree().call_group("mobs","Queue_free")


func _on_MobTimer_timeout():
	# Create a new instance of the Mob Scene.
	var mob=mob_scene.instance()
	
	# Choose a random location on Path2D
	var mob_spawn_location= get_node("MobPath/MobSpawnLocation")
	mob_spawn_location.offset = randi()

	# Set the mob's direction perpendicular to the path direction
	var direction= mob_spawn_location.rotation + PI/2
	
	mob.position = mob_spawn_location.position
	
	# Add some randomness to the direction
	direction += rand_range(-PI / 4, PI / 4)
	mob.rotation = direction
	
	# Choose the velocity for the mob.
	var velocity = Vector2(rand_range(150,250),0)
	mob.linear_velocity = velocity.rotated(direction)
	
	# Spawn the mob by adding it to the Main Scene
	add_child(mob)

func _on_ScoreTimer_timeout():
	score+=1
	HUD.update_score(score)


func _on_StartTimer_timeout():
	MobTimer.start()
	ScoreTimer.start()


