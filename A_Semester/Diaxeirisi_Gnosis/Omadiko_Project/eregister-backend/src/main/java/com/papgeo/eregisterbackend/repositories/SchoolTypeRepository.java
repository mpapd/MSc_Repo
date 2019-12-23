package com.papgeo.eregisterbackend.repositories;

import com.papgeo.eregisterbackend.entities.SchoolTypeEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface SchoolTypeRepository extends JpaRepository<SchoolTypeEntity, Integer> {
    SchoolTypeEntity findBySchoolTypeId(Integer schoolTypeId);
}
