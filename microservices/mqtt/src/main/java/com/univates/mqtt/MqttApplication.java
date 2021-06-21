package com.univates.mqtt;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.client.RestTemplate;

@SpringBootApplication
public class MqttApplication {

	public static void main(String[] args) {
		SpringApplication.run(MqttApplication.class, args);

		Client.getIntance().refresh();
	}

}
