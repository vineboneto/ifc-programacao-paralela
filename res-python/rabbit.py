class Rabbit:
    def connect(self):
        import pika

        self.connection = pika.BlockingConnection(pika.ConnectionParameters("localhost"))

        self.channel = self.connection.channel()

        self.channel.queue_declare(queue="ifc")
