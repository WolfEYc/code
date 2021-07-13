""" Eliza homework. Answers Questions """
__author__="Jude McKenna"
import re

def detectFamily(username):
    if(username== "mom" or username == "mother" or username == "dad" or username == "father" or username == "brother" or username == "sister" or username == "friend"):
        return True
    return False


username = input('What is your name?: ')

if(detectFamily(username)):
    print("Hey family member: ", username)
else:
    print("Nice to meet you,", username)

print("How are you today?")
userInput = input()
while (userInput != "bye"):
    person = username
    family = []
    data = userInput.split(" ");
    for word in data:
        if detectFamily(word):
            family.append(word);

    sad = re.findall(r'sad|crummy|worry',userInput)
    ok = re.findall(r'ok|eh|alright|fine',userInput)
    good = re.findall(r'good|decent|well',userInput)
    bad = re.findall(r'bad|not good|trash|terrible|horrible|badly|sucks|worst|poor',userInput)
    joy = re.findall(r'joy|awesome|fantastic|amazing|great|epic',userInput)
    happy = re.findall(r'happy|smil+.*|glad',userInput)
    edVerbs = re.findall(r'(\w+ed)',userInput)


    if not len(family) == 0:
        person = family[0]
    
    if sad != []:
        print(f'why is {person} sad')
    elif happy != []:
        print(f'Glad that {person} is {happy[0]}')
    elif joy != []:
        print (f"Enjoy, {person} haha")
    elif ok != []:
        print(f"ok is ok to be {person}")
    elif bad != []:
        print(f"That's {bad[0]}, feel better {person}")
    elif good != []:
        print(f"Good to know {person} is {good[0]}")
    elif edVerbs != []:
        verb = edVerbs[0][:len(edVerbs[0]) - 2]
        print(f"{person} {verb}ed eh?")
    else:
        print("interesting...")
    
        
    

    userInput = input()