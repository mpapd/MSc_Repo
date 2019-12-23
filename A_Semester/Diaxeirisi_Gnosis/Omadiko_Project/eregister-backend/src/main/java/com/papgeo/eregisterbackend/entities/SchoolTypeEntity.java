package com.papgeo.eregisterbackend.entities;

import javax.persistence.*;

@Entity
@Table(name = "school_types")
public class SchoolTypeEntity {
    private int schoolTypeId;
    private String type;

    @Id
    @Column(name = "school_type_id")
    public int getSchoolTypeId() {
        return schoolTypeId;
    }

    public void setSchoolTypeId(int schoolTypeId) {
        this.schoolTypeId = schoolTypeId;
    }

    @Basic
    @Column(name = "type")
    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        SchoolTypeEntity that = (SchoolTypeEntity) o;

        if (schoolTypeId != that.schoolTypeId) return false;
        if (type != null ? !type.equals(that.type) : that.type != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = schoolTypeId;
        result = 31 * result + (type != null ? type.hashCode() : 0);
        return result;
    }
}
