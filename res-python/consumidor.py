import json
from time import sleep
from rabbit import Rabbit
from threading import Thread, Lock
from queue import Queue

NUM_THREADS = 10

queue = Queue()

lock = Lock()


def task_consumer(thread_name):
    while True:
        print("starter thread", thread_name)
        if not queue.empty():
            lock.acquire()
            message = queue.get(block=False)
            lock.release()
            print(message)
            sleep(10)


def on_message(channel, method_frame, header_frame, body):
    queue.put(json.loads(body))

    channel.basic_ack(delivery_tag=method_frame.delivery_tag)


rabbit = Rabbit()

rabbit.connect()

rabbit.channel.basic_consume(queue="ifc", on_message_callback=on_message)


if __name__ == "__main__":
    for i in range(NUM_THREADS):
        thread = Thread(target=task_consumer, args=([i]))
        thread.start()

    try:
        rabbit.channel.start_consuming()
    except KeyboardInterrupt:
        rabbit.channel.stop_consuming()
        rabbit.connection.close()
