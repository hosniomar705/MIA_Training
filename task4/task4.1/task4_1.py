from oop import gru
from oop import vector
import random
import time

#pass character stats so we can print it
def print_stats(stats):
    print(f"health:{stats[0]}\nenergy:{stats[1]}\nshield:{stats[2]}%\n")
#pass game mode 1 for one player mode 2 for two player mode and get from user the character, he wants to play with (gru or vector) 
#return created villains
def get_characters(mode):
    #first we print available characters
    print("available characters: 1- gru 2- vector")
    #we ask player1 to enter number of wanted character

    player1 = int(input("player1 choose a character:"))
    #to check if player1 enter a correct choice
    while(player1 != 1 and player1 != 2):
        player1 = int(input("Choose valid character (1,2): "))
    #create villain that  the player1 chose
    player1 = gru(100,500) if player1==1 else vector(100,500)
    #if user enter one player mode we create pc villain not the same as the player chose

    if mode == 1:
        pc = vector(100,500) if player1.name()=="gru" else gru(100,500)
        #return created villains
        return player1,pc
    
    #we ask player2 to enter number of wanted character
    player2 = int(input("player2 choose a character:"))
    #to check if player2 enter a correct choice
    while(player2 != 1 and player2 != 2):
        player2 = int(input("Choose valid character (1,2): "))
    #create villain that  the player2 chose
    player2 = gru(100,500) if player2==1 else vector(100,500)
    #return created villains
    return player1,player2


#two_player_mode fun will start two_player_mode game
def two_player_mode():
    #first create villains
    player1,player2 = get_characters(2)
    #set turn = 1 so player one will start
    turn = 1

    #game will still running untill break statement happens
    #player die health =0
    #or player cant make any moves because he dont have enough energy to make min energy needed to make a move
    while 1:
        #check if one of the player die or ran of energy
        if player1.return_stats()[0] == 0 or player1.return_stats()[1] < player1.min_energy_to_play():
            print("congratulations pc won,hard luck player1")
            break
        elif player2.return_stats()[0] == 0 or player1.return_stats()[1] < player2.min_energy_to_play():
            print("congratulations player1 won,hard luck player2")
            break
        #we ask player if he wants to attack or defend
        player_move = int(input("Choose 1-attack or 2-shield:"))
        #check if the player entered a valid input
        while(player_move != 1 and player_move != 2):
            player_move = int(input("Choose 1-attack or 2-shield:"))
        
        #first if a player choose to attack
        if player_move ==1:
            #check if player1 or player2 who will play
            if turn == 1:
                #print available_weapons that the player1 has
                available_weapons = list(player1.available_weapons())
                for i in range(len(available_weapons)):
                    print(f"{i+1}-{available_weapons[i]}")
                #ask player1 to choose a weapon
                weapontype = int(input("Choose a weapon: "))
                #check if user enter a valid input
                while(weapontype not in range(1,len(available_weapons)+1)):
                    weapontype = int(input("Choose a valid weapon: "))
                #store damage that the weapon deals so we can damage the other player
                damage = player1.weapons(available_weapons[weapontype-1])

                #check if damage is a number or an error message ("not enough energy" or "not enough resources")
                if isinstance(damage,int):
                    #if damage is a number we check if the weapon has a special feature
                    if available_weapons[weapontype-1] == "Kalman Missile":
                        player2.set_shield(0)
                    elif available_weapons[weapontype-1] == "Mega Magnet":
                        player1.set_shield(20)
                    #deal damage to player2
                    player2.damage_taken(damage)


                else :
                    # if damage not a number we print error message 
                    #and then we continue so we dont swap the turns and player1 play again
                    print(damage)
                    continue
                #after each round we reset player2 shield so the shield is valid for only one round
                player2.set_shield(0)
            
            #check if player1 or player2 who will play
            elif turn == 2:
                #print available_weapons that the player2 has
                available_weapons = list(player2.available_weapons())
                for i in range(len(available_weapons)):
                    print(f"{i+1}-{available_weapons[i]}")
                #ask player1 to choose a weapon
                weapontype = int(input("Choose a weapon: "))
                #check if user enter a valid input
                while(weapontype not in range(1,len(available_weapons)+1)):
                    weapontype = int(input("Choose a valid weapon: "))
                #store damage that the weapon deals so we can damage the other player
                damage = player2.weapons(available_weapons[weapontype-1])

                #check if damage is a number or an error message ("not enough energy" or "not enough resources")
                if isinstance(damage,int):
                    #if damage is a number we check if the weapon has a special feature
                    if available_weapons[weapontype-1] == "Kalman Missile":
                        player1.set_shield(0)
                    elif available_weapons[weapontype-1] == "Mega Magnet":
                        player2.set_shield(20)
                    #deal damage to player1
                    player1.damage_taken(damage)
                else :
                    # if damage not a number we print error message 
                    #and then we continue so we dont swap the turns and player2 plays again
                    print(damage)
                    continue
                #after each round we reset player1 shield so the shield is valid for only one round
                player1.set_shield(0)

        #first if a player choose to defend
        if player_move ==2:
            #check if player1 or player2 who will play
            if turn == 1:
                #print available_shields that the player1 has
                available_shields = list(player1.available_shields())
                for i in range(len(available_shields)):
                    print(f"{i+1}-{available_shields[i]}")
                #ask player1 to choose a shield
                shieldtype = int(input("Choose a shield: "))
                #check if user enter a valid input
                while(shieldtype not in range(1,len(available_shields)+1)):
                    shieldtype = int(input("Choose a valid shield: "))
                #store shield percentage for the shield that the player1 chose
                shield = player1.shields(available_shields[shieldtype-1])

                #check if shield is a number or an error message ("not enough energy" or "not enough resources")
                if isinstance(shield,int):
                    #set shield for player1
                    player1.set_shield(shield)
                else :
                    # if shield not a number we print error message 
                    #and then we continue so we dont swap the turns and player1 plays a gain
                    print(shield)
                    continue
                #after each round we reset player2 shield so the shield is valid for only one round
                player2.set_shield(0)
            
            #check if player1 or player2 who will play
            if turn == 2:
                #print available_shields that the player2 has
                available_shields = list(player2.available_shields())
                for i in range(len(available_shields)):
                    print(f"{i+1}-{available_shields[i]}")
                #ask player1 to choose a shield
                shieldtype = int(input("Choose a shield: "))
                #check if user enter a valid input
                while(shieldtype not in range(1,len(available_shields)+1)):
                    shieldtype = int(input("Choose a valid shield: "))
                #store shield percentage for the shield that the player2 chose
                shield = player2.shields(available_shields[shieldtype-1])

                #check if shield is a number or an error message ("not enough energy" or "not enough resources")
                if isinstance(shield,int):
                    #set shield for player2
                    player2.set_shield(shield)
                else :
                    # if shield not a number we print error message 
                    #and then we continue so we dont swap the turns and player1 plays a gain
                    print(shield)
                    continue
                #after each round we reset player1 shield so the shield is valid for only one round
                player1.set_shield(0)
        #after each round we print players stats
        print("player1:")
        print_stats(player1.return_stats())
        print("player2:")
        print_stats(player2.return_stats())
        #swap turns
        turn = 1 if turn==2 else 2



