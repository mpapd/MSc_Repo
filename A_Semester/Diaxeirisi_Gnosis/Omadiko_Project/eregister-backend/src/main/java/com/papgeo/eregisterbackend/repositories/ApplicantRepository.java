package com.papgeo.eregisterbackend.repositories;

import com.papgeo.eregisterbackend.entities.ApplicantEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ApplicantRepository extends JpaRepository<ApplicantEntity, Integer> {

}
