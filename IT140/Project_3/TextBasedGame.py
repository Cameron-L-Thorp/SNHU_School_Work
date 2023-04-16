#Cameron Thorp, IT-140 Introduction to Scripting, Project 3 Room Text Game

import os

#Simple function to keep screen from clearing while user reads
def wait():
    wait = input("Press enter to continue...")

#Allows for linkage of item to rooms
class RoomDefault:
    room_name : str = ""
    room_item : str = ""
    item_pickup : bool = False
    description : str = ""

    def __init__(self, name : str, item : str, present = False):
        self.room_name = name
        self.room_item = item
        self.item_pickup = present

#Create rooms with items
antechamber = RoomDefault("Antechamber", "")
dining_hall = RoomDefault("Dining Hall", "Cleaned Bones", True)
kings_quarters = RoomDefault("Kings Quarters", "Ritual Instructions", True)
kitchen = RoomDefault("Kitchen", "Mortar and Pestel", True)
laboratory = RoomDefault("Laboratory", "Strange Powder", True)
study = RoomDefault("Study", "Page of Knowledge", True)
throne_room = RoomDefault("Throne Room", "")
training_hall = RoomDefault("Training Hall", "Bloody Rag", True)
waiting_room = RoomDefault("Waiting Room", "Charcoal", True)
all_rooms = [antechamber, dining_hall, kings_quarters, kitchen, laboratory, study, throne_room, training_hall, waiting_room]

#Can the player perform the ritual?
all_items = ["Bloody Rag", "Charcoal", "Cleaned Bones", "Mortar and Pestel", "Page of Knowledge", "Ritual Instructions", "Strange Powder"]
items_without_instructions = ["Bloody Rag", "Charcoal", "Cleaned Bones", "Mortar and Pestel", "Page of Knowledge", "Strange Powder"]


#Full map of all rooms accessible to player
room_master_dict = {"Antechamber" : {"North": "Throne Room", "East": "Waiting Room", "West": "Training Hall"}, 
                    "Dining Hall": {"North": "Kitchen", "South": "Waiting Room"},
                    "Kings Quarters": {"East": "Laboratory", "South": "Study"},
                    "Kitchen": {"South": "Dining Hall", "West": "Laboratory"},
                    "Laboratory": {"East": "Kitchen", "West": "Kings Quarters"},
                    "Study": {"North": "Kings Quarters", "South": "Training Hall"},
                    "Throne Room": {"South": "Antechamber"},
                    "Training Hall": {"North": "Study", "East": "Antechamber"},
                    "Waiting Room": {"North": "Dining Hall", "West": "Antechamber"}}

#Allows for object creation to track player progress, position, and other info
class Player:
    player_name : str = "Bob"
    player_inventory : list = []
    player_location : RoomDefault = antechamber
    ritual_ready : bool= False

    #constructor
    def __init__(self):
        self.player_name : str = str(input("Enter your name adventurer: "))

    #Diplays current progress
    def player_status(self):
        item_ctr = 0
        print(f"Adventurer name: {self.player_name}", end="  |  ")
        print(f"Current locaiton: {self.player_location.room_name}")
        print(f"Inventory: ", end = "\t")
        if len(self.player_inventory) == 0:
            print("(empty)", end = " ")
        else:
            for item in self.player_inventory:
                item_ctr += 1
                if item_ctr % 3 == 0:
                   print(f"{item_ctr}. {item:<20}", end="\n           \t")
                else:
                   print(f"{item_ctr}. {item:<20}", end = " ")
        print()
    
    def item_pickup(self):
        if self.player_location.item_pickup:
            self.player_inventory.append(self.player_location.room_item)
            self.player_location.item_pickup = False
            print(f"You have picked up '{self.player_location.room_item}'")
        elif not self.player_location.item_pickup:
            print("There is no item in this room.")

def action_options(cur_player : Player):
    selected_action = ""
    available_actions = "['Move'"
    if cur_player.player_location.item_pickup:
        available_actions += ", 'Pickup'"
    if cur_player.player_location == antechamber:
        available_actions += ", 'Combine Ingredients'"
    if cur_player.player_location == throne_room:
        available_actions += ", 'Perform Ritual'"
    print(f"Please type an available action. {available_actions}", end = "]\n")
    selected_action = str(input("Action: ")).title().strip()
    while selected_action not in available_actions:
        print(f"Invalid action entered, please select from: {available_actions}", end="]\n")
        selected_action = str(input("Action: ")).title().strip()
    return selected_action
    

