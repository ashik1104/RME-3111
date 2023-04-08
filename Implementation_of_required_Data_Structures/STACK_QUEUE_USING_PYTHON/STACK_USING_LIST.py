""" Stack implementation using built in list """


class Stack:
    def __init__(self):
        self.__list = []

    def push(self, value):
        self.__list.append(value)

    def pop(self):
        self.__list.pop()

    def empty(self):
        if len(self.__list) == 0:
            return True
        else:
            return False

    def Top(self):
        return self.__list[-1]

    def size(self):
        return len(self.__list)
