import React from 'react';
import { Router, Route, Link } from 'react-router-dom';
import { history } from '../_helpers';
import { authenticationService } from '../_services';
import { PrivateRoute } from '../_components';
import { HomePage } from '../HomePage';
import { LoginPage } from '../LoginPage';
import { Application } from '../Application';

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

                        <nav className="navbar navbar-expand-sm bg-dark navbar-dark justify-content-end">
                            <div className="navbar-nav">
                                <Link to="/" className="nav-item nav-link">Αιτήσεις</Link>
                                <a onClick={this.logout} className="nav-item nav-link">Αποσύνδεση</a>
                            </div>
                            <Link to="/application" className="btn btn-success ml-auto mr-1">Δημιουργία Αίτησης</Link>
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