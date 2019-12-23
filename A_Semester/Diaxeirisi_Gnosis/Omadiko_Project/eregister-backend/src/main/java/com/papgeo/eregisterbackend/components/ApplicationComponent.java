package com.papgeo.eregisterbackend.components;

import com.papgeo.eregisterbackend.entities.ApplicantEntity;
import com.papgeo.eregisterbackend.entities.ApplicationEntity;
import com.papgeo.eregisterbackend.entities.SchoolEntity;
import com.papgeo.eregisterbackend.entities.UserEntity;
import com.papgeo.eregisterbackend.entities.dao.ApplicationDAO;
import com.papgeo.eregisterbackend.repositories.ApplicantRepository;
import com.papgeo.eregisterbackend.repositories.ApplicationRepository;
import com.papgeo.eregisterbackend.repositories.SchoolRepository;
import com.papgeo.eregisterbackend.repositories.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class ApplicationComponent {
    @Autowired
    private ApplicantRepository applicantRepository;

    @Autowired
    private ApplicationRepository applicationRepository;

    @Autowired
    private SchoolRepository schoolRepository;

    @Autowired
    private UserRepository userRepository;

    public void saveApplication(ApplicationDAO application, int userId){
        ApplicantEntity applicantEntity = applicantRepository.saveAndFlush(application.convertToApplicantEntity());

        UserEntity userEntity = userRepository.findByUserId(userId);

        SchoolEntity schoolEntity =  schoolRepository.findBySchoolId(application.getSchool_id());

        applicationRepository.saveAndFlush(application.convertToApplicationEntity(userEntity, applicantEntity,schoolEntity));

    }

    public List<ApplicationEntity> getApplications(int userId){

        UserEntity userEntity = userRepository.findByUserId(userId);

        return applicationRepository.findByUsersByUserId(userEntity);

    }
}
