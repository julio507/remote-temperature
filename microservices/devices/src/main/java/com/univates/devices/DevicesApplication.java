package com.univates.devices;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.cloud.client.loadbalancer.LoadBalanced;
import org.springframework.context.annotation.Bean;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
import org.springframework.web.client.RestTemplate;

@SpringBootApplication
public class DevicesApplication {

	public static void main(String[] args) {
		SpringApplication.run(DevicesApplication.class, args);
	}

	@Bean
	@LoadBalanced
	public RestTemplate RestTemplate(){
		return new RestTemplate();
	}
}
