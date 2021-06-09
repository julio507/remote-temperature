package com.univates.mqtt;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class Subscriber {

    private String device;

    private String[] topics;
    private IMqttMessageListener[] listeners;

    public Subscriber(String device) {
        this.device = device;

        topics = new String[] { device + "/sensor" };

        listeners = new IMqttMessageListener[] { new IMqttMessageListener() {
            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {
                System.out.println(topic + message);
            }
        } };
    }

    public String[] getTopics(){
        return topics;
    }

    public IMqttMessageListener[] getListeners(){
        return listeners;
    }
}
