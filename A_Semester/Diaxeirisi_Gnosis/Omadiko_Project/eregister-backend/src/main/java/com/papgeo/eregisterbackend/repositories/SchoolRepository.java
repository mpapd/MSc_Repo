package com.papgeo.eregisterbackend.repositories;

import com.papgeo.eregisterbackend.entities.CategoryEntity;
import com.papgeo.eregisterbackend.entities.SchoolEntity;
import com.papgeo.eregisterbackend.entities.SchoolTypeEntity;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface SchoolRepository extends JpaRepository<SchoolEntity, Integer> {
    List<SchoolEntity> findByCategoriesByCategoryIdAndDistrictEngAndTownEng(CategoryEntity categoryEntity, String districtEng, String town);
    List<SchoolEntity> findBySchoolTypesBySchoolTypeIdAndTownEng(SchoolTypeEntity schoolTypeEntity, String town);
    SchoolEntity findBySchoolId(Integer schoolId);
}
