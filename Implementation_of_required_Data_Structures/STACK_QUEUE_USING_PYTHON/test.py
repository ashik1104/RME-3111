class queue_node:
    def init(self, value):
        self.value = value
        self.next = None


class Queue:
    def init(self):
        self.front = None
        self.rear = None
        self.count = 0

    def push(self, value):
        new_node = queue_node(value)
        if self.front is None:
            self.front = new_node
            self.rear = new_node
            self.count += 1
            return
        self.rear.next = new_node
        self.rear = self.rear.next
        self.count += 1

    def pop(self):
        if self.rear is None:
            print('Queue underflow')
            return

        del_node = self.front
        self.front = self.front.next

        if self.front is None:
            self.rear = None
        del del_node
        self.count -= 1

    def Front(self):
        return self.front.value

    def back(self):
        return self.rear.value

    def size(self):
        return self.count

    def empty(self):
        if self.front is None and self.__rear is None:
            return True
        else:
            return False