#one_player_mode fun will start one_player_mode game
def one_player_mode():
    #first create villains
    player1,pc = get_characters(1)
    #set turn = 1 so player one will start
    turn = 1

    #game will still running untill break statement happens
    #player die health =0
    #or player cant make any moves because he dont have enough energy to make min energy needed to make a move
    while 1:
        #check if one of the player die or ran of energy
        if player1.return_stats()[0] == 0 or player1.return_stats()[1] < player1.min_energy_to_play():
            print("game over!! pc won,hard luck player1")
            break
        elif pc.return_stats()[0] == 0 or player1.return_stats()[1] < pc.min_energy_to_play():
            print("congratulations you won")
            break
        #we ask player1 if he wants to attack or defend
        if turn == 1:
            player_move = int(input("Choose 1-attack or 2-shield:"))
            while(player_move != 1 and player_move != 2):
                player_move = int(input("Choose 1-attack or 2-shield:"))
        #if pc will play , it will choose randomly between 1 or 2
        else:
            player_move = random.randint(1, 2)
        
        #first if a player choose to attack
        if player_move ==1:
            #check if player1 or pc who will play
            if turn == 1:
                #print available_weapons that the player1 has
                available_weapons = list(player1.available_weapons())
                for i in range(len(available_weapons)):
                    print(f"{i+1}-{available_weapons[i]}")
                #ask player1 to choose a weapon
                weapontype = int(input("Choose a weapon: "))
                #check if user enter a valid input
                while(weapontype not in range(1,len(available_weapons)+1)):
                    weapontype = int(input("Choose a valid weapon: "))
                #store damage that the weapon deals so we can damage the other player
                damage = player1.weapons(available_weapons[weapontype-1])

                #check if damage is a number or an error message ("not enough energy" or "not enough resources")         
                if isinstance(damage,int):
                    #if damage is a number we check if the weapon has a special feature
                    if available_weapons[weapontype-1] == "Kalman Missile":
                        pc.set_shield(0)
                    elif available_weapons[weapontype-1] == "Mega Magnet":
                        player1.set_shield(20)
                    #deal damage to pc
                    pc.damage_taken(damage)


                else :
                    # if damage not a number we print error message 
                    #and then we continue so we dont swap the turns and player1 play again
                    print(damage)
                    continue
                
                #after each round we reset pc shield so the shield is valid for only one round
                pc.set_shield(0)
            
            #check if player1 or pc who will play
            elif turn == 2:
                #we set a delay so player1 can read the stats before pc plays
                print("pc is calculating the best move :)")
                time.sleep(1)
                available_weapons = list(pc.available_weapons())
                #we will make pc choose randomly between weapons
                weapontype = random.randint(1,len(available_weapons))
                #store damage that the weapon deals so we can damage the other player
                damage = pc.weapons(available_weapons[weapontype-1])

                #check if damage is a number or an error message ("not enough energy" or "not enough resources")
                if isinstance(damage,int):
                    #if damage is a number we check if the weapon has a special feature
                    if available_weapons[weapontype-1] == "Kalman Missile":
                        player1.set_shield(0)
                    elif available_weapons[weapontype-1] == "Mega Magnet":
                        pc.set_shield(20)
                    #deal damage to player1
                    player1.damage_taken(damage)
                    #print pc weapon name to the user
                    print(f"pc chose weapon: {available_weapons[weapontype-1]}")
                else :
                    # if damage not a number 
                    #then we continue so we dont swap the turns and player1 play again
                    continue
                #after each round we reset player1 shield so the shield is valid for only one round
                player1.set_shield(0)

        #first if a player choose to defend
        if player_move ==2:
            #check if player1 or player2 who will play
            if turn == 1:
                #print available_shields that the player1 has
                available_shields = list(player1.available_shields())
                for i in range(len(available_shields)):
                    print(f"{i+1}-{available_shields[i]}")
                #ask player1 to choose a shield
                shieldtype = int(input("Choose a shield: "))
                #check if user enter a valid input
                while(shieldtype not in range(1,len(available_shields)+1)):
                    shieldtype = int(input("Choose a valid shield: "))
                #store shield percentage for the shield that the player1 chose
                shield = player1.shields(available_shields[shieldtype-1])

                #check if shield is a number or an error message ("not enough energy" or "not enough resources")
                if isinstance(shield,int):
                    #set shield for player1
                    player1.set_shield(shield)
                else :
                    # if shield not a number we print error message 
                    #and then we continue so we dont swap the turns and player1 plays a gain
                    print(shield)
                    continue
                #after each round we reset player2 shield so the shield is valid for only one round
                pc.set_shield(0)
            
            #check if player1 or player2 who will play
            if turn == 2:
                #we set a delay so player1 can read the stats before pc plays
                print("pc is calculating the best move :)")
                time.sleep(1)
                #we will make pc choose randomly between weapons
                available_shields = list(pc.available_shields())
                shieldtype = random.randint(1,len(available_shields))
                #store shield percentage for the shield that the player1 chose
                shield = pc.shields(available_shields[shieldtype-1])

                 #check if shield is a number or an error message ("not enough energy" or "not enough resources")
                if isinstance(shield,int):
                    #set shield for pc
                    pc.set_shield(shield)
                    #print pc shield name to the user
                    print(f"pc chose Shield: {available_shields[shieldtype-1]}")
                else :
                    # if damage not a number 
                    #then we continue so we dont swap the turns and player1 play again
                    continue
                #after each round we reset player1 shield so the shield is valid for only one round
                player1.set_shield(0)

        #after each round we print players stats
        print("player1:")
        print_stats(player1.return_stats())
        print("pc:")
        print_stats(pc.return_stats())
        #swap turns
        turn = 1 if turn==2 else 2
               


#start the game 
def start_game():
    print("Welcome to SKY CLASH")
    #make the user enter game mode
    print("Game modes : 1-one player mode 2-two player mode")
    game_mode = int(input("Choose game mode (1,2): "))
    #check if user entered a valid input
    while(game_mode != 1 and game_mode != 2):
        game_mode = int(input("Choose valid game mode (1,2): "))
    #if user chose one_player_mode we call one_player_mode fun or two_player_mode we call two_player_mode fun 
    if game_mode==1:
        one_player_mode()
    else:
        two_player_mode()


play_again ="y"
#check if player wants to play again
while(play_again == "y" or play_again == "Y"):
    start_game()
    play_again = input("To play again enter (y):")

