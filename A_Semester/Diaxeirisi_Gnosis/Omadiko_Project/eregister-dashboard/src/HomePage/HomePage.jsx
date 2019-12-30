import React from 'react';
import 'bootstrap/dist/css/bootstrap.min.css';
import { userService, authenticationService } from '../_services';
import './HomePage.css';




class HomePage extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            currentUser: authenticationService.currentUserValue,
            applications: null
        };
    }

    componentDidMount() {
        userService.getAll().then(
            applications => this.setState(({applications: applications}))            
            );
        
    }
    
    
    

    render() {
        const { currentUser, applications } = this.state;
        

        return (
            <div>
                <h3>Οι αιτήσεις μου</h3>
                <br></br>
                
                <div>
                    {(this.state.applications !== null 
                    && this.state.applications.length>0)? (
                    <div>      
                
                        {this.state.applications.map((application,i) =>
                            
                        <div key={i}>    
                            <div className="card card-body bg-light" key={i}> 
                            
                                        
                                    <table className="table table-hover table-fixed">

                                    <thead>
                                    <tr>
                                        <th></th>
                                        <th>Πληροφορίες</th>
                                        
                                    </tr>
                                    </thead>

                                    <tbody>
                                    <tr>
                                        <th scope="row">Όνομα</th>
                                        <td>{application.applicantDetails.firstname}</td>
                                        
                                    </tr>
                                    <tr>
                                        <th scope="row">Επώνυμο</th>
                                        <td>{application.applicantDetails.lastname}</td>
                                        
                                    </tr>
                                    <tr>
                                        <th scope="row">ΗΜ. Γέννησης</th>
                                        <td>{application.applicantDetails.birthdate.split("T")[0]}</td>
                                    
                                    </tr>
                                    <tr>
                                        <th scope="row">Όνομα Πατέρα</th>
                                        <td>{application.applicantDetails.fathername}</td>
                                        
                                    </tr>
                                    <tr>
                                        <th scope="row">Όνομα Μητέρας</th>
                                        <td>{application.applicantDetails.mothername}</td>
                                    
                                    </tr>
                                    <tr>
                                        <th scope="row">Πόλη</th>
                                        <td>{application.applicantDetails.district}, {application.applicantDetails.town}</td>
                                    
                                    </tr>
                                    <tr>
                                        <th scope="row">Διεύθυνση</th>
                                        <td>{application.applicantDetails.street}</td>
                                    
                                    </tr>
                                    <tr>
                                        <th scope="row">Σχολείο Επιλογής</th>
                                        <td>{application.schoolDetails.name}</td>
                                    
                                    </tr>
                                    <tr>
                                        <th scope="row">Γλώσσες Επιλογής</th>
                                        <td>{application.applicantDetails.foreignLanguage1} <br></br> {application.applicantDetails.foreignLanguage2}</td>
                                    
                                    </tr>
                                    <tr>
                                        <th scope="row">Μαθήματα Επιλογής</th>
                                        <td>{application.applicantDetails.optionalClass1} <br></br> {application.applicantDetails.optionalClass2}</td>
                                    
                                    </tr>
                                    <tr>
                                        <th scope="row">Ημερομηνία Αίτησης</th>
                                        <td>{application.date.split("T")[0]}</td>
                                    
                                    </tr>
                                    </tbody>

                                    </table>
                                        
                            </div> 
                            <br></br> <br></br> 
                        </div>
                        )}
                     
                    </div>          
                    

                    ): ''} 
                    </div>

                 
                
                
            </div>
        );
    }
}

export { HomePage };
