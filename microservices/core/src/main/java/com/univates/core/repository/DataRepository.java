package com.univates.core.repository;

import org.springframework.stereotype.Repository;

import com.univates.core.model.Data;

import org.springframework.data.jpa.repository.JpaRepository;

@Repository
public interface DataRepository extends JpaRepository<Data, Long>{
    
}
