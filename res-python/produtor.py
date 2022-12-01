import json
from faker import Faker
from rabbit import Rabbit


if __name__ == "__main__":
    rabbit = Rabbit()

    rabbit.connect()

    rabbit.channel.queue_purge(queue="ifc")

    fake = Faker()

    for _ in range(10000):
        order = {"id": fake.uuid4(), "price": fake.random_number(digits=4), "tax": fake.random_number(digits=3)}
        rabbit.channel.basic_publish(exchange="", routing_key="ifc", body=json.dumps(order))
