package com.papgeo.eregisterbackend.components;

import com.papgeo.eregisterbackend.entities.SchoolEntity;
import com.papgeo.eregisterbackend.entities.SchoolTypeEntity;
import com.papgeo.eregisterbackend.repositories.CategoryRepository;
import com.papgeo.eregisterbackend.repositories.SchoolRepository;
import com.papgeo.eregisterbackend.repositories.SchoolTypeRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class SchoolComponent {

    @Autowired
    private SchoolRepository schoolRepository;

    @Autowired
    private CategoryRepository categoryRepository;

    @Autowired
    private SchoolTypeRepository schoolTypeRepository;

    public List<SchoolEntity> getSchoolsByCategoryAndDistrict(String town, String district, Integer categoryId){
        return schoolRepository.findByCategoriesByCategoryIdAndDistrictEngAndTownEngAndSchoolTypesBySchoolTypeId(categoryRepository.findByCategoryId(categoryId), district, town,schoolTypeRepository.findBySchoolTypeId(1));
    }

    public List<SchoolEntity> getSpecialSchoolsByTown(Integer school_type_id, String town){
        return schoolRepository.findBySchoolTypesBySchoolTypeIdAndTownEng(schoolTypeRepository.findBySchoolTypeId(school_type_id),town);

    }



}
