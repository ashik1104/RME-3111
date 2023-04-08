""" Stack implementation using linked list """


class node:
    def __init__(self, value):
        self.value = value
        self.next = None
        self.prev = None


class Stack:
    def __init__(self):
        self.__head = None
        self.__top = None
        self.__count = 0

    def push(self, value):
        new_node = node(value)
        if self.__head is None:
            self.__head = self.__top = new_node
            self.__count += 1
            return
        self.__top.next = new_node
        new_node.prev = self.__top
        self.__top = new_node
        self.__count += 1

    def pop(self):
        del_node = self.__top
        if self.__head is None:
            print('Stack underflow')
        elif self.__top == self.__head:
            self.__top = self.__head = None
        else:
            self.__top = del_node.prev
            self.__top.next = None

        del del_node
        self.__count -= 1

    def empty(self):
        if self.__head is None:
            return True
        else:
            return False

    def Top(self):
        if self.__top is None:
            print('Stack underflow')
        else:
            return self.__top.value

    def size(self):
        return self.__count
