from datetime import timedelta
from datetime import datetime


class schedule:
    early = {}
    soon = {}
    curr = {}

    def add(self, name ,session):
        if self.conflict(session) == False:
            self.early[name] = session

    def conflict(self, newSession):
        for name, session in self.early.items():
            if (newSession[0] >= session[0] and newSession[0] <= session[1]) or (newSession[1] >= session[0] and newSession[1] <= session[1]):
                return name

        for name, session in self.soon.items():
            if (newSession[0] >= session[0] and newSession[0] <= session[1]) or (newSession[1] >= session[0] and newSession[1] <= session[1]):
                return name

        return False

    def update(self):
        now = datetime.now()
        fifminlater = now + timedelta(minutes=15)

        for name, session in self.early.items():
            if now + fifminlater >= session:
                self.soon[name] = session

        for name, session in self.early.items():
            if now >= session[0] and now <= session[1]:
                self.curr[name] = session
                self.early.pop(name)

        for name, session in self.curr.items():
            if now > session[1]:
                self.curr.pop(name)

        
    def notify(self):
        for session in self.soon.items():
            name, time = session
            self.soon.pop(name)
            return session

        

    


        



