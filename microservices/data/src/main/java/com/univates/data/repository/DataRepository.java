package com.univates.data.repository;

import org.springframework.stereotype.Repository;

import com.univates.data.model.Data;

import org.springframework.data.jpa.repository.JpaRepository;

@Repository
public interface DataRepository extends JpaRepository<Data, Long>{
    
}
