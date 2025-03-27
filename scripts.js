const brokerUrl = 'ws://broker.emqx.io:8083/mqtt';
const topicTemperature = "120323430448/dht22/temp";
const topicHumidity = "120323430448/dht22/hum";

const client = new MQTTClient(brokerUrl);
const options = { qos: 2, retain: true };

client.onConnect = () => {
    client.subscribe(topicTemperature);
    client.subscribe(topicHumidity);
};

client.onMessage = (topic, message) => {
    console.log('Topic:', topic);
    console.log('Message:', message.toString());
};

client.connect();