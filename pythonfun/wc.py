import sys

filename = sys.argv[1]

file = open(filename,"r")

doc = file.readlines()

wordlist = {}
total = 0
chars = 0

for line in doc:
    words = line.split()
    chars+=len(line)
    for word in words:
        total+=1
        if(word in wordlist.keys()):
            wordlist[word] += 1
        else:
            wordlist[word] = 1

print("lines:", len(doc), ", unique:",len(wordlist), ", words:",total, ", chars:",chars)

mostfrequent = max(wordlist, key=wordlist.get)

leastfrequent = min(wordlist, key=wordlist.get)


print("Most frequent word:",mostfrequent,"(",wordlist[mostfrequent],"times )","Least frequent word:",min(wordlist),"(",wordlist[min(wordlist)],"times )")

