import { parentPort } from "node:worker_threads"

parentPort.once('message', (message) => {
  const sum = message.reduce((prev, curr) => prev + curr, 0)
  parentPort.postMessage(sum)
})