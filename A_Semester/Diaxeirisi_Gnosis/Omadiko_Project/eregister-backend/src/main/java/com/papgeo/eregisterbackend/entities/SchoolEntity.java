package com.papgeo.eregisterbackend.entities;

import javax.persistence.*;

@Entity
@Table(name = "schools")
public class SchoolEntity {
    private int schoolId;
    private String name;
    private String town;
    private String townEng;
    private String district;
    private String districtEng;
    private String street;
    private String phone;
    private SchoolTypeEntity schoolTypesBySchoolTypeId;
    private CategoryEntity categoriesByCategoryId;

    @Id
    @Column(name = "school_id")
    public int getSchoolId() {
        return schoolId;
    }

    public void setSchoolId(int schoolId) {
        this.schoolId = schoolId;
    }

    @Basic
    @Column(name = "name")
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
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
    @Column(name = "phone")
    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        SchoolEntity that = (SchoolEntity) o;

        if (schoolId != that.schoolId) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        if (town != null ? !town.equals(that.town) : that.town != null) return false;
        if (townEng != null ? !townEng.equals(that.townEng) : that.townEng != null) return false;
        if (district != null ? !district.equals(that.district) : that.district != null) return false;
        if (districtEng != null ? !districtEng.equals(that.districtEng) : that.districtEng != null) return false;
        if (street != null ? !street.equals(that.street) : that.street != null) return false;
        if (phone != null ? !phone.equals(that.phone) : that.phone != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = schoolId;
        result = 31 * result + (name != null ? name.hashCode() : 0);
        result = 31 * result + (town != null ? town.hashCode() : 0);
        result = 31 * result + (townEng != null ? townEng.hashCode() : 0);
        result = 31 * result + (district != null ? district.hashCode() : 0);
        result = 31 * result + (districtEng != null ? districtEng.hashCode() : 0);
        result = 31 * result + (street != null ? street.hashCode() : 0);
        result = 31 * result + (phone != null ? phone.hashCode() : 0);
        return result;
    }

    @ManyToOne
    @JoinColumn(name = "school_type_id", referencedColumnName = "school_type_id", nullable = false)
    public SchoolTypeEntity getSchoolTypesBySchoolTypeId() {
        return schoolTypesBySchoolTypeId;
    }

    public void setSchoolTypesBySchoolTypeId(SchoolTypeEntity schoolTypesBySchoolTypeId) {
        this.schoolTypesBySchoolTypeId = schoolTypesBySchoolTypeId;
    }

    @ManyToOne
    @JoinColumn(name = "category_id", referencedColumnName = "category_id", nullable = false)
    public CategoryEntity getCategoriesByCategoryId() {
        return categoriesByCategoryId;
    }

    public void setCategoriesByCategoryId(CategoryEntity categoriesByCategoryId) {
        this.categoriesByCategoryId = categoriesByCategoryId;
    }
}
