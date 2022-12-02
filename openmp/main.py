import threading
import random
import time

TOTAL  = 2000000
NUM_THREADS = 16
SIZE = int(TOTAL / NUM_THREADS)
arr = []
threads = []
results = []

def task_sum(arr, ):
  total = sum(arr)
  results.append(total)

for i in range(TOTAL):
  arr.append(random.randint(0, 50))
  
if __name__ == '__main__':
  start_time = time.time()
  for i in range(NUM_THREADS):
    t = threading.Thread(target=task_sum, args=(arr[i*SIZE : (i * SIZE) + SIZE], ))
    threads.append(t)
    t.start()
    
  for t in threads:
    v = t.join()
    
  print(sum(results))
  print("--- %s seconds ---" % (time.time() - start_time))
  # print(sum(arr))