#Allows player to create ritual, or will inform them if they require more items
def combine_ingredients(cur_player : Player):
    if sorted(cur_player.player_inventory) == all_items:
        cur_player.ritual_ready = True
        print("You combine the ingredients together according to the instructions you found.\nAs you pulverize them and mix them in the mortar, a strong, unplacable odor begins to eminate from them.\nYou feel the hair on the back of your neck rise, the ritual must be ready.")
    elif sorted(cur_player.player_inventory) == items_without_instructions:
        cur_player.ritual_ready = True
        print("Assuming that you have what you need, you begin to mix the ingredients.\nA stench begins to come from them, that probably means it worked.\nOnly one way to find out...") 
    elif (sorted(cur_player.player_inventory) != all_items) and ("Ritual Instructions" in cur_player.player_inventory):
        print("You begin to read the scratchy writing on the instructions you found.\nIt looks like to perform the ritual, you still need...")
        for item in items_without_instructions:
            if item not in cur_player.player_inventory:
                print(item)
    elif cur_player.player_inventory == []:
        print("You don't have anything to combine yet.")
    else:
        print("You try to mix the ingredients together.\nNothing seems to happen, no sparks, no smells, no sign of any magic.\nIt's possible you're missing something.")
    wait()

#Checks to see if player has prepared ritual, and gives them their final choices.
def perform_ritual(cur_player : Player, cont_game : bool):
    if cur_player.ritual_ready:
        print("As you channel your concentration and fling the prepared powder at the Dracolich he scoffs.\n\"Foolish mortal, but you are brave. A fine addition you will be to my necrotic legion\"\nIt seems like the ritual had no effect...\n\nMoments later, you see the rotting nostrils of the undead dragon curl, as if he had inhaled something foul.\nRearing back to presumably engulf the room in eldrich flame and end your adventure, he unleashes a powerful sneeze.\nOne so powerful you feel the castle shudder and stone crack, the Dracolich was never meant to sneeze...\nBefore your eyes, his powerful form slowly starts to crumble as he unleashes his final words.\nYou can't understand his screams in draconic, but they carry a tone of anger and embarassment as the beast is no more.")
    else:
        print("The action you take seems to have no effect on the Dracolich.\nDeeply chuckling he utters \"A shame such a brave soul should die in such a meaningless way.\"\nBefore you can react, the room is engulfed with purple fires, ending your adventure.")
    wait()
    cont_game = False
    return cont_game

#Recieves user input for movement and moves if valid, otherwise prompts for different input
def move_player(cur_player : Player):
    chosen_dir = input("Enter the direction you would like to travel: ").title().strip() #Title case conversion to match key strings

    #Handles player exit without adding to room map
    while chosen_dir not in room_master_dict[cur_player.player_location.room_name]:
        if chosen_dir in ["Exit", "Quit"]:
            exit_function()
        elif chosen_dir == "Manual":
            manual_function()
            continue
        else:
            chosen_dir = input("Invalid direction, please enter a direction from the options listed.\nDirection: ").title().strip()
        
    if chosen_dir in room_master_dict[cur_player.player_location.room_name]:
        new_room = antechamber
        for room in all_rooms:
            if room.room_name == room_master_dict[cur_player.player_location.room_name][chosen_dir]:
                new_room = room
        cur_player.player_location = new_room
    
#Presents options for where players can move.
def movement_options(cur_player : Player):
    print(f"You are currently in the {cur_player.player_location.room_name}.")
    print(f"You may travel: ")
    for direction, room in room_master_dict[cur_player.player_location.room_name].items():
        print(f"{direction} to the {room}...")
    move_player(cur_player)

#Function to help player with gameplay
def manual_function():
    print("Manual:")
    print("- Enter your name to begin the game.")
    print("- Move my typing the direction of the destination room. [\"North\" | \"East\" | \"South\" | \"West\"]")
    print("- If there is an item in the room, type \"Pickup\" to add it to your inventory.")
    print("- Combine items in the Antechamber to create a ritual and defeat the Dracolich.")
    print("- If items are combined incorrectly or incompletely, the ritual will fail and you will be defeated (there may be an item to help you out).")
    print("- At any input, type \"Quit\" or \"Exit\" to leave the game or \"Manual\" to display these rules.")
    input("Press Enter to continue...")

#Funciton to enable smooth quitting
def exit_function():
    print("Thank you for playing.")
    exit()

#Primary function to run the program
def main():
    manual_function()
    adventurer = Player()
    os.system('cls')
    game_on = True
    while (game_on):
        adventurer.player_status()
        selected_action = action_options(adventurer)
        print(selected_action)
        match selected_action:
            case "Move":
                movement_options(adventurer)
            case "Pickup":
                adventurer.item_pickup()
            case "Combine Ingredients":
                combine_ingredients(adventurer)
            case "Perform Ritual":
                game_on = perform_ritual(adventurer, game_on)
            case "Manual":
                manual_function()
            case "Quit":
                exit_function()
            case "Exit":
                exit_function()
        os.system("cls")
    print("Thank you for playing! \nGame by: Cameron Thorp")
    

if __name__ == "__main__":
    main()