""" Eliza homework. Answers Questions """
author="Jude McKenna"
import re
username = input('What is your name?: ')
if(username== "mom" or username == username == "mother" or username == "dad" or username == "father" or username == "brother" or username == "sister" or username == "friend"):
    print("Hey family member: ", username)
else:
    print("Nice to meet you,", username)
print("How are you today?")
userInput = input()
while (userInput != "bye"):
    sad = re.findall(r'sad',userInput)
    ok = re.findall(r'ok',userInput)
    good = re.findall(r'good',userInput)
    bad = re.findall(r'bad',userInput)
    joy = re.findall(r'joy',userInput)
    happy = re.findall(r'happy',userInput)
    edVerbs = re.findall(r'(w+ed)',userInput)
    if sad != []:
        print("why are you sad")
    elif happy != []:
        print("Glad that you are happy")
    elif joy != []:
        print ("Enjoy, haha")
    elif ok != []:
        print("ok is ok to be")
    elif good != []:
        print("Good to know you are good")
    elif bad != []:
        print("Too bad feel better")
    elif edVerbs != []:
        verb = edVerbs[0][:len(edVerbs[0]) - 2]
        print(verb)
    else:
        print("")
    print("Let's talk about something else")
    userInput = input()