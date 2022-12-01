const { Faker, faker } = require('@faker-js/faker')

const { RabbitMQServer } = require('./rabbit')

const rabbit = new RabbitMQServer()

const fake = new Faker({ locale: 'pt_BR', locales: faker.locales })

const messages = Array.from({ length: 10000 }).map((_) => ({
  id: fake.datatype.uuid(),
  price: fake.random.numeric(4),
  tax: fake.random.numeric(3),
}))

rabbit
  .connection(1)
  .then(() => {
    for (const message of messages) {
      rabbit.publish(JSON.stringify(message))
    }
  })
  .catch(console.log)
