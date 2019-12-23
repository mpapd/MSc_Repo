package com.papgeo.eregisterbackend.entities;

import com.fasterxml.jackson.annotation.JsonIgnore;
import com.fasterxml.jackson.annotation.JsonProperty;

import javax.persistence.*;
import java.sql.Timestamp;

@Entity
@Table(name = "applications")
public class ApplicationEntity {
    private int applicationId;
    private Timestamp date;
    private String comments;
    private UserEntity usersByUserId;
    private ApplicantEntity applicantsByApplicantId;
    private SchoolEntity schoolsBySchoolId;

    @Id
    @Column(name = "application_id")
    public int getApplicationId() {
        return applicationId;
    }

    public void setApplicationId(int applicationId) {
        this.applicationId = applicationId;
    }

    @Basic
    @Column(name = "date")
    public Timestamp getDate() {
        return date;
    }

    public void setDate(Timestamp date) {
        this.date = date;
    }

    @Basic
    @Column(name = "comments")
    public String getComments() {
        return comments;
    }

    public void setComments(String comments) {
        this.comments = comments;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        ApplicationEntity that = (ApplicationEntity) o;

        if (applicationId != that.applicationId) return false;
        if (date != null ? !date.equals(that.date) : that.date != null) return false;
        if (comments != null ? !comments.equals(that.comments) : that.comments != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = applicationId;
        result = 31 * result + (date != null ? date.hashCode() : 0);
        result = 31 * result + (comments != null ? comments.hashCode() : 0);
        return result;
    }

    @JsonIgnore
//    @JsonProperty("userDetails")
    @ManyToOne
    @JoinColumn(name = "user_id", referencedColumnName = "user_id", nullable = false)
    public UserEntity getUsersByUserId() {
        return usersByUserId;
    }

    public void setUsersByUserId(UserEntity usersByUserId) {
        this.usersByUserId = usersByUserId;
    }

    @JsonProperty("applicantDetails")
    @ManyToOne
    @JoinColumn(name = "applicant_id", referencedColumnName = "applicant_id", nullable = false)
    public ApplicantEntity getApplicantsByApplicantId() {
        return applicantsByApplicantId;
    }

    public void setApplicantsByApplicantId(ApplicantEntity applicantsByApplicantId) {
        this.applicantsByApplicantId = applicantsByApplicantId;
    }

    @JsonProperty("schoolDetails")
    @ManyToOne
    @JoinColumn(name = "school_id", referencedColumnName = "school_id", nullable = false)
    public SchoolEntity getSchoolsBySchoolId() {
        return schoolsBySchoolId;
    }

    public void setSchoolsBySchoolId(SchoolEntity schoolsBySchoolId) {
        this.schoolsBySchoolId = schoolsBySchoolId;
    }
}
