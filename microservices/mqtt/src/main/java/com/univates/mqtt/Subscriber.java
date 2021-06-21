package com.univates.mqtt;

import java.util.Date;

import com.univates.mqtt.model.Data;
import com.univates.mqtt.model.Device;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.web.client.RestTemplate;

public class Subscriber {

    private Device device;

    private String[] topics;
    private IMqttMessageListener[] listeners;

    public Subscriber(Device device) {
        this.device = device;

        topics = new String[] { device.getIp() + "/sensor" };

        listeners = new IMqttMessageListener[] { new IMqttMessageListener() {
            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                RestTemplate template = new RestTemplate();

                String[] data = message.toString().split(";");

                Data d = new Data();

                d.setDate( new Date() );
                d.setTemperature(Double.parseDouble(data[0]));
                d.setHumidity(Double.parseDouble(data[1]));
                d.setDevice( device );

                template.postForEntity("http://localhost:8080/data/save", d, Data.class);

                System.out.print(d);
            }
        } };
    }

    public String[] getTopics() {
        return topics;
    }

    public IMqttMessageListener[] getListeners() {
        return listeners;
    }
}
