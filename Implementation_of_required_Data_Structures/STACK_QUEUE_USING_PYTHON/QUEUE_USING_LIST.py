""" Queue implementation using built in list """


class Queue:
    def __init__(self):
        self.list = []

    def push(self, value):
        self.list.append(value)

    def pop(self):
        self.list.pop(0)

    def front(self):
        return self.list[0]

    def back(self):
        return self.list[-1]

    def size(self):
        return len(self.list)

    def empty(self):
        if len(self.list) == 0:
            return True
        else:
            return False
