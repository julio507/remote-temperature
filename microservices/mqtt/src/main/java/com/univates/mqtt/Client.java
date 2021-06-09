package com.univates.mqtt;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.UUID;

import com.univates.core.model.Device;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

public class Client {

    private List<Subscriber> subs = new ArrayList();

    private static Client instance;
    MqttClient client;

    private Client() {
    }

    public static Client getIntance() {
        if (instance == null) {
            instance = new Client();
        }

        return instance;
    }

    public void publish(String topic, String message) {
        try {
            client.publish(topic, new MqttMessage(message.getBytes()));
        }

        catch (MqttException e) {
            e.printStackTrace();
        }
    }

    public void connect(List<String> topics) {
        for (String t : topics) {
            subs.add(new Subscriber(t));
        }

        connect();
    }

    private void connect() {

        try {
            if (client == null) {
                MemoryPersistence persistence = new MemoryPersistence();
                client = new MqttClient("tcp://localhost:1883", UUID.randomUUID().toString(), persistence);
                MqttConnectOptions connOpts = new MqttConnectOptions();
                connOpts.setCleanSession(true);
                client.connect(connOpts);
            }

            List<String> topics = new ArrayList<String>();
            List<IMqttMessageListener> listeners = new ArrayList();

            for (Subscriber s : subs) {
                topics.addAll(Arrays.asList(s.getTopics()));
                listeners.addAll(Arrays.asList(s.getListeners()));
            }

            IMqttToken token = client.subscribeWithResponse(topics.toArray(new String[topics.size()]),
                    listeners.toArray(new IMqttMessageListener[listeners.size()]));

            token.waitForCompletion();

        } catch (MqttException me) {
            me.printStackTrace();
        }
    }
}
