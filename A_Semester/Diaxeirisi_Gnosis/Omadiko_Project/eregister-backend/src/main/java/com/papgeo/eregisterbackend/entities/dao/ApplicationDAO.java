package com.papgeo.eregisterbackend.entities.dao;

import com.papgeo.eregisterbackend.entities.ApplicantEntity;
import com.papgeo.eregisterbackend.entities.ApplicationEntity;
import com.papgeo.eregisterbackend.entities.SchoolEntity;
import com.papgeo.eregisterbackend.entities.UserEntity;

import java.sql.Timestamp;

public class ApplicationDAO {

    private String firstname;
    private String lastname;
    private String fathername;
    private String mothername;
    private Timestamp birthdate;
    private String town;
    private String townEng;
    private String district;
    private String districtEng;
    private String street;
    private String foreignLanguage1;
    private String foreignLanguage2;
    private String optionalClass1;
    private String optionalClass2;
    private int school_id;
    private String comments;

    public ApplicationDAO() {
    }

    public ApplicationDAO(String firstname, String lastname, String fathername, String mothername, Timestamp birthdate, String town, String townEng, String district, String districtEng, String street, String foreignLanguage1, String foreignLanguage2, String optionalClass1, String optionalClass2, int school_id, String comments) {
        this.firstname = firstname;
        this.lastname = lastname;
        this.fathername = fathername;
        this.mothername = mothername;
        this.birthdate = birthdate;
        this.town = town;
        this.townEng = townEng;
        this.district = district;
        this.districtEng = districtEng;
        this.street = street;
        this.foreignLanguage1 = foreignLanguage1;
        this.foreignLanguage2 = foreignLanguage2;
        this.optionalClass1 = optionalClass1;
        this.optionalClass2 = optionalClass2;
        this.school_id = school_id;
        this.comments = comments;
    }

    public String getFirstname() {
        return firstname;
    }

    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }

    public String getLastname() {
        return lastname;
    }

    public void setLastname(String lastname) {
        this.lastname = lastname;
    }

    public String getFathername() {
        return fathername;
    }

    public void setFathername(String fathername) {
        this.fathername = fathername;
    }

    public String getMothername() {
        return mothername;
    }

    public void setMothername(String mothername) {
        this.mothername = mothername;
    }

    public Timestamp getBirthdate() {
        return birthdate;
    }

    public void setBirthdate(Timestamp birthdate) {
        this.birthdate = birthdate;
    }

    public String getTown() {
        return town;
    }

    public void setTown(String town) {
        this.town = town;
    }

    public String getTownEng() {
        return townEng;
    }

    public void setTownEng(String townEng) {
        this.townEng = townEng;
    }

    public String getDistrict() {
        return district;
    }

    public void setDistrict(String district) {
        this.district = district;
    }

    public String getDistrictEng() {
        return districtEng;
    }

    public void setDistrictEng(String districtEng) {
        this.districtEng = districtEng;
    }

    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    public String getForeignLanguage1() {
        return foreignLanguage1;
    }

    public void setForeignLanguage1(String foreignLanguage1) {
        this.foreignLanguage1 = foreignLanguage1;
    }

    public String getForeignLanguage2() {
        return foreignLanguage2;
    }

    public void setForeignLanguage2(String foreignLanguage2) {
        this.foreignLanguage2 = foreignLanguage2;
    }

    public String getOptionalClass1() {
        return optionalClass1;
    }

    public void setOptionalClass1(String optionalClass1) {
        this.optionalClass1 = optionalClass1;
    }

    public String getOptionalClass2() {
        return optionalClass2;
    }

    public void setOptionalClass2(String optionalClass2) {
        this.optionalClass2 = optionalClass2;
    }

    public int getSchool_id() {
        return school_id;
    }

    public void setSchool_id(int school_id) {
        this.school_id = school_id;
    }

    public String getComments() {
        return comments;
    }

    public void setComments(String comments) {
        this.comments = comments;
    }

    public ApplicantEntity convertToApplicantEntity(){
        ApplicantEntity applicantEntity = new ApplicantEntity();
        applicantEntity.setBirthdate(this.birthdate);
        applicantEntity.setDistrict(this.district);
        applicantEntity.setDistrictEng(this.districtEng);
        applicantEntity.setFathername(this.fathername);
        applicantEntity.setMothername(this.mothername);
        applicantEntity.setFirstname(this.firstname);
        applicantEntity.setLastname(this.lastname);
        applicantEntity.setForeignLanguage1(this.foreignLanguage1);
        applicantEntity.setForeignLanguage2(this.foreignLanguage2);
        applicantEntity.setOptionalClass1(this.optionalClass1);
        applicantEntity.setOptionalClass2(this.optionalClass2);
        applicantEntity.setTown(this.town);
        applicantEntity.setTownEng(this.townEng);
        applicantEntity.setStreet(this.street);
        return applicantEntity;
    }

    public ApplicationEntity convertToApplicationEntity(UserEntity userEntity, ApplicantEntity applicantEntity, SchoolEntity schoolEntity){
        ApplicationEntity applicationEntity = new ApplicationEntity();
        applicationEntity.setComments(this.comments);
        applicationEntity.setDate(new Timestamp(System.currentTimeMillis()));
        applicationEntity.setUsersByUserId(userEntity);
        applicationEntity.setApplicantsByApplicantId(applicantEntity);
        applicationEntity.setSchoolsBySchoolId(schoolEntity);
        return applicationEntity;
    }
}
