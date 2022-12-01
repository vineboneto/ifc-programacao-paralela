const { connect } = require('amqplib')

class RabbitMQServer {
  constructor() {
    this.mapper = new Map()
    this.count = 1
  }

  async connection(totalChannels = 1) {
    this.conn = await connect('amqp://guest:guest@localhost:5672')
    for (let i = 0; i < totalChannels; i++) {
      console.log(i)
      const channel = await this.conn.createChannel()
      await channel.prefetch(1)
      const key = i + 1
      this.mapper.set(key, channel)
    }
    await this.mapper.get(1).assertQueue('ifc')
  }

  publish(message) {
    const result = this.mapper.get(1).sendToQueue('ifc', Buffer.from(message))
  }

  async consume(queue, callback) {
    for (const channel of Array.from(this.mapper.values())) {
      channel.consume(queue, async (message) => {
        try {
          const content = JSON.parse(message.content?.toString())
          await callback(content)
          await channel.ack(message)
        } catch {
          channel.reject(message, false)
        }
      })
    }
  }
}

module.exports = { RabbitMQServer }
