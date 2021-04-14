package com.univates.devices;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

@SpringBootApplication
@EntityScan({"com.univates.core.model"})
@EnableJpaRepositories( {"com.univates.core.repository"} )
public class DevicesApplication {

	public static void main(String[] args) {
		SpringApplication.run(DevicesApplication.class, args);
	}

}
