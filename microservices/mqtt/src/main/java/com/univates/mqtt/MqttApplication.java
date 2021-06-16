package com.univates.mqtt;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.web.client.RestTemplate;

@SpringBootApplication
public class MqttApplication {

	public static void main(String[] args) {
		SpringApplication.run(MqttApplication.class, args);

		RestTemplate template = new RestTemplate();

		List<LinkedHashMap<String, String>> devices = template.getForObject( "http://localhost:8080/devices/getAll", List.class );

		List<String> topics = new ArrayList<String>();

		for( LinkedHashMap<String, String> d : devices )
		{
			topics.add( d.get( "ip" ) );
		}

		Client.getIntance().connect(topics);
	}

}
