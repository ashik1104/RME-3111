""" IMPLEMENTATION OF QUEUE USING LINKED LIST IN PYTHON """


class queue_node:
    def __init__(self, value):
        self.value = value
        self.next = None


class Queue:
    def __init__(self):
        self.__front = None
        self.__rear = None
        self.__count = 0

    def push(self, value):
        new_node = queue_node(value)
        if self.__front is None:
            self.__front = new_node
            self.__rear = new_node
            self.__count += 1
            return
        self.__rear.next = new_node
        self.__rear = self.__rear.next
        self.__count += 1

    def pop(self):
        if self.__rear is None:
            print('Queue underflow')
            return

        del_node = self.__front
        self.__front = self.__front.next

        if self.__front is None:
            self.__rear = None
        del del_node
        self.__count -= 1

    def Front(self):
        return self.__front.value

    def back(self):
        return self.__rear.value

    def size(self):
        return self.__count

    def empty(self):
        if self.__front is None and self.__rear is None:
            return True
        else:
            return False
