import React from 'react';
import { Router, Route, Link } from 'react-router-dom';
import { history } from '../_helpers';
import { authenticationService } from '../_services';
import { PrivateRoute } from '../_components';
import { HomePage } from '../HomePage';
import { LoginPage } from '../LoginPage';
import { Application } from '../Application';
import logo from '../images/logo.png';
import './App.css';

class App extends React.Component {
    constructor(props) {
        super(props);

        this.state = {
            currentUser: null
        };
    }

    componentDidMount() {
        authenticationService.currentUser.subscribe(x => this.setState({ currentUser: x }));
    }

    logout() {
        authenticationService.logout();
        history.push('/login');
    }

    render() {
        const { currentUser } = this.state;
        return (
            <Router history={history}>
                <div>
                    {currentUser &&

                        // <nav className="navbar navbar-expand-sm bg-dark navbar-dark justify-content-end">
                        //     <div className="navbar-nav">
                        //         <Link to="/" className="nav-item nav-link">Αιτήσεις</Link>
                        //         <a onClick={this.logout} className="nav-item nav-link">Αποσύνδεση</a>
                        //         <li><img src={logo} /></li>
                                
                                
                        //     </div>
                        //     <Link to="/application" className="btn btn-success ml-auto mr-1">Δημιουργία Αίτησης</Link>
                        // </nav>
                        <nav class="navbar navbar-expand-md navbar-dark bg-dark">
                            <div class="navbar-collapse collapse w-100 order-1 order-md-0 dual-collapse2">
                                <ul class="navbar-nav mr-auto">
                                    <li class="nav-item">
                                    <Link to="/" className="nav-item nav-link">Αιτήσεις</Link>
                                    </li>
                                    <li class="nav-item">
                                        <a onClick={this.logout} className="nav-item nav-link">Αποσύνδεση</a>
                                    </li>
                                </ul>
                            </div>
                            <div class="mx-auto order-0">
                                <img src={logo} />
                                <button class="navbar-toggler" type="button" data-toggle="collapse" data-target=".dual-collapse2">
                                    <span class="navbar-toggler-icon"></span>
                                </button>
                            </div>
                            <div class="navbar-collapse collapse w-100 order-3 dual-collapse2">
                                <ul class="navbar-nav ml-auto">
                                    <li class="nav-item">
                                        <Link to="/application" className="btn btn-success ml-auto mr-1">Δημιουργία Αίτησης</Link>
                                    </li>
                                    
                                </ul>
                            </div>
                        </nav>

                    }
                    <div className="jumbotron">
                        <div className="container">
                            <div className="row">
                                <div className="col-md-6 offset-md-3">
                                    <PrivateRoute exact path="/" component={HomePage} />
                                    <Route path="/login" component={LoginPage} />
                                    <PrivateRoute exact path="/application" component={Application} />
                                </div>
                                
                            </div>
                        </div>
                        
                    </div>
                    
                </div>
            </Router>
            
        );
    }
}

export { App }; 