const { RabbitMQServer } = require('./rabbit')

const rabbit = new RabbitMQServer()

const sleep = (ms) => new Promise((resolve) => setTimeout(resolve, ms))

rabbit
  .connection(10)
  .then(async () => {
    await rabbit.consume('ifc', async (message) => {
      console.log(message)
      await sleep(1000)
    })
  })
  .catch(console.log)
