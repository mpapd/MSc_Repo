package com.papgeo.eregisterbackend.entities;

import javax.persistence.*;
import java.sql.Timestamp;

@Entity
@Table(name = "applicants")
public class ApplicantEntity {


    private int applicantId;
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



    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "applicant_id")
    public int getApplicantId() {
        return applicantId;
    }

    public void setApplicantId(int applicantId) {
        this.applicantId = applicantId;
    }

    @Basic
    @Column(name = "firstname")
    public String getFirstname() {
        return firstname;
    }

    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }

    @Basic
    @Column(name = "lastname")
    public String getLastname() {
        return lastname;
    }

    public void setLastname(String lastname) {
        this.lastname = lastname;
    }

    @Basic
    @Column(name = "fathername")
    public String getFathername() {
        return fathername;
    }

    public void setFathername(String fathername) {
        this.fathername = fathername;
    }

    @Basic
    @Column(name = "mothername")
    public String getMothername() {
        return mothername;
    }

    public void setMothername(String mothername) {
        this.mothername = mothername;
    }

    @Basic
    @Column(name = "birthdate")
    public Timestamp getBirthdate() {
        return birthdate;
    }

    public void setBirthdate(Timestamp birthdate) {
        this.birthdate = birthdate;
    }

    @Basic
    @Column(name = "town")
    public String getTown() {
        return town;
    }

    public void setTown(String town) {
        this.town = town;
    }

    @Basic
    @Column(name = "town_eng")
    public String getTownEng() {
        return townEng;
    }

    public void setTownEng(String townEng) {
        this.townEng = townEng;
    }

    @Basic
    @Column(name = "district")
    public String getDistrict() {
        return district;
    }

    public void setDistrict(String district) {
        this.district = district;
    }

    @Basic
    @Column(name = "district_eng")
    public String getDistrictEng() {
        return districtEng;
    }

    public void setDistrictEng(String districtEng) {
        this.districtEng = districtEng;
    }

    @Basic
    @Column(name = "street")
    public String getStreet() {
        return street;
    }

    public void setStreet(String street) {
        this.street = street;
    }

    @Basic
    @Column(name = "foreign_language1")
    public String getForeignLanguage1() {
        return foreignLanguage1;
    }

    public void setForeignLanguage1(String foreignLanguage1) {
        this.foreignLanguage1 = foreignLanguage1;
    }

    @Basic
    @Column(name = "foreign_language2")
    public String getForeignLanguage2() {
        return foreignLanguage2;
    }

    public void setForeignLanguage2(String foreignLanguage2) {
        this.foreignLanguage2 = foreignLanguage2;
    }

    @Basic
    @Column(name = "optional_class1")
    public String getOptionalClass1() {
        return optionalClass1;
    }

    public void setOptionalClass1(String optionalClass1) {
        this.optionalClass1 = optionalClass1;
    }

    @Basic
    @Column(name = "optional_class2")
    public String getOptionalClass2() {
        return optionalClass2;
    }

    public void setOptionalClass2(String optionalClass2) {
        this.optionalClass2 = optionalClass2;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        ApplicantEntity that = (ApplicantEntity) o;

        if (applicantId != that.applicantId) return false;
        if (firstname != null ? !firstname.equals(that.firstname) : that.firstname != null) return false;
        if (lastname != null ? !lastname.equals(that.lastname) : that.lastname != null) return false;
        if (fathername != null ? !fathername.equals(that.fathername) : that.fathername != null) return false;
        if (mothername != null ? !mothername.equals(that.mothername) : that.mothername != null) return false;
        if (birthdate != null ? !birthdate.equals(that.birthdate) : that.birthdate != null) return false;
        if (town != null ? !town.equals(that.town) : that.town != null) return false;
        if (townEng != null ? !townEng.equals(that.townEng) : that.townEng != null) return false;
        if (district != null ? !district.equals(that.district) : that.district != null) return false;
        if (districtEng != null ? !districtEng.equals(that.districtEng) : that.districtEng != null) return false;
        if (street != null ? !street.equals(that.street) : that.street != null) return false;
        if (foreignLanguage1 != null ? !foreignLanguage1.equals(that.foreignLanguage1) : that.foreignLanguage1 != null)
            return false;
        if (foreignLanguage2 != null ? !foreignLanguage2.equals(that.foreignLanguage2) : that.foreignLanguage2 != null)
            return false;
        if (optionalClass1 != null ? !optionalClass1.equals(that.optionalClass1) : that.optionalClass1 != null)
            return false;
        if (optionalClass2 != null ? !optionalClass2.equals(that.optionalClass2) : that.optionalClass2 != null)
            return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = applicantId;
        result = 31 * result + (firstname != null ? firstname.hashCode() : 0);
        result = 31 * result + (lastname != null ? lastname.hashCode() : 0);
        result = 31 * result + (fathername != null ? fathername.hashCode() : 0);
        result = 31 * result + (mothername != null ? mothername.hashCode() : 0);
        result = 31 * result + (birthdate != null ? birthdate.hashCode() : 0);
        result = 31 * result + (town != null ? town.hashCode() : 0);
        result = 31 * result + (townEng != null ? townEng.hashCode() : 0);
        result = 31 * result + (district != null ? district.hashCode() : 0);
        result = 31 * result + (districtEng != null ? districtEng.hashCode() : 0);
        result = 31 * result + (street != null ? street.hashCode() : 0);
        result = 31 * result + (foreignLanguage1 != null ? foreignLanguage1.hashCode() : 0);
        result = 31 * result + (foreignLanguage2 != null ? foreignLanguage2.hashCode() : 0);
        result = 31 * result + (optionalClass1 != null ? optionalClass1.hashCode() : 0);
        result = 31 * result + (optionalClass2 != null ? optionalClass2.hashCode() : 0);
        return result;
    }
}
