import React, { Component } from 'react';
import { Map, GoogleApiWrapper, Marker } from 'google-maps-react';
import { googleapi } from '../_keys/googleapi';

export class MapComponent extends Component {
    constructor(props) {
        super(props);
      
        this.state = {
            information: null,
            street: null,
            district : null
        };
      }


    componentDidMount(){

        this.setState({street:this.props.street, district: this.props.district });
        googleapi.getCoordinates(this.props.street,this.props.district,this.props.town).then(
            response => this.setState(({information: response.results[0]}))            
        );
            
        
    }

    componentDidUpdate(){
        if(this.props.street !== this.state.street ){
            this.setState({street:this.props.street, district: this.props.district });
            googleapi.getCoordinates(this.props.street,this.props.district,this.props.town).then(
                response => this.setState(({information: response.results[0]}))            
            );
            
        }
    }
    render() {
        return (
            <div>
                {(this.state.information !== null)?(
                    
                    <div>
                        <Map
                            google={this.props.google}
                            zoom={16}
                            style={mapStyles}
                            initialCenter={{ lat: this.state.information.geometry.location.lat, lng: this.state.information.geometry.location.lng}}
                            center={{ lat: this.state.information.geometry.location.lat, lng: this.state.information.geometry.location.lng}}
                            >
                            <Marker position={{ lat: this.state.information.geometry.location.lat, lng: this.state.information.geometry.location.lng}} />
                        </Map>

                    </div>
                ): ''} 
            </div>
        );

    }
}
export default GoogleApiWrapper({
    apiKey: googleapi.getApiKey()
  })(MapComponent);
const mapStyles = {
    width: '100%',
    height: '50%',
  }