import { isMainThread, parentPort, Worker } from 'node:worker_threads'

const arr = Array.from({ length: 2e6 }).map((_) => parseInt(Math.random() * 50))

const NUM_THREADS = 16

const size = parseInt(arr.length / NUM_THREADS)

async function createThread(data) {
  const worker = new Worker('./sum_tasks.mjs')

  const promise = new Promise((resolve, reject) => {
    worker.once('message', resolve)
    worker.once('error', reject)
  })

  worker.postMessage(data)

  return promise
}


console.time()
const threads = Array.from({ length: NUM_THREADS })
  .map((_, idx) => createThread(arr.slice(idx*size , (idx * size) + size)))
const results = await Promise.all(threads)
const total = results.reduce((prev, curr) => prev + curr, 0)
console.log('total', total)
console.timeEnd()
console.log(arr.reduce((prev, curr) => prev + curr), 0)

 